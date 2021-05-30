#pragma once
#include "BufferData.h"
#include "Asteroid.h"
#include "tvector.h"
#include <stdlib.h>
class AsteroidsGenerator
{
	float min_asteroid_radius;
	float max_asteroid_radius;
	int min_asteroid_vertices;
	int max_asteroid_vertices;
	float min_asteroid_speed;
	float max_asteroid_speed;
	float orbit_radius;
	BufferData *buffer;
public:
	
	AsteroidsGenerator(BufferData *buff,
		               float min_asteroid_radius,
		               float max_asteroid_radius,
		               int min_asteroid_vertices,
		               int max_asteroid_vertices,
					   float min_asteroid_speed,
					   float max_asteroid_speed,
		               float orbit_radius);

	void CreateAsteroid();
	void CreateAsteroids(int qtd);
};