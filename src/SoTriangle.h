#pragma once

#include "SoConstant.h"
#include  "SoTexture.h"
namespace SoRendering
{
	struct SoTriangle
	{
		SoVector4f vertex[3];
		SoColor color[3];
		SoVector2f textureCoord[3];

		SoTriangle()
		{
			for(int i = 0; i < 3; ++i)
			{
				color[i] = SO_PRESET_COLOR_RED;
			}
		}


		bool IsPointInside(const SoVector3f& point, bool cullingBack = true) const;
		SoVector3f GetBarycentricCoord(const SoVector3f& point) const;
		SoVector3f GetBarycentricCoord2D(const SoVector2f& point) const;

		template<typename T, typename S = typename T::Scalar>
		static T InterploateWithBarycentricCoord(const T& v0, const T& v1, const T& v2, const SoVector3f& barycentricCoord)
		{
			return (v0.cast<float>() * barycentricCoord[0] + v1.cast<float>() * barycentricCoord[1] + v2.cast<float>() * barycentricCoord[2]).cast<S>();
		}

	};
}
