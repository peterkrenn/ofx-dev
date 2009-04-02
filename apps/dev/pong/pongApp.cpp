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
