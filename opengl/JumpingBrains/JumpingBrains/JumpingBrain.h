// Patrick Bunetic
// Changes indicated with [PB]

/////////////////////////////////////////////////////////////////////////////////////////
// JumpingBrain.h - JumpingBrain Class Definition                                      //
//                                                                                     //
// The JumpingBrain class models a two-armed, two-legged "brain" which, when animated, //
// produces a hopping motion. Like the Running Man model, body parts can be made       //
// invisible, orientation can be altered, and velocity can be changed.                 //
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef JUMPING_BRAIN_H

#include <gl/freeglut.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include "JumpingBrainGlobals.h"
#include "Joint.h"
#include "CrossJoint.h"

class JumpingBrain 
{
	public:
		JumpingBrain();
		JumpingBrain(const float colors[3]); // [PB] Set color of brain on creation; maybe?
		void draw();
		void update();
		void init();
		void reset();
		void getCenter(float ctr[]) {
			float pelvisCtr[3], shouldersCtr[3];
			Pelvis.getSphereCenter(pelvisCtr);
			Shoulders.getSphereCenter(shouldersCtr);
			for (int i = 0; i < 3; i++)
				ctr[i] = (pelvisCtr[i] + shouldersCtr[i]) / 2.0f;
		}

		// [PB]
		// Set starting position
		// The y-axis value is not needed here since all frogs are on a flat disk.
		//    (If this were not the case, a third value would be added.)
		void setStartPositon(float x, float z) {
			startPosition[0] = x;
			startPosition[1] = z;
		}

		// [PB]
		// getters for positioning
		float getXstart()
		{
			return startPosition[0];
		}
		float getXoffset()
		{
			return posOffset[0];
		}
		float getZstart()
		{
			return startPosition[1];
		}
		float getZoffset()
		{
			return posOffset[1];
		}

		// [PB]
		// Set angle the jumping brain faces.
		// Brain will be rotated on y-axis this many degrees
		void setRotation(int degrees) {
			rotation = degrees;
		}

		// [PB]
		// getter for rotation
		float getRotation() {
			return rotation;
		}

		// [PB]
		// Set color of jumping brain.
		void setColor(const float colors[3])
		{
			color[0] = colors[0];
			color[1] = colors[1];
			color[2] = colors[2];
		}

		// [PB]
		// set diskRadius, radius on which this brain is jumping
		void setDiskRadius(int radius)
		{
			diskRadius = radius;
		}

		// [PB]
		// get height
		float getHeight()
		{
			return height;
		}

	private:
		CrossJoint Shoulders;
		CrossJoint Pelvis;
		Joint      Body;
		Joint      LeftArm[3];         // 0=Humerus, 1=Forearm, 2=Hand
		Joint      RightArm[3];
		Joint      LeftLeg[4];         // 0=Thigh, 1=Shin, 2=Foot, 3=Toe
		Joint      RightLeg[4];

		// [PB]
		float      color[3];
		float      scaleFactor = BRAIN_SCALE_FACTOR; // scale factor for jumping brain resize; necessary??
		int	       rotation = 0; // Rotation on y-axis
		int        diskRadius;
		float	   height = 0;   // height (pertains to jumping/falling, not stationary position so is
								 //    is separate from below array values
		float      jumpInc = JUMP_INCREMENT;
		float      startPosition[2] = { 0.0f, 0.0f }; // Start position (x-/z-offsets from origin)
		float      posOffset[2]		= { 0.0f, 0.0f }; // Current offset from startPosition)
		// (startPosition and posOffset are separate so that the brain may be reset to startPosition)
		// Brain's x-position will be, from the origin, startPosition[0]+posOffset[0].
		//    z-position will be similar.

		// [PB]
		// draw 'textured' body
		void       drawBody(GLUquadricObj *qObj);
};

void SetMaterialProperties();

#define JUMPING_BRAIN_H
#endif
