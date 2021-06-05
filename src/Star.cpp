#include "Star.h"
#include <GL/glew.h> 

vec2* StarVertices(const vec2& centro);

Star::Star(const vec2& center, vec3 scenario_color, float rotation_speed)
{
    vertices = StarVertices(center);
    length = 6;
    this->center = center;
    this->color = scenario_color;
    this->rotation_speed = rotation_speed;
}

void Star::Draw(int first, Shader& shader) const
{
    shader.SetColor(color);
    glDrawArrays(GL_LINE_STRIP, first, length);
}

bool Star::Collision(vec2 point, float radius) const
{
    return false;
}

void Star::Update(float delta_time)
{
    Rotate(rotation_speed * delta_time);
}

vec2* StarVertices(const vec2& centro) {
    vec2* vertices = new vec2[6];

    vertices[0] = vec2(0.5f, 0.2f);
    vertices[1] = vec2(-0.5f, 0.2f);
    vertices[2] = vec2(0.375f, -0.55f);
    vertices[3] = vec2(0.0f, 0.7f);
    vertices[4] = vec2(-0.375f, -0.55f);
    vertices[5] = vec2(0.5f, 0.2);

    return vertices;
}