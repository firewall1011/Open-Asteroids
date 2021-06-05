#pragma once
#include "Object.h"

class Planet : public Object {
	vec2 move_dir;
	float speed;
	float radius;
	float init_radius;

	short int stage = 0;
	const static short int max_stage = 3;
public:
	Planet(int num_vertices, const vec2& centro);

	virtual void Draw(int first) const;
	virtual bool Collision(vec2 point, float radius) const;
	virtual void Update(float delta_time);

	void Damage();
	void Reset();
	void SetMoveDir(vec2 dir);
};