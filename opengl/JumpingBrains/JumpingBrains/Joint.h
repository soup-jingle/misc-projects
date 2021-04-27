// Patrick Bunetic
// NO CHANGES MADE

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
	Joint(float sphRad, float sphClr[],  float sphSca[],
		  float cylRad, float cylLen, float cylClr[],
		  float pit, float minPit, float maxPit, float pitInc);

	void initialize(const float sphRad, const float sphClr[], const float sphSca[],
		            const float cylRad, const float cylLen, const float cylClr[],
		            const float pit, const float minPit, const float maxPit, const float pitInc);

	void  setSphereRadius(float sphRad);
	float getSphereRadius();
	void  setSphereCenter(float sphCent[]);
	void  setSphereCenter(float sphCentX, float sphCentY, float sphCentZ);
	void  getSphereCenter(float sphCent[]);
	void  getSphereCenter(float &sphCentX, float &sphCentY, float &sphCentZ);
	void  setSphereColor(float sphClr[]);
	void  getSphereColor(float sphClr[]);
	void  setSphereScale(float sphSca[]) { for (int i = 0; i <= 2; i++) SphereScale[i] = sphSca[i]; return; }
	void  getSphereScale(float sphSca[]) { for (int i = 0; i <= 2; i++) sphSca[i] = SphereScale[i]; return; }
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
	void  reverseVisible() { Visible = !Visible; return; }
	void  setVisible(bool vis) { Visible = vis; return; }
	float getVisible() { return Visible; }
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

private:
	float SphereRadius;
	float SphereCenter[3];
	float SphereColor[3];
	float SphereScale[3];
	float CylinderRadius;
	float CylinderLength;
	float CylinderColor[3];
	float CurrentPitch;
	float InitPitch;
	float MinPitch;
	float MaxPitch;
	float PitchIncrement;
	float InitPitchIncrement;
	bool  Visible;                  // User may turn off component visibility
	float VelocityFactor = ROTATION_VELOCITY_FACTOR;           // [PB] changed, no user control
};

#define JOINT_H
#endif
