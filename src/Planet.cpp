#include "Planet.h"
#include <GL/glew.h> 

vec2* PlanetVertices(int num_vertices, const vec2& centro);

Planet::Planet(int num_vertices, const vec2& center, int color_bind, vec3 scenario_color, vec3 obj_color, float rotation_speed)
{
    vertices = PlanetVertices(num_vertices, center);
    length = num_vertices;
    this->center = center;
    this->color_bind = color_bind;
    this->scenario_color = scenario_color;
    this->obj_color = obj_color;
    this->rotation_speed = rotation_speed;
}

void Planet::Draw(int first) const
{
    glUniform4f((GLint) this->color_bind, (GLfloat)obj_color.x, (GLfloat)obj_color.y, (GLfloat)obj_color.z, 1);
    glDrawArrays(GL_LINE_LOOP, first, length/2);
    glDrawArrays(GL_POINTS, first + length/2 , length / 2);
    glUniform4f((GLint) this->color_bind, (GLfloat)scenario_color.x, (GLfloat)scenario_color.y, (GLfloat)scenario_color.z, 1);
}

bool Planet::Collision(vec2 point, float radius) const
{
	return false;
}

void Planet::Update(float delta_time)
{
    Rotate(rotation_speed * delta_time);
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