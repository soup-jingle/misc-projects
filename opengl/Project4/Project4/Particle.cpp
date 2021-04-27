// Patrick Bunetic
// No changes made
///////////////////////////////////////////////////////
// Particle.cpp - Particle Class Implementation      //
//                                                   //
// The Particle class is an abstract super-class for //
// defining individual particles that will comprise  //
// particle systems. The implementation includes a   //
// default constructor, as well as accessors and     //
// mutators for all data members. In addition, the   //
// implementation includes default update and draw   //
// member functions, which can be overridden in any  //
// subclass.                                         //
///////////////////////////////////////////////////////

#include <gl/freeglut.h>
#include "Particle.h"
#include "PrelimTPBrainGlobals.h"

// Default Constructor
Particle::Particle()
{
	for (int i = 0; i < 3; i++)
	{
		position[i]         = 0.0;
		deltaPosition[i]    = 0.0;
		previousPosition[i] = 0.0;
		acceleration[i]     = 0.0;
		gravity[i]          = 0.0;
		color[i]            = 1.0;
		deltaColor[i]       = 0.0;
	}
	size              = 1.0;
	deltaSize         = 0.0;
	transparency      = 1.0;
	deltaTransparency = 0.0;
	lifetime          = 100;
	deltaLifetime     = -1;
}

// InitialPosition Mutator
void Particle::SetInitialPosition(float init[])
{
	for (int i = 0; i < 3; i++)
		initialPosition[i] = init[i];
}

// InitialPosition Accessor
void Particle::GetInitialPosition(float init[])
{
	for (int i = 0; i < 3; i++)
		init[i] = initialPosition[i];
}

// Position Mutator
void Particle::SetPosition(float pos[])
{
	for (int i = 0; i < 3; i++)
		position[i] = pos[i];
}

// Position Accessor
void Particle::GetPosition(float pos[])
{
	for (int i = 0; i < 3; i++)
		pos[i] = position[i];
}

// DeltaPosition Mutator
void Particle::SetDeltaPosition(float delta[])
{
	for (int i = 0; i < 3; i++)
		deltaPosition[i] = delta[i];
}

// DeltaPosition Accessor
void Particle::GetDeltaPosition(float delta[])
{
	for (int i = 0; i < 3; i++)
		delta[i] = deltaPosition[i];
}

// PrevPosition Mutator
void Particle::SetPreviousPosition(float prev[])
{
	for (int i = 0; i < 3; i++)
		previousPosition[i] = prev[i];
}

// PrevPosition Accessor
void Particle:: GetPreviousPosition(float prev[])
{
	for (int i = 0; i < 3; i++)
		prev[i] = previousPosition[i];
}

// Acceleration Mutator
void Particle::SetAcceleration(float accel[])
{
	for (int i = 0; i < 3; i++)
		acceleration[i] = accel[i];
}

// Acceleration Accessor
void Particle::GetAcceleration(float accel[])
{
	for (int i = 0; i < 3; i++)
		accel[i] = acceleration[i];
}

// Gravity Mutator
void Particle::SetGravity(float grav[])
{
	for (int i = 0; i < 3; i++)
		gravity[i] = grav[i];
}

// Gravity Accessor
void Particle::GetGravity(float grav[])
{
	for (int i = 0; i < 3; i++)
		grav[i] = gravity[i];
}

// Size Mutator
void Particle::SetSize(float sz)
{
	size = sz;
}

// Size Accessor
float Particle::GetSize()
{
	return size;
}

// DeltaSize Mutator
void Particle::SetDeltaSize(float delta)
{
	deltaSize = delta;
}

// DeltaSize Accessor
float Particle::GetDeltaSize()
{
	return deltaSize;
}

// Color Mutator
void Particle::SetColor(float clr[])
{
	for (int i = 0; i < 3; i++)
		color[i] = clr[i];
}

// Color Accessor
void Particle::GetColor(float clr[])
{
	for (int i = 0; i < 3; i++)
		clr[i] = color[i];
}

// DeltaColor Mutator
void Particle::SetDeltaColor(float delta[])
{
	for (int i = 0; i < 3; i++)
		deltaColor[i] = delta[i];
}

// DeltaColor Accessor
void Particle::GetDeltaColor(float delta[])
{
	for (int i = 0; i < 3; i++)
		delta[i] = deltaColor[i];
}

// Transparency Mutator
void Particle::SetTransparency(float trans)
{
	transparency = trans;
}

// Transparency Accessor
float Particle::GetTransparency()
{
	return transparency;
}

// DeltaTransparency Mutator
void Particle::SetDeltaTransparency(float delta)
{
	deltaTransparency = delta;
}

// DeltaTransparency Accessor
float Particle::GetDeltaTransparency()
{
	return deltaTransparency;
}

// Size Mutator
void Particle::SetLifetime(int lt)
{
	lifetime = lt;
}

// Size Accessor
int Particle::GetLifetime()
{
	return lifetime;
}

// DeltaSize Mutator
void Particle::SetDeltaLifetime(int delta)
{
	deltaLifetime = delta;
}

// DeltaSize Accessor
int Particle::GetDeltaLifetime()
{
	return deltaLifetime;
}

// Update function for updating the data members of the Particle class.
void Particle::update()
{
	for (int i = 0; i < 3; i++)
	{
		previousPosition[i] = position[i];
		position[i] += deltaPosition[i];
		deltaPosition[i] += acceleration[i] + gravity[i];
		color[i] += deltaColor[i];
	}
	size += deltaSize;
	transparency += deltaTransparency;
	lifetime += deltaLifetime;
}

// Draw function for rendering the particle as a semi-transparent point.
void Particle::draw()
{
	glPointSize(size);
	if (lifetime > 0)
	{
		glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE);
		glColor4f( color[0], color[1], color[2], transparency );
		glBegin(GL_POINTS);
			glVertex3f(position[0], position[1], position[2]);
		glEnd();
		glDisable(GL_BLEND);
	}
}
