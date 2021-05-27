#include "mat4.h"
#include "tvector.h"
#include "Shader.h"

using namespace TLibrary;

class Object
{
public:
    vec2 center;
    vec2* vertices;
    int length;

    float rotation;
    vec2 position;
    vec2 scale; 
    
    unsigned int buffer;

    Object() : center(vec2()), vertices(nullptr), length(0), scale(1,1), rotation(0), buffer(0){}

    virtual void Draw() const = 0;
    virtual bool Collision(vec2 point) const = 0;
    virtual void Update(float delta_time) = 0;

    void Rotate(float degrees);
    void Move(vec2 translation);
    void Scale(vec2 value);
    mat4 Transform();
};