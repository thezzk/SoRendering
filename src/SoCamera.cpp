#include "SoCamera.h"
#include "SoMath.h"
namespace SoRendering
{
	SoCamera::SoCamera()
	: position(SoVector3f::Zero()), targetDirection(SoVector3f::UnitZ()), upDirection(SoVector3f::UnitY()),
		orthogonalViewportSize({160.f, 90.f}), projectionType(CAMERA_PROJECTION_ORTHOGRAPHIC), fovY(SO_PI/3.f), aspect(16.f / 9.f),
		nearPlane(1.f), farPlane(1000.f)
		
	{
		UpdateProjectMatrix();
		UpdateViewMatrix();
	}

	void SoCamera::SetFovY(const float fovY)
	{
		this->fovY = fovY;
		UpdateProjectMatrix();
	}

	void SoCamera::SetAspect(const float aspect)
	{
		this->aspect = aspect;
		UpdateProjectMatrix();
	}

	void SoCamera::SetProjectionType(const CAMERA_PROJECTION_TYPE projType)
	{
		this->projectionType = projType;
		UpdateProjectMatrix();
	}

	void SoCamera::SetPosition(const SoVector3f& position)
	{
		this->position = position;
		UpdateViewMatrix();
	}

	void SoCamera::LookAt(const SoVector3f& targetDirection, const SoVector3f& upDirection)
	{
		this->targetDirection = targetDirection.normalized();
		this->upDirection = upDirection.normalized();
		UpdateViewMatrix();
	}

	void SoCamera::UpdateViewMatrix()
	{
		SoMatrix4f invTranslate, invRotate;
		invTranslate <<
			1.f, 0, 0, -position.x(),
			0, 1.f, 0, -position.y(),
			0, 0, 1.f, -position.z(),
			0, 0, 0, 1.f;


		const SoVector3f cross = (-targetDirection).cross(upDirection).normalized();

		invRotate <<
			cross.x(), cross.y(), cross.z(), 0,
			upDirection.x(), upDirection.y(), upDirection.z(), 0,
			-targetDirection.x(), -targetDirection.y(), -targetDirection.z(), 0,
			0, 0, 0, 1.f;



		viewMatrix = invRotate * invTranslate;
	}

	void SoCamera::UpdateOrthoProject()
	{
		float l = -orthogonalViewportSize.x() / 2,
			r = orthogonalViewportSize.x() / 2,
			t = orthogonalViewportSize.y() / 2,
			b = -orthogonalViewportSize.y() / 2,
			n = nearPlane, f = -farPlane;
		SoMatrix4f translate;
		translate << 1.f, 0, 0, -(r + l) / 2.f,
			0, 1.f, 0, -(t + b) / 2.f,
			0, 0, 1.f, -(n + f) / 2.f,
			0, 0, 0, 1.f;
		SoMatrix4f scale;
		scale << 2.f / (r - l), 0, 0, 0,
			0, 2.f / (t - b), 0, 0,
			0, 0, 2.f / (n - f), 0,
			0, 0, 0, 1.f;
		projectMatrix = scale * translate;
	}

	void SoCamera::UpdatePerspectiveProject()
	{
		float s = 1 / tan(fovY / 2);
		projectMatrix <<
			s, 0, 0, 0,
			0, s, 0, 0,
			0, 0, -farPlane / (farPlane - nearPlane), -1.f,
			0, 0, -(farPlane * nearPlane) / (farPlane - nearPlane), 0;
		
			
	}


	void SoCamera::UpdateProjectMatrix()
	{
		if(projectionType == CAMERA_PROJECTION_ORTHOGRAPHIC)
		{
			UpdateOrthoProject();
		}
		else if(projectionType == CAMERA_PROJECTION_PERSPECTIVE)
		{
			UpdatePerspectiveProject();
		}

	}

}