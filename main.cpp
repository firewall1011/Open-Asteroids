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
#include <thread>
#include <chrono>

using namespace std::chrono_literals;
using namespace std::chrono;

#define FPS 144
#define MS_FTIME 1000ms/FPS

int main(void) {

    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(600, 600, "Loja Radical de Spinner", NULL, NULL);

    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s\n", glewGetErrorString(GlewInitResult));

    TLibrary::Shader my_shader("color.shader");

    vec2 triangle[] = { (0.5f,0.0f), (-0.5f,0.0f), (0.0f, 0.5f) };
    GLuint buffer_idx;
    
    glGenBuffers(1, &buffer_idx);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_idx);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    GLuint program = my_shader.GetID();

    GLuint loc_position = glGetAttribLocation(program, "position");
    GLuint loc_color = glGetUniformLocation(program, "color");

    //linkamos/bindamos o vetor de vertices na gpu
    glEnableVertexAttribArray(loc_position);
    glVertexAttribPointer(loc_position, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    my_shader.Bind();

    // Exibindo nossa janela
    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window))
    {
        auto start = steady_clock::now();
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        
        glUniform4f(loc_color, 0.0, 0.0, 1.0, 1.0); //BLUE
        glDrawArrays(GL_TRIANGLES, 0, 3);


#ifdef DEBUG
        while (int error = glGetError() != GL_NO_ERROR)
        {
            std::cout << "GlErrorFlag: " << error << std::endl;
        }
#endif
        std::this_thread::sleep_for(start + MS_FTIME - steady_clock::now());
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}