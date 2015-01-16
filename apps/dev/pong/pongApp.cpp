/*
 *  pongApp.cpp
 *  pong
 *
 *  Created by Peter Krenn on 3/10/09.
 */

#include "pongApp.h"

void pongApp::setup()
{
  ofSetLogLevel(OF_LOG_NOTICE);

  screenWidth = 800;
  screenHeight = 400;

  ofSetWindowShape(screenWidth, screenHeight);
  ofSetFullscreen(false);
  ofSetFrameRate(60);
  ofBackground(0, 0, 0);
  ofSetCircleResolution(80);
  ofNoFill();
  ofEnableSmoothing();

  paddleRadius = 25;

  leftPaddle = ofPoint(200, 200);
  rightPaddle = ofPoint(600, 200);

  leftPaddleSpeed = 2;
  rightPaddleSpeed = 2;
  moveLeftPaddle = 0;
  moveRightPaddle = 0;

  ballRadius = 5;
  resetBall();

  videoGrabber.initGrabber(320, 240);
  threshold = 80;
  grabBackground = true;

  colorImage.allocate(320, 240);
  grayscaleImage.allocate(320, 240);
  backgroundImage.allocate(320, 240);

  serial.enumerateDevices();
  serial.setup(2, 9600);
  for (int i = 0; i < sizeof(serialHistory); i++)
  {
    serialHistory[i] = 0;
  }
}

void pongApp::update()
{
  videoGrabber.grabFrame();

  if (videoGrabber.isFrameNew())
  {
    colorImage.setFromPixels(videoGrabber.getPixels(), 320, 240);
    grayscaleImage = colorImage;

    if (grabBackground)
    {
      backgroundImage = grayscaleImage;
      grabBackground = false;
    }

    grayscaleImage.absDiff(backgroundImage, grayscaleImage);
    grayscaleImage.threshold(threshold);

    tracker.findFiducials(grayscaleImage);

    for (list<ofxFiducial>::iterator fiducial = tracker.fiducialsList.begin(); fiducial != tracker.fiducialsList.end(); fiducial++)
    {
      if (fiducial->getX() < 160)
      {
        rightPaddle.y = fiducial->getAngleDeg() / 360 * 400;
      }
      else
      {
        leftPaddle.y = fiducial->getAngleDeg() / 360 * 400;
      }

      ofLog(OF_LOG_NOTICE, "Fiducial %d: Rotation %.2f, X-Position %.2f", fiducial->getId(), fiducial->getAngleDeg(), fiducial->getX());
    }
  }

  // Poll serial
  serial.writeByte('a');

  // Check for message from serial
  if (serial.available())
  {
    memset(serialMessage, 0, sizeof(serialMessage));
    serial.readBytes(serialMessage, sizeof(serialMessage));
    serial.flush();

    // Check for start/end tokens and double messages
    int start = strchr((const char*)serialMessage, '^') - (const char *)serialMessage + 1;
    int dbl = strchr((const char*)serialMessage + 1, '^') - (const char *)serialMessage + 1;
    int end = strchr((const char*)serialMessage, '$') - (const char *)serialMessage + 1;
    if (start == 1 && end > 2 && dbl < 0)
    {
      // Cut start/end tokens off
      char *message = (char *)malloc((end - start) * sizeof(char));
      strncpy(message, (const char *)serialMessage + 1, end - start - 1);
      message[end - 2] = '\0';

      rightPaddle.y = filterSerial(atol((const char*)message)) / 1024.0 * 400;

      free(message);
    }
  }

  collidePaddlesWithBoundaries();
  collideBallWithBoundaries();
  collideBallWithPaddle(leftPaddle);
  collideBallWithPaddle(rightPaddle);
  moveBall();
}

void pongApp::draw()
{
  drawPaddle(leftPaddle);
  drawPaddle(rightPaddle);
  drawBall();
  // grayscaleImage.draw(0, 0);
}

void pongApp::keyPressed(int key)
{
  switch (key)
  {
    case 97:
      moveLeftPaddle = -1;
      break;

    case 122:
      moveLeftPaddle = 1;
      break;

    case 39:
      moveRightPaddle = -1;
      break;

    case 47:
      moveRightPaddle = 1;
      break;

    case ' ':
      grabBackground = true;
      break;

    case 13:
      resetBall();
      break;
  }
}

void pongApp::keyReleased(int key)
{
  switch (key)
  {
    case 97:
      moveLeftPaddle = 0;
      break;

    case 122:
      moveLeftPaddle = 0;
      break;

    case 39:
      moveRightPaddle = 0;
      break;

    case 47:
      moveRightPaddle = 0;
      break;
  }
}

void pongApp::drawPaddle(ofPoint &paddle)
{
  ofSetLineWidth(2);
  ofCircle(paddle.x, paddle.y, paddleRadius);
}

void pongApp::collidePaddlesWithBoundaries()
{
  leftPaddle.y += moveLeftPaddle * leftPaddleSpeed;
  leftPaddle.y = ofClamp(leftPaddle.y, paddleRadius, screenHeight - paddleRadius);
  rightPaddle.y += moveRightPaddle * rightPaddleSpeed;
  rightPaddle.y = ofClamp(rightPaddle.y, paddleRadius, screenHeight - paddleRadius);
}

void pongApp::resetBall()
{
  ball = ofPoint(400, 200);
  ballVelocity = ofPoint(1, 0);
}

void pongApp::moveBall()
{
  ball += ballVelocity;
}

void pongApp::drawBall()
{
  ofSetLineWidth(1);
  ofCircle(ball.x, ball.y, ballRadius);
}

void pongApp::collideBallWithBoundaries()
{
  if (ball.x <= ballRadius || ball.x >= screenWidth - ballRadius)
  {
    ballVelocity.x *= -1;
  }

  if (ball.y <= ballRadius || ball.y >= screenHeight - ballRadius)
  {
    ballVelocity.y *= -1;
  }
}

void pongApp::collideBallWithPaddle(ofPoint &paddle)
{
  // None of the built in vector functions seem to work
  // Check for collision
  ofPoint distance = ofPoint(ball.x - paddle.x, ball.y - paddle.y);
  double squaredLength = distance.x * distance.x + distance.y * distance.y;
  if (squaredLength > pow(ballRadius + paddleRadius, 2))
  {
    return;
  }

  // Calculate new velocity
  double length = sqrt(squaredLength);
  ofPoint normal = ofPoint(-1 * distance.y / length, distance.x / length);
  double ballVelocityNormal = ballVelocity.x * normal.x + ballVelocity.y * normal.y;
  ballVelocity.x = normal.x * ballVelocityNormal * 2 - ballVelocity.x;
  ballVelocity.y = normal.y * ballVelocityNormal * 2 - ballVelocity.y;

  // Move ball to collision point
  double distanceLength = sqrt(distance.x * distance.x + distance.y * distance.y);
  ofPoint normalizedDistance = ofPoint(distance.x / distanceLength, distance.y / distanceLength);
  ball = ofPoint(paddle.x + normalizedDistance.x * (ballRadius + paddleRadius),
    paddle.y + normalizedDistance.y * (ballRadius + paddleRadius));
}

int pongApp::filterSerial(int value)
{
  // Weighted mean of the last 10 values
  float weight = 1.0;
  float sum = value * weight;
  float weightSum = weight;
  for (int i = 0; i < sizeof(serialHistory) - 1; i++)
  {
    weight /= 2;
    sum += serialHistory[i] * weight;
    weightSum += weight;
    serialHistory[i + 1] = serialHistory[i];
  }
  serialHistory[0] = value;

  return sum / weightSum;
}

void pongApp::mouseMoved(int x, int y)
{
}

void pongApp::mouseDragged(int x, int y, int button)
{
}

void pongApp::mousePressed(int x, int y, int button)
{
}

void pongApp::mouseReleased()
{
}
