#pragma once
#include "Object.h"

class Bullet : public Object
{
	vec2 move_dir;
public:
	static const float speed;
	static const float radius;
	
	Bullet();
	
	virtual void Draw(int first, Shader& shader) const;
	virtual bool Collision(vec2 point, float radius) const;
	virtual void Update(float delta_time);

	void SetMoveDir(vec2 dir);
};