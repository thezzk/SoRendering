#pragma once

#include <vector>

namespace SoRendering
{
	template <typename T>
	struct SoFrameBuffer
	{
		int width;
		int height;

		std::vector<T> buffData;

		SoFrameBuffer(int w, int h, const T& defaultVal): width(w), height(h), buffData(width * height, defaultVal)
		{
		}
	};
}
