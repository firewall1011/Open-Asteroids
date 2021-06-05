#pragma once
#include "Object.h"

class Planet : public Object {
	int color_bind;
	vec3 scenario_color;
	vec3 obj_color;
	float rotation_speed;
public:
	Planet(int num_vertices, const vec2& center, int color_bind, vec3 scenario_color, vec3 obj_color, float rotation_speed);

	virtual void Draw(int first) const;
	virtual bool Collision(vec2 point, float radius) const;
	virtual void Update(float delta_time);
};