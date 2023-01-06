#include "SoTriangle.h"

namespace SoRendering
{
	bool SoTriangle::IsPointInside(const SoVector3f& point, bool cullingBack) const
	{
		SoVector3f pointWithoutZ(point.x(), point.y(), 1.f);
		SoVector3f flattenTriVertices[3];
		for (int i = 0; i < 3; ++i)
		{
			flattenTriVertices[i] = SoVector3f(vertex[i].x(), vertex[i].y(), 1.f);
		}
		float c1 = (flattenTriVertices[1] - flattenTriVertices[0]).cross(pointWithoutZ - flattenTriVertices[0]).dot(SoVector3f::UnitZ());
		float c2 = (flattenTriVertices[2] - flattenTriVertices[1]).cross(pointWithoutZ - flattenTriVertices[1]).dot(SoVector3f::UnitZ());
		float c3 = (flattenTriVertices[0] - flattenTriVertices[2]).cross(pointWithoutZ - flattenTriVertices[2]).dot(SoVector3f::UnitZ());

		return cullingBack ? (c1 > 0 && c2 > 0 && c3 > 0) : (c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0);
	}

	SoVector3f SoTriangle::GetBarycentricCoord(const SoVector3f& point) const
	{
		SoVector3f a = vertex[0].head<3>();
		SoVector3f b = vertex[1].head<3>();
		SoVector3f c = vertex[2].head<3>();

		float area = ((b - a).cross(c - a)).norm() / 2.f;

		float w = ((point - b).cross(c - b)).norm() / 2.f / area;
		float u = ((point - c).cross(a - c)).norm() / 2.f / area;
		float v = ((point - a).cross(b - a)).norm() / 2.f / area;

		return { w, u, v };
	}


}
