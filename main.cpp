#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>  
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "tvector.h"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;
using namespace std::chrono;

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

    GLFWwindow* window = create_window(600, 600, "Hoje");

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s\n", glewGetErrorString(GlewInitResult));

    TLibrary::Shader shader("color.shader");

    vec2 triangle[3] = { 
        { -0.50f, -0.50f },
        { +0.50f, -0.50f },
	    { +1.00f, -1.00f },
    };

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), &triangle, GL_STATIC_DRAW);

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

        glPolygonMode(GL_POLYGON_MODE, GL_LINE);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        //rotation = T_PI/4;
        rotation += 0.001f;
        float cosx = cosf(rotation);
        float sinx = sinf(rotation);

        float transform_rotation[16] = {
                1.0f, 0.0f,  0.0f, 0.0f,
                0.0f, 1.0f, 0.0f , 0.0f,
                0.0f, 0.0f,  1.0f, 0.0f,
                0.0f, 0.0f,  0.0f, 1.0f
        };

        // Transforma e desenha cilindro
        shader.Bind();
        glUniformMatrix4fv(loc_transform, 1, GL_TRUE, transform_rotation);



        glUniform4f(loc_color, 0, 1, 0, 1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
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

    return EXIT_SUCCESS;
}