/*
 *  pongApp.cpp
 *  pong
 *
 *  Created by Peter Krenn on 3/10/09.
 */

#include "pongApp.h"

void pongApp::setup()
{
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
  ball = ofPoint(400, 200);
  ballVelocity = ofPoint(1, 1);
}

void pongApp::update()
{
  collidePaddlesWithBoundaries();
  collideBallWithBoundaries();
  moveBall();
}

void pongApp::draw()
{
  drawPaddle(leftPaddle);
  drawPaddle(rightPaddle);
  drawBall();
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
