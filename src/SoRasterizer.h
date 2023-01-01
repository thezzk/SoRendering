#pragma once

#include <SoCamera.h>
#include <SoFrameBuffer.h>

namespace SoRendering
{
	class SoRasterizer
	{
	public:
		SoRasterizer();
		void Draw();
	private:
		SoCamera camera;
		SoFrameBuffer<SoVector3f> colorBuffer;
	};
}
