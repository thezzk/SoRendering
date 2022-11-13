#include "SoTransform.h"
#include "SoMath.h"

namespace SoRendering
{

	SoTransform::SoTransform():
	matrix({
			{1.f, 0, 0, 0},
			{0, 1.f, 0, 0},
			{0, 0, 1.f, 0},
			{0, 0, 0, 1.f}
		}),
	position(0, 0, 0),
	rotation(0, 0, 0, 1.f),
	scale(1.f, 1.f, 1.f)
	{
	}

	//Getter
	SoVector3f SoTransform::GetRotationInEulerAngle()
	{
		return SoMath::GetEulerAngleFromQuaternion(rotation);
	}

	//Setter
	void SoTransform::SetPosition(SoVector3f position)
	{
		this->position = position;
		UpdateTransformMatrix();
	}

	void SoTransform::SetRotation(SoQuaternion quaternion)
	{
		this->rotation = quaternion;
		UpdateTransformMatrix();

	}

	void SoTransform::SetScale(SoVector3f scale)
	{
		this->scale = scale;
		UpdateTransformMatrix();
	}

	//Calculation
	void SoTransform::UpdateTransformMatrix()
	{
		matrix = GetTranslationMatrix(position) * GetRotationMatrix(rotation) * GetScaleMatrix(scale);
	}

	SoMatrix4f SoTransform::GetTranslationMatrix(SoVector3f position)
	{
		return SoMatrix4f
		{
			{1.f, 0, 0, position(0)},
			{0, 1.f, 0, position(1)},
			{0, 0, 1.f, position(2)},
			{0, 0, 0, 1.f}
		};
	}

	SoMatrix4f SoTransform::GetRotationMatrix(SoQuaternion quaternion)
	{
		float xSqr = powf(quaternion(0), 2.f);
		float ySqr = powf(quaternion(1), 2.f);
		float zSqr = powf(quaternion(2), 2.f);
		float xy = quaternion(0) * quaternion(1);
		float xz = quaternion(0) * quaternion(2);
		float yz = quaternion(1) * quaternion(2);
		float wx = quaternion(3) * quaternion(0);
		float wy = quaternion(3) * quaternion(1);
		float wz = quaternion(3) * quaternion(2);

		return SoMatrix4f
		{
			{1 - 2 * ySqr - 2 * zSqr,	2 * xy - 2 * wz,			2 * xz + 2 * wy,			0},
			{2 * xy + 2 * wz,			1 - 2 * xSqr - 2 * zSqr,	2 * yz - 2 * wx,			0},
			{2 * xz - 2 * wy,			2 * yz + 2 * wx,			1 - 2 * xSqr - 2 * ySqr,	0},
			{0,							0,							0,							1.f}
		};
	}

	SoMatrix4f SoTransform::GetScaleMatrix(SoVector3f scale)
	{
		void UpdateTransformMatrix();
		
		return SoMatrix4f
		{
			{scale(0), 0, 0, 0},
			{0, scale(1), 0, 0},
			{0, 0, scale(2), 0},
			{0, 0, 0, 1.f}
		};
	}

};