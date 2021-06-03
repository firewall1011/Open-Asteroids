#define GLFW_INCLUDE_NONE
#include "Asteroid.h"
#include <GL/glew.h> 
#include <Collisions.h>

vec2* AsteroidVertices(int num_vertices, float radius, float distance, const vec2& centro);

Asteroid::Asteroid(int num_vertices, float radius, float noise, vec2 center, vec2 move_dir, float speed) : Object() 
{
    vertices = AsteroidVertices(num_vertices, radius, noise, center);
    length = num_vertices;
    this->center = center;
    this->radius = radius;
    this->init_radius = radius;
    this->move_dir = move_dir;
    this->speed = speed;
}

Asteroid::Asteroid(int num_vertices, float radius, float noise, float speed) 
{
    vertices = AsteroidVertices(num_vertices, radius, noise, center);
    length = num_vertices;
    this->radius = radius;
    this->init_radius = radius;
    this->speed = speed;
    this->isActive = false;
}

void Asteroid::Draw(int first) const
{
    glDrawArrays(GL_LINE_LOOP, first, length);
}

bool Asteroid::Collision(vec2 point, float obj_radius) const
{
    return Collisions::CircleWithCircle(position, point, radius, obj_radius);
}

void Asteroid::Update(float delta_time)
{
    Move((move_dir) * speed * delta_time);
    Rotate(3.0f * delta_time);

    if (abs(position.x) > 2.1f || abs(position.y) > 2.1f)
        isActive = false;
}

void Asteroid::SetMoveDir(vec2 dir)
{
    move_dir = dir;
    LookAt(move_dir);
}

void Asteroid::Damage() 
{
    stage--;
    
    float scale = (stage / (float)max_stage);
    SetScale(vec2(1, 1) * scale);
    radius = init_radius * scale;
    
    if (stage <= 0)
        isActive = false;
}

void Asteroid::Reset() 
{
    stage = max_stage;

    float scale = (stage / (float)max_stage);
    SetScale(vec2(1, 1) * scale);
    radius = init_radius * scale;
}

vec2* AsteroidVertices(int num_vertices, float radius, float distance, const vec2& centro) 
{
    vec2* vertices = new vec2[num_vertices];

    float angle = 0.0f;

    float x, y;
    for (int i = 0; i < num_vertices; i++)
    {
        float _radius = radius + (rand() / (float)RAND_MAX) * distance;
        x = (cosf(angle) * _radius) + centro.x;
        y = (sinf(angle) * _radius) + centro.y;
        vertices[i].x = x;
        vertices[i].y = y;
        angle += (2 * T_PI) / (num_vertices - 1);
    }

    return vertices;
}