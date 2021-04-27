// Patrick Bunetic
// Particle system for neurons
/////////////////////////////////////////////////////////
// NeuronParticle.cpp - NeuronParticle Class Implementation
/////////////////////////////////////////////////////////

#include <cmath>
#include <ctime>
#include "NeuronParticle.h"
#include "PrelimTPBrainGlobals.h"

// Default Constructor
NeuronParticle::NeuronParticle()
{
	lifetime = 12;
	for (int i = 0; i < 3; i++)
	{
		initialPosition[i] = 0.0;
		previousPosition[i] = 0.0;
	}
	size = NEURON_WIDTH;
}

void NeuronParticle::initialize(float pos[3], float clr[3], int lifetime)
{
	for (int i = 0; i < 3; i++)
	{
		initialPosition[i] = pos[i];
		previousPosition[i] = pos[i];
		deltaPosition[i] = pos[i]; // velocity same as position (this makes it come from center of brain)
		color[i] = clr[i];
		position[i] = previousPosition[i] + deltaPosition[i];
	}
	size = NEURON_WIDTH;
	this->lifetime = 0;
	this->initLife = lifetime;
}

void NeuronParticle::reset() // "reset" just means "start" in this case
{
	lifetime = initLife;
	for (int i = 0; i < 3; ++i) {
		previousPosition[i] = initialPosition[i];
		position[i] = previousPosition[i] + deltaPosition[i];
	}
}

// Render the line segments represented by this blade of NEURON.
void NeuronParticle::draw()
{
	if (lifetime > 0) {
		glPushMatrix();
		glColor3f(color[0], color[1], color[2]);
		glEnable(GL_LINE_SMOOTH);
		glLineWidth(size);
		glBegin(GL_LINES);
			glVertex3f(previousPosition[0], previousPosition[1], previousPosition[2]);
			glVertex3f(position[0], position[1], position[2]);
		glEnd();
		glPopMatrix();
	}
}

void NeuronParticle::update() {
	for (int i = 0; i < 3; ++i) {
		previousPosition[i] = position[i];
		position[i] = position[i] + deltaPosition[i];
	}
	--lifetime;
}