// Patrick Bunetic
// No changes made

///////////////////////////////////////////////////////////////////////////////////////////////////
// Brain.h - Brain Class Definition                                                              //
//                                                                                               //
// The Brain consists of a large (invisible) sphere encrusted with many small (visible) spheres. //
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BRAIN_H

#include <gl/freeglut.h>
#include <cmath>
#include <ctime>
#include "PrelimTPBrainGlobals.h"

class Brain {
	public:
		Brain();
		Brain(float bsRad, float bsSca[], float bsClr[],
			  float cylRad, float cylLen, float cylClr[],
			  float pit, float minPit, float maxPit, float pitInc);

		void initialize(const float bsRad, const float bsSca[], const float bsClr[],
			            const float cylRad, const float cylLen, const float cylClr[],
						const float pit, const float minPit, const float maxPit, const float pitInc);
		
		void setBigSphereRadius(float bsRad)	{ if (bsRad >= 0.0) BigSphereRadius = bsRad; return; }
		float getBigSphereRadius()				{ return BigSphereRadius; }
		void setBigSphereScale(float bsSca[])	{ for (int i = 0; i <= 2; i++) BigSphereScale[i] = bsSca[i]; return; }
		void getBigSphereScale(float bsSca[])	{ for (int i = 0; i <= 2; i++) bsSca[i] = BigSphereScale[i]; return; }
		void setBigSphereColor(float bsClr[]) { for (int i = 0; i <= 2; i++) BigSphereColor[i] = bsClr[i]; return; }
		void getBigSphereColor(float bsClr[]) { for (int i = 0; i <= 2; i++) bsClr[i] = BigSphereColor[i]; return; }
		void setCylinderRadius(float cylRad)	{ if (cylRad >= 0.0) CylinderRadius = cylRad; return; }
		float getCylinderRadius()				{ return CylinderRadius; }
		void setCylinderLength(float cylLen)	{ if (cylLen >= 0.0) CylinderLength = cylLen; return; }
		float getCylinderLength()				{ return CylinderLength; }
		void setCylinderColor(float cylClr[]) { for (int i = 0; i <= 2; i++) CylinderColor[i] = cylClr[i]; return; }
		void getCylinderColor(float cylClr[]) { for (int i = 0; i <= 2; i++) cylClr[i] = CylinderColor[i]; return; }
		void setCurrentPitch(float pit)			{ CurrentPitch = pit; return; }
		float getCurrentPitch()					{ return CurrentPitch; }
		void setMinPitch(float minPit)			{ MinPitch = minPit; return; }
		float getMinPitch()						{ return MinPitch; }
		void setMaxPitch(float maxPit)			{ MaxPitch = maxPit; return; }
		float getMaxPitch()						{ return MaxPitch; }
		void setPitchIncrement(float pitInc)	{ PitchIncrement = pitInc; return; }
		float getPitchIncrement()				{ return PitchIncrement; }
		float getInitPitchIncrement()			{ return InitPitchIncrement; }
		void reverseVisible()					{ Visible = !Visible; return; }
		void setVisible(bool vis)				{ Visible = vis; return; }
		float getVisible()						{ return Visible; }
		float getVelocityFactor()               { return VelocityFactor; }
		void  resetVelocityFactor()             { 
													VelocityFactor = MIN_VEL_SCALE_FACTOR; 
													CurrentPitch = InitPitch;
													PitchIncrement = InitPitchIncrement;
													return; 
		                                        }
		void  incrementVelocityFactor()         { 
													VelocityFactor += VEL_SCALE_FACTOR_INCREMENT;  
													if (VelocityFactor > MAX_VEL_SCALE_FACTOR) 
														VelocityFactor = MAX_VEL_SCALE_FACTOR;
													return; 
		                                        }
		void  decrementVelocityFactor()         { 
													VelocityFactor -= VEL_SCALE_FACTOR_INCREMENT;  
													if (VelocityFactor < MIN_VEL_SCALE_FACTOR) 
														VelocityFactor = MIN_VEL_SCALE_FACTOR; 
													return; 
		                                        }

		void update(GLfloat velocityFactor);
		void draw(GLUquadricObj *qObj);

	private:
		float BigSphereRadius;
		float BigSphereScale[3];
		float BigSphereColor[3];
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
		float VelocityFactor;           // User may control speed of forward advance and limb rotations
};

#define BRAIN_H
#endif
