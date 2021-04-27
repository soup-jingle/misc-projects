// Patrick Bunetic
// Particle system, initialized with a starting position and an orientation (the way it 'points' as it 'grows')
/////////////////////////////////////////////////////////
// GrassParticle.cpp -GrassParticle Class Implementation //GrassParticle
/////////////////////////////////////////////////////////

#include <cmath>
#include <ctime>
#include "GrassParticle.h"
#include "PrelimTPBrainGlobals.h"
//#include <iostream>

// Default Constructor
GrassParticle::GrassParticle()
{
	for (int i = 0; i < 3; i++)
	{
		position[i] = 0.0;
		previousPosition[i] = 0.0;
	}
	size = GRASS_WIDTH;
}

void GrassParticle::initialize(float pos[], float orientation)
{
	for (int i = 0; i < 3; i++)
	{
		initialPosition[i] = pos[i];
		previousPosition[i] = pos[i];
		color[i] = GRASS_COLOR[i];
	}
	initialPosition[1] = previousPosition[1] = GRASS_HEIGHT_CORRECTION - 0.1f; // Grass grows from its spot at the bottom
	this->orientation = orientation;
	size = GRASS_WIDTH;
}

// Render the line segments represented by this blade of grass.
void GrassParticle::draw()
{
	glPushMatrix();
	glColor3f(color[0], color[1], color[2]);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(size);
	glBegin(GL_LINES);
	for (int i = 9; i >= -1 + (10 - NUM_SEG); --i) {

		float y = COEFFICIENT * FACTOR * FACTOR * i * i; // y = a * x^2:
														 //   x = i * factor; a = coefficient

		// x, z steadily move in direction of orientation by FACTOR
		// is the max grass height minus the 'y' calculated above
		position[0] = previousPosition[0] + FACTOR * sin(PI_OVER_180 * orientation);
		position[1] = GRASS_HEIGHT - y + GRASS_HEIGHT_CORRECTION;
		position[2] = previousPosition[2] + FACTOR * cos(PI_OVER_180 * orientation);
		
		// draw the segment
		glVertex3f(previousPosition[0], previousPosition[1], previousPosition[2]);
		glVertex3f(position[0], position[1], position[2]);

		// Update previous position so to pick up drawing next segment where just left off
		previousPosition[0] = position[0];
		previousPosition[1] = position[1];
		previousPosition[2] = position[2];
	}
	glEnd();
	glPopMatrix();

	// Reset this so that the grass 'grows' from same spot each time redrawn
	// This 'could' be done in update, but then a whole new loop just for that would be needed.
	// This prevents that extra loop
	for (int i = 0; i < 3; i++) 
	{
		previousPosition[i] = initialPosition[i];
	}
}

// No updating necessary
void GrassParticle::update() {
}