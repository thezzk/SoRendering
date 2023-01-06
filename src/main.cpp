
#include <raylib.h>

#include "SoConstant.h"
#include "SoRasterizer.h"
#include "SoCamera.h"
#include "SoTriangle.h"
#include "SoMesh.h"
#include <vector>

static const int screenWidth = 800;
static const int screenHeight = 450;

int main()
{

    SoRendering::SoRasterizer rasterizer(800, 450, SoRendering::SoRasterizer::RASTERIZER_MODE_COLOR);

    SoRendering::SoCamera camera;
    camera.SetPosition({0, 0, -10.f});
    camera.SetProjectionType(SoRendering::SoCamera::CAMERA_PROJECTION_PERSPECTIVE);
    rasterizer.Init();

    std::vector<SoRendering::SoTriangle> triLst;
    SoRendering::SoTriangle tri;
    tri.vertex[0] = { 30.f, 0.0f, 5.f, 1.f };
    tri.vertex[1] = { 0.f, 20.0f, 5.f, 1.f };
    tri.vertex[2] = { -2.f, 0.0f, 5.f, 1.f };
    tri.color[0] = SoRendering::SoVector3f(255.f, 0, 0);
    tri.color[1] = SoRendering::SoVector3f(255.f, 0, 0);
    tri.color[2] = SoRendering::SoVector3f(255.f, 0, 0);
    triLst.push_back(tri);

	SoRendering::SoTriangle tri2;
    tri2.vertex[0] = { -10.f, 0.0f, 10.f, 1.f };
    tri2.vertex[1] = { 10.f, 5.0f, 10.f, 1.f };
    tri2.vertex[2] = { 0.f, 20.0f, 10.f, 1.f };
    tri2.color[0] = SoRendering::SoVector3f(0, 255.f, 0);
    tri2.color[1] = SoRendering::SoVector3f(0, 255.f, 0);
    tri2.color[2] = SoRendering::SoVector3f(0, 255.f, 0);
    triLst.push_back(tri2);

    SoRendering::SoTriangle triback;
    triback.vertex[0] = { -10.f, 0.0f, 5.f, 1.f };
    triback.vertex[1] = { 0.f, 0.0f, 5.f, 1.f };
    triback.vertex[2] = { 0.f, -10.0f, 5.f, 1.f };
    triback.color[0] = SoRendering::SoVector3f(0, 0, 255.f);
    triback.color[1] = SoRendering::SoVector3f(0, 0, 255.f);
    triback.color[2] = SoRendering::SoVector3f(0, 0, 255.f);
    triLst.push_back(triback);

	rasterizer.GetTriangleLst() = triLst;

    //SoRendering::SoMesh teapot;
    //teapot.LoadFromObj("./objs/teapot.obj");
    //rasterizer.GetTriangleLst() = teapot.GetTriangleList();
	while(1)
    {
        SoRendering::SoVector3f cameraPos = camera.GetPosition();
        const float moveDelta = 2.f;
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

