#include "mat3.h"

namespace TLibrary {

	float mat3::GetElementAt(unsigned int i, unsigned int j) const
	{
		return m[i * 3 + j];
	}

	float* mat3::At(unsigned int i, unsigned int j)
	{
		return &m[i * 3 + j];
	}

	mat3 mat3::operator*(const mat3& other) const
	{
		mat3 result;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					*result.At(i, j) += GetElementAt(i, k) * other.GetElementAt(k, j);
				}
			}
		}
		return result;
	}

	mat3 mat3::Identity()
	{
		return mat3
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
		};
	}

	mat3 mat3::translate(const vec2& v)
	{
		return
		{
			1.0f, 0.0f, v.x,
			0.0f, 1.0f, v.y,
			0.0f, 0.0f, 1.0f,
		};
	}

	mat3 mat3::rotate(float angle)
	{
		return
		{
			cosf(angle), -sinf(angle), 0.0f,
			sinf(angle),  cosf(angle), 0.0f,
				   0.0f,	 	 0.0f, 1.0f,
		};
	}

	mat3 mat3::scale(float s)
	{
		return mat3
		{
			   s, 0.0f, 0.0f,
			0.0f,    s, 0.0f,
			0.0f, 0.0f, 1.0f,
		};
	}

	mat3 mat3::scale(const vec2& s)
	{
		return mat3
		{
			s.x,  0.0f, 0.0f,
			0.0f,  s.y, 0.0f,
			0.0f, 0.0f, 1.0f,
		};
	}

	std::ostream& operator<<(std::ostream& os, const mat3& m) 
	{

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++)
				os << m.GetElementAt(i, j) << ", ";
			os << m.GetElementAt(i, 2) << std::endl;
		}
		return os;
	}
}