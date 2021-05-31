#pragma once
#include "Asteroid.h"
#include "Player.h"
#include <vector>

namespace AsteroidPoolingSystem
{
	extern std::vector<Asteroid*> asteroids;
	void SpawnAsteroid();
	Asteroid* FindInactiveAsteroid();
};

