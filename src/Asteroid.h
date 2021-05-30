#pragma once
#include "Object.h"

class Asteroid : public Object {
	vec2 move_dir;
	float speed;
public:
	Asteroid(int num_vertices, float radius, float noise, vec2 center, vec2 move_dir, float speed);
	virtual void Draw(int first) const;
	virtual bool Collision(vec2 point) const;
	virtual void Update(float delta_time);
};