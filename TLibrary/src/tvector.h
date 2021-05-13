#pragma once
#include <iostream>
#define T_PI 3.14159f

struct vec2
{
    float x, y;

    vec2 normalized();
    float magnitude();
    vec2 operator*(float);
    void operator+=(const vec2&);
};

struct vec3 
{
    float x, y, z;

    vec3 normalized();
    float magnitude();
    vec3 operator*(const float);
    void operator+=(const vec3&);
};

std::ostream& operator<<(std::ostream& os, const vec3& v);


vec2* CriarCirculo(int num_vertices = 8, float raio = 1.0, const vec2& centro = { 0,0 }, float angulo_inicial = 0.0, float angulo_final = 2 * T_PI);
vec2* CriarQuadrado(float largura, const vec2& centro);
vec2* CriarRetangulo(float largura, float altura, const vec2& centro);

vec3* CriarCilindro(const int num_vertices = 16, const float raio = 1.0, const float height = 1.0f, const vec3& base = { 0 });