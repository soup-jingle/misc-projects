// Patrick Bunetic
// Changes indicated with [PB]

//////////////////////////////////////////////////////////
// JumpingBrain.cpp - JumpingBrain Class Implementation //
//////////////////////////////////////////////////////////

#include "JumpingBrain.h"

// Default Constructor
JumpingBrain::JumpingBrain(
)
{
	// [PB]
	// Init with colors, maybe not necessary
	color[0] = COLOR_WHITE[0];
	color[1] = COLOR_WHITE[1];
	color[2] = COLOR_WHITE[2];

	reset();
}

// [PB]
// Ended up not going this route, but left this in here anyway
JumpingBrain::JumpingBrain(const float colors[3])
{
	// Init with colors
	color[0] = colors[0];
	color[1] = colors[1];
	color[2] = colors[2];

    reset();
}

// Initialize the JumpingBrain's data members to the parameterized values.
void JumpingBrain::init()
{
	reset();
}

// Reset JumpingBrain to default values
void JumpingBrain::reset()
{
	// [PB]
	// set offset back to 0, and height to 0 so it is back in its
	//    starting position and has not left the ground yet
	posOffset[0] = 0.0f;
	posOffset[1] = 0.0f;
	height = 0;

	// [PB]
	// all joints/crossjoints initialized with color of jumpingbrain
    // Initialize Body "joint"
	Body.initialize(BODY_SPHERE_RADIUS, color, BODY_SPHERE_SCALE,
		                    BODY_CYLINDER_RADIUS, BODY_CYLINDER_LENGTH, color,
                            BODY_MIN_PITCH, BODY_MIN_PITCH, BODY_MAX_PITCH, BODY_PITCH_INCREMENT);

    // Initialize Shoulders
    Shoulders.initialize(SHOULDERS_SPHERE_RADIUS, SHOULDERS_SPHERE_CENTER, color, SHOULDERS_SPHERE_SCALE,
		            SHOULDERS_CYLINDER_RADIUS, SHOULDERS_CYLINDER_LENGTH, color,
					SHOULDERS_ROLL, SHOULDERS_MIN_ROLL, SHOULDERS_MAX_ROLL, -SHOULDERS_ROLL_INCREMENT, 
					SHOULDERS_YAW, SHOULDERS_MIN_YAW, SHOULDERS_MAX_YAW, SHOULDERS_YAW_INCREMENT);

    // Initialize Humeruses
	LeftArm[0].initialize(HUMERUS_SPHERE_RADIUS, color, HUMERUS_SPHERE_SCALE,
		                  HUMERUS_CYLINDER_RADIUS, HUMERUS_CYLINDER_LENGTH, color,
						  HUMERUS_MAX_PITCH, HUMERUS_MIN_PITCH, HUMERUS_MAX_PITCH, -HUMERUS_PITCH_INCREMENT);
    RightArm[0].initialize(HUMERUS_SPHERE_RADIUS, color, HUMERUS_SPHERE_SCALE,
		                   HUMERUS_CYLINDER_RADIUS, HUMERUS_CYLINDER_LENGTH, HUMERUS_CYLINDER_COLOR,
						   HUMERUS_MAX_PITCH, HUMERUS_MIN_PITCH, HUMERUS_MAX_PITCH, -HUMERUS_PITCH_INCREMENT);

	// Initialize Forearms
	LeftArm[1].initialize(FOREARM_SPHERE_RADIUS, color, FOREARM_SPHERE_SCALE,
		                  FOREARM_CYLINDER_RADIUS, FOREARM_CYLINDER_LENGTH, color,
						  FOREARM_MAX_PITCH, FOREARM_MIN_PITCH, FOREARM_MAX_PITCH, FOREARM_PITCH_INCREMENT);
	RightArm[1].initialize(FOREARM_SPHERE_RADIUS, color, FOREARM_SPHERE_SCALE,
		                   FOREARM_CYLINDER_RADIUS, FOREARM_CYLINDER_LENGTH, color,
						   FOREARM_MAX_PITCH, FOREARM_MIN_PITCH, FOREARM_MAX_PITCH, FOREARM_PITCH_INCREMENT);

	LeftArm[2].initialize(HAND_SPHERE_RADIUS, color, HAND_SPHERE_SCALE,
		                  HAND_CYLINDER_RADIUS, HAND_CYLINDER_LENGTH, color,
						  HAND_MAX_PITCH, HAND_MIN_PITCH, HAND_MAX_PITCH, -HAND_PITCH_INCREMENT);
	RightArm[2].initialize(HAND_SPHERE_RADIUS, color, HAND_SPHERE_SCALE,
		                   HAND_CYLINDER_RADIUS, HAND_CYLINDER_LENGTH, color,
						   HAND_MAX_PITCH, HAND_MIN_PITCH, HAND_MAX_PITCH, -HAND_PITCH_INCREMENT);

	// Initialize Pelvis
	Pelvis.initialize(PELVIS_SPHERE_RADIUS, PELVIS_SPHERE_CENTER, color, PELVIS_SPHERE_SCALE,
		            PELVIS_CYLINDER_RADIUS, PELVIS_CYLINDER_LENGTH, color,
					PELVIS_ROLL, PELVIS_MIN_ROLL, PELVIS_MAX_ROLL, -PELVIS_ROLL_INCREMENT, 
					PELVIS_YAW, PELVIS_MIN_YAW, PELVIS_MAX_YAW, PELVIS_YAW_INCREMENT);

	// Initialize Thighs
	LeftLeg[0].initialize(THIGH_SPHERE_RADIUS, color, THIGH_SPHERE_SCALE,
		                  THIGH_CYLINDER_RADIUS, THIGH_CYLINDER_LENGTH, color,
						  THIGH_MIN_PITCH, THIGH_MIN_PITCH, THIGH_MAX_PITCH, THIGH_PITCH_INCREMENT);
	RightLeg[0].initialize(THIGH_SPHERE_RADIUS, color, THIGH_SPHERE_SCALE,
		                   THIGH_CYLINDER_RADIUS, THIGH_CYLINDER_LENGTH, color,
						   THIGH_MIN_PITCH, THIGH_MIN_PITCH, THIGH_MAX_PITCH, THIGH_PITCH_INCREMENT);
	// Initialize Shins
	LeftLeg[1].initialize(SHIN_SPHERE_RADIUS, color, SHIN_SPHERE_SCALE,
		                  SHIN_CYLINDER_RADIUS, SHIN_CYLINDER_LENGTH, color,
						  SHIN_MAX_PITCH, SHIN_MIN_PITCH, SHIN_MAX_PITCH, -SHIN_PITCH_INCREMENT);
	RightLeg[1].initialize(SHIN_SPHERE_RADIUS, color, SHIN_SPHERE_SCALE,
		                   SHIN_CYLINDER_RADIUS, SHIN_CYLINDER_LENGTH, color,
						   SHIN_MAX_PITCH, SHIN_MIN_PITCH, SHIN_MAX_PITCH, -SHIN_PITCH_INCREMENT);
	// Initialize Feet
	LeftLeg[2].initialize(FOOT_SPHERE_RADIUS, color, FOOT_SPHERE_SCALE,
		                  FOOT_CYLINDER_RADIUS, FOOT_CYLINDER_LENGTH, color,
						  FOOT_MIN_PITCH, FOOT_MIN_PITCH, FOOT_MAX_PITCH, FOOT_PITCH_INCREMENT);
	RightLeg[2].initialize(FOOT_SPHERE_RADIUS, color, FOOT_SPHERE_SCALE,
		                   FOOT_CYLINDER_RADIUS, FOOT_CYLINDER_LENGTH, color,
						   FOOT_MIN_PITCH, FOOT_MIN_PITCH, FOOT_MAX_PITCH, FOOT_PITCH_INCREMENT);
	// Initialize Toes
	LeftLeg[3].initialize(TOE_SPHERE_RADIUS, color, TOE_SPHERE_SCALE,
		                  TOE_CYLINDER_RADIUS, TOE_CYLINDER_LENGTH, color,
						  TOE_MIN_PITCH, TOE_MIN_PITCH, TOE_MAX_PITCH, TOE_PITCH_INCREMENT);
	RightLeg[3].initialize(TOE_SPHERE_RADIUS, color, TOE_SPHERE_SCALE,
		                   TOE_CYLINDER_RADIUS, TOE_CYLINDER_LENGTH, color,
						   TOE_MIN_PITCH, TOE_MIN_PITCH, TOE_MAX_PITCH, TOE_PITCH_INCREMENT);
}

// Set up the quadric object to display the graphical components of the JumpingBrain.
void JumpingBrain::draw()
{
	float offset[3];
	GLUquadricObj *qObj;
	qObj = gluNewQuadric();
	gluQuadricDrawStyle(qObj, GLU_FILL);

	glPushMatrix();  // Render Entire Jumping Brain
        glEnable(GL_COLOR_MATERIAL);
		// [PB]
		// Set position of this jumping brain
		glRotatef(getRotation(), 0.0f, 1.0f, 0.0f);
		glTranslatef(startPosition[0]+posOffset[0], height, startPosition[1]+posOffset[1]);
		glScalef(BRAIN_SCALE_FACTOR, BRAIN_SCALE_FACTOR, BRAIN_SCALE_FACTOR);

            glPushMatrix();
				glTranslatef(0.0f, Body.getCylinderLength(), 0.0f);
                //Body.draw(qObj); // [PB] no longer drawing the body
				drawBody(qObj); // [PB] instead, drawing several smaller spheres
	        glPopMatrix();

            glPushMatrix();  // Position Shoulders and Arms
                Shoulders.getSphereCenter(offset);
                glTranslatef(offset[0],offset[1], offset[2]);

                glPushMatrix();  // Render Shoulders and Arms
                    glRotatef(Shoulders.getCurrentYaw(), 0.0, 1.0, 0.0);
                    glRotatef(Shoulders.getCurrentRoll(), 0.0, 0.0, 1.0);
					Shoulders.draw(qObj);

                    glRotatef(180.0, 0.0, 1.0, 0.0);
   			        glPushMatrix();  // Render Left Arm
				        glTranslatef(Shoulders.getCylinderLength()/2, 0.0, 0.0 );
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
				        glTranslatef(-Shoulders.getCylinderLength()/2, 0.0, 0.0 );
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
                    glPopMatrix();  // Render Right Arm
                glPopMatrix();  // Render Shoulders and Arms
            glPopMatrix();   //Position Shoulders and Arms    

			glPushMatrix();  //Position Pelvis and Legs
				Pelvis.getSphereCenter(offset);
				glTranslatef(offset[0], offset[1], offset[2]);

				glPushMatrix();  //Render Pelvis and Legs
					glRotatef(Pelvis.getCurrentYaw(), 0.0, 1.0, 0.0);
					glRotatef(Pelvis.getCurrentRoll(), 0.0, 0.0, 1.0);
					Pelvis.draw(qObj);

					glPushMatrix();  // Render Left Leg
						glTranslatef(Pelvis.getCylinderLength()/2, 0.0, 0.0 );
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
						glTranslatef(-Pelvis.getCylinderLength()/2, 0.0, 0.0 );
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

	gluDeleteQuadric(qObj);

    glColor3f(1, 1, 1);
}

// Update the positions and orientations associated
// with the joints and cross-joints of the JumpingBrain.
void JumpingBrain::update()
{
	Pelvis.update();
    Shoulders.update();
    Body.update();

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

	// [PB]
	// Jump, reversing direction if reached lowest/highest point and it's not over the edge
	int x = startPosition[0] + posOffset[0];
	int z = startPosition[1] + posOffset[1];
	int paraPos = x*x + z*z;
	int r2 = diskRadius * diskRadius; // r^2 = x^2 + y^2 (detect when brain goes over the edge)
	if (   (height >= JUMP_HEIGHT && jumpInc > 0) || (height <= JUMP_MIN && jumpInc < 0 && paraPos < r2) ) jumpInc = -jumpInc;
	height += jumpInc;
	// Move offset while jumping
	posOffset[1] += JUMP_DISTANCE_INCREMENT;
}

// Set the material properties of the JumpingBrain
void SetMaterialProperties()
{
	float mat_ambient[]   = { AMBIENT_COEFF,  AMBIENT_COEFF,  AMBIENT_COEFF,  1.0 };
	float mat_diffuse[]   = { DIFFUSE_COEFF,  DIFFUSE_COEFF,  DIFFUSE_COEFF,  1.0 };
	float mat_specular[]  = { SPECULAR_COEFF, SPECULAR_COEFF, SPECULAR_COEFF, 1.0 };
	float mat_shininess[] = { SPECULAR_EXPON };

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// [PB]
// Draw the new, textured body
void JumpingBrain::drawBody(GLUquadricObj *qObj) {
	float radius = Body.getSphereRadius();

	// shrink texture radius by the radius of the spheres it will be made from
	// this prevents the texture spheres from covering up the limbs
	radius = radius - BUMP_RADIUS; 


	float scale[3];
	float color[3];
	Body.getSphereScale(scale);
	Body.getSphereColor(color);


	float convert = PI / 180; // cos() uses radians
	int degreeStep = 20;

	float r; // the new radius
	//float d;
	int n; // the number of texture spheres to place in a band
	int a; // the angle to rotate around a band, placing spheres

	glPushMatrix();
	glColor3f(color[0], color[1], color[2]);
	glScalef(scale[0] * scaleFactor, scale[1] * scaleFactor, scale[2] * scaleFactor);

	// This works by translating up by the radius of the body, rotating it about the x-axis (forwards and backwards)
	// 20degrees, the creating an appropriate amount of sphere, rotating them about the z-axis
	for (int deg = 0; deg < 90; deg += degreeStep)
	{
		r = abs(radius * cos(deg * convert)); // radius of current band is body-sphere radius * cosine of current angle
		n = ceil(2 * PI * r / BUMP_RADIUS);   // divide circumference of band radius by radius of texture spheres for number of spheres
		a = ceil(360.0 / n); // angle to rotate is 360 degrees / number of spheres to make


		for (int i = 0; i < n; ++i)
		{
			if (deg == 0)  // Do middle band
			{
				glPushMatrix();
				glRotatef(i*a, 0.0f, 0.0f, 1.0f);
				glRotatef(deg, 1.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, radius, 0.0f);
				gluSphere(qObj, BUMP_RADIUS, 8, 8); // lowered number of slices and stacks just in case, for performance
				glPopMatrix();
			}
			else // Do all other bands
			{
				// Go forwards
				glPushMatrix();
				glRotatef(i*a, 0.0f, 0.0f, 1.0f);
				glRotatef(deg, 1.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, radius, 0.0f);
				gluSphere(qObj, BUMP_RADIUS, 8, 8);
				glPopMatrix();

				// Go backwards
				glPushMatrix();
				glRotatef(i*a, 0.0f, 0.0f, 1.0f);
				glRotatef(-deg, 1.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, radius, 0.0f);
				gluSphere(qObj, BUMP_RADIUS, 8, 8);
				glPopMatrix();
			}
		}

	}
	glPopMatrix();
}