#include "mat4.h"
#include "tvector.h"
#include "Object.h"

using namespace TLibrary;

void Object::Rotate(float degrees) 
{
    rotation += degrees;
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