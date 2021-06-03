#pragma once
#include "Asteroid.h"
#include "Player.h"
#include <vector>

namespace AsteroidPoolingSystem
{
	constexpr float ASTEROID_RESPAWN_COOLDOWN = 0.35f;

	extern std::vector<Asteroid*> asteroids;
	extern Timer timer;
	void SpawnAsteroid();
	Asteroid* FindInactiveAsteroid();
	void Tick(float delta_time);
};

