#include "AsteroidPoolingSystem.h"
#include "Random.h"

namespace AsteroidPoolingSystem
{	
	std::vector<Asteroid*> asteroids;
	void SpawnAsteroid()
	{
		Asteroid* a = FindInactiveAsteroid();
		if (a == nullptr)
			return;
		a->position = Random::insideUnitCircle() * 2.0f;
		a->SetMoveDir( -a->position );
		a->isActive = true;
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
}
