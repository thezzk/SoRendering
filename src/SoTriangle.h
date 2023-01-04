#pragma once

#include "SoConstant.h"

namespace SoRendering
{
	struct SoTriangle
	{
		SoVector4f vertex[3];
		SoVector3f color[3];


		static bool IsPointInside(const SoVector3f& point, const SoTriangle& tri)
		{
			SoVector3f pointWithoutZ(point.x(), point.y(), 1.f);
			SoVector3f flattenTriVertices[3];
			for (int i = 0; i < 3; ++i)
			{
				flattenTriVertices[i] = SoVector3f(tri.vertex[i].x(), tri.vertex[i].y(), 1.f);
			}
			float c1 = (flattenTriVertices[1] - flattenTriVertices[0]).cross(pointWithoutZ - flattenTriVertices[0]).dot(SoVector3f::UnitZ());
			float c2 = (flattenTriVertices[2] - flattenTriVertices[1]).cross(pointWithoutZ - flattenTriVertices[1]).dot(SoVector3f::UnitZ());
			float c3 = (flattenTriVertices[0] - flattenTriVertices[2]).cross(pointWithoutZ - flattenTriVertices[2]).dot(SoVector3f::UnitZ());

			return (c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0);
		}

	};
}
