#pragma once
#include <picopng.h>
#include <vector>
#include <string>
#include <cassert>
#include "SoConstant.h"

namespace SoRendering
{
	class SoTexture
	{
	private:
		int width;
		int height;
		std::vector<SoColor> data;
	public:
		SoTexture():width(0), height(0)
		{
		}

		SoTexture(const std::string& path)
		{
			LoadFromPNG(path);
		}

		SoVector2i GetSize() const { return SoVector2i(width, height); }

		void LoadFromPNG(const std::string& path);

		SoColor SampleByPos(const SoVector2i& pos) const
		{
			return data[width * pos.y() + pos.x()];
		}

		SoColor SampleByUV(const SoVector2f& uv) const
		{
			int x = (int)(uv[0] * (float)width);
			x = x == width ? width - 1: x;
			int y = (int)((1.f- uv[1]) * (float)height);
			y = y == height ? height - 1 : y;
			return SampleByPos(SoVector2i(x, y));
		}


	};
}
