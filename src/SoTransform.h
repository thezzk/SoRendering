#pragma once
#include "SoConstant.h"

namespace SoRendering
{

	class SoTransform
	{
	private:
		SoMatrix4f matrix;
		SoVector3f position;
		SoQuaternion rotation;
		SoVector3f scale;
		void UpdateTransformMatrix();

	public:
		SoTransform();

		//Getter
		SoMatrix4f GetMatrix() const { return matrix; }
		SoVector3f GetPosition() const { return position; }
		SoQuaternion GetRotationInQuaternion() const { return rotation; }
		SoVector3f GetRotationInEulerAngle();

		//Setter
		void SetPosition(SoVector3f position);
		void SetRotation(SoQuaternion quaternion);
		void SetRotation(SoVector3f eulerAngle);
		void SetScale(SoVector3f scale);

		//Calculation
		static SoMatrix4f GetTranslationMatrix(SoVector3f position);
		static SoMatrix4f GetRotationMatrix(SoQuaternion quaternion);
		static SoMatrix4f GetScaleMatrix(SoVector3f scale);

	};
};