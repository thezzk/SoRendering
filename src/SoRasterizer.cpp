#include "raylib.h"
#include "SoRasterizer.h"
#include "SoTransform.h"
#include "SoMath.h"

namespace SoRendering
{

	SoRasterizer::SoRasterizer(): screenWidth(800), screenHeight(450), colorBuffer(800, 450, SO_PRESET_COLOR_BLACK), zBuffer(800, 450, -std::numeric_limits<float>::max()), rasterizerMode(RASTERIZER_MODE_COLOR)
	{
	}

	SoRasterizer::SoRasterizer(int width, int height, RASTERIZER_MODE rasterizerMode): screenWidth(width), screenHeight(height),
	colorBuffer(width, height, SO_PRESET_COLOR_BLACK), zBuffer(width, height, -std::numeric_limits<float>::max()), rasterizerMode(rasterizerMode)
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

		transform.SetPosition(SoVector3f(0.f, 0.f, 0.f));
		static float degree = 270.0f;
		degree += 2.f;
		if(degree > 360.f)
		{
			degree = 0;
		}
		if(degree > 60.f && degree <180.f)
		{
			rasterizerMode = RASTERIZER_MODE_WIRE;
		}
		else if(degree > 180.f && degree < 300.f)
		{
			rasterizerMode = RASTERIZER_MODE_TEXTURE;
		}
		else
		{
			rasterizerMode = RASTERIZER_MODE_PHONG;
		}


		transform.SetRotation(SoMath::GetQuaternionFromEulerAngle
		(SoRendering::SoVector3f(
			SoRendering::SO_DEG2RAD * 0,
			SoRendering::SO_DEG2RAD * degree,
			SoRendering::SO_DEG2RAD * 0.f)));

		//transform.SetScale(SoVector3f(0.5f, 2.f, 1.f));

		//End of hard coded transform

		colorBuffer.Clear();
		zBuffer.Clear();
		const SoMatrix4f modelMatrix = transform.GetMatrix();
		const SoMatrix4f viewMatrix = camera.GetViewMatrix();
		const SoMatrix4f projectMatrix = camera.GetProjectMatrix();

		SoMatrix4f mvp = projectMatrix * viewMatrix * modelMatrix;
		SoMatrix4f mv  = viewMatrix * modelMatrix;


		for(SoTriangle& tri: triangleLst)
		{
			SoVector3f viewPos[3];

			SoTriangle transformedTri(tri);
			for(int i = 0; i < 3; ++i)
			{
				viewPos[i] = (mv * tri.vertex[i]).head<3>();

				SoVector4f& v = transformedTri.vertex[i];
				v = mvp * tri.vertex[i];
				v.x() = v.x() / v.w();
				v.y() = v.y() / v.w();
				v.z() = v.z() / v.w();
				v.w() = 1.f;
				v.x() = 0.5f * (float)screenWidth * (v.x() + 1.0f);
				v.y() = 0.5f * (float)screenHeight * (v.y() + 1.0f);
			}
			SoVector3f normal = (viewPos[1] - viewPos[0]).cross(viewPos[2] - viewPos[0]).normalized();

			RasterizeTriangle(transformedTri, texture, viewPos, normal);
		}
	}

	void SoRasterizer::RasterizeTriangle(const SoTriangle& tri, const SoTexture& texture, const SoVector3f viewPos[3], const SoVector3f& normal)
	{
		switch (rasterizerMode)
		{
		case RASTERIZER_MODE_COLOR:
			RasterizeTriangleColorMode(tri);
			break;
		case RASTERIZER_MODE_WIRE:
			RasterizeTriangleWireMode(tri);
			break;
		case RASTERIZER_MODE_TEXTURE:
			RasterizeTriangleTextureMode(tri, texture);
			break;
		case RASTERIZER_MODE_PHONG:
			RasterizeTrianglePhongMode(tri, texture, viewPos, normal);
			break;
		}
	}

	void SoRasterizer::RasterizeTriangleColorMode(const SoTriangle& tri)
	{
		float xmin = std::numeric_limits<float>::max();
		float xmax = 0;
		float ymin = std::numeric_limits<float>::max();
		float ymax = 0;
		for (const SoVector4f& v : tri.vertex)
		{
			if (v.x() < xmin)
				xmin = std::max(0.f, v.x());
			if (v.x() > xmax)
				xmax = std::min((float)(screenWidth - 1), v.x());
			if (v.y() < ymin)
				ymin = std::max(0.f, v.y());
			if (v.y() > ymax)
				ymax = std::min((float)(screenHeight - 1), v.y());
		}
		for (int i = (int)xmin; i <= (int)xmax; ++i)
		{
			for (int j = (int)ymin; j <= (int)ymax; ++j)
			{
				//Calculate sample point on the triangle surface
				SoVector3f samplePoint((float)i, (float)j, 1.f);
				if (tri.IsPointInside(samplePoint))
				{

					SoVector3f barycentricCoord = tri.GetBarycentricCoord2D(SoVector2f(samplePoint.x(), samplePoint.y()));
					float z = SoTriangle::InterploateWithBarycentricCoord(tri.vertex[0], tri.vertex[1], tri.vertex[2], barycentricCoord).z();

					const SoColor& color = SoTriangle::InterploateWithBarycentricCoord(tri.color[0], tri.color[1], tri.color[2], barycentricCoord);

					if (zBuffer.GetValueAtPos(i, j) < z)
					{
						DrawPoint<SoColor>(colorBuffer, SoVector2i(i, j), color);
						DrawPoint<float>(zBuffer, SoVector2i(i, j), z);
					}
				}
			}
		}
	}

	void SoRasterizer::RasterizeTriangleWireMode(const SoTriangle& tri)
	{
		for(int i = 0; i < 3; ++i)
		{
			int x0 = (int)tri.vertex[i].x();
			x0 = x0 >= screenWidth ? screenWidth - 1 : x0;
			x0 = x0 < 0 ? 0 : x0;
			int y0 = (int)tri.vertex[i].y();
			y0 = y0 >= screenHeight ? screenHeight - 1 : y0;
			y0 = y0 < 0 ? 0 : y0;
			int x1 = (int)tri.vertex[(i + 1)%3].x();
			x1 = x1 >= screenWidth ? screenWidth - 1 : x1;
			x1 = x1 < 0 ? 0 : x1;
			int y1 = (int)tri.vertex[(i + 1)%3].y();
			y1 = y1 >= screenHeight ? screenHeight - 1 : y1;
			y1 = y1 < 0 ? 0 : y1;

			DrawLine(SoVector2i(x0, y0), SoVector2i(x1, y1), tri.color[0]);
		}
	}

	// Bresenham's line algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	void SoRasterizer::DrawLine(const SoVector2i& from, const SoVector2i& to, const SoColor& color)
	{
		int x0 = from.x(), y0 = from.y(), x1 = to.x(), y1 = to.y();
		int dx = abs(x1 - x0);
		int sx = x0 < x1 ? 1 : -1;
		int dy = -abs(y1 - y0);
		int sy = y0 < y1 ? 1 : -1;
		int error = dx + dy;

		while (true)
		{
			DrawPoint<SoColor>(colorBuffer, SoVector2i(x0, y0), color);

			if (x0 == x1 && y0 == y1)
				break;
			int e2 = 2 * error;
			if (e2 >= dy)
			{
				if (x0 == x1)
					break;
				error = error + dy;
				x0 = x0 + sx;
			}
			if (e2 <= dx) 
			{
				if (y0 == y1)
					break;
				error = error + dx;
				y0 = y0 + sy;
			}
		}
	}


	void SoRasterizer::RasterizeTriangleTextureMode(const SoTriangle& tri, const SoTexture& texture)
	{
		float xmin = std::numeric_limits<float>::max();
		float xmax = std::numeric_limits<float>::min();
		float ymin = std::numeric_limits<float>::max();
		float ymax = std::numeric_limits<float>::min();
		for (const SoVector4f& v : tri.vertex)
		{
			if (v.x() < xmin)
				xmin = std::max(0.f, v.x());
			if (v.x() > xmax)
				xmax = std::min((float)screenWidth - 1.f, v.x());
			if (v.y() < ymin)
				ymin = std::max(0.f, v.y());
			if (v.y() > ymax)
				ymax = std::min((float)screenHeight - 1.f, v.y());
		}
		for (int i = (int)xmin; i <= (int)xmax; ++i)
		{
			for (int j = (int)ymin; j <= (int)ymax; ++j)
			{
				SoVector3f samplePoint((float)i, (float)j, 1.f);
				if (tri.IsPointInside(samplePoint))
				{

					SoVector3f barycentricCoord = tri.GetBarycentricCoord2D(SoVector2f(samplePoint.x(), samplePoint.y()));

					SoVector2f uv =
						SoTriangle::InterploateWithBarycentricCoord(tri.textureCoord[0], tri.textureCoord[1], tri.textureCoord[2], barycentricCoord);
					float z = SoTriangle::InterploateWithBarycentricCoord(tri.vertex[0], tri.vertex[1], tri.vertex[2], barycentricCoord).z();

					const SoColor color = texture.SampleByUV(uv);

					if (zBuffer.GetValueAtPos(i, j) < z)
					{
						DrawPoint<SoColor>(colorBuffer, SoVector2i(i, j), color);
						DrawPoint<float>(zBuffer, SoVector2i(i, j), z);
					}
				}
			}
		}
	}


	void SoRasterizer::RasterizeTrianglePhongMode(const SoTriangle& tri, const SoTexture& texture,  
		const SoVector3f viewPos[3], const SoVector3f& normal)
	{
		float xmin = std::numeric_limits<float>::max();
		float xmax = std::numeric_limits<float>::min();
		float ymin = std::numeric_limits<float>::max();
		float ymax = std::numeric_limits<float>::min();
		for (const SoVector4f& v : tri.vertex)
		{
			if (v.x() < xmin)
				xmin = std::max(0.f, v.x());
			if (v.x() > xmax)
				xmax = std::min((float)screenWidth - 1.f, v.x());
			if (v.y() < ymin)
				ymin = std::max(0.f, v.y());
			if (v.y() > ymax)
				ymax = std::min((float)screenHeight - 1.f, v.y());
		}

		for (int i = (int)xmin; i <= (int)xmax; ++i)
		{
			for (int j = (int)ymin; j <= (int)ymax; ++j)
			{
				SoVector3f samplePoint((float)i, (float)j, 1.f);
				if (tri.IsPointInside(samplePoint))
				{

					SoVector3f barycentricCoord = tri.GetBarycentricCoord2D(SoVector2f(samplePoint.x(), samplePoint.y()));

					SoVector2f uv =
						SoTriangle::InterploateWithBarycentricCoord(tri.textureCoord[0], tri.textureCoord[1], tri.textureCoord[2], barycentricCoord);
					float z = SoTriangle::InterploateWithBarycentricCoord(tri.vertex[0], tri.vertex[1], tri.vertex[2], barycentricCoord).z();

					if (zBuffer.GetValueAtPos(i, j) < z)
					{
						const SoColor textureColor = texture.SampleByUV(uv);

						SoVector3f color = textureColor.cast<float>().head<3>();

						SoVector3f vp[3] = {viewPos[0], viewPos[1], viewPos[2] };
						SoVector3f point = SoTriangle::InterploateWithBarycentricCoord(vp[0], vp[1], vp[2], barycentricCoord);
						SoVector3f nor = normal.normalized();

						SoVector3f ka = { 0.005f, 0.005f, 0.005f };
						SoVector3f kd = color / 255.f;
						SoVector3f ks = { 0.78f, 0.78f, 0.78f };

						SoPointLight l1 = { {15.f, 15.f, -15.f}, {800.f, 800.f, 800.f} };
						SoPointLight l2 = { {0.f, 40.f, -10.f}, {1000.f, 1000.f, 1000.f} };

						std::vector<SoPointLight> lightList;

						lightList.push_back(l1);
						lightList.push_back(l2);

						SoVector3f ambLightIntensity{ 20.f, 20.f, 20.f };
						float  p = 150.f;

						SoVector3f result = { 0, 0, 0 };

						SoVector3f la = { 0, 0, 0 };
						SoVector3f ld = { 0, 0, 0 };
						SoVector3f ls = { 0, 0, 0 };

						la = ka.cwiseProduct(ambLightIntensity);
						for(auto& light: lightList)
						{
							SoVector3f intensity =  light.intensity / (light.position - point).squaredNorm();
							SoVector3f l = (light.position - point).normalized();
							ld += kd.cwiseProduct(intensity) * std::max(0.f, nor.dot(l));
							SoVector3f v = (-point).normalized();
							SoVector3f h = (l + v).normalized();
							ls += ks.cwiseProduct(intensity) * std::pow(std::max(0.0f, nor.dot(h)), p);
						}
						
						result = la + ld + ls;
						SoColor resultColor = 
							{
								std::min(255, (int)(result[0] * 255.f)),
								std::min(255, (int)(result[1] * 255.f)),
								std::min(255, (int)(result[2] * 255.f)),
								255
							};
						DrawPoint<SoColor>(colorBuffer, SoVector2i(i, j), resultColor);
						DrawPoint<float>(zBuffer, SoVector2i(i, j), z);
					}
				}
			}
		}
	}

	void SoRasterizer::DrawFrame()
	{
		BeginDrawing();
		for(int i = 0; i < screenWidth; ++i)
		{
			for(int j = 0; j < screenHeight; ++j)
			{
				const SoColor& soColor = colorBuffer.GetValueAtPos(i, j);
				Color color;
				color.r = (char)soColor[0];
				color.g = (char)soColor[1];
				color.b = (char)soColor[2];
				color.a = (char)soColor[3];
				DrawPixel(i, screenHeight - 1 - j, color); // IN Raylib, coordinate (0,0) begins from the top left corner
			}
		}
		EndDrawing();
	}

	



}
