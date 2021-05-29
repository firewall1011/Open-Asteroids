#define GLFW_INCLUDE_NONE

#include"object.h"
#include<GLFW/glfw3.h>
#include"tvector.h"
#include<gl/glew.h>


class Player : public Object {
    GLFWwindow* window;
    int scr_width, scr_height;
public:
    Player(GLFWwindow* w);

    virtual void Draw(int first) const;

    virtual bool Collision(vec2 point) const;

    virtual void Update(float delta_time);

};