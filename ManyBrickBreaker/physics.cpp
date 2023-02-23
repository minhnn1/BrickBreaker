#include "pch.h"
#include "physics.h"

float linear_interpolation(float x, float y, float z)
{
	//current speed, max speed, acceleration
	return ((1.0f - z) * x) + (z * y);
}
