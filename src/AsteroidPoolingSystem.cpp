#include "AsteroidPoolingSystem.h"
#include "Random.h"

namespace AsteroidPoolingSystem
{	
	std::vector<Asteroid*> asteroids;
	Timer timer(ASTEROID_RESPAWN_COOLDOWN);

	void SpawnAsteroid()
	{
		Asteroid* a = FindInactiveAsteroid();
		if (a == nullptr)
			return;
		a->position = Random::insideUnitCircle() * 2.0f;
		a->SetMoveDir( -a->position );
		a->isActive = true;
		a->Reset();
	}

	Asteroid* FindInactiveAsteroid()
	{
		for (auto& a : asteroids) 
		{
			if (!a->isActive)
				return a;
		}

		return nullptr;
	}

	void Tick(float delta_time)
	{
		if (timer.Tick(delta_time)) 
		{
			SpawnAsteroid();
			timer.Reset();
		}
	}
}
