#pragma once
#include <stdlib.h>
#include <vector>

#include "BufferData.h"
#include "Asteroid.h"
#include "tvector.h"

class AsteroidsGenerator
{
	float min_asteroid_radius;
	float max_asteroid_radius;
	int min_asteroid_vertices;
	int max_asteroid_vertices;
	float min_asteroid_speed;
	float max_asteroid_speed;
	float orbit_radius;

public:
	
	AsteroidsGenerator(float min_asteroid_radius,
		               float max_asteroid_radius,
		               int min_asteroid_vertices,
		               int max_asteroid_vertices,
					   float min_asteroid_speed,
					   float max_asteroid_speed,
		               float orbit_radius);

	Asteroid* CreateAsteroid();
	void CreateAsteroids(int qtd);
};