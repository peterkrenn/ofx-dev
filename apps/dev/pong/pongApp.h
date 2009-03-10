/*
 *  pongApp.h
 *  pong
 *
 *  Created by Peter Krenn on 3/10/09.
 *  Copyright (c) 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _pong_APP
#define _pong_APP

#include "ofMain.h"
#include "ofAddons.h"

class pongApp : public ofBaseApp {
public:
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

#endif /*_pong_APP*/
