#pragma once
#include "Object.h"

class Star : public Object {
	int color_bind;
	vec3 scenario_color;
	vec3 obj_color;
public:
	Star(const vec2& centro, int color_bind, vec3 scenario_color, vec3 obj_color);

	virtual void Draw(int first) const;
	virtual bool Collision(vec2 point, float radius) const;
	virtual void Update(float delta_time);

	void Damage();
	void Reset();
	void SetMoveDir(vec2 dir);
};