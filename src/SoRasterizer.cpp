#include "raylib.h"
#include "SoRasterizer.h"
#include "SoTransform.h"
#include "SoMath.h"
namespace SoRendering
{

	SoRasterizer::SoRasterizer(): screenWidth(1600), screenHeight(900), colorBuffer(1600, 900, SoVector3f::Zero())
	{
	}

	SoRasterizer::SoRasterizer(int width, int height): screenWidth(width), screenHeight(height), colorBuffer(width, height, SoVector3f::Zero())
	{
	}

	void SoRasterizer::Init()
	{
		InitWindow(screenWidth, screenHeight, "SoRendering");
		SetTargetFPS(60);
	}

	void SoRasterizer::UpdateFrameBuffer(const SoCamera& camera)
	{
		//hard coded transform
		SoTransform transform;

		transform.SetPosition(SoVector3f(60.f, 0.f, -30.f));

		transform.SetRotation(SoMath::GetQuaternionFromEulerAngle
		(SoRendering::SoVector3f(
			SoRendering::SO_DEG2RAD * 0.f,
			SoRendering::SO_DEG2RAD * 0.f,
			SoRendering::SO_DEG2RAD * 45.f)));

		//transform.SetScale(SoVector3f(0.5f, 2.f, 1.f));
		//End of hard coded transform

		colorBuffer.Clear();

		const SoMatrix4f modelMatrix = transform.GetMatrix();
		const SoMatrix4f viewMatrix = camera.GetViewMatrix();
		const SoMatrix4f projectMatrix = camera.GetProjectMatrix();

		SoMatrix4f mvp = projectMatrix * viewMatrix * modelMatrix;

		for(SoTriangle& tri: triangleLst)
		{
			SoTriangle transformedTri;
			for(int i = 0; i < 3; ++i)
			{
				SoVector4f& v = transformedTri.vertex[i];
				v = mvp * tri.vertex[i];
				v.x() = v.x() / v.w();
				v.y() = v.y() / v.w();
				v.z() = v.z() / v.w();
				v.x() = 0.5f * (float)screenWidth * (v.x() + 1.0f);
				v.y() = 0.5f * (float)screenHeight * (v.y() + 1.0f);
			}
			RasterizeTriangle(transformedTri);
		}
	}

	void SoRasterizer::RasterizeTriangle(const SoTriangle& tri)
	{
		float xmin = std::numeric_limits<float>::max();
		float xmax = std::numeric_limits<float>::min();
		float ymin = std::numeric_limits<float>::max();
		float ymax = std::numeric_limits<float>::min();
		for(const SoVector4f& v: tri.vertex)
		{
			if (v.x() < xmin)
				xmin = std::max(0.f, v.x());
			if (v.x() > xmax)
				xmax = std::min((float)screenWidth, v.x());
			if (v.y() < ymin)
				ymin = std::max(0.f , v.y());
			if (v.y() > ymax)
				ymax = std::min((float)screenHeight, v.y());
		}
		for(int i = (int)xmin; i < (int)xmax; ++i)
		{
			for(int j = (int)ymin; j < (int)ymax; ++j)
			{
				if(SoTriangle::IsPointInside(SoVector3f(i, j, 1.f), tri))
				{
					colorBuffer.SetValueAtPos(i, j, SoVector3f(255.f, 0.f, 0.f));
				}
			}
		}
	}


	void SoRasterizer::DrawFrame()
	{
		BeginDrawing();
		for(int i = 0; i < screenHeight; ++i)
		{
			for(int j = 0; j < screenWidth; ++j)
			{
				const SoVector3f& colorV = colorBuffer.GetValueAtPos(j, i);

				Color color;
				color.r = (char)colorV[0];
				color.g = (char)colorV[1];
				color.b = (char)colorV[2];
				color.a = 255;
				DrawPixel(j, screenHeight - 1 - i, color); // IN Raylib, coordinate (0,0) begins from the top left corner
			}
		}
		EndDrawing();
	}

	



}
