#include "Physics.h"
#include <stdlib.h>


Physics::Physics(pos_t pos /*0, 0*/, pos_t vel /*0, 0*/, pos_t acc /*0, 0*/)
{
	position = pos;
	velocity = vel;
	acceleration = acc;
}

void Physics::move(int dt, bool ball /*false*/) 
{
	double acc_sd = 0.9999; // slightly slowdown
	double vel_sd = 0.999323002320; // max 1.0
	acceleration = acceleration * acc_sd; //zmiana przyspieszenia w kazdej klatce
	velocity = (velocity + acceleration * dt);
	if (!ball) velocity = velocity * vel_sd;
	if (ball) position = position + velocity * dt + acceleration * dt * dt * 0.5;
	if (!ball) position[0] = position[0] + velocity[0] * 1.099 * dt;
}

void Physics::bounce(int axis, float direction) { // zmiana kiernku przyspieszenia i predkosci przy odbiciu
	velocity[axis] = abs(velocity[axis]) * direction;
	acceleration[axis] = abs(acceleration[axis]) * direction;
	//position[axis] = abs(position[axis]) * direction;
}

Physics::~Physics()
{
}