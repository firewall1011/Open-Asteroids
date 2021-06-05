#include "Star.h"
#include <GL/glew.h> 

vec2* StarVertices(const vec2& centro);

Star::Star(const vec2& center, int color_bind, vec3 scenario_color, vec3 obj_color, float rotation_speed)
{
    vertices = StarVertices(center);
    length = 6;
    this->center = center;
    this->color_bind = color_bind;
    this->scenario_color = scenario_color;
    this->obj_color = obj_color;
    this->rotation_speed = rotation_speed;
}

void Star::Draw(int first) const
{
    glUniform4f((GLint) this->color_bind, (GLfloat)obj_color.x, (GLfloat)obj_color.y, (GLfloat)obj_color.z, 1);
    glDrawArrays(GL_LINE_STRIP, first, length);
    glUniform4f((GLint) this->color_bind, (GLfloat)scenario_color.x, (GLfloat)scenario_color.y, (GLfloat)scenario_color.z, 1);
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