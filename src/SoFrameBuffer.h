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
		T defaultValue;

		SoFrameBuffer(int w, int h, const T& defaultVal): width(w), height(h), defaultValue(defaultVal), buffData(width * height, defaultVal)
		{
		}

		void SetValueAtPos(int x, int y, const T& value)
		{
			buffData[x + y * width] = value;
		}

		const T& GetValueAtPos(int x, int y)
		{
			return buffData[x + y * width];
		}

		void Clear()
		{
			for(T& i: buffData)
			{
				i = defaultValue;
			}
		}
		
	};
}
