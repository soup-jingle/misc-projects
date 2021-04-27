// PATRICK BUNETIC
// Things I added/changed indicated by "[PB]" comment
////////////////////////////////////////////////////////
// JumpingBrain.cpp - JumpingBrain Class Implementation //
////////////////////////////////////////////////////////

#include <string>
#include "JumpingBrain.h"

// Default Constructor
JumpingBrain::JumpingBrain()
{
	reset();
}

// Initialize the Jumper's data members to the parameterized values.
void JumpingBrain::init()
{
	reset();
}

// Reset JumpingBrain to default values
void JumpingBrain::reset()
{
	// Initialize Torso and Head "joint"
	TorsoAndHead.initialize(TORSO_AND_HEAD_SPHERE_RADIUS, TORSO_AND_HEAD_SPHERE_CENTER, TORSO_AND_HEAD_SPHERE_COLOR,
		TORSO_AND_HEAD_CYLINDER_RADIUS, TORSO_AND_HEAD_CYLINDER_LENGTH, TORSO_AND_HEAD_CYLINDER_COLOR,
		TORSO_AND_HEAD_MIN_PITCH, TORSO_AND_HEAD_MIN_PITCH, TORSO_AND_HEAD_MAX_PITCH, TORSO_AND_HEAD_PITCH_INCREMENT,
		TORSO_AND_HEAD_SPHERE_SCALE_X, TORSO_AND_HEAD_SPHERE_SCALE_Y, TORSO_AND_HEAD_SPHERE_SCALE_Z);

	// Initialize Shoulders
	Shoulders.initialize(SHOULDERS_SPHERE_RADIUS, SHOULDERS_SPHERE_CENTER, SHOULDERS_SPHERE_COLOR,
		SHOULDERS_CYLINDER_RADIUS, SHOULDERS_CYLINDER_LENGTH, SHOULDERS_CYLINDER_COLOR,
		SHOULDERS_ROLL, SHOULDERS_MIN_ROLL, SHOULDERS_MAX_ROLL, -SHOULDERS_ROLL_INCREMENT,
		SHOULDERS_YAW, SHOULDERS_MIN_YAW, SHOULDERS_MAX_YAW, SHOULDERS_YAW_INCREMENT,
		SHOULDERS_SPHERE_SCALE_X, SHOULDERS_SPHERE_SCALE_Y, SHOULDERS_SPHERE_SCALE_Z);

	// Initialize Humeruses
	LeftArm[0].initialize(HUMERUS_SPHERE_RADIUS, HUMERUS_SPHERE_CENTER, HUMERUS_SPHERE_COLOR,
		HUMERUS_CYLINDER_RADIUS, HUMERUS_CYLINDER_LENGTH, HUMERUS_CYLINDER_COLOR,
		HUMERUS_MAX_PITCH, HUMERUS_MIN_PITCH, HUMERUS_MAX_PITCH, HUMERUS_PITCH_INCREMENT,
		HUMERUS_SPHERE_SCALE_X, HUMERUS_SPHERE_SCALE_Y, HUMERUS_SPHERE_SCALE_Z);
	RightArm[0].initialize(HUMERUS_SPHERE_RADIUS, HUMERUS_SPHERE_CENTER, HUMERUS_SPHERE_COLOR,
		HUMERUS_CYLINDER_RADIUS, HUMERUS_CYLINDER_LENGTH, HUMERUS_CYLINDER_COLOR,
		HUMERUS_MAX_PITCH, HUMERUS_MIN_PITCH, HUMERUS_MAX_PITCH, HUMERUS_PITCH_INCREMENT,
		HUMERUS_SPHERE_SCALE_X, HUMERUS_SPHERE_SCALE_Y, HUMERUS_SPHERE_SCALE_Z);

	// Initialize Forearms
	LeftArm[1].initialize(FOREARM_SPHERE_RADIUS, FOREARM_SPHERE_CENTER, FOREARM_SPHERE_COLOR,
		FOREARM_CYLINDER_RADIUS, FOREARM_CYLINDER_LENGTH, FOREARM_CYLINDER_COLOR,
		FOREARM_MAX_PITCH, FOREARM_MIN_PITCH, FOREARM_MAX_PITCH, FOREARM_PITCH_INCREMENT,
		FOREARM_SPHERE_SCALE_X, FOREARM_SPHERE_SCALE_Y, FOREARM_SPHERE_SCALE_Z);
	RightArm[1].initialize(FOREARM_SPHERE_RADIUS, FOREARM_SPHERE_CENTER, FOREARM_SPHERE_COLOR,
		FOREARM_CYLINDER_RADIUS, FOREARM_CYLINDER_LENGTH, FOREARM_CYLINDER_COLOR,
		FOREARM_MAX_PITCH, FOREARM_MIN_PITCH, FOREARM_MAX_PITCH, FOREARM_PITCH_INCREMENT,
		FOREARM_SPHERE_SCALE_X, FOREARM_SPHERE_SCALE_Y, FOREARM_SPHERE_SCALE_Z);
	
	// Iniitialize Hands
	LeftArm[2].initialize(HAND_SPHERE_RADIUS, HAND_SPHERE_CENTER, HAND_SPHERE_COLOR,
		HAND_CYLINDER_RADIUS, HAND_CYLINDER_LENGTH, HAND_CYLINDER_COLOR,
		HAND_MAX_PITCH, HAND_MIN_PITCH, HAND_MAX_PITCH, HAND_PITCH_INCREMENT,
		HAND_SPHERE_SCALE_X, HAND_SPHERE_SCALE_Y, HAND_SPHERE_SCALE_Z);
	RightArm[2].initialize(HAND_SPHERE_RADIUS, HAND_SPHERE_CENTER, HAND_SPHERE_COLOR,
		HAND_CYLINDER_RADIUS, HAND_CYLINDER_LENGTH, HAND_CYLINDER_COLOR,
		HAND_MAX_PITCH, HAND_MIN_PITCH, HAND_MAX_PITCH, HAND_PITCH_INCREMENT,
		HAND_SPHERE_SCALE_X, HAND_SPHERE_SCALE_Y, HAND_SPHERE_SCALE_Z);

	// Initialize Hips
	Hips.initialize(HIPS_SPHERE_RADIUS, HIPS_SPHERE_CENTER, HIPS_SPHERE_COLOR,
		HIPS_CYLINDER_RADIUS, HIPS_CYLINDER_LENGTH, HIPS_CYLINDER_COLOR,
		HIPS_ROLL, HIPS_MIN_ROLL, HIPS_MAX_ROLL, -HIPS_ROLL_INCREMENT,
		HIPS_YAW, HIPS_MIN_YAW, HIPS_MAX_YAW, HIPS_YAW_INCREMENT,
		HIPS_SPHERE_SCALE_X, HIPS_SPHERE_SCALE_Y, HIPS_SPHERE_SCALE_Z);

	// Initialize Thighs
	LeftLeg[0].initialize(THIGH_SPHERE_RADIUS, THIGH_SPHERE_CENTER, THIGH_SPHERE_COLOR,
		THIGH_CYLINDER_RADIUS, THIGH_CYLINDER_LENGTH, THIGH_CYLINDER_COLOR,
		THIGH_MIN_PITCH, THIGH_MIN_PITCH, THIGH_MAX_PITCH, THIGH_PITCH_INCREMENT,
		THIGH_SPHERE_SCALE_X, THIGH_SPHERE_SCALE_Y, THIGH_SPHERE_SCALE_Z);
	RightLeg[0].initialize(THIGH_SPHERE_RADIUS, THIGH_SPHERE_CENTER, THIGH_SPHERE_COLOR,
		THIGH_CYLINDER_RADIUS, THIGH_CYLINDER_LENGTH, THIGH_CYLINDER_COLOR,
		THIGH_MIN_PITCH, THIGH_MIN_PITCH, THIGH_MAX_PITCH, THIGH_PITCH_INCREMENT,
		THIGH_SPHERE_SCALE_X, THIGH_SPHERE_SCALE_Y, THIGH_SPHERE_SCALE_Z);
	// Initialize Shins
	LeftLeg[1].initialize(SHIN_SPHERE_RADIUS, SHIN_SPHERE_CENTER, SHIN_SPHERE_COLOR,
		SHIN_CYLINDER_RADIUS, SHIN_CYLINDER_LENGTH, SHIN_CYLINDER_COLOR,
		SHIN_MAX_PITCH, SHIN_MIN_PITCH, SHIN_MAX_PITCH, SHIN_PITCH_INCREMENT,
		SHIN_SPHERE_SCALE_X, SHIN_SPHERE_SCALE_Y, SHIN_SPHERE_SCALE_Z);
	RightLeg[1].initialize(SHIN_SPHERE_RADIUS, SHIN_SPHERE_CENTER, SHIN_SPHERE_COLOR,
		SHIN_CYLINDER_RADIUS, SHIN_CYLINDER_LENGTH, SHIN_CYLINDER_COLOR,
		SHIN_MAX_PITCH, SHIN_MIN_PITCH, SHIN_MAX_PITCH, SHIN_PITCH_INCREMENT,
		SHIN_SPHERE_SCALE_X, SHIN_SPHERE_SCALE_Y, SHIN_SPHERE_SCALE_Z);
	// Initialize Heels
	LeftLeg[2].initialize(HEEL_SPHERE_RADIUS, HEEL_SPHERE_CENTER, HEEL_SPHERE_COLOR,
		HEEL_CYLINDER_RADIUS, HEEL_CYLINDER_LENGTH, HEEL_CYLINDER_COLOR,
		HEEL_MIN_PITCH, HEEL_MIN_PITCH, HEEL_MAX_PITCH, HEEL_PITCH_INCREMENT,
		HEEL_SPHERE_SCALE_X, HEEL_SPHERE_SCALE_Y, HEEL_SPHERE_SCALE_Z);
	RightLeg[2].initialize(HEEL_SPHERE_RADIUS, HEEL_SPHERE_CENTER, HEEL_SPHERE_COLOR,
		HEEL_CYLINDER_RADIUS, HEEL_CYLINDER_LENGTH, HEEL_CYLINDER_COLOR,
		HEEL_MIN_PITCH, HEEL_MIN_PITCH, HEEL_MAX_PITCH, HEEL_PITCH_INCREMENT,
		HEEL_SPHERE_SCALE_X, HEEL_SPHERE_SCALE_Y, HEEL_SPHERE_SCALE_Z);
	// Initialize Toes
	LeftLeg[3].initialize(TOE_SPHERE_RADIUS, TOE_SPHERE_CENTER, TOE_SPHERE_COLOR,
		TOE_CYLINDER_RADIUS, TOE_CYLINDER_LENGTH, TOE_CYLINDER_COLOR,
		TOE_MIN_PITCH, TOE_MIN_PITCH, TOE_MAX_PITCH, TOE_PITCH_INCREMENT,
		TOE_SPHERE_SCALE_X, TOE_SPHERE_SCALE_Y, TOE_SPHERE_SCALE_Z);
	RightLeg[3].initialize(TOE_SPHERE_RADIUS, TOE_SPHERE_CENTER, TOE_SPHERE_COLOR,
		TOE_CYLINDER_RADIUS, TOE_CYLINDER_LENGTH, TOE_CYLINDER_COLOR,
		TOE_MIN_PITCH, TOE_MIN_PITCH, TOE_MAX_PITCH, TOE_PITCH_INCREMENT,
		TOE_SPHERE_SCALE_X, TOE_SPHERE_SCALE_Y, TOE_SPHERE_SCALE_Z);
}

// Set all body parts of JumpingBrain to parameterized color.
void JumpingBrain::setColor(const float color[])
{
	float c[3];
	c[0] = color[0];
	c[1] = color[1];
	c[2] = color[2];
	RightLeg[0].setSphereColor(c);
	RightLeg[1].setSphereColor(c);
	RightLeg[2].setSphereColor(c);
	RightLeg[3].setSphereColor(c);
	LeftLeg[0].setSphereColor(c);
	LeftLeg[1].setSphereColor(c);
	LeftLeg[2].setSphereColor(c);
	LeftLeg[3].setSphereColor(c);
	TorsoAndHead.setSphereColor(c);
	TorsoAndHead.setCylinderColor(c);
	Hips.setSphereColor(c);
	Shoulders.setSphereColor(c);
	RightArm[0].setSphereColor(c);
	RightArm[1].setSphereColor(c);
	RightArm[2].setSphereColor(c);
	LeftArm[0].setSphereColor(c);
	LeftArm[1].setSphereColor(c);
	LeftArm[2].setSphereColor(c);
}

// Set up the quadric object to display the graphical components of the JumpingBrain.
// [PB]
// Removed the "wobble" from the RunningDude code (from shoulders and hips).
//     JumpingBrain does not have/need that motion
// Changes also made to way "arms", "legs" rendered. Changes are described below,
//     closer to the relevant code.
void JumpingBrain::draw()
{
	float offset[3];
	GLUquadricObj *qObj;
	qObj = gluNewQuadric();
	gluQuadricDrawStyle(qObj, GLU_FILL);

	glPushMatrix(); // Entire Jumping Brain
		glEnable(GL_COLOR_MATERIAL);

		Hips.getSphereCenter(offset);
		glTranslatef(offset[0], offset[1], offset[2]);

		glPushMatrix(); // Pelvis
			if(pelvisVis) Hips.draw(qObj);

			glPushMatrix();  // Torso & Head
				glTranslatef(0.0, TorsoAndHead.getCylinderLength(), 0.0);
				if(bodyVis) TorsoAndHead.draw(qObj);
			glPopMatrix();  // Torso & Head

			glPushMatrix();  // Arms & Shoulders
				Shoulders.getSphereCenter(offset);
				glTranslatef(offset[0], offset[1], offset[2]);

				glPushMatrix(); // Shoulders
					if(shoulderVis) Shoulders.draw(qObj);

					glRotatef(180.0, 0.0, 1.0, 0.0);
					glPushMatrix();  // Left Arm [PB]
									 // Humerus is translated along X axis to the end of shoulder cylinder
									 //     it rotates around its center on the x-axis
									 // The forearm is moved down by its own radius (so that its end touches the
									 //     the humerus rather than its center). It is then rotated by its
									 //     pitch around the x-axis. Then it is shifted down the length of the
									 //     humerus's cylinder so that is where the come together like a joint
									 // The hand is similar to the forearm, it needs a translation after rotation
									 //     so that it is moved down by the length of the forearm's cylinder.
						glTranslatef(Shoulders.getCylinderLength() / 2, 0.0, 0.0);
						glRotatef(LeftArm[0].getCurrentPitch(), 1.0, 0.0, 0.0);
						if(humerusVis) LeftArm[0].draw(qObj);
						glTranslatef(0.0, -LeftArm[0].getCylinderLength(), 0.0);
						glRotatef(LeftArm[1].getCurrentPitch(), 1.0, 0.0, 0.0);
						glTranslatef(0.0, -LeftArm[1].getSphereRadius(), 0.0);
						if(forearmVis) LeftArm[1].draw(qObj);
						glTranslatef(0.0, -LeftArm[1].getCylinderLength(), 0.0);
						glRotatef(LeftArm[2].getCurrentPitch(), 1.0, 0.0, 0.0);
						glTranslatef(0.0, -LeftArm[2].getSphereRadius(), 0.0);
						if(handVis) LeftArm[2].draw(qObj);
					glPopMatrix();  // Left Arm

					glPushMatrix();  // Right Arm [PB]
									 // Similar to 'Left Arm'
						glTranslatef(-Shoulders.getCylinderLength() / 2, 0.0, 0.0);
						glRotatef(RightArm[0].getCurrentPitch(), 1.0, 0.0, 0.0);	
						if(humerusVis) RightArm[0].draw(qObj);
						glTranslatef(0.0, -RightArm[0].getCylinderLength(), 0.0);
						glRotatef(RightArm[1].getCurrentPitch(), 1.0, 0.0, 0.0);
						glTranslatef(0.0, -RightArm[1].getSphereRadius(), 0.0);
						if(forearmVis) RightArm[1].draw(qObj);
						glTranslatef(0.0, -RightArm[1].getCylinderLength(), 0.0);
						glRotatef(RightArm[2].getCurrentPitch(), 1.0, 0.0, 0.0);
						glTranslatef(0.0, -RightArm[2].getSphereRadius(), 0.0);
						if(handVis) RightArm[2].draw(qObj);
					glPopMatrix();  // Right Arm

				glPopMatrix();  // Shoulder Rotation

			glPopMatrix();  // Arms & Shoulders

			glPushMatrix();  // Left Leg [PB]
							 // Similar to "Left Arm". Each more extreme joint needs to be translated down
							 //     by their own radius, rotated by their pitch around the x-axis, then
							 //     translated down again to sit at the end of the less exteme joint's cylinder.
				glRotatef(LeftLeg[0].getCurrentPitch(), 1.0, 0.0, 0.0);
				glTranslatef(Hips.getCylinderLength() / 2, 0.0, 0.0);
				if(thighVis) LeftLeg[0].draw(qObj);
				glTranslatef(0.0, -LeftLeg[0].getCylinderLength(), 0.0);
				glRotatef(LeftLeg[1].getCurrentPitch(), 1.0, 0.0, 0.0);
				glTranslatef(0.0, -LeftLeg[1].getSphereRadius(), 0.0);
				if(shinVis) LeftLeg[1].draw(qObj);
				glTranslatef(0.0, -LeftLeg[1].getCylinderLength(), 0.0);
				glRotatef(LeftLeg[2].getCurrentPitch(), 1.0, 0.0, 0.0);
				glTranslatef(0.0, LeftLeg[2].getSphereRadius(), 0.0);
				glRotatef(180.0, 1.0, 0.0, 0.0); // Spin foot around because for some reason it is backwards
				if(footVis) LeftLeg[2].draw(qObj);
				glTranslatef(0.0, -LeftLeg[2].getCylinderLength(), 0.0);
				glRotatef(LeftLeg[3].getCurrentPitch(), 1.0, 0.0, 0.0);
				glTranslatef(0.0, -LeftLeg[3].getSphereRadius(), 0.0);
				if(toeVis) LeftLeg[3].draw(qObj);
			glPopMatrix();  // Left Leg

			glPushMatrix();  // Right Leg [PB]
							 // Similar to "Left Leg"
				glRotatef(RightLeg[0].getCurrentPitch(), 1.0, 0.0, 0.0);
				glTranslatef(-Hips.getCylinderLength() / 2, 0.0, 0.0);
				if (thighVis) RightLeg[0].draw(qObj);
				glTranslatef(0.0, -RightLeg[0].getCylinderLength(), 0.0);
				glRotatef(RightLeg[1].getCurrentPitch(), 1.0, 0.0, 0.0);
				glTranslatef(0.0, -RightLeg[1].getSphereRadius(), 0.0);
				if (shinVis) RightLeg[1].draw(qObj);
				glTranslatef(0.0, -RightLeg[1].getCylinderLength(), 0.0);
				glRotatef(RightLeg[2].getCurrentPitch(), 1.0, 0.0, 0.0);
				glTranslatef(0.0, RightLeg[2].getSphereRadius(), 0.0);
				glRotatef(180.0, 1.0, 0.0, 0.0); // Spin foot around because for some reason it is backwards
				if (footVis) RightLeg[2].draw(qObj);
				glTranslatef(0.0, -RightLeg[2].getCylinderLength(), 0.0);
				glRotatef(RightLeg[3].getCurrentPitch(), 1.0, 0.0, 0.0);
				glTranslatef(0.0, -RightLeg[3].getSphereRadius(), 0.0);
				if (toeVis) RightLeg[3].draw(qObj);
			glPopMatrix();  // Right Leg

		glPopMatrix();  // Hip Rotation

	glPopMatrix();  // Entire Jumping Brain

	gluDeleteQuadric(qObj);
	glColor3f(1, 1, 1);
}

// Update the positions and orientations associated
// with the joints and cross-joints of the Jumper.
void JumpingBrain::update()
{
	// Update the positions and orientations associated
	// with the joints and cross-joints of the Jumper.
	Hips.update();
	Shoulders.update();
	TorsoAndHead.update();

	int i;
	for (i = 0; i < 3; i++)
	{
		LeftArm[i].update();
		RightArm[i].update();
	}
	for (i = 0; i < 4; i++)
	{
		LeftLeg[i].update();
		RightLeg[i].update();
	}
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

// toggle part visibility [PB]
// Pass the key which was pressed to the function, then this function
//     will change a corresponding boolean in the "JumpingBrain" class 
//     which is checked before drawing that different joint.
void JumpingBrain::toggleVisibility(char c) {
	switch (c)
	{
	case 'B': // Body
		bodyVis = !bodyVis; break;
	case 'S': // Shoulders
		shoulderVis = !shoulderVis; break;
	case 'H': // Humerus
		humerusVis = !humerusVis; break;
	case 'F': // Forearm
		forearmVis = !forearmVis; break;
	case 'h': // hand
		handVis = !handVis; break;
	case 'P': // Pelvis
		pelvisVis = !pelvisVis; break;
	case 'T': // Thigh
		thighVis = !thighVis; break;
	case 's': // shin
		shinVis = !shinVis; break;
	case 'f': // foot
		footVis = !footVis; break;
	case 't': // toe
		toeVis = !toeVis; break;
	}
}

// used for changing title of window [PB]
// Window title tells which keys to press to inc/dec speed
//     as well as which keys toggle visibility of different parts.
// Only visible parts are listed in window title
// The key which is pressed to toggle visibility is circled in parentheses.
//     e.g. 'S' toggles shoulder visibility, so "(S)houlder" is displayed.
std::string JumpingBrain::getTitle() {
	std::string t = "SPEED: Arms(A/a),Legs(L/l),All(+/-); VISIBILITY: ";
	if(bodyVis) t += "(B)ody, ";
	if(shoulderVis) t += "(S)houlders, ";
	if(humerusVis) t += "(H)umerus, " ;
	if(forearmVis) t += "(F)orearm, " ;
	if(handVis) t += "(h)and , " ;
	if(pelvisVis) t += "(P)elvis, " ;
	if(thighVis) t += "(T)high, " ;
	if(shinVis) t += "(s)hin, " ;
	if(footVis) t += "(f)oot, " ;
	if(toeVis) t += "(t)oe" ;
	return t;
}