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
    vec2 up;

    bool isActive = true;

    Object() : center(vec2()), vertices(nullptr), length(0), scale(1, 1), rotation(0), up({ 0,1 }) {}
    ~Object();
    virtual void Draw(int first, Shader& shader) const = 0;
    virtual bool Collision(vec2 point, float radius) const = 0;
    virtual void Update(float delta_time) = 0;

    void Rotate(float degrees);
    void LookAt(vec2 point);
    void Move(vec2 translation);
    void ScaleRelative(vec2 value);
    void SetScale(vec2 value);
    mat4 Transform();
};