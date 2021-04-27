// PATRICK BUNETIC
// (Things I added/changed from 'RunningDude' are indicated with "[PB]" comment)
//////////////////////////////////////////////////////////////
// JumpingBrain.h - JumpingBrain Class Definition             //
//////////////////////////////////////////////////////////////

#ifndef JUMPING_BRAIN_H

#include <gl/freeglut.h>
#include <cmath>
#include <iostream>
#include "JumpingBrainGlobals.h"
#include "Joint.h"
#include "CrossJoint.h"

class JumpingBrain 
{
	public:
		JumpingBrain();                        // default constructor
		void draw();                          // draw runner to screen
		void update();                        // update joint positions
		void init();
		void reset();                         // set runner's parameters to default values
		void setColor(const float color[]);
		void incrementAllSpeed() {
			int i, j;
			for (j = 0; j < 4; j++)
			{
				LeftLeg[j].incrementVelocityFactor();
				RightLeg[j].incrementVelocityFactor();
			}
			Hips.incrementVelocityFactor();
			for (i = 0; i < 3; i++)
			{
				LeftArm[i].incrementVelocityFactor();
				RightArm[i].incrementVelocityFactor();
			}
			TorsoAndHead.incrementVelocityFactor();
			Shoulders.incrementVelocityFactor();
			return;
		}
		void decrementAllSpeed() {
			int i, j;
			for (j = 0; j < 4; j++)
			{
				LeftLeg[j].decrementVelocityFactor();
				RightLeg[j].decrementVelocityFactor();
			}
			Hips.decrementVelocityFactor();
			for (i = 0; i < 3; i++)
			{
				LeftArm[i].decrementVelocityFactor();
				RightArm[i].decrementVelocityFactor();
			}
			TorsoAndHead.decrementVelocityFactor();
			Shoulders.decrementVelocityFactor();
			return;
		}

		// dec/inc "arm" speed [PB]
		// Same as original 'inc-/decrementAllSpeed()' but only applies to arms
		void incrementArmSpeed() {
			for (int i = 0; i < 3; i++)
			{
				LeftArm[i].incrementVelocityFactor();
				RightArm[i].incrementVelocityFactor();
			}
			TorsoAndHead.incrementVelocityFactor();
			Shoulders.incrementVelocityFactor();
			return;
		}
		void decrementArmSpeed() {
			for (int i = 0; i < 3; i++)
			{
				LeftArm[i].decrementVelocityFactor();
				RightArm[i].decrementVelocityFactor();
			}
			TorsoAndHead.decrementVelocityFactor();
			Shoulders.decrementVelocityFactor();
			return;
		}

		// dec/inc "leg" speed [PB]
		// Same as original 'inc-/decrementAllSpeed()' but only applies to legs
		void incrementLegSpeed() {
			for (int j = 0; j < 4; j++)
			{
				LeftLeg[j].incrementVelocityFactor();
				RightLeg[j].incrementVelocityFactor();
			}
			Hips.incrementVelocityFactor();
			return;
		}
		void decrementLegSpeed() {
			for (int j = 0; j < 4; j++)
			{
				LeftLeg[j].decrementVelocityFactor();
				RightLeg[j].decrementVelocityFactor();
			}
			Hips.decrementVelocityFactor();
			return;
		}

		// toggle part visibility [PB]
		// Pass the key which was pressed to the function, then this function
		//     will change a corresponding boolean in the "JumpingBrain" class 
		//     which is checked before drawing that different joint.
		void JumpingBrain::toggleVisibility(char c);
		
		// used for changing title of window [PB]
		// Window title tells which keys to press to inc/dec speed
		//     as well as which keys toggle visibility of different parts.
		// Only visible parts are listed in window title
		std::string getTitle();

		CrossJoint Shoulders;
		CrossJoint Hips;
		Joint      TorsoAndHead;
		Joint      LeftArm[3];         // 0=Humerus, 1=Forearm, 2=Hand
		Joint      RightArm[3];
		Joint      LeftLeg[4];         // 0=Thigh, 1=Shin, 2=Heel, 3=Toe
		Joint      RightLeg[4];


	// Private member variables for the visibility of the different joints/crosspoints [PB]
	private:
		bool bodyVis = true;
		bool shoulderVis = true;
		bool humerusVis = true;
		bool forearmVis = true;
		bool handVis = true;
		bool pelvisVis = true;
		bool thighVis = true;
		bool shinVis = true;
		bool footVis = true;
		bool toeVis = true;
};

void SetMaterialProperties();

#define JUMPING_BRAIN_H
#endif
