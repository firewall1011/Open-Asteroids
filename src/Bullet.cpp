#include <GL/glew.h>

#include "Bullet.h"
#include "Collisions.h"

const float Bullet::speed = 0.005f;
const float Bullet::radius = 0.02f;

Bullet::Bullet()
{
	center = vec2();

	vertices = CriarCirculo(6, radius, center, 0.0f, T_PI);
	length = 6;

	SetScale(vec2(0.5f, 1.0f));
	isActive = false;
}

void Bullet::Draw(int first) const
{
	glDrawArrays(GL_LINE_LOOP, first, length);
}

bool Bullet::Collision(vec2 other_point, float other_radius) const
{
	return Collisions::CircleWithCircle(center, other_point, radius, other_radius);
}

void Bullet::Update(float delta_time)
{
	Move(move_dir * speed);

	if (abs(position.x) > 1.0f || abs(position.y) > 1.0f)
		isActive = false;
}

void Bullet::SetMoveDir(vec2 dir) 
{
	move_dir = dir;
	LookAt(move_dir);
}