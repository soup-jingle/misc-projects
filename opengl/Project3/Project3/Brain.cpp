// Patrick Bunetic
// No changes made

////////////////////////////////////////////
// Brain.cpp - Brain Class Implementation //
////////////////////////////////////////////

#include "Brain.h"

// Default Constructor
Brain::Brain()
{
}

// Initializing Constructor
Brain::Brain(float bsRad, float bsSca[], float bsClr[],
			 float cylRad, float cylLen, float cylClr[],
			 float pit, float minPit, float maxPit, float pitInc)
{
	BigSphereRadius       = bsRad;
	BigSphereScale[0]     = bsSca[0];
	BigSphereScale[1]     = bsSca[1];
	BigSphereScale[2]     = bsSca[2];
	BigSphereColor[0]     = bsClr[0];
	BigSphereColor[1]     = bsClr[1];
	BigSphereColor[2]     = bsClr[2];
	CylinderRadius        = cylRad;
	CylinderLength        = cylLen;
	CylinderColor[0]      = cylClr[0];
	CylinderColor[1]      = cylClr[1];
	CylinderColor[2]      = cylClr[2];
	CurrentPitch          = pit;
	InitPitch             = pit;
	MinPitch              = minPit;
	MaxPitch              = maxPit;
	PitchIncrement        = pitInc;
	InitPitchIncrement    = pitInc;
	Visible               = true;
}

// Initialization, using parametreized values.
void Brain::initialize(const float bsRad, const float bsSca[], const float bsClr[],
					   const float cylRad, const float cylLen, const float cylClr[],
					   const float pit, const float minPit, const float maxPit, const float pitInc)
{
	BigSphereRadius       = bsRad;
	BigSphereScale[0]     = bsSca[0];
	BigSphereScale[1]     = bsSca[1];
	BigSphereScale[2]     = bsSca[2];
	BigSphereColor[0]     = bsClr[0];
	BigSphereColor[1]     = bsClr[1];
	BigSphereColor[2]     = bsClr[2];
	CylinderRadius        = cylRad;
	CylinderLength        = cylLen;
	CylinderColor[0]      = cylClr[0];
	CylinderColor[1]      = cylClr[1];
	CylinderColor[2]      = cylClr[2];
	CurrentPitch          = pit;
	InitPitch             = pit;
	MinPitch              = minPit;
	MaxPitch              = maxPit;
	PitchIncrement        = pitInc;
	InitPitchIncrement    = pitInc;
	Visible               = true;
}

// Update Brain's pitch, altering increment values if necessary.
// VelocityFactor specifies the rate at which it should change
// its pitch relative to its base pitch increment. VelocityFactor
// equal to 1.0 would be no change, < 1.0 would be slower, > 1.0
// would be faster
void Brain::update(GLfloat velocityFactor)
{
	VelocityFactor = velocityFactor;
    CurrentPitch += VelocityFactor * PitchIncrement;
    
	if (CurrentPitch < MinPitch)
	{
		CurrentPitch = MinPitch;
		PitchIncrement *= -1;
	}
	else if (CurrentPitch > MaxPitch)
	{
		CurrentPitch = MaxPitch;
		PitchIncrement *= -1;
	}
}

// Render the components of the Brain.
void Brain::draw(GLUquadricObj *qObj)
{
	if (Visible)
	{
		glPushMatrix();
			glColor3f(BigSphereColor[0], BigSphereColor[1], BigSphereColor[2]);
			glPushMatrix();
				glScalef(BigSphereScale[0], BigSphereScale[1], BigSphereScale[2]);
				gluSphere(qObj, BigSphereRadius, 16, 16);
			glPopMatrix();
			glColor3f(CylinderColor[0], CylinderColor[1], CylinderColor[2]);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			gluCylinder(qObj, CylinderRadius, CylinderRadius, CylinderLength, 12, 6);
		glPopMatrix();
	}
}