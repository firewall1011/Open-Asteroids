#pragma once
#include "Object.h"

class Asteroid : public Object {
	vec2 move_dir;
	float speed;
	float radius;
	float init_radius;

	short int stage = 0;
	const static short int max_stage = 3;
public:
	Asteroid(int num_vertices, float radius, float noise, vec2 center, vec2 move_dir, float speed);
	Asteroid(int num_vertices, float radius, float noise, float speed);

	virtual void Draw(int first, Shader& shader) const;
	virtual bool Collision(vec2 point, float radius) const;
	virtual void Update(float delta_time);

	void Damage();
	void Reset();
	void SetMoveDir(vec2 dir);
};