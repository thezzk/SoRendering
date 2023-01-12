#pragma once

#include "SoCamera.h"
#include "SoFrameBuffer.h"
#include "SoTriangle.h"
#include "SoPointLight.h"

namespace SoRendering
{
	class SoRasterizer
	{
	public:
		enum RASTERIZER_MODE
		{
			RASTERIZER_MODE_COLOR,
			RASTERIZER_MODE_WIRE,
			RASTERIZER_MODE_TEXTURE,
			RASTERIZER_MODE_PHONG,
			RASTERIZER_MODE_COUNT
		};


		SoRasterizer();
		SoRasterizer(int width, int height, RASTERIZER_MODE rasterizerMode);

		void Init();
		void UpdateFrameBuffer(const SoCamera& camera);
		void DrawFrame();
		void DrawLine(const SoVector2i& from, const SoVector2i& to, const SoColor& color);
		template <typename T>
		void DrawPoint(SoFrameBuffer<T>& targetBuffer, const SoVector2i& pos, const T& pixel){ targetBuffer.SetValueAtPos(pos.x(), pos.y(), pixel); }

		std::vector<SoTriangle>& GetTriangleLst() { return triangleLst; }

		void SetTexture(const SoTexture& texture) { this->texture = texture; };
		void SetRasterizerMode(RASTERIZER_MODE mode) { rasterizerMode = mode; };
	private:
		void RasterizeTriangle(const SoTriangle& tri, const SoTexture& texture, const SoVector3f viewPos[3], const SoVector3f& normal);
		void RasterizeTriangleColorMode(const SoTriangle& tri);
		void RasterizeTriangleWireMode(const SoTriangle& tri);
		void RasterizeTriangleTextureMode(const SoTriangle& tri, const SoTexture& texture);
		void RasterizeTrianglePhongMode(const SoTriangle& tri, const SoTexture& texture,
			const SoVector3f viewPos[3], const SoVector3f& normal);


		RASTERIZER_MODE rasterizerMode;
		SoFrameBuffer<SoColor> colorBuffer;
		SoFrameBuffer<float> zBuffer;
		int screenWidth;
		int screenHeight;
		std::vector<SoTriangle> triangleLst;
		SoTexture texture;
	};
}
