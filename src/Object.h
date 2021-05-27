#pragma once
#include "mat4.h"
#include "tvector.h"
#include "Shader.h"

using namespace TLibrary;

class Object {
public:
    vec2 center;
    vec2* vertices;
    int length;

    float rotation;
    vec2 position;
    vec2 scale; 

    Object() : center(vec2()), vertices(nullptr), length(0), scale(1,1), rotation(0){}
    ~Object();
    virtual void Draw(int first) const = 0;
    virtual bool Collision(vec2 point) const = 0;
    virtual void Update(float delta_time) = 0;

    void Rotate(float degrees);
    void Move(vec2 translation);
    void Scale(vec2 value);
    mat4 Transform();
};