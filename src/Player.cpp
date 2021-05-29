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
    vertices = CriarCirculo(16,0.125f/2);
    length = 16;
}

void Player::Draw(int first) const {
    glDrawArrays(GL_TRIANGLE_FAN, first, 16);
}

bool Player::Collision(vec2 point) const {
    return true;
}

void Player::Update(float delta_time) {
    double xpos = 0, ypos = 0;
    glfwGetCursorPos(window, &xpos, &ypos);
  
    //coordinate transformation
    xpos = 2 * (xpos/scr_width) - 1;
    ypos = 1 - 2 * (ypos/scr_height);

    vec2 look_dir = (vec2((float) xpos, (float) ypos) - center).normalized();
    vec2 x_dir = vec2(1.0f, 0.0f);
    float cos = look_dir.x * x_dir.x + look_dir.y*x_dir.y;
    float sin = look_dir.x * x_dir.y - look_dir.y * x_dir.x;
    
    std::cout << -(atan2(sin, cos)) * 180/T_PI  << std::endl;

    position = { (float)xpos, (float)ypos };
}
