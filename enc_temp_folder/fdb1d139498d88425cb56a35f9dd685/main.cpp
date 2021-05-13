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

float rotation = 0.0f;

int main(void) {

    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(600, 600, "Minha Janela", NULL, NULL);

    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

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

    std::cout << loc_position << loc_transform << loc_color;

    glEnableVertexAttribArray(loc_position);
    glVertexAttribPointer(loc_position, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    // Exibindo nossa janela
    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window))
    {
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

        glfwSwapBuffers(window);

#ifdef DEBUG
        while (int error = glGetError() != GL_NO_ERROR)
        {
            std::cout << "GlErrorFlag: " << error << std::endl;
        }
#endif // DEBUG

    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}