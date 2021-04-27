// Patrick Bunetic
// Changes indicated with [PB]
// Altered update()
////////////////////////////////////////////////////////////
// PrelimTPBrain.cpp - PrelimTPBrain Class Implementation //
////////////////////////////////////////////////////////////

#include "PrelimTPBrain.h"
#include <iostream>

// Default Constructor
PrelimTPBrain::PrelimTPBrain()
{
	reset();
}

// Initialize the JumpingBrain's data members to the parameterized values.
void PrelimTPBrain::init(const GLfloat pos[3], const GLfloat pt1[4], const GLfloat pt2[4], const GLfloat ori, const GLfloat clr[3])
{
	orient = ori;
	origOrient = ori; // [PB] used for turning
	velocityFactor = (MIN_VEL_SCALE_FACTOR + MAX_VEL_SCALE_FACTOR) / 2.0f;
	for (int i = 0; i < 3; i++)
	{
		position[i] = pos[i];
		color[i] = clr[i];
		scaleFactor[i] = JUMPINGBRAIN_SCALE_FACTOR;
	}

	float oVec[3];
	for (int i = 0; i < 3; i++)
	{
		point1[i] = pt1[i]; // fourth values are useless, but left them in anyway
		point2[i] = pt2[i];
		
		oVec[i] = point2[i] - point1[i];
	}
	angleY = (180 / PI) * acos(oVec[1] / (sqrt(oVec[1] * oVec[1] + oVec[2] * oVec[2] + oVec[0] * oVec[0])));
	std::cout << angleY << std::endl;

	neurons.initialize(color);
	reset();
	neurons.reset();
}

// Reset JumpingBrain to default values
void PrelimTPBrain::reset()
{
	neurons.reset();

	// Initialize Torso and Head "brain"
	Body.initialize(BODY_SPHERE_RADIUS, BODY_SPHERE_SCALE, color,
		BODY_CYLINDER_RADIUS, BODY_CYLINDER_LENGTH, color,
		BODY_MIN_PITCH, BODY_MIN_PITCH, BODY_MAX_PITCH, BODY_PITCH_INCREMENT);

	// Initialize Shoulders
	Shoulders.initialize(SHOULDERS_SPHERE_RADIUS, SHOULDERS_SPHERE_CENTER, SHOULDERS_SPHERE_SCALE,
		SHOULDERS_CYLINDER_RADIUS, SHOULDERS_CYLINDER_LENGTH,
		SHOULDERS_ROLL, SHOULDERS_MIN_ROLL, SHOULDERS_MAX_ROLL, -SHOULDERS_ROLL_INCREMENT,
		SHOULDERS_YAW, SHOULDERS_MIN_YAW, SHOULDERS_MAX_YAW, SHOULDERS_YAW_INCREMENT);

	// Initialize Humeruses
	LeftArm[0].initialize(HUMERUS_SPHERE_RADIUS, HUMERUS_SPHERE_SCALE,
		HUMERUS_CYLINDER_RADIUS, HUMERUS_CYLINDER_LENGTH,
		HUMERUS_MAX_PITCH, HUMERUS_MIN_PITCH, HUMERUS_MAX_PITCH, -HUMERUS_PITCH_INCREMENT);
	RightArm[0].initialize(HUMERUS_SPHERE_RADIUS, HUMERUS_SPHERE_SCALE,
		HUMERUS_CYLINDER_RADIUS, HUMERUS_CYLINDER_LENGTH,
		HUMERUS_MAX_PITCH, HUMERUS_MIN_PITCH, HUMERUS_MAX_PITCH, -HUMERUS_PITCH_INCREMENT);

	// Initialize Forearms
	LeftArm[1].initialize(FOREARM_SPHERE_RADIUS, FOREARM_SPHERE_SCALE,
		FOREARM_CYLINDER_RADIUS, FOREARM_CYLINDER_LENGTH,
		FOREARM_MAX_PITCH, FOREARM_MIN_PITCH, FOREARM_MAX_PITCH, FOREARM_PITCH_INCREMENT);
	RightArm[1].initialize(FOREARM_SPHERE_RADIUS, FOREARM_SPHERE_SCALE,
		FOREARM_CYLINDER_RADIUS, FOREARM_CYLINDER_LENGTH,
		FOREARM_MAX_PITCH, FOREARM_MIN_PITCH, FOREARM_MAX_PITCH, FOREARM_PITCH_INCREMENT);

	LeftArm[2].initialize(HAND_SPHERE_RADIUS, HAND_SPHERE_SCALE,
		HAND_CYLINDER_RADIUS, HAND_CYLINDER_LENGTH,
		HAND_MAX_PITCH, HAND_MIN_PITCH, HAND_MAX_PITCH, -HAND_PITCH_INCREMENT);
	RightArm[2].initialize(HAND_SPHERE_RADIUS, HAND_SPHERE_SCALE,
		HAND_CYLINDER_RADIUS, HAND_CYLINDER_LENGTH,
		HAND_MAX_PITCH, HAND_MIN_PITCH, HAND_MAX_PITCH, -HAND_PITCH_INCREMENT);

	// Initialize Hips
	Pelvis.initialize(PELVIS_SPHERE_RADIUS, PELVIS_SPHERE_CENTER, PELVIS_SPHERE_SCALE,
		PELVIS_CYLINDER_RADIUS, PELVIS_CYLINDER_LENGTH,
		PELVIS_ROLL, PELVIS_MIN_ROLL, PELVIS_MAX_ROLL, -PELVIS_ROLL_INCREMENT,
		PELVIS_YAW, PELVIS_MIN_YAW, PELVIS_MAX_YAW, PELVIS_YAW_INCREMENT);

	// Initialize Thighs
	LeftLeg[0].initialize(THIGH_SPHERE_RADIUS, THIGH_SPHERE_SCALE,
		THIGH_CYLINDER_RADIUS, THIGH_CYLINDER_LENGTH,
		THIGH_MIN_PITCH, THIGH_MIN_PITCH, THIGH_MAX_PITCH, THIGH_PITCH_INCREMENT);
	RightLeg[0].initialize(THIGH_SPHERE_RADIUS, THIGH_SPHERE_SCALE,
		THIGH_CYLINDER_RADIUS, THIGH_CYLINDER_LENGTH,
		THIGH_MIN_PITCH, THIGH_MIN_PITCH, THIGH_MAX_PITCH, THIGH_PITCH_INCREMENT);
	// Initialize Shins
	LeftLeg[1].initialize(SHIN_SPHERE_RADIUS, SHIN_SPHERE_SCALE,
		SHIN_CYLINDER_RADIUS, SHIN_CYLINDER_LENGTH,
		SHIN_MAX_PITCH, SHIN_MIN_PITCH, SHIN_MAX_PITCH, -SHIN_PITCH_INCREMENT);
	RightLeg[1].initialize(SHIN_SPHERE_RADIUS, SHIN_SPHERE_SCALE,
		SHIN_CYLINDER_RADIUS, SHIN_CYLINDER_LENGTH,
		SHIN_MAX_PITCH, SHIN_MIN_PITCH, SHIN_MAX_PITCH, -SHIN_PITCH_INCREMENT);
	// Initialize Heels
	LeftLeg[2].initialize(HEEL_SPHERE_RADIUS, HEEL_SPHERE_SCALE,
		HEEL_CYLINDER_RADIUS, HEEL_CYLINDER_LENGTH,
		HEEL_MIN_PITCH, HEEL_MIN_PITCH, HEEL_MAX_PITCH, HEEL_PITCH_INCREMENT);
	RightLeg[2].initialize(HEEL_SPHERE_RADIUS, HEEL_SPHERE_SCALE,
		HEEL_CYLINDER_RADIUS, HEEL_CYLINDER_LENGTH,
		HEEL_MIN_PITCH, HEEL_MIN_PITCH, HEEL_MAX_PITCH, HEEL_PITCH_INCREMENT);
	// Initialize Toes
	LeftLeg[3].initialize(TOE_SPHERE_RADIUS, TOE_SPHERE_SCALE,
		TOE_CYLINDER_RADIUS, TOE_CYLINDER_LENGTH,
		TOE_MIN_PITCH, TOE_MIN_PITCH, TOE_MAX_PITCH, TOE_PITCH_INCREMENT);
	RightLeg[3].initialize(TOE_SPHERE_RADIUS, TOE_SPHERE_SCALE,
		TOE_CYLINDER_RADIUS, TOE_CYLINDER_LENGTH,
		TOE_MIN_PITCH, TOE_MIN_PITCH, TOE_MAX_PITCH, TOE_PITCH_INCREMENT);
}

// Set up the quadric object to display the graphical components of the JumpingBrain.
void PrelimTPBrain::draw()
{
	float offset[3];
	GLUquadricObj *qObj;
	qObj = gluNewQuadric();
	// gluQuadricDrawStyle(qObj, GLU_FILL); // [PB] moved down

	glPushMatrix();  // Render Entire Jumping Brain
	glEnable(GL_COLOR_MATERIAL); // [PB]
	glColor3f(color[0], color[1], color[2]);


	glTranslatef(position[0], position[1], position[2]); // move to slerp position

	//glPushMatrix(); // ** ADDED FOR DEBUG
	glRotatef(angleP, 1.0f, 0.0f, 0.0f); // rotate pitch (so is 'upright' on planet)
	//glRotatef(angleY, 0.0f, 1.0f, 0.0f); // rotate yaw (so is facing direction of travel)

	//glRotatef(orient, 0.0f, 1.0f, 0.0f);
	//glRotatef(JUMPINGBRAIN_PITCH, 1.0f, 0.0f, 0.0f);
	glScalef(scaleFactor[0], scaleFactor[1], scaleFactor[2]);

	gluQuadricDrawStyle(qObj, GLU_FILL);
	gluQuadricTexture(qObj, GL_TRUE);
	glPushMatrix();  // Render Body
	glTranslatef(0.0, Body.getCylinderLength(), 0.0);
	glEnable(GL_TEXTURE_2D); // [PB] allow texture, but only for the actual brain part
	glBindTexture(GL_TEXTURE_2D, brainTexture); // [PB] texture
	Body.draw(qObj);
	glDisable(GL_TEXTURE_2D); // [PB] disable texture so that (cross)joints unaffected
	neurons.draw(); // [PB] draw neurons
	glPopMatrix();  // Render Body

	glPushMatrix();  // Position Shoulders and Arms
	Shoulders.getSphereCenter(offset);
	glTranslatef(offset[0], offset[1], offset[2]);
	glPushMatrix();  // Render Shoulders and Arms
	glRotatef(Shoulders.getCurrentYaw(), 0.0, 1.0, 0.0);
	glRotatef(Shoulders.getCurrentRoll(), 0.0, 0.0, 1.0);
	Shoulders.draw(qObj);

	glRotatef(180.0, 0.0, 1.0, 0.0);
	glPushMatrix();  // Render Left Arm
	glTranslatef(Shoulders.getCylinderLength() / 2, 0.0, 0.0);
	glRotatef(LeftArm[0].getCurrentPitch(), 1.0, 0.0, 0.0);
	LeftArm[0].draw(qObj);
	glTranslatef(0.0, -LeftArm[0].getCylinderLength(), 0.0);
	glRotatef(LeftArm[1].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -LeftArm[1].getCylinderLength(), 0.0);
	LeftArm[1].draw(qObj);
	glTranslatef(0.0, -LeftArm[1].getCylinderLength(), 0.0);
	glRotatef(LeftArm[2].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -LeftArm[2].getCylinderLength(), 0.0);
	LeftArm[2].draw(qObj);
	glPopMatrix();  // Render Left Arm

	glPushMatrix();  // Render Right Arm
	glTranslatef(-Shoulders.getCylinderLength() / 2, 0.0, 0.0);
	glRotatef(RightArm[0].getCurrentPitch(), 1.0, 0.0, 0.0);
	RightArm[0].draw(qObj);
	glTranslatef(0.0, -RightArm[0].getCylinderLength(), 0.0);
	glRotatef(RightArm[1].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -RightArm[1].getCylinderLength(), 0.0);
	RightArm[1].draw(qObj);
	glTranslatef(0.0, -RightArm[1].getCylinderLength(), 0.0);
	glRotatef(RightArm[2].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -RightArm[2].getCylinderLength(), 0.0);
	RightArm[2].draw(qObj);
	glPopMatrix();	//Render Right Arm
	glPopMatrix();  // Render Shoulders and Arms
	glPopMatrix();  // Position Shoulders and Arms

	glPushMatrix();  // Position Pelvis and Arms
	Pelvis.getSphereCenter(offset);
	glTranslatef(offset[0], offset[1], offset[2]);

	glPushMatrix();  // Render Pelvis and Legs
	glRotatef(Pelvis.getCurrentYaw(), 0.0, 1.0, 0.0);
	glRotatef(Pelvis.getCurrentRoll(), 0.0, 0.0, 1.0);
	Pelvis.draw(qObj);

	glPushMatrix();  //Render Left Leg
	glTranslatef(Pelvis.getCylinderLength() / 2, 0.0, 0.0);
	glRotatef(LeftLeg[0].getCurrentPitch(), 1.0, 0.0, 0.0);
	LeftLeg[0].draw(qObj);
	glTranslatef(0.0, -LeftLeg[0].getCylinderLength(), 0.0);
	glRotatef(LeftLeg[1].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -LeftLeg[1].getCylinderLength(), 0.0);
	LeftLeg[1].draw(qObj);
	glTranslatef(0.0, -LeftLeg[1].getCylinderLength(), 0.0);
	glRotatef(LeftLeg[2].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -LeftLeg[2].getCylinderLength(), 0.0);
	LeftLeg[2].draw(qObj);
	glTranslatef(0.0, -LeftLeg[2].getCylinderLength(), 0.0);
	glRotatef(LeftLeg[3].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -LeftLeg[3].getCylinderLength(), 0.0);
	LeftLeg[3].draw(qObj);
	glPopMatrix();  // Render Left Leg

	glPushMatrix();  // Render Right Leg
	glTranslatef(-Pelvis.getCylinderLength() / 2, 0.0, 0.0);
	glRotatef(RightLeg[0].getCurrentPitch(), 1.0, 0.0, 0.0);
	RightLeg[0].draw(qObj);
	glTranslatef(0.0, -RightLeg[0].getCylinderLength(), 0.0);
	glRotatef(RightLeg[1].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -RightLeg[1].getCylinderLength(), 0.0);
	RightLeg[1].draw(qObj);
	glTranslatef(0.0, -RightLeg[1].getCylinderLength(), 0.0);
	glRotatef(RightLeg[2].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -RightLeg[2].getCylinderLength(), 0.0);
	RightLeg[2].draw(qObj);
	glTranslatef(0.0, -RightLeg[2].getCylinderLength(), 0.0);
	glRotatef(RightLeg[3].getCurrentPitch(), 1.0, 0.0, 0.0);
	glTranslatef(0.0, -RightLeg[3].getCylinderLength(), 0.0);
	RightLeg[3].draw(qObj);
	glPopMatrix();  // Render Right Leg
	glPopMatrix();  // Render Pelvis and Legs
	glPopMatrix();  // Position Pelvis and Legs
	glPopMatrix();  // Render Entire Jumping Brain
	//glPushMatrix(); // ** ADDED FOR DEBUG
	gluDeleteQuadric(qObj);

	glColor3f(1, 1, 1);
}

// Update the positions and orientations associated
// with the joints and cross-joints of the JumpingBrain.
// [PB] used a "moveFactor" to determine whether or not to continue moving
//     Keeps brain from moving while turning.
void PrelimTPBrain::update()
{

	if (rotInd == 0) {

		for (int i = 0; i < 3; ++i) {
			float temp = -point1[i];
			point1[i] = point2[i];
			point2[i] = temp;
		}

		float u = 0;
		for (int i = 0; i < 3; ++i) {
			u+= (point1[i]) * (point2[i]);

		}
		this->angle = acos(u);
		slerpMoveTicks = angle * (180 / PI) / rotIncr; // determine slerp ticks

	}

	angleP = 180 / PI * acos( position[1] / (sqrt(position[1]*position[1] + position[2]*position[2] + position[0] * position[0])) );
	//std::cout << angleP << std::endl;
	
	float t = rotInd * rotIncr;

	for (int i = 0; i < 3; ++i) {
		position[i] = (point1[i] * DISK_RADIUS * ((sin((1 - t) * angle)) / sin(angle)))
			+ (point2[i] * DISK_RADIUS * ((sin(t * angle)) / sin(angle)));
	}

	// If left thigh is swinging forward, raise altitude; if backwards, lower altitude
	if (LeftLeg[0].getPitchIncrement() > 0.0f)
		position[1] += 0.03f;
	else {
		position[1] -= 0.03f;
		neurons.reset();
	}

	// [PB] At end of hop, fire out neurons
	// neurons.reset();

	Pelvis.update((velocityFactor * moveFactor));
	Shoulders.update((velocityFactor * moveFactor));
	Body.update((velocityFactor * moveFactor));
	int i;
	for (i = 0; i < 3; i++)
	{
		LeftArm[i].update((velocityFactor * moveFactor));
		RightArm[i].update((velocityFactor * moveFactor));
	}
	for (i = 0; i < 4; i++)
	{
		LeftLeg[i].update((velocityFactor * moveFactor));
		RightLeg[i].update((velocityFactor * moveFactor));
	}

	neurons.update();
	rotInd = (rotInd + 1) % slerpMoveTicks;
}

// Set the material properties of the JumpingBrain
void SetMaterialProperties()
{
	float mat_ambient[] = { AMBIENT_COEFF,  AMBIENT_COEFF,  AMBIENT_COEFF,  1.0 };
	float mat_diffuse[] = { DIFFUSE_COEFF,  DIFFUSE_COEFF,  DIFFUSE_COEFF,  1.0 };
	float mat_specular[] = { SPECULAR_COEFF, SPECULAR_COEFF, SPECULAR_COEFF, 1.0 };
	float mat_shininess[] = { SPECULAR_EXPON };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}
