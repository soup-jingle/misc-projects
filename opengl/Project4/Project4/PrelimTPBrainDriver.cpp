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
#include "NeuronParticle.h"
#include "PrelimTPBrainGlobals.h"

using namespace std;

/********************/
/* GLOBAL VARIABLES */
/********************/

// The initial window and viewport sizes (in pixels), set to ensure that
// the aspect ration for the viewport, will be a constant. If the window
// is resized, the viewport will be adjusted to preserve the aspect ratio.
GLint currWindowSize[2] = { INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1] };
GLint currViewportSize[2] = { INIT_WINDOW_SIZE[0], INIT_WINDOW_SIZE[1] };

// Application-specific variables
PrelimTPBrain brain[NBR_JUMPING_BRAINS];

float viewerAzimuth = ORIG_VIEWER_AZIMUTH;      // Left-right viewer rotation.
float viewerElevation = ORIG_VIEWER_ELEVATION;    // Up-down viewer rotation.

												  //GLuint  diskTexture = 1;
GLuint sphereTexture = 1;
GLuint  brainTexture[NBR_JUMPING_BRAINS] = { 2, 3, 4, 5, 6, 7, 8 };

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition);
void TimerFunction(int value);
void Display();

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

void DrawPlanet(); // [PB]

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1]);
	glutInitWindowSize(currWindowSize[0], currWindowSize[1]);
	glutCreateWindow("JUMPING BRAIN #3 - Arrow Keys Rotate Viewer Left/Right And Up/Down; R Key Resets");

	// Specify the resizing and refreshing routines.
	glutReshapeFunc(ResizeWindow);
	glutKeyboardFunc(KeyboardPress);
	glutSpecialFunc(NonASCIIKeyboardPress);
	glutDisplayFunc(Display);
	glutTimerFunc(20, TimerFunction, 1);

	/* Set up standard lighting, shading, and depth testing. */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 0.0f);
	glViewport(0, 0, currWindowSize[0], currWindowSize[1]);

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
	switch (pressedKey)
	{
	case 'R':
	case 'r': { ResetCharacters(); break; }
	case 's': { running = !running; break; } // [PB] used in testing/debugging
	}
}

// Function to react to non-ASCII keyboard keys pressed by the user. //
// Used to alter spherical coordinates of the viewer's position.     //
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition)
{
	glutIgnoreKeyRepeat(false);
	switch (pressedKey)
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
	case GLUT_KEY_UP: {
		viewerElevation -= ELEVATION_INCREMENT;
		if (viewerElevation < MIN_ELEVATION)
			viewerElevation = MIN_ELEVATION;
		break;
	}
	case GLUT_KEY_DOWN: {
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
	int i;
	for (i = 0; i < NBR_JUMPING_BRAINS; i++) {
		if (running) // added for debugging purposes
			brain[i].update();
	}
	glutPostRedisplay();
	glutTimerFunc(20, TimerFunction, 1);
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

	DrawPlanet(); // Hidden for debugging

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

// [PB] Draw planet sphere (with texture)
void DrawPlanet()
{
	GLUquadricObj *qObj;
	qObj = gluNewQuadric();
	glEnable(GL_TEXTURE_2D);
	//gluQuadricDrawStyle(qObj, GLU_FILL);
	gluQuadricTexture(qObj, GL_TRUE);
	glPushMatrix();
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glColor3f(DISK_COLOR[0], DISK_COLOR[1], DISK_COLOR[2]);
	glBindTexture(GL_TEXTURE_2D, sphereTexture);
	glTranslatef(DISK_POSITION[0], DISK_POSITION[1], DISK_POSITION[2]);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	gluSphere(qObj, DISK_RADIUS, DISK_NUMBER_SLICES, DISK_NUMBER_LOOPS);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

// Reset the characters to their initial positions and orientations. //
void ResetCharacters()
{
	for (int i = 0; i < NBR_JUMPING_BRAINS; i++)
		brain[i].init(INIT_JUMPINGBRAIN_POSITION[i], BRAIN_QUATS[i], BRAIN_QUATS[(i + 1) % 7], INIT_JUMPINGBRAIN_ORIENTATION[i], JUMPINGBRAIN_COLOR[i]);
}

// Create the textures associated with all texture-mapped objects being displayed. //
void MakeAllImages()
{
	//MakeImage(DISK_TEXTURE_FILENAME, diskTexture, false);
	MakeImage(SPHERE_TEXTURE_FILENAME, sphereTexture, false); // [PB] planet texture
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