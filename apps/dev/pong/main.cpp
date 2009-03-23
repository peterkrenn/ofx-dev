/*
 *  main.cpp
 *  pong
 *
 *  Created by Peter Krenn on 3/10/09.
 *  Copyright (c) 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "pongApp.h"

int main(int argc, char *argv[]) {
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetupOpenGL(800, 600, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	ofRunApp(new pongApp);
}
