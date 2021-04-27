// PATRICK BUNETIC
// (Things I added are indicated with "[PB]" comment)
//////////////////////////////////////
// Joint.h - Joint Class Definition //
//////////////////////////////////////

#ifndef JOINT_H

#include <gl/freeglut.h>
#include <cmath>
#include "JumpingBrainGlobals.h"

class Joint {
public:
	Joint();
	Joint(float sphRad, float sphCent[],  float sphClr[],
		  float cylRad, float cylLen, float cylClr[],
		  float pit, float minPit, float maxPit, float pitInc,
		  float ssX, float ssY, float ssZ);	

	void initialize(const float sphRad, const float sphCent[], const float sphClr[],
		            const float cylRad, const float cylLen, const float cylClr[],
		            const float pit, const float minPit, const float maxPit, const float pitInc,
					const float ssX, const float ssY, const float ssZ);

	void  setSphereRadius(float sphRad);
	float getSphereRadius();
	void  setSphereCenter(float sphCent[]);
	void  setSphereCenter(float sphCentX, float sphCentY, float sphCentZ);
	void  getSphereCenter(float sphCent[]);
	void  getSphereCenter(float &sphCentX, float &sphCentY, float &sphCentZ);
	void  setSphereColor(float sphClr[]);
	void  getSphereColor(float sphClr[]);
	void  setCylinderRadius(float cylRad);
	float getCylinderRadius();
	void  setCylinderLength(float cylLen);
	float getCylinderLength();
	void  setCylinderColor(float cylClr[]);
	void  getCylinderColor(float cylClr[]);
	void  setCurrentPitch(float pit);
	float getCurrentPitch();
	void  setMinPitch(float minPit);
	float getMinPitch();
	void  setMaxPitch(float maxPit);
	float getMaxPitch();
	void  setPitchIncrement(float pitInc);
	float getPitchIncrement();
	float getInitPitchIncrement() { return InitPitchIncrement; }
	float getVelocityFactor() { return VelocityFactor; }
	void  resetVelocityFactor() {
		VelocityFactor = MIN_VEL_SCALE_FACTOR;
		CurrentPitch = InitPitch;
		PitchIncrement = InitPitchIncrement;
		return;
	}
	void  incrementVelocityFactor() {
		VelocityFactor += VEL_SCALE_FACTOR_INCREMENT;
		if (VelocityFactor > MAX_VEL_SCALE_FACTOR)
			VelocityFactor = MAX_VEL_SCALE_FACTOR;
		return;
	}
	void  decrementVelocityFactor() {
		VelocityFactor -= VEL_SCALE_FACTOR_INCREMENT;
		if (VelocityFactor < MIN_VEL_SCALE_FACTOR)
			VelocityFactor = MIN_VEL_SCALE_FACTOR;
		return;
	}

	void update();
	void draw(GLUquadricObj *qObj);

	// [PB]
	// Scale factors mutators/accessors
	void setSphereScaleX(float scale);
	float getSphereScaleX() { return SphereScaleX; }
	void setSphereScaleY(float scale);
	float getSphereScaleY() { return SphereScaleY; }
	void setSphereScaleZ(float scale);
	float getSphereScaleZ() { return SphereScaleZ; }

private:
	float SphereRadius;
	float SphereCenter[3];
	float SphereColor[3];
	float CylinderRadius;
	float CylinderLength;
	float CylinderColor[3];
	float CurrentPitch;
	float InitPitch;
	float MinPitch;
	float MaxPitch;
	float PitchIncrement;
	float InitPitchIncrement;
	
	// [PB]
	// Scale factors
	// The factors by which the radius of the sphere will be multiplied
	float SphereScaleX;
	float SphereScaleY;
	float SphereScaleZ;

	float VelocityFactor;           // User may control speed of rotations
};

#define JOINT_H
#endif
