#pragma once
#include <stdlib.h>

namespace Random 
{
	// Returns a random float within [0.0..1.0] (range is inclusive) (Read Only).
	inline float Value() {
		return (rand() / (float)RAND_MAX);
	}

	// Returns a random float within[minInclusive..maxInclusive](range is inclusive).
	inline float Range(float min, float max)
	{
		return Value() * (max-min) + min;
	}
	
	//InitState	Initializes the random number generator state with a seed.
	inline void InitState(unsigned int seed)
	{
		srand(seed);
	}

	//insideUnitCircle	Returns a random point inside or on a circle with radius 1.0 (Read Only).
	//insideUnitSphere	Returns a random point inside or on a sphere with radius 1.0 (Read Only).
	//onUnitSphere	Returns a random point on the surface of a sphere with radius 1.0 (Read Only).
	//rotation	Returns a random rotation(Read Only).
	//rotationUniform	Returns a random rotation with uniform distribution(Read Only).
	//ColorHSV	Generates a random color from HSVand alpha ranges.
}