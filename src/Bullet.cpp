#include <GL/glew.h>

#include "Bullet.h"
#include "Collisions.h"

const float Bullet::speed = 0.0005f;
const float Bullet::radius = 0.02f;

Bullet::Bullet(vec2 center, vec2 move_dir) : move_dir(move_dir)
{
	this->center = center;

	vertices = CriarCirculo(6, radius, center, 0.0f, T_PI);
	length = 6;

	SetScale(vec2(0.5f, 1.0f));
	LookAt(move_dir);
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
}