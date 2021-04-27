// PATRICK BUNETIC
// Things I added/changed indicated by "[PB]" comment
// This would just be registering actions for key presses
////////////////////////////////////////////////////////////////////
//                                                                //
// RunningbrainDriver.cpp - Bill White - CS 482.001 - Fall 2017    //
//                                                                //
// This program displays a simple model of a Jumping Brain, with   //
// keyboard controls for toggling body part visibility, modifying //
// limb speed, and altering camera orientation.                   //
//                                                                //
////////////////////////////////////////////////////////////////////

#include <gl/freeglut.h>
#include <cmath>
#include <ctime>
#include <string>
#include "JumpingBrain.h"
#include "JumpingBrainGlobals.h"

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
JumpingBrain brain;
float viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
float viewerAltitude = INITIAL_VIEWER_ALTITUDE;

std::string WINDOW_TITLE = "SPEED: Arms(A/a),Legs(L/l),All(+/-); VISIBILITY: ";
char *TITLE_INIT_VIS = "SPEED: Arms(A/a),Legs(L/l),All(+/-); VISIBILITY: (B)ody, (S)houlders, (H)umerus, (F)orearm, (h)and, (P)elvis, (T)high, (s)hin, (f)oot, (t)oe";

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition);
void TimerFunction(int value);
void Display();

void ResetCharacter();

void  ResizeWindow(GLsizei w, GLsizei h);
float GenerateRandomNumber(float lowerBound, float upperBound);

/****************************/
/* Function implementations */
/****************************/

// The main function sets up the data and the  //
// environment to display the scene's objects. //
void main(int argc, char* argv[])
{
	// Set up the display window.
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowPosition( INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1] );
	glutInitWindowSize( currWindowSize[0], currWindowSize[1] );
	glutCreateWindow(TITLE_INIT_VIS);

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
	glutMainLoop();
	return;
}

// Function to react to ASCII keyboard keys pressed by the user. //
// Used to alter upper/lower body speed and to toggle whether    //
// various body parts are visible.                               //
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
{
	char pressedChar = char(pressedKey);
	switch(pressedKey)
	{
	case '+': { brain.incrementAllSpeed(); break; }
	case '-': { brain.decrementAllSpeed(); break; }
	// Increment/Decrement speed of arms/legs separately [PB]
	case 'A': { brain.incrementArmSpeed(); break; }
	case 'a': { brain.decrementArmSpeed(); break; }
	case 'L': { brain.incrementLegSpeed(); break; }
	case 'l': { brain.decrementLegSpeed(); break; }
			  
	// Visibility for body parts [PB]
	case 'B': // Body
	case 'S': // Shoulders
	case 'H': // Humerus
	case 'F': // Forearm
	case 'h': // hand
	case 'P': // Pelvis
	case 'T': // Thigh
	case 's': // shin
	case 'f': // foot
	case 't': // toe
	{ 
		brain.toggleVisibility(pressedKey);
		glutSetWindowTitle(brain.getTitle().c_str());  
		break;
	}

	}
}

// Function to react to non-ASCII keyboard keys pressed by the user. //
// Used to alter the jumping brain's hopping direction and to alter  //
// his hopping speed.                                                //
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition)
{
	glutIgnoreKeyRepeat(false);
	switch (pressedKey)
	{
		case GLUT_KEY_RIGHT: {
			viewerAzimuth += VIEWER_ANGLE_INCREMENT;
			if (viewerAzimuth > 2 * PI)
				viewerAzimuth -= 2 * PI;
			break;
		}
		case GLUT_KEY_LEFT: {
			viewerAzimuth -= VIEWER_ANGLE_INCREMENT;
			if (viewerAzimuth < 0.0)
				viewerAzimuth += 2 * PI;
			break;
		}
		case GLUT_KEY_UP: {
			viewerAltitude += VIEWER_ANGLE_INCREMENT;
			if (viewerAltitude > PI - VIEWER_ANGLE_INCREMENT)
				viewerAltitude = PI - VIEWER_ANGLE_INCREMENT;
			break;
		}
		case GLUT_KEY_DOWN: {
			viewerAltitude -= VIEWER_ANGLE_INCREMENT;
			if (viewerAltitude < VIEWER_ANGLE_INCREMENT)
				viewerAltitude = VIEWER_ANGLE_INCREMENT;
			break;
		}
	}
}

// Function to update any animation. //
void TimerFunction(int value)
{
	brain.update();
	glutPostRedisplay();
	glutTimerFunc(20, TimerFunction, 1);
}

// Principal display routine: sets up material, lighting, //
// and camera properties, clears the frame buffer, and    //
// draws all objects within the window.                   //
void Display()
{
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

	// Position and orient viewer.
	float position[] = { 0.0f, 0.0f, 0.0f };
	gluLookAt(position[0] + VIEWER_DISTANCE * sin(viewerAltitude) * sin(viewerAzimuth),
		position[1] + VIEWER_DISTANCE * cos(viewerAltitude),
		position[2] + VIEWER_DISTANCE * sin(viewerAltitude) * cos(viewerAzimuth),
		position[0], position[1], position[2],
		0.0, 1.0, 0.0);

	// Save the current modelview matrix (the identity matrix).
	glPushMatrix();	

			brain.draw();

	// Restore the original modelview matrix (the identity matrix).
	glPopMatrix();

	// Do the buffer swap.
	glutSwapBuffers();

	// Tell GLUT to do it again.
	glutPostRedisplay();
}

// Reset the character to its initial pose. //
void ResetCharacter()
{
	brain.init();
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