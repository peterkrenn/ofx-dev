/*
 *  pongApp.h
 *  pong
 *
 *  Created by Peter Krenn on 3/10/09.
 */

#ifndef _pong_APP
#define _pong_APP

#include "ofMain.h"

#define OF_ADDON_USING_OFXOPENCV
#define OF_ADDON_USING_OFXFIDUCIALFINDER
#include "ofAddons.h"

class pongApp : public ofBaseApp
{
public:
  int screenWidth, screenHeight;

  float paddleRadius;
  ofPoint leftPaddle;
  ofPoint rightPaddle;

  float ballRadius;
  ofPoint ball;
  ofPoint ballVelocity;

  float leftPaddleSpeed;
  float rightPaddleSpeed;
  int moveLeftPaddle;
  int moveRightPaddle;

  ofVideoGrabber videoGrabber;
  ofxCvColorImage colorImage;
  ofxCvGrayscaleImage grayscaleImage;
  ofxCvGrayscaleImage backgroundImage;
  bool grabBackground;
  int threshold;

  ofxFiducialTracker tracker;

  ofSerial serial;
  unsigned char serialMessage[6];
  float serialHistory[10];
  
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);

  void collidePaddlesWithBoundaries();
  void drawPaddle(ofPoint &paddle);

  void resetBall();
  void moveBall();
  void drawBall();
  void collideBallWithBoundaries();
  void collideBallWithPaddle(ofPoint &paddle);

  int filterSerial(int value);

  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased();
};

#endif
