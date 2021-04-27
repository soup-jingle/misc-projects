// Patrick Bunetic
////////////////////////////////////////////////////
// GrassParticle.h - RainParticle Class Definition //
////////////////////////////////////////////////////

#ifndef GRASS_PARTICLE_H

#include <gl/freeglut.h>
#include "Particle.h"

class GrassParticle : public Particle
{
public:
	GrassParticle();

	void initialize(float pos[], float orientation);
	void draw();
	void update();  // this may be unneccessary, but did not want any updating taking place by default

private:
	float orientation = 0.0f; // added an orientation, so blades grow off to some side
};

#define GRASS_PARTICLE_H
#endif
