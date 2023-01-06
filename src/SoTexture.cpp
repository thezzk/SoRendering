#include "SoTexture.h"

namespace SoRendering
{
	void SoTexture::LoadFromPNG(const std::string& path)
	{

		data.clear();
		std::vector<unsigned char> png;
		std::vector<unsigned char> image; //the raw pixels

		//load and decode
		loadFile(png, path);
		if (png.empty())
		{
			std::cout << "PNG load fail" << std::endl;
			return;
		}
		unsigned long w, h;
		int	error = decodePNG(image, w, h, png.empty() ? 0 : &png[0], (unsigned long)png.size());

		width = (int)w;
		height = (int)h;
		//if there's an error, display it
		if (error != 0) std::cout << "PNG decode error: " << error << std::endl;

		//Make sure we read RGBA for each pixel
		assert(image.size() % 4 == 0);

		for (uint i = 0; i < image.size(); i += 4)
		{
			SoColor c(image[i], image[i + 1], image[i + 2], image[i + 3]);
			data.push_back(c);
		}
	}

}
