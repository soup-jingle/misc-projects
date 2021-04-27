// Patrick Bunetic
// No changes made
/////////////////////////////////////////////////////////////
// Particle.h - Particle Class Definition                  //
//                                                         //
// The Particle class keeps track of an individual member  //
// of a particle system, withg a variety of associated     //
// parameters, including (a) initial, current, previous,   //
// and delta position values, (b) acceleration and gravity //
// values to impact the particle's speed and elevation,    //
// (c) the particle's size and its delta value (in case it //
// cxhanges), (d) the color and its delta vale, (e) the    //
// transparency and its rate of change, and (f) the        //
// lifetime and the rate of change of that lifetime.       //
/////////////////////////////////////////////////////////////

#ifndef PARTICLE_H

class Particle
{
	public:
		Particle();
		
		void  SetInitialPosition(float init[]);
		void  GetInitialPosition(float init[]);
		void  SetPosition(float pos[]);
		void  GetPosition(float pos[]);
		void  SetDeltaPosition(float delta[]);
		void  GetDeltaPosition(float delta[]);
		void  SetPreviousPosition(float prev[]);
		void  GetPreviousPosition(float prev[]);
		void  SetAcceleration(float accel[]);
		void  GetAcceleration(float accel[]);
		void  SetGravity(float grav[]);
		void  GetGravity(float grav[]);
		void  SetSize(float sz);
		float GetSize();
		void  SetDeltaSize(float delta);
		float GetDeltaSize();
		void  SetColor(float clr[]);
		void  GetColor(float clr[]);
		void  SetDeltaColor(float delta[]);
		void  GetDeltaColor(float delta[]);
		void  SetTransparency(float trans);
		float GetTransparency();
		void  SetDeltaTransparency(float delta);
		float GetDeltaTransparency();
		void  SetLifetime(int lt);
		int   GetLifetime();
		void  SetDeltaLifetime(int delta);
		int   GetDeltaLifetime();

		virtual void update();
		virtual void draw();

	protected:
		float initialPosition[3];
		float position[3];
		float deltaPosition[3];
		float previousPosition[3];
		float acceleration[3];
		float gravity[3];
		float size;
		float deltaSize;
		float color[3];
		float deltaColor[3];
		float transparency;
		float deltaTransparency;
		int   lifetime;
		int   deltaLifetime;
};

#define PARTICLE_H
#endif
