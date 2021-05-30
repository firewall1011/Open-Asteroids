#pragma once
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>  
#include <vector>
#include "Object.h"

class BufferData {
	unsigned int bufferId;
public:
	std::vector<Object*> data;

	void Draw(Shader& shader, GLuint matrix) 
	{
		shader.Bind();
		int offset = 0;
		for (Object*& obj : data)
		{
			glUniformMatrix4fv(matrix, 1, GL_TRUE, obj->Transform().m);
			obj->Draw(offset);
			offset += obj->length;
		}
	}

	void Update(float delta_time)
	{
		int offset = 0;
		for (Object*& obj : data)
		{
			obj->Update(delta_time);
			offset += obj->length;
		}
	}

	void SendToGPU() {

		int size = 0;
		for(Object*& obj : data) 
		{
			size += obj->length;
		}

		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * size, nullptr, GL_STATIC_DRAW);

		int offset = 0;
		for (Object*& obj : data) 
		{
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec2) * offset, sizeof(vec2) * obj->length, obj->vertices);
			offset += obj->length;
		}
	}

	~BufferData() 
	{
		for (auto& o : data)
			o->~Object();
	}
};