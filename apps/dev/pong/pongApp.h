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
  ofVideoGrabber vidGrabber;
  
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased();
};

#endif
