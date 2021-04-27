// Patrick Bunetic
// Changes denoted by "[PB]" comments
// Rain-related code left in, just commented out

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// PrelimTPBrainsDriver.cpp - Bill White - CS 482.001 - Fall 2017            //
//                                                                           //
// This program expands the previous Jumping Brain model by placing seven of //
// those characters on a texture-mapped disk, on which they hop. The disk    //
// uses a particle systems to generate a rain pattern across its surface.    //
// No detection of mutual collision between the characters occurs, and each  //
// character still plummets off the edge when it reaches the disk boundary.  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include <gl/freeglut.h>
#include <cmath>
#include <ctime>
#include "RGBpixmap.h" 
#include "PrelimTPBrain.h"
//#include "RainParticle.h" // [PB] no rain
#include "GrassParticle.h"
#include "PrelimTPBrainGlobals.h"

using namespace std;

/********************/
/* GLOBAL VARIABLES */
/********************/

// The initial window and viewport sizes (in pixels), set to ensure that
// the aspect ration for the viewport, will be a constant. If the window
// is resized, the viewport will be adjusted to preserve the aspect ratio.
GLint currWindowSize[2]   = { INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1] };
GLint currViewportSize[2] = { INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1] };

// Application-specific variables
PrelimTPBrain brain[NBR_JUMPING_BRAINS];

float viewerAzimuth   = ORIG_VIEWER_AZIMUTH;      // Left-right viewer rotation.
float viewerElevation = ORIG_VIEWER_ELEVATION;    // Up-down viewer rotation.

GLuint  diskTexture = 1;
GLuint  brainTexture[NBR_JUMPING_BRAINS] = { 2, 3, 4, 5, 6, 7, 8 };

// RainParticle drop[NUMBER_RAINDROPS]; // [PB] no rain
GrassParticle blade[NUMBER_BLADES]; // [PB] grass instead of rain

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition);
void TimerFunction(int value);
void Display();
//void DrawRain(); // [PB] no rain
void DrawGround();

void ResetCharacters();

void MakeAllImages();
void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha);

void ResizeWindow(GLsizei w, GLsizei h);
// void SetUpCamera(); // [PB] no definition
float GenerateRandomNumber(float lowerBound, float upperBound);


/********************************************************************************************/
/* [PB] prototypes and variables by me ******************************************************/

// function to set the GLuint for textures to corresponding brains
void SetAllImages(); // set textures to brains
void DrawGrass(); // same as DrawRain() but for my grass

bool running = true; // used in testing/debugging

/********************************************************************************************/

/****************************/
/* Function implementations */
/****************************/

// The main function sets up the data and the   //
// environment to display the textured objects. //
void main(int argc, char* argv[])
{
	// Set up the display window.
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowPosition( INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1] );
	glutInitWindowSize( currWindowSize[0], currWindowSize[1] );
	glutCreateWindow("JUMPING BRAIN #3 - Arrow Keys Rotate Viewer Left/Right And Up/Down; R Key Resets");

	// Specify the resizing and refreshing routines.
	glutReshapeFunc( ResizeWindow );
	glutKeyboardFunc( KeyboardPress );
	glutSpecialFunc( NonASCIIKeyboardPress );
	glutDisplayFunc( Display );
	glutTimerFunc( 20, TimerFunction, 1 );

	/* Set up standard lighting, shading, and depth testing. */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 0.0f);
	glViewport(0, 0, currWindowSize[0], currWindowSize[1]);

	// Initializa raindrops.
	// [PB] no rain
	/*for (int i = 0; i < NUMBER_RAINDROPS; i++)
	{
		float radius = GenerateRandomNumber(0.0f, DISK_RADIUS);
		float pos[3], delta[3];
		pos[0] = DISK_POSITION[0] + radius * sin(2 * PI * i / NUMBER_RAINDROPS);
		pos[1] = DISK_POSITION[1] + VIEWER_DISTANCE + 1.0f;
		pos[2] = DISK_POSITION[2] + radius * cos(2 * PI * i / NUMBER_RAINDROPS);
		for (int j = 0; j < 3; j++)
			delta[j] = GenerateRandomNumber(MIN_DROP_DELTA[j], MAX_DROP_DELTA[j]);
		// drop[i].initialize(pos, delta); // [PB] no rain
	}*/

	/*****************************************************************************/
	// [PB] intialize grass clusters
	// Each part is explained below
	// Goes around NUM_CONC_CIRC concentric circles, calculates how many degrees to travel around circle,
	//     travels around that many, then randomly pulls points out of smaller concentric circles (this time
	//     the circles belong to a particular patch). An orientation is also randomly drawn, then a blade of
	//     grass is initialized in that position with that orientation.
	// These loops stop once the maximum number of blades of grass is produced. This is not the most ideal
	//     way of handling that, but it allows for arbitrary alteration to the number of blades, number of patches,
	//     number of concentric circles, etc.
	int index = 0;
	for (int cc = 1; cc <= NUM_CONC_CIRC; ++cc) {					// corresponding to big concentric circles
		int patches_on_circle = floor((PATCH_RADIUS * 2 * PI) * cc / PATCH_DISTANCE);
		cout << "Circle " << cc << endl << "Patches: " << patches_on_circle << endl;

		for (int p = 1; p <= patches_on_circle; ++p) {				// create patches on concentric circle CC
			float patchAngle = p*(360.0f / patches_on_circle);
			cout << "   angle: " << patchAngle << endl;

			for (int b = 0; b < BLADES_PER_PATCH; ++b) {	// blades placed similarly to patches, but more random
				int patch_circle = (b % NUM_CONC_CIRC) + 1;		// each blade placed on next patch concentric circle

				float orientation = GenerateRandomNumber(0.0f, 360.0f); // every blade of grass 'faces' different direction

				float innerAngle = GenerateRandomNumber(0.0f, 360.0f);  // randomly generate some angle around this patch concentric circle
																		//     on which to place this blade of grass
																		//     (this is done to reduce number of for-loops)

				float pos[3];

				pos[1] = 0; // start at bottom, all blades have initial y-value of 0
				pos[0] = (PATCH_RADIUS * cc * sin(patchAngle)) + (patch_circle * INNER_RADIUS * sin(innerAngle));
				pos[2] = (PATCH_RADIUS * cc * cos(patchAngle)) + (patch_circle * INNER_RADIUS * cos(innerAngle))
						 + GRASS_Z_CORRECTION;

				blade[index++].initialize(pos, orientation);

				if (index >= NUMBER_BLADES) break; // Break out of loop when at max number of blades of grass
												   // This is done to reduce calculations on variations in loops
												   //     when changing certain variables and allows flexibility
			}
			if (index >= NUMBER_BLADES) break;
		}
		if (index >= NUMBER_BLADES) break;
	}
	/*****************************************************************************/

	// Set up all texture maps and texture-mapped objects.
	MakeAllImages();
	SetAllImages(); // [PB] new, to set brain textures, too
	ResetCharacters();
	glutMainLoop();
	return;
}

// Function to react to ASCII keyboard keys pressed by the user. //
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
{
	char pressedChar = char(pressedKey);
	switch(pressedKey)
	{
		case 'R': 
		case 'r': { ResetCharacters(); break; }
		// case 's': { running = !running; break; } // [PB] used in testing/debugging
	}
}

// Function to react to non-ASCII keyboard keys pressed by the user. //
// Used to alter spherical coordinates of the viewer's position.     //
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition)
{
	glutIgnoreKeyRepeat(false);
	switch(pressedKey)
	{
		case GLUT_KEY_LEFT: {
								viewerAzimuth += AZIMUTH_INCREMENT;
								if (viewerAzimuth > 2 * PI)
									viewerAzimuth -= 2 * PI;
								break;
							}
	case GLUT_KEY_RIGHT: {
							viewerAzimuth -= AZIMUTH_INCREMENT;
							if (viewerAzimuth < 0.0)
								viewerAzimuth += 2 * PI;
							break;
						}
		case GLUT_KEY_UP:    { 
								viewerElevation -= ELEVATION_INCREMENT; 
								if (viewerElevation < MIN_ELEVATION) 
									viewerElevation = MIN_ELEVATION; 
								break; 
							 }
		case GLUT_KEY_DOWN:  { 
								viewerElevation += ELEVATION_INCREMENT; 
								if (viewerElevation > MAX_ELEVATION)  
									viewerElevation = MAX_ELEVATION; 
								break; 
							 }
	}
}

// Function to update any animation. //
void TimerFunction(int value)
{
	if (running) { // added for debugging purposes
		int i;
		for (i = 0; i < NBR_JUMPING_BRAINS; i++)
			brain[i].update();
		/*for (i = 0; i < NUMBER_RAINDROPS; i++)
			drop[i].update();
			*/ // [PB] no rain
		glutPostRedisplay();
		glutTimerFunc(20, TimerFunction, 1);
	}
}

// Principal display routine: sets up material, lighting, //
// and camera properties, clears the frame buffer, and    //
// draws all objects within the window.                   //
void Display()
{
	GLUquadricObj *qObj;
	qObj = gluNewQuadric();
	gluQuadricDrawStyle(qObj, GLU_FILL);

	/* Set up the properties of the surface material. */
	GLfloat matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat matShininess[] = { 200.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

	/* Set up the properties of the light source. */
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat lightPosition[] = { 2.0f, 5.0f, 2.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// Set up the properties of the viewing camera.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float viewerPos[3] = { DISK_POSITION[0] + VIEWER_DISTANCE * cos(viewerAzimuth) * cos(viewerElevation), 
							DISK_POSITION[1] + VIEWER_DISTANCE * sin(viewerElevation),
							DISK_POSITION[2] + VIEWER_DISTANCE * sin(viewerAzimuth) * cos(viewerElevation) };

	// Set up the viewer's perspective.
	gluLookAt(viewerPos[0], viewerPos[1], viewerPos[2], DISK_POSITION[0], DISK_POSITION[1], DISK_POSITION[2], 0.0, 1.0, 0.0);

	// DrawRain(); // [PB] No rain
	DrawGrass();
	DrawGround();

	// Render the jumping brain (the push/pop isn't needed here, but
	// might be used if additional transformations are applied).
	glPushMatrix();
		for (int i = 0; i < NBR_JUMPING_BRAINS; i++)
			brain[i].draw();
	glPopMatrix();

	// Do the buffer swap.
	glutSwapBuffers();

	// Tell GLUT to do it again.
	glutPostRedisplay();
}


// [PB] no rain
// Cycle through the list of raindrops, drawing each one in its current position.
/* void DrawRain()
{
	glPushMatrix();
	for (int i = 0; i < NUMBER_RAINDROPS; i++)
		drop[i].draw();
	glPopMatrix();
} */

// Draw the ground as a large disk centered beneath the Jumping Brain.
void DrawGround()
{
	GLUquadricObj *qObj;
	qObj = gluNewQuadric();
	glEnable(GL_TEXTURE_2D);
	gluQuadricDrawStyle(qObj, GLU_FILL);
	gluQuadricTexture(qObj, GL_TRUE);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColor3f(DISK_COLOR[0], DISK_COLOR[1], DISK_COLOR[2]);
		glBindTexture(GL_TEXTURE_2D, diskTexture);
		glTranslatef(DISK_POSITION[0], DISK_POSITION[1], DISK_POSITION[2]);
		glRotatef(270.0, 1.0, 0.0, 0.0);
		gluDisk(qObj, 0.0, DISK_RADIUS, DISK_NUMBER_SLICES, DISK_NUMBER_LOOPS);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

// Reset the characters to their initial positions and orientations. //
void ResetCharacters()
{
	for (int i = 0; i < NBR_JUMPING_BRAINS; i++)
		brain[i].init(INIT_JUMPINGBRAIN_POSITION[i], INIT_JUMPINGBRAIN_ORIENTATION[i], JUMPINGBRAIN_COLOR[i]);
}

// Create the textures associated with all texture-mapped objects being displayed. //
void MakeAllImages()
{
	MakeImage(DISK_TEXTURE_FILENAME, diskTexture, false);
	for (int i = 0; i < NBR_JUMPING_BRAINS; ++i) {
		MakeImage(BRAIN_TEXTURE_FILENAME[i], brainTexture[i], false);
	}
	return;
}

// Convert the bitmap with the parameterized name into an OpenGL texture. //
void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha)
{
	RGBpixmap pix;
	pix.readBMPFile(bitmapFilename, hasAlpha);
	pix.setTexture(textureName);
	return;
}

// Window-reshaping callback, adjusting the viewport to be as large  //
// as possible within the window, without changing its aspect ratio. //
void ResizeWindow(GLsizei w, GLsizei h)
{
	currWindowSize[0] = w;
	currWindowSize[1] = h;
	if (ASPECT_RATIO > w / h)
	{
		currViewportSize[0] = w;
		currViewportSize[1] = int(w / ASPECT_RATIO);
	}
	else
	{
		currViewportSize[1] = h;
		currViewportSize[0] = int(h * ASPECT_RATIO);
	}
	
	glViewport(int(0.5f*(w - currViewportSize[0])), int(0.5f*(h - currViewportSize[1])), currViewportSize[0], currViewportSize[1]);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Generate a random floating-point value between the two parameterized values. //
float GenerateRandomNumber(float lowerBound, float upperBound)
{
	static bool firstTime = true;
	static time_t randomNumberSeed;

	if (firstTime)
	{
		time(&randomNumberSeed);
		firstTime = false;
		srand(int(randomNumberSeed));
	}

	return (lowerBound + ((upperBound - lowerBound) * (float(rand()) / RAND_MAX)));
}

/********************************************************************************************/
/* [PB] functions added by me */
// Set the image texture from MakeImage/MakeAllImages in the brain itself so it knows what texture is assigned to it
void SetAllImages() {
	for (int i = 0; i < NBR_JUMPING_BRAINS; ++i) {
		brain[i].setImage(brainTexture[i]);
	}
}

// [PB] draw grass
// Loop through array of blades of grass and draw each one
void DrawGrass()
{
	glPushMatrix();
	for (int i = 0; i < NUMBER_BLADES; i++)
	blade[i].draw();
	glPopMatrix();
}