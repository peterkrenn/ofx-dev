/*
 *  pongApp.cpp
 *  pong
 *
 *  Created by Peter Krenn on 3/10/09.
 */

#include "pongApp.h"

void pongApp::setup()
{
  ofSetWindowShape(800, 400);
  ofSetFullscreen(false);
  ofSetFrameRate(60);
  ofBackground(0, 0, 0);
  ofSetCircleResolution(80);
  ofNoFill();
  ofEnableSmoothing();
}

void pongApp::update()
{
}

void pongApp::draw()
{
  ofSetLineWidth(2);
  ofCircle(400, 200, 25);
}

void pongApp::keyPressed(int key)
{
}

void pongApp::keyReleased(int key)
{
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
