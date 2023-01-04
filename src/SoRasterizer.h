#pragma once

#include <SoCamera.h>
#include <SoFrameBuffer.h>
#include <SoTriangle.h>

namespace SoRendering
{
	class SoRasterizer
	{
	public:
		SoRasterizer();
		SoRasterizer(int width, int height);

		void Init();
		void UpdateFrameBuffer(const SoCamera& camera);
		void DrawFrame();

		std::vector<SoTriangle>& GetTriangleLst() { return triangleLst; }

	private:
		void RasterizeTriangle(const SoTriangle& tri);

		SoFrameBuffer<SoVector3f> colorBuffer;
		int screenWidth;
		int screenHeight;
		std::vector<SoTriangle> triangleLst;
	};
}
