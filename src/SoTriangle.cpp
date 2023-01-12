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
		SoVector3f f0 = flattenTriVertices[1].cross(flattenTriVertices[0]);
		SoVector3f f1 = flattenTriVertices[2].cross(flattenTriVertices[1]);
		SoVector3f f2 = flattenTriVertices[0].cross(flattenTriVertices[2]);

		if ((pointWithoutZ.dot(f0) * f0.dot(flattenTriVertices[2]) > 0)
			&& (pointWithoutZ.dot(f1) * f1.dot(flattenTriVertices[0]) > 0)
			&& (pointWithoutZ.dot(f2) * f2.dot(flattenTriVertices[1]) > 0))
			return true;
		return false;
	}

	SoVector3f SoTriangle::GetBarycentricCoord2D(const SoVector2f& point) const
	{
		float c1 = (point.x() * (vertex[1].y() - vertex[2].y()) + (vertex[2].x() - vertex[1].x()) * point.y() + vertex[1].x() * vertex[2].y() - vertex[2].x() * vertex[1].y()) / (vertex[0].x() * (vertex[1].y() - vertex[2].y()) + (vertex[2].x() - vertex[1].x()) * vertex[0].y() + vertex[1].x() * vertex[2].y() - vertex[2].x() * vertex[1].y());
		float c2 = (point.x() * (vertex[2].y() - vertex[0].y()) + (vertex[0].x() - vertex[2].x()) * point.y() + vertex[2].x() * vertex[0].y() - vertex[0].x() * vertex[2].y()) / (vertex[1].x() * (vertex[2].y() - vertex[0].y()) + (vertex[0].x() - vertex[2].x()) * vertex[1].y() + vertex[2].x() * vertex[0].y() - vertex[0].x() * vertex[2].y());
		float c3 = (point.x() * (vertex[0].y() - vertex[1].y()) + (vertex[1].x() - vertex[0].x()) * point.y() + vertex[0].x() * vertex[1].y() - vertex[1].x() * vertex[0].y()) / (vertex[2].x() * (vertex[0].y() - vertex[1].y()) + (vertex[1].x() - vertex[0].x()) * vertex[2].y() + vertex[0].x() * vertex[1].y() - vertex[1].x() * vertex[0].y());
		return SoVector3f(c1,c2,c3);
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
