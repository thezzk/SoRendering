#pragma once

#include "SoConstant.h"

namespace SoRendering
{
	struct SoTriangle
	{
		SoVector4f vertex[3];
		SoVector3f color[3];



		SoTriangle()
		{
			for(int i = 0; i < 3; ++i)
			{
				color[i] = SoVector3f(255.f, 0, 0);
			}
		}

		

		bool IsPointInside(const SoVector3f& point, bool cullingBack = true) const;
		SoVector3f GetBarycentricCoord(const SoVector3f& point) const;

		template<typename T> static T InterploateWithBarycentricCoord(const T& v0, const T& v1, const T& v2, const SoVector3f& barycentricCoord)
		{
			return v0 * barycentricCoord[0] + v1 * barycentricCoord[1] + v2 * barycentricCoord[2];
		}

	};
}
