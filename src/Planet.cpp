#include "Planet.h"
#include <GL/glew.h> 
vec2* PlanetVertices(int num_vertices, const vec2& centro);
Planet::Planet(int num_vertices, const vec2& centro)
{
    vertices = PlanetVertices(num_vertices, centro);
    length = num_vertices;
    this->center = center;
    this->radius = radius;
    this->init_radius = radius;
}

void Planet::Draw(int first) const
{
    glDrawArrays(GL_LINE_LOOP, first, length/2);
    glDrawArrays(GL_POINTS, first + length/2 , length / 2);
}

bool Planet::Collision(vec2 point, float radius) const
{
	return false;
}

void Planet::Update(float delta_time)
{
}

void Planet::Damage()
{
}

void Planet::Reset()
{
}

void Planet::SetMoveDir(vec2 dir)
{
}

vec2* PlanetVertices(int num_vertices, const vec2& centro) {
    vec2* vertices = new vec2[num_vertices];

    float angle = 0.0f;

    float x, y;
    for (int i = 0; i < num_vertices/2; i++)
    {
        x = (cosf(angle)) + centro.x;
        y = (sinf(angle)) + centro.y;
        vertices[i].x = x;
        vertices[i].y = y;
        angle += (2 * T_PI) / (num_vertices/2 - 1);;
    }
    
    int count_vertices = num_vertices/2;
    angle = 0.0f;
    for (int i = num_vertices / 2; i < num_vertices; i++)
    {
        x = 2.6f*(cosf(angle));
        y = 0.2f*(sinf(angle));
        if ((x < -0.816 || x > 0.816  || (y < 0 && -0.816< x && x < 0.816))) {
            vertices[i].x = x + centro.x;
            vertices[i].y = y + centro.y;
        }
        angle += (2 * T_PI) / (num_vertices/2 - 1);;
    }
 

    return vertices;
}