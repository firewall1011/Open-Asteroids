#pragma once
#include "Object.h"

class Asteroid : public Object {
public:
	Asteroid(int num_vertices, float radius, float noise, vec2 center);

	virtual void Draw(int first) const;
	virtual bool Collision(vec2 point) const;
	virtual void Update(float delta_time);
};