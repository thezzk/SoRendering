#pragma once
#include <cmath>

#include "Eigen/Core"
#include "SoConstant.h"
#include "SoTransform.h"
namespace SoRendering
{
	namespace SoMath
	{
		inline bool EqualWithEpsilon(const float x, const float y)
		{
			return abs(x - y) < SO_EPSILON;
		}

		// Get quaternion from pass in euler angle (in radius)
		inline SoQuaternion GetQuaternionFromEulerAngle(SoVector3f eulerAngle)
		{
			float roll = eulerAngle[0];
			float pitch = eulerAngle[1];
			float yaw = eulerAngle[2];

			float cr = cosf(roll * 0.5f);
			float sr = sinf(roll * 0.5f);
			float cp = cosf(pitch * 0.5f);
			float sp = sinf(pitch * 0.5f);
			float cy = cosf(yaw * 0.5f);
			float sy = sinf(yaw * 0.5f);

			SoQuaternion retval;
			retval[0] = sr * cp * cy - cr * sp * sy;
			retval[1] = cr * sp * cy + sr * cp * sy;
			retval[2] = cr * cp * sy - sr * sp * cy;
			retval[3] = cr * cp * cy + sr * sp * sy;

			return retval;
		}

		// Get euler angle (in radius) from pass in quaternion
		inline SoVector3f GetEulerAngleFromQuaternion(SoQuaternion quaternion)
		{
			SoVector3f angle(0, 0, 0);
			//roll (x-axis)
			float sinr_cosp = 2.f * (quaternion(3) * quaternion(0) + quaternion(1) * quaternion(2));
			float cosr_cosp = 1.f - 2.f * (quaternion(0) * quaternion(0) + quaternion(1) * quaternion(1));
			angle(0) = atan2f(sinr_cosp, cosr_cosp);

			//pitch (y-axis)
			float sinp = 2.f * (quaternion(3) * quaternion(1) - quaternion(2) * quaternion(0));
			if (abs(sinp) >= 1.f)
				angle(1) = copysignf(SO_PI / 2.f, sinp);
			else
				angle(1) = asinf(sinp);

			//yaw (z-axis)
			float siny_cosp = 2.f * (quaternion(3) * quaternion(2) + quaternion(0) * quaternion(1));
			float cosy_cosp = 1.f - 2.f * (quaternion(1) * quaternion(1) + quaternion(2) * quaternion(2));
			angle(2) = atan2f(siny_cosp, cosy_cosp);

			return angle;
		}
	}
}