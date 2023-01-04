#include "pch.h"
#include "raymath.h"
#include "SoMath.h"
#include "CppUnitTest.h"
#include <Eigen/Core>
#include "SoTriangle.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(RasterizerTest)
	{
	public:
		TEST_METHOD(PointInsideTriangleTest)
		{
			SoRendering::SoTriangle tri;
			tri.vertex[0] = { 4.f, 3.f, 1.f, 1.f };
			tri.vertex[1] = { 3.f, -2.f, 1.f, 1.f};
			tri.vertex[2] = { -7.f, 6.f, 1.f, 1.f};
			SoRendering::SoVector3f point = {0, 3.f, 1.f};
			Assert::IsTrue(SoRendering::SoTriangle::IsPointInside(point, tri));
			point = { 1.46f, 2.44f, 1.f };
			Assert::IsTrue(SoRendering::SoTriangle::IsPointInside(point, tri));
			point = {6.27f, 1.12f, 1.f};
			Assert::IsFalse(SoRendering::SoTriangle::IsPointInside(point, tri));


			tri.vertex[0] = { 0.867f, -1.855f, 1.f, 1.f };
			tri.vertex[1] = { -3.199f, -4.16f, 1.f, 1.f };
			tri.vertex[2] = { 3.f, -2.f, 1.f, 1.f };
			point = { -3.289f, 2.066f, 1.f };
			Assert::IsFalse(SoRendering::SoTriangle::IsPointInside(point, tri));
			point = { -1.093f, -3.198f, 1.f };
			Assert::IsTrue(SoRendering::SoTriangle::IsPointInside(point, tri));
			point = { 0.213f, -3.289f, 1.f };
			Assert::IsFalse(SoRendering::SoTriangle::IsPointInside(point, tri));
		}

	};
}
