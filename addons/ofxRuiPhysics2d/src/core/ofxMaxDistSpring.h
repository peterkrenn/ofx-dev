/*
 * Copyright (c) 2009, Rui Madeira
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * http://creativecommons.org/licenses/LGPL/2.1/
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

#include "ofxConstraint.h"

//a spring that only activates once the distance between the particles is greater than a determined value
class ofxMaxDistSpring:public ofxConstraint{
protected:

public:
	ofxMaxDistSpring(ofxParticle *_a, ofxParticle* _b, float _rest, float _strength = 1.0f):
	ofxConstraint(_a, _b, _rest, _strength, OFX_MAX_DIST_SPRING){
	};

	virtual void update(){
		if(!bOn) return;
		if(!a->isActive() and !b->isActive()) return;
		delta.x = b->x - a->x;
		delta.y = b->y - a->y;
		float dist = delta.x*delta.y;
		if(dist < rest*rest) return;
		dist = dist < 1 ? 1 : sqrt(dist);
		float moveAmount;
		if(a->isActive() && b->isActive()){
			moveAmount = strength*(dist - rest) / (dist*(a->getInvMass() + b->getInvMass()));
			a->x += delta.x * moveAmount * a->getInvMass();
			a->y += delta.y * moveAmount * a->getInvMass();
			b->x -= delta.x * moveAmount * b->getInvMass();
			b->y -= delta.y * moveAmount * b->getInvMass();
		} else {
			moveAmount = strength*(dist - rest) / dist*0.5f;
			if(a->isActive()){
				a->x += delta.x * moveAmount;
				a->y += delta.y * moveAmount;
			} else {
				b->x -= delta.x * moveAmount;
				b->y -= delta.y * moveAmount;
			}
		}
	}
};

