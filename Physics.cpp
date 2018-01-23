#include "Physics.h"
#include <stdlib.h>


Physics::Physics(pos_t pos /*0, 0*/, pos_t vel /*0, 0*/, pos_t acc /*0, 0*/)
{
	position = pos;
	velocity = vel;
	acceleration = acc;
}

void Physics::move(int dt, bool resistance /*false*/) // jak dlufo renderowala sie klatka tak mocno sie ruszy
{
	double acc_sd = 1.0; //slowdown
	double vel_sd = 0.999803; // max 1.0
	if (resistance) acceleration = acceleration * acc_sd;
	velocity = (velocity + acceleration * dt);
	if (resistance) velocity = velocity * vel_sd;
	position = position + velocity * dt + acceleration * dt * dt * 0.5;
}

void Physics::bounce(int axis, float direction) {
	velocity[axis] = abs(velocity[axis]) * direction;
	acceleration[axis] = abs(acceleration[axis]) * direction;
	//position[axis] = abs(position[axis]) * direction;
}

Physics::~Physics()
{
}