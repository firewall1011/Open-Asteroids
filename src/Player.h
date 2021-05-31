#pragma once
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<gl/glew.h>

#include"Object.h"
#include"tvector.h"
#include "Timer.h"


class Player : public Object {
    GLFWwindow* window;
    int scr_width, scr_height;
    bool canShoot = true;
    Timer timer;
public:
    Player(GLFWwindow* w);

    virtual void Draw(int first) const;

    virtual bool Collision(vec2 point, float radius) const;

    virtual void Update(float delta_time);
private:
    void CalculateLookPoint();
    void ProcessInput();
    void Shoot();
};