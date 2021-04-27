// Patrick BuneticNeuronParticle
////////////////////////////////////////////////////
// NeuronParticle.h - NeuronParticle Class Definition //
////////////////////////////////////////////////////

#ifndef NEURON_PARTICLE_H

#include <gl/freeglut.h>
#include "Particle.h"

class NeuronParticle : public Particle
{
public:
	NeuronParticle();

	void initialize(float pos[3], float clr[3], int lifetime);
	void reset();
	void draw();
	void update();

private:
	GLfloat color[3];
	int initLife;
};

#define NEURON_PARTICLE_H
#endif
