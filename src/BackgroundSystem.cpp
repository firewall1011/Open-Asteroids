#include "BackgroundSystem.h"
namespace BackgroundSystem
{
	std::vector<Object*> universe;
	void CreateBackground(float star_qtd_proportion, float max_celestial_size, float min_celestial_size, int universe_population, int color_bind, vec3 scenario_color, vec3 obj_color)
	{
		float prop, scale, rotation;
		vec2 position;

		for (size_t i = 0; i < universe_population; i++)
		{
			prop = Random::Range(0, 1);
			scale = Random::Range(min_celestial_size, max_celestial_size);
			position = vec2(Random::Range(-1, 1), Random::Range(-1, 1));
			rotation = Random::Range(-0.15f, 0.15f);

			if (prop < star_qtd_proportion) {
				Star* s = new Star(vec2(0.0f, 0.0f), color_bind, scenario_color, obj_color);
				s->Move(position);
				s->SetScale(vec2(scale, scale));
				s->rotation = rotation;
				BackgroundSystem::universe.push_back((Object*)s);
			}
			else {
				Planet* p = new Planet(100, vec2(0.0f, 0.0f), color_bind, scenario_color, obj_color);
				p->Move(position);
				p->SetScale(vec2(scale, scale));
				p->rotation = rotation;
				BackgroundSystem::universe.push_back((Object*)p);
			}

		}
	}
}