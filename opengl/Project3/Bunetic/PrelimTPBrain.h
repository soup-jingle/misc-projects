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

class PrelimTPBrain
{
	public:
		PrelimTPBrain();
		void draw();
		void update();
		void init(const GLfloat pos[3], const GLfloat ori, const GLfloat clr[3]);
		void reset();

		float getVelocityFactor()             { return velocityFactor; }
		void setVelocityFactor(float vf)      { velocityFactor = vf; return; }
		float getOrientation()                { return orient; }
		void setOrientation(float ori)        { orient = ori; return; }
		void getScaleFactor(float sf[])       { for (int i = 0; i < 3; i++) sf[i] = scaleFactor[i]; return; }
		void setScaleFactor(float sf[])       { for (int i = 0; i < 3; i++) scaleFactor[i] = sf[i]; return; }
		void getPosition(float pos[])         { for (int i = 0; i < 3; i++) pos[i] = position[i]; return; }
		void setPosition(float pos[])         { for (int i = 0; i < 3; i++) position[i] = pos[i]; return; }
		void getColor(float clr[])            { for (int i = 0; i < 3; i++) clr[i] = color[i]; return; }
		void setColor(float clr[])            { for (int i = 0; i < 3; i++) color[i] = clr[i]; return; }

		void incrementOrientation()           { orient += ORIENTATION_INCREMENT; if (orient > 360.0f) orient -= 360.0f; return; }
		void decrementOrientation()           { orient -= ORIENTATION_INCREMENT; if (orient < 0.0f) orient += 360.0f; return; }
		void incrementAllSpeed()              { 
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
		void decrementAllSpeed()              { 
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


		GLuint     brainTexture;		// [PB] texture value
		int        moveFactor = 1;
		float      origOrient;			// variable used when turning around near border
};

void SetMaterialProperties();

#define PRELIM_TP_BRAIN_H
#endif
