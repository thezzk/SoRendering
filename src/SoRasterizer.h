#pragma once

#include <SoCamera.h>
#include <SoFrameBuffer.h>
#include <SoTriangle.h>

namespace SoRendering
{
	class SoRasterizer
	{
	public:
		enum RASTERIZER_MODE
		{
			RASTERIZER_MODE_COLOR,
			RASTERIZER_MODE_WIRE,
			RASTERIZER_MODE_TEXTURE
		};


		SoRasterizer();
		SoRasterizer(int width, int height, RASTERIZER_MODE rasterizerMode);

		void Init();
		void UpdateFrameBuffer(const SoCamera& camera);
		void DrawFrame();
		void DrawLine(SoVector2i from, SoVector2i to, SoVector3f color);
		template <typename T>
		void DrawPoint(SoFrameBuffer<T>& targetBuffer, SoVector2i pos, const T& pixel){ targetBuffer.SetValueAtPos(pos.x(), pos.y(), pixel); }

		std::vector<SoTriangle>& GetTriangleLst() { return triangleLst; }

	private:
		void RasterizeTriangle(const SoTriangle& tri);
		void RasterizeTriangleColorMode(const SoTriangle& tri);
		void RasterizeTriangleWireMode(const SoTriangle& tri);

		RASTERIZER_MODE rasterizerMode;
		SoFrameBuffer<SoVector3f> colorBuffer;
		SoFrameBuffer<float> zBuffer;
		int screenWidth;
		int screenHeight;
		std::vector<SoTriangle> triangleLst;
	};
}
