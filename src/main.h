#pragma once
// System Libs
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>  
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>

// Math / Utils
#include "Shader.h"
#include "tvector.h"
#include "mat4.h"
#include "Random.h"

// Objects
#include "Asteroid.h"

// Systems
#include "BufferData.h"
#include "AsteroidsGenerator.h"
#include "BulletFireSystem.h"
#include "AsteroidPoolingSystem.h"

// Window
GLFWwindow* create_window(int width, int height, const char* name);
void close_window(GLFWwindow* window);

// Collisions
void CheckCollisionWithPlayer(Player* player, bool& game_is_running);
void CheckBulletToAsteroidCollision(int& points);
