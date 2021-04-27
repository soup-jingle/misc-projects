// Patrick Bunetic
// No changes made

////////////////////////////////////////////////
// CrossJoint.h - CrossJoint Class Definition //
////////////////////////////////////////////////

#ifndef CROSS_JOINT_H

#include <gl/freeglut.h>
#include <cmath>
#include "PrelimTPBrainGlobals.h"

class CrossJoint {
public:
	CrossJoint();
	CrossJoint(float sphRad, float sphCent[], float sphSca[], 
		       float cylRad, float cylLen, 
		       float rol, float minRol, float maxRol, float rolInc,
		       float ya, float minYa, float maxYa, float yaInc);

	void CrossJoint::initialize(const float sphRad, const float sphCent[], const float sphSca[], 
		                        const float cylRad, const float cylLen, 
		                        const float rol, const float minRol, const float maxRol, const float rolInc,
		                        const float ya, const float minYa, const float maxYa, const float yaInc);

	void  setSphereRadius(float sphRad);
	float getSphereRadius();
	void  setSphereCenter(float sphCent[]);
	void  setSphereCenter(float sphCentX, float sphCentY, float sphCentZ);
	void  getSphereCenter(float sphCent[]);
	void  getSphereCenter(float &sphCentX, float &sphCentY, float &sphCentZ);
	void  setSphereScale(float sphSca[]) { for (int i = 0; i <= 2; i++) SphereScale[i] = sphSca[i]; return; }
	void  getSphereScale(float sphSca[]) { for (int i = 0; i <= 2; i++) sphSca[i] = SphereScale[i]; return; }
	void  setCylinderRadius(float cylRad);
	float getCylinderRadius();
	void  setCylinderLength(float cylLen);
	float getCylinderLength();
	void  setCurrentRoll(float pit);
	float getCurrentRoll();
	void  setMinRoll(float minRol);
	float getMinRoll();
	void  setMaxRoll(float maxRol);
	float getMaxRoll();
	void  setRollIncrement(float rolInc);
	float getRollIncrement();
	float getInitRollIncrement() { return InitRollIncrement; }
	void  setCurrentYaw(float ya);
	float getCurrentYaw();
	void  setMinYaw(float minYa);
	float getMinYaw();
	void  setMaxYaw(float maxYa);
	float getMaxYaw();
	void  setYawIncrement(float yaInc);
	float getYawIncrement();
	float getInitYawIncrement() { return InitYawIncrement; }
	void reverseVisible() { Visible = !Visible; return; }
	void setVisible(bool vis) { Visible = vis; return; }
	float getVisible() { return Visible; }
	float getVelocityFactor() { return VelocityFactor; }
	void  resetVelocityFactor() {
		VelocityFactor = MIN_VEL_SCALE_FACTOR;
		CurrentRoll = InitRoll;
		RollIncrement = InitRollIncrement;
		CurrentYaw = InitYaw;
		YawIncrement = InitYawIncrement;
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

	void update(GLfloat velocityFactor);
	void draw(GLUquadricObj *qObj);

private:
	float SphereRadius;
	float SphereCenter[3];
	float SphereScale[3];
	float CylinderRadius;
	float CylinderLength;
	float CurrentRoll;
	float InitRoll;
	float MinRoll;
	float MaxRoll;
	float RollIncrement;
	float InitRollIncrement;
	float CurrentYaw;
	float InitYaw;
	float MinYaw;
	float MaxYaw;
	float YawIncrement;
	float InitYawIncrement;
	bool  Visible;                  // User may turn off component visibility
	float VelocityFactor;           // User may control speed of limb rotations
};

#define CROSS_JOINT_H
#endif
