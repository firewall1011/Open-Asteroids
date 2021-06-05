#include "BackgroundSystem.h"
namespace BackgroundSystem
{
	std::vector<Object*> universe;
	void CreateBackground(float star_qtd_proportion, float max_celestial_size, float min_celestial_size, int universe_population, vec3 scenario_color)
	{
		float prop, scale, rotation_speed;
		vec2 position;

		for (size_t i = 0; i < universe_population; i++)
		{
			prop = Random::Range(0, 1);
			scale = Random::Range(min_celestial_size, max_celestial_size);
			position = vec2(Random::Range(-1, 1), Random::Range(-1, 1));
			rotation_speed = 0.02f;

			if (prop < star_qtd_proportion) {
				Star* s = new Star(position, scenario_color, rotation_speed);
				s->Move(position);
				s->SetScale(vec2(scale, scale));
				BackgroundSystem::universe.push_back((Object*)s);
			}
			else {
				Planet* p = new Planet(100, position, scenario_color, rotation_speed);
				p->Move(position);
				p->SetScale(vec2(scale, scale));
				BackgroundSystem::universe.push_back((Object*)p);
			}

		}
	}
}