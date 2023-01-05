
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
    camera.SetProjectionType(SoRendering::SoCamera::CAMERA_PROJECTION_PERSPECTIVE);
    rasterizer.Init();

    SoRendering::SoTriangle tri;
    tri.vertex[0] = { 30.f, 0.0f, 30.f, 1.f };
    tri.vertex[1] = { 0.f, 20.0f, 30.f, 1.f };
    tri.vertex[2] = { -10.f, 0.0f, 30.f, 1.f };
    std::vector<SoRendering::SoTriangle> triLst;
    triLst.push_back(tri);
    rasterizer.GetTriangleLst() = triLst;
    while(1)
    {
        SoRendering::SoVector3f cameraPos = camera.GetPosition();
        const float moveDelta = 5.f;
    	if (IsKeyDown(KEY_W))
        {
            cameraPos[2] += moveDelta;
        }
        if (IsKeyDown(KEY_S))
        {
            cameraPos[2] -= moveDelta;
        }
        if (IsKeyDown(KEY_A))
        {
            cameraPos[0] -= moveDelta;
        }
        if (IsKeyDown(KEY_D))
        {
            cameraPos[0] += moveDelta;
        }
        if (IsKeyDown(KEY_R))
        {
            cameraPos[1] += moveDelta;
        }
        if (IsKeyDown(KEY_F))
        {
            cameraPos[1] -= moveDelta;
        }
        camera.SetPosition(cameraPos);
        rasterizer.UpdateFrameBuffer(camera);
        rasterizer.DrawFrame();
    }
    return 0;
}

