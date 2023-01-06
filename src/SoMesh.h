#pragma once
#include <vector>
#include <OBJ_Loader.h>
#include "SoTriangle.h"
namespace SoRendering
{
	class SoMesh
	{
	private:
		std::vector<SoTriangle> triangleList;
	public:
		const std::vector<SoTriangle>& GetTriangleList() const { return triangleList; }
		void LoadFromObj(std::string path)
		{
            objl::Loader Loader;
            bool loadout = Loader.LoadFile(path);
            if (!loadout)
            {
                std::cout << "Obj file:" << path << "load failed!";
                return;
            }
			for (auto mesh : Loader.LoadedMeshes)
            {
                for (uint i = 0; i < mesh.Vertices.size(); i += 3)
                {
                    SoTriangle t;
                    for (uint j = 0; j < 3; j++)
                    {
                        t.vertex[j] = SoVector4f(mesh.Vertices[i + j].Position.X, mesh.Vertices[i + j].Position.Y, mesh.Vertices[i + j].Position.Z, 1.0);
                    }
                    triangleList.push_back(t);
                }
            }

		}
	};
}