#pragma once
#include "tvector.h"

using namespace TLibrary;

namespace Collisions 
{
	inline bool CircleWithCircle(vec2 point1, vec2 point2, float radius1, float radius2)
	{
		return (point1 - point2).magnitude() <= radius1 + radius2;
	}
}