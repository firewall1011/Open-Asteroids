#pragma once
#include "Object.h"

class Star : public Object {
	vec3 color;
	float rotation_speed;
public:
	Star(const vec2& centro, vec3 scenario_color, float rotation_speed);

	virtual void Draw(int first, Shader& shader) const;
	virtual bool Collision(vec2 point, float radius) const;
	virtual void Update(float delta_time);
};