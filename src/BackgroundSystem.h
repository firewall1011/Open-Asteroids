#pragma once
#include <stdlib.h>
#include <vector>

#include "Planet.h"
#include "Star.h"
#include "Random.h"
#include <GL/glew.h> 

namespace BackgroundSystem
{

	extern std::vector<Object*> universe;
	void CreateBackground(float star_qtd_proportion, 
						  float max_celestial_size, 
						  float min_celestial_size, 
						  int universe_population, 
						  int color_bind, 
						  vec3 scenario_color, 
		                  vec3 obj_color);
};