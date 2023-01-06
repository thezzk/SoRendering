#include "pch.h"
#include "raylib.h"
#include "SoMath.h"
#include "CppUnitTest.h"
#include <Eigen/Core>
#include "SoTriangle.h"
#include "SoTexture.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(RasterizerTest)
	{
	public:
		TEST_METHOD(LoadPNGToTexture)
		{
			SoRendering::SoTexture texture = SoRendering::SoTexture("../models/blub/blub_texture_low.png");
			int width = texture.GetSize().x(), height = texture.GetSize().y();
			InitWindow(width, height, "texture test");
			BeginDrawing();
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					auto soColor = texture.Sample(SoRendering::SoVector2i(i, j));
					Color c;
					c.r = soColor[0], c.g = soColor[1], c.b = soColor[2], c.a = soColor[3];
					DrawPixel(i, j, c);
				}
			}
			EndDrawing();

			WaitTime(3);
		}

		TEST_METHOD(PointInsideTriangleTest)
		{
			SoRendering::SoTriangle tri;
			tri.vertex[0] = { 4.f, 3.f, 1.f, 1.f };
			tri.vertex[1] = { 3.f, -2.f, 1.f, 1.f};
			tri.vertex[2] = { -7.f, 6.f, 1.f, 1.f};
			SoRendering::SoVector3f point = {0, 3.f, 1.f};
			Assert::IsTrue(tri.IsPointInside(point, false));
			point = { 1.46f, 2.44f, 1.f };
			Assert::IsTrue(tri.IsPointInside(point, false));
			point = {6.27f, 1.12f, 1.f};
			Assert::IsFalse(tri.IsPointInside(point, false));


			tri.vertex[0] = { 0.867f, -1.855f, 1.f, 1.f };
			tri.vertex[1] = { -3.199f, -4.16f, 1.f, 1.f };
			tri.vertex[2] = { 3.f, -2.f, 1.f, 1.f };
			point = { -3.289f, 2.066f, 1.f };
			Assert::IsFalse(tri.IsPointInside(point, false));
			point = { -1.093f, -3.198f, 1.f };
			Assert::IsTrue(tri.IsPointInside(point, false));
			point = { 0.213f, -3.289f, 1.f };
			Assert::IsFalse(tri.IsPointInside(point, false));
		}

	};
}
