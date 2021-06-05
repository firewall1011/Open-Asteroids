#define GLFW_INCLUDE_NONE

#include<GLFW/glfw3.h>
#include<gl/glew.h>

#include"tvector.h"
#include"Object.h"
#include"Player.h"
#include "BulletFireSystem.h"

vec2* CreatePlayerCharacter(int& length)
{
    vec2* vertices = new vec2[]
    {
        //#begin lineloop
        vec2(-0.194f,-0.974f), //A
        vec2(0.2026f, - 0.972f), //B
        vec2(0.316f, -0.808f), //C
        vec2(0.46f, -0.682f), // D
        vec2(0.8f, -0.6f), //E
        vec2(0.4f, -0.4f), //F
        vec2(0.2f, -0.2f), //G
        vec2(0.0f, 0.2f), // H
        vec2(-0.2f, -0.2f), // N
        vec2(-0.4f, -0.4f), // M
        vec2(-0.8f, -0.6f), // L
        vec2(-0.465f, -0.681f), // K
        vec2(-0.326f, -0.804f), // J
        //#end lineloop
        //#begin linestrip
        vec2(-0.4f, -0.4f), // M
        vec2(0.0f, 1.0f), // I
        vec2(0.4f, -0.4f), //F
        //#end linestrip
    };
    
    length = 16;

    return vertices;
}

Player::Player(GLFWwindow* w, float fireSpeed) : Object(), timer(1/fireSpeed)
{
    window = w;
    glfwGetWindowSize(window, &scr_width, &scr_height);
    vertices = CreatePlayerCharacter(length);

    SetScale(vec2(0.05f, 0.05f));
}

void Player::Draw(int first, Shader& shader) const
{
    shader.SetColor(vec3(0, 0, 0));
    glDrawArrays(GL_TRIANGLE_FAN, first, 13);
    glDrawArrays(GL_TRIANGLES, first + 13, 3);
    shader.SetColor(vec3(1, 0.219f, 0.392f));
    glDrawArrays(GL_LINE_LOOP, first, 13);
    glDrawArrays(GL_LINE_STRIP, first + 13, 3);
}

// Not implemented
bool Player::Collision(vec2 point, float radius) const {
    return false;
}

void Player::Update(float delta_time) {
    CalculateLookPoint();
    ProcessInput();
    if (timer.Tick(delta_time)) 
        canShoot = true;
}

void Player::CalculateLookPoint() 
{
    double xpos = 0, ypos = 0;
    glfwGetCursorPos(window, &xpos, &ypos);
  
    //coordinate transformation
    xpos = 2 * (xpos/scr_width) - 1;
    ypos = 1 - 2 * (ypos/scr_height);

    vec2 look_point = vec2((float)xpos, (float)ypos);

    LookAt(look_point);
}

void Player::ProcessInput() 
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        Shoot();
    }
}

void Player::Shoot() 
{
    if (canShoot) 
    {
        BulletFireSystem::SpawnBullet(this);
        canShoot = false;
        timer.Reset();
    }
}