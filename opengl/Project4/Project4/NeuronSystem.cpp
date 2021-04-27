#include <stdlib.h>
#include <time.h>
#include "PrelimTPBrainGlobals.h"
#include "NeuronSystem.h"
#include "NeuronParticle.h"

NeuronSystem::NeuronSystem() {
	
}

void NeuronSystem::initialize(float clr[3]) {
	for (int i = 0; i < 3; ++i) {
		color[i] = clr[i];
	}

	srand(time(NULL));
	float pos[3];
	int lifetime;
	for (int i = 0; i < NUMBER_NEURONS; ++i) {
		for (int j = 0; j < 3; ++j) {
			pos[j] = (((rand() % 1000) / 2000.0) - NEURON_FACTOR);
		}
		lifetime = rand() % NEURON_LIFETIME_SCALE + NEURON_MIN_LIFETIME;
		neurons[i].initialize(pos, clr, lifetime);
	}
}

void NeuronSystem::reset() {
	for (int i = 0; i < NUMBER_NEURONS; ++i) {
		neurons[i].reset();
	}
}

void NeuronSystem::update() {
	for (int i = 0; i < NUMBER_NEURONS; ++i) {
		neurons[i].update();
	}
}

void NeuronSystem::draw() {
	for (int i = 0; i < NUMBER_NEURONS; ++i) {
		neurons[i].draw();
	}
}