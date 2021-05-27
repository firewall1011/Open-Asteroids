#pragma once
#include "tvector.h"

namespace TLibrary {

	struct mat3 {
		float m[9] = { 0.0f };

		float GetElementAt(unsigned int i, unsigned int j) const;
		float* At(unsigned int i, unsigned int j);
		mat3 operator*(const mat3& other) const;

		static mat3 Identity();
		static mat3 translate(const vec2&);
		static mat3 rotate(float);
		static mat3 scale(float);
		static mat3 scale(const vec2&);
	};

	std::ostream& operator<<(std::ostream& os, const mat3& m);
}