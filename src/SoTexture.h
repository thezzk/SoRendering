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

		SoColor Sample(const SoVector2i& pos) const
		{
			return data[width * pos.y() + pos.x()];
		}
	};
}
