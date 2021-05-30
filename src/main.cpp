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
#include "Shader.h"
#include "tvector.h"
#include "mat4.h"
#include "Asteroid.h"
#include "BufferData.h"
#include "Player.h"
#include "AsteroidsGenerator.h"

using namespace std::chrono_literals;
using namespace std::chrono;
using namespace TLibrary;

#define FPS 144
#define MS_FTIME 1000ms/FPS

float rotation = 0.0f;

GLFWwindow* create_window(int width, int height, const char* name) {
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);

    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    return window;
}

void close_window(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main(void) {

    GLFWwindow* window = create_window(720, 720, "Asteroids");

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s\n", glewGetErrorString(GlewInitResult));

    TLibrary::Shader shader("color.shader");

    /*vec2 triangle[3] = {
        {-0.2f, -0.2f },
        {0.2f, -0.2f},
        {0.0f, 0.5f}
    };*/

    //vec2 centro = (triangle[0] + triangle[1] + triangle[2])/3;
    {
        BufferData bufferData;

        AsteroidsGenerator asteroidsGenerator = AsteroidsGenerator(&bufferData, 0.03f, 0.08f, 50, 100, 0.001f, 0.003f, 2.0f);
        srand(time(NULL));
        asteroidsGenerator.CreateAsteroids(10);
       
        Player* player = new Player(window);
        
        bufferData.data.push_back(player);

        bufferData.SendToGPU();
        /*GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * asteroid.length, asteroid.vertices, GL_STATIC_DRAW);*/

        // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
        GLint loc_position = glGetAttribLocation(shader.GetID(), "position");
        GLint loc_transform = glGetUniformLocation(shader.GetID(), "transformation_matrix");
        GLint loc_color = glGetUniformLocation(shader.GetID(), "color");

        glEnableVertexAttribArray(loc_position);
        glVertexAttribPointer(loc_position, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

        // Exibindo nossa janela
        glfwShowWindow(window);

        while (!glfwWindowShouldClose(window))
        {
            auto start = steady_clock::now();
            glfwPollEvents();

            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            // Transforma e desenha cilindro
            glUniform4f(loc_color, 1, 0, 0, 1);
            
            bufferData.Update(10);

            bufferData.Draw(shader, loc_transform);

            std::this_thread::sleep_for(start + MS_FTIME - steady_clock::now());

            glfwSwapBuffers(window);
            
#ifdef DEBUG
            while (int error = glGetError() != GL_NO_ERROR)
            {
                std::cout << "GlErrorFlag: " << error << std::endl;
            }
#endif // DEBUG

        }

        close_window(window);
    }

    return EXIT_SUCCESS;
}