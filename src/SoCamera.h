#pragma once
#include "SoConstant.h"

namespace SoRendering
{
	class SoCamera
	{
	public:
		enum CAMERA_PROJECTION_TYPE
		{
			CAMERA_PROJECTION_PERSPECTIVE,
			CAMERA_PROJECTION_ORTHOGRAPHIC
		};
	private:
		SoVector3f position;
		SoVector3f targetDirection;
		SoVector3f upDirection;
		SoMatrix4f viewMatrix;
		SoMatrix4f projectMatrix;
		CAMERA_PROJECTION_TYPE projectionType;
		float fovY;
		float aspect;

		void UpdateViewMatrix();
		void UpdateProjectMatrix();
	public:
		SoCamera();

		void SetFovY(const float fovY);
		void SetAspect(const float aspect);
		void SetProjectionType(const CAMERA_PROJECTION_TYPE projType);
		void SetPosition(const SoVector3f& position);
		void LookAt(const SoVector3f& targetDirection, const SoVector3f& upDirection);

		float GetFovY() const
		{
			return fovY;
		}

		float GetAspect() const
		{
			return aspect;
		}

		CAMERA_PROJECTION_TYPE GetProjectionType() const
		{
			return projectionType;
		}

		const SoMatrix4f& GetViewMatrix() const
		{
			return viewMatrix;
		}

		const SoMatrix4f& GetProjectMatrix() const
		{
			return projectMatrix;
		}
	};
}