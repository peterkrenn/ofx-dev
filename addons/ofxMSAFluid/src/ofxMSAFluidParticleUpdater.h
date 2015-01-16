/***********************************************************************

 This class interfaces the fluid solver with ofxMSAPhysics (applies fluid velocity as forces to particles)

 /***********************************************************************

 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/


#pragma once

#ifdef OF_ADDON_USING_OFXMSAPHYSICS

#include "ofxMSAParticleUpdater.h"
#include "ofxMSAFluid.h"



class ofxMSAFluidParticleUpdater : public ofxMSAParticleUpdater {
public:
	ofxMSAFluidParticleUpdater() {
		_fluidSolver = NULL;
	}

	void init(ofxMSAFluidSolver* f) {
		_fluidSolver = f;

	}

	void update(ofxMSAParticle* p) {
		ofPoint vel;
		_fluidSolver->getInfoAtPos(p->x * p->params->invWidth, p->y * p->params->invHeight, &vel, NULL);
		float invMass = p->getInvMass();
		p->addVelocity(vel.x * invMass, vel.y * invMass, 0);
	}


protected:
	ofxMSAFluidSolver *_fluidSolver;

};

#endif