// Patrick Bunetic
// Class to take care of cluster of neuron particles

#include "NeuronParticle.h"

#ifndef NEURON_SYSTEM_H

class NeuronSystem
{
public:
	NeuronSystem();

	void initialize(float clr[3]);
	void reset();
	void update();
	void draw();
	
private:
	NeuronParticle neurons[NUMBER_NEURONS];
	int lifetime;
	float color[3];
};

#define NEURON_SYSTEM_H
#endif