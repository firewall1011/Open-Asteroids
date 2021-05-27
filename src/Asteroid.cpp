#define GLFW_INCLUDE_NONE
#include "Asteroid.h"
#include <GL/glew.h> 

vec2* AsteroidVertices(int num_vertices, float radius, float distance, const vec2& centro);

Asteroid::Asteroid(int num_vertices, float radius, float noise, vec2 center) : Object() {
    vertices = AsteroidVertices(num_vertices, radius, noise, center);
    length = num_vertices;
    center = center;

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * length, vertices, GL_STATIC_DRAW);

}

void Asteroid::Draw() const
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glDrawArrays(GL_LINES, 0, length);
}

bool Asteroid::Collision(vec2 point) const 
{
    return true;
}

void Asteroid::Update(float delta_time)
{
    return;
}

vec2* AsteroidVertices(int num_vertices, float radius, float distance, const vec2& centro) {
    vec2* vertices = new vec2[num_vertices];

    float angle = 0.0f;

    float x, y;
    for (int i = 0; i < num_vertices; i++)
    {
        float random = rand() / RAND_MAX;
        float _radius = radius + (rand()%2 == 0 ? - distance : distance) * random;
        x = (cosf(angle) * _radius) + centro.x;
        y = (sinf(angle) * _radius) + centro.y;
        vertices[i].x = x;
        vertices[i].y = y;
        angle += (360.0f) / (num_vertices - 1);
    }

    return vertices;
}