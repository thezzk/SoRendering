
#include <raylib.h>

#include "SoConstant.h"
#include "SoRasterizer.h"
#include "SoCamera.h"
#include "SoTriangle.h"
#include <vector>

static const int screenWidth = 800;
static const int screenHeight = 450;

int main()
{

    SoRendering::SoRasterizer rasterizer;

    SoRendering::SoCamera camera;
    camera.SetPosition({20.f, 0, 0});
    rasterizer.Init();

    SoRendering::SoTriangle tri;
    tri.vertex[0] = { 30.f, 0.0f, -30.f, 1.f };
    tri.vertex[1] = { 0.f, 20.0f, -30.f, 1.f };
    tri.vertex[2] = { -10.f, 0.0f, -30.f, 1.f };
    std::vector<SoRendering::SoTriangle> triLst;
    triLst.push_back(tri);
    rasterizer.GetTriangleLst() = triLst;
    while(1)
    {
        rasterizer.UpdateFrameBuffer(camera);
        rasterizer.DrawFrame();
    }
    return 0;
}

