#define GLFW_INCLUDE_NONE

#include"player.h"
#include"object.h"
#include<GLFW/glfw3.h>
#include"tvector.h"
#include<gl/glew.h>

Player::Player(GLFWwindow* w) : Object()
{
    window = w;
    glfwGetWindowSize(window, &scr_width, &scr_height);
    
    vertices = CriarTrianguloIsosceles(0.9f, center);
    length = 3;

    SetScale(vec2(0.05f, 0.05f));
}

void Player::Draw(int first) const {
    glDrawArrays(GL_LINE_LOOP, first, length);
}

bool Player::Collision(vec2 point, float radius) const {
    return true;
}

void Player::Update(float delta_time) {
    double xpos = 0, ypos = 0;
    glfwGetCursorPos(window, &xpos, &ypos);
  
    //coordinate transformation
    xpos = 2 * (xpos/scr_width) - 1;
    ypos = 1 - 2 * (ypos/scr_height);

    vec2 look_point = vec2((float)xpos, (float)ypos);

    LookAt(look_point);
}
