// Patrick Bunetic
// Changes indicated with [PB]

/////////////////////////////////////////////////////////////////////////////////////////
// PrelimTP - PrelimTPlass Definition                                                  //
//                                                                                     //
// The PrelimTPlass models ...                                                         //
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef PRELIM_TP_BRAIN_H

#include <gl/freeglut.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include "PrelimTPBrainGlobals.h"
#include "Joint.h"
#include "CrossJoint.h"
#include "Brain.h"
#include "NeuronSystem.h"

class PrelimTPBrain
{
public:
	PrelimTPBrain();
	void draw();
	void update();
	void init(const GLfloat pos[3], const GLfloat pt1[4], const GLfloat pt2[4], const GLfloat ori, const GLfloat clr[3]);
	void reset();

	float getVelocityFactor() { return velocityFactor; }
	void setVelocityFactor(float vf) { velocityFactor = vf; return; }
	float getOrientation() { return orient; }
	void setOrientation(float ori) { orient = ori; return; }
	void getScaleFactor(float sf[]) { for (int i = 0; i < 3; i++) sf[i] = scaleFactor[i]; return; }
	void setScaleFactor(float sf[]) { for (int i = 0; i < 3; i++) scaleFactor[i] = sf[i]; return; }
	void getPosition(float pos[]) { for (int i = 0; i < 3; i++) pos[i] = position[i]; return; }
	void setPosition(float pos[]) { for (int i = 0; i < 3; i++) position[i] = pos[i]; return; }
	void getColor(float clr[]) { for (int i = 0; i < 3; i++) clr[i] = color[i]; return; }
	void setColor(float clr[]) { for (int i = 0; i < 3; i++) color[i] = clr[i]; return; }

	void incrementOrientation() { orient += ORIENTATION_INCREMENT; if (orient > 360.0f) orient -= 360.0f; return; }
	void decrementOrientation() { orient -= ORIENTATION_INCREMENT; if (orient < 0.0f) orient += 360.0f; return; }
	void incrementAllSpeed() {
		int i, j;
		velocityFactor += VEL_SCALE_FACTOR_INCREMENT;
		if (velocityFactor > MAX_VEL_SCALE_FACTOR)
			velocityFactor = MAX_VEL_SCALE_FACTOR;
		if (LeftLeg[0].getVelocityFactor() != LeftArm[0].getVelocityFactor())
		{
			for (j = 0; j < 4; j++)
			{
				LeftLeg[j].resetVelocityFactor();
				RightLeg[j].resetVelocityFactor();
			}
			Pelvis.resetVelocityFactor();
			for (i = 0; i < 3; i++)
			{
				LeftArm[i].resetVelocityFactor();
				RightArm[i].resetVelocityFactor();
			}
			Body.resetVelocityFactor();
			Shoulders.resetVelocityFactor();
		}
		for (j = 0; j < 4; j++)
		{
			LeftLeg[j].incrementVelocityFactor();
			RightLeg[j].incrementVelocityFactor();
		}
		Pelvis.incrementVelocityFactor();
		for (i = 0; i < 3; i++)
		{
			LeftArm[i].incrementVelocityFactor();
			RightArm[i].incrementVelocityFactor();
		}
		Body.incrementVelocityFactor();
		Shoulders.incrementVelocityFactor();
		return;
	}
	void decrementAllSpeed() {
		int i, j;
		velocityFactor -= VEL_SCALE_FACTOR_INCREMENT;
		if (velocityFactor < MIN_VEL_SCALE_FACTOR)
			velocityFactor = MIN_VEL_SCALE_FACTOR;
		if (LeftLeg[0].getVelocityFactor() != LeftArm[0].getVelocityFactor())
		{
			for (j = 0; j < 4; j++)
			{
				LeftLeg[j].resetVelocityFactor();
				RightLeg[j].resetVelocityFactor();
			}
			Pelvis.resetVelocityFactor();
			for (i = 0; i < 3; i++)
			{
				LeftArm[i].resetVelocityFactor();
				RightArm[i].resetVelocityFactor();
			}
			Body.resetVelocityFactor();
			Shoulders.resetVelocityFactor();
		}
		for (j = 0; j < 4; j++)
		{
			LeftLeg[j].decrementVelocityFactor();
			RightLeg[j].decrementVelocityFactor();
		}
		Pelvis.decrementVelocityFactor();
		for (i = 0; i < 3; i++)
		{
			LeftArm[i].decrementVelocityFactor();
			RightArm[i].decrementVelocityFactor();
		}
		Body.decrementVelocityFactor();
		Shoulders.decrementVelocityFactor();
		return;
	}

	void setImage(GLuint image) {
		brainTexture = image;
	}

	GLuint getImage() {
		return brainTexture;
	}

	/*
	// [PB] slerp function
	void slerp(GLfloat output[4], GLfloat in1[4], GLfloat in2[4], double t) {
	double dot = 0;
	double mag = 0;
	double angle;
	double u[4];
	for (int i = 0; i < 4; ++i) {
	dot += in1[i] * in2[i];
	}
	for (int i = 0; i < 4; ++i) {
	u[i] = in1[i] - dot * in2[i];
	}
	for (int i = 0; i < 4; ++i) {
	mag += u[i] * u[i];
	}
	mag = sqrt(mag);
	for (int i = 0; i < 4; ++i) {
	u[i] = u[i] / mag;
	}
	angle = acos(dot);

	for (int i = 0; i < 4; ++i) {
	output[i] = cos(t*angle) *in1[i] + sin(t*angle) * u[i];
	}
	}

	void quatToMat(GLfloat q[4]) {
	matrix[15] = 1;
	for (int i = 0; i < 3; ++i) {
	matrix[i * 4 + 3] = 0;
	matrix[12 + i] = 0;
	}
	matrix[0] = 1.0f - 2 * q[1] * q[1] + 2 * q[2] * q[2];
	matrix[1] = (2 * q[0] * q[1]) + (2 * q[2] * q[3]);
	matrix[2] = (2 * q[0] * q[2]) - (2 * q[1] * q[3]);

	matrix[4] = (2 * q[0] * q[1]) - (2 * q[2] * q[3]);
	matrix[5] = 1.0f - 2 * q[0] * q[0] + 2 * q[2] * q[2];
	matrix[6] = (2 * q[1] * q[2]) + (2 * q[0] * q[3]);

	matrix[8] = (2 * q[0] * q[2]) + (2 * q[1] * q[3]);
	matrix[9] = (2 * q[1] * q[2]) - (2 * q[0] * q[3]);
	matrix[10] = 1.0f - 2 * q[0] * q[0] + 2 * q[1] * q[1];
	}
	*/
private:
	CrossJoint Shoulders;
	CrossJoint Pelvis;
	Brain      Body;
	Joint      LeftArm[3];         // 0=Humerus, 1=Forearm, 2=Hand
	Joint      RightArm[3];
	Joint      LeftLeg[4];         // 0=Thigh, 1=Shin, 2=Heel, 3=Toe
	Joint      RightLeg[4];

	float      velocityFactor;
	float      orient;             // Direction in ground plane that character is facing
	float      scaleFactor[3];
	float      position[3];
	float      color[3];
	GLfloat    point1[4];
	GLfloat    point2[4]; // The other point that the brain passes through


	GLuint     brainTexture;		// [PB] texture value
	NeuronSystem neurons;			// [PB] particle system
	int        moveFactor = 1;
	float      origOrient;			// variable used when turning around near border
	GLfloat    matrix[16];
	int        rotInd = 0;
	float      rotIncr = ROTATION_INC;
	bool       second = false;
	//int        multiplier = 1;
	float	   angleP;
	float	   angleY = UNSET_YAW_ANGLE;
	int		   slerpMoveTicks = ROTATION_MAX_COUNT;
	float	   angle;
};

void SetMaterialProperties();

#define PRELIM_TP_BRAIN_H
#endif
