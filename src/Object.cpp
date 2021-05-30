#include "mat4.h"
#include "tvector.h"
#include "Object.h"

using namespace TLibrary;

vec2 RotateVec(vec2 v, float rad) {
    return { (cos(rad) * v.x - sin(rad) * v.y), (sin(rad) * v.x + cos(rad) * v.y)};
}

void Object::Rotate(float degrees) 
{
    up = RotateVec(up, degrees * T_PI / 180);
    rotation += degrees;
}

void Object::LookAt(vec2 point) {
    vec2 look_dir = (vec2((float)point.x, (float)point.y)).normalized();
    
    float cos = look_dir.x * up.x + look_dir.y * up.y;
    float sin = look_dir.x * up.y - look_dir.y * up.x;

    float rotate_deg = -(atan2(sin, cos)) * 180 / T_PI;
    
    up = RotateVec(up, rotate_deg * T_PI / 180);
    
    rotation += rotate_deg * T_PI / 180;
}

void Object::Move(vec2 translation)
{
    position += translation;
}

void Object::Scale(vec2 value)
{
    scale += value;
}

mat4 Object::Transform()
{
    
    return mat4::scale(scale) * mat4::translate(center) * mat4::rotate2D(rotation) * mat4::translate(-center) * mat4::translate(position);
}

Object::~Object() 
{
    delete[] vertices;
    vertices = nullptr;
}