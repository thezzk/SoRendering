#pragma once
#include <Eigen/Core>



namespace SoRendering
{
	constexpr float SO_PI = 3.14159265358979323846f;
	constexpr float SO_EPSILON = 0.000001f;
	constexpr float SO_DEG2RAD = SO_PI / 180.f;
	constexpr float SO_RAD2DEG = 180.f / SO_PI;

	//Vector
	typedef Eigen::Matrix<float, 3, 1> SoVector3f;
	typedef Eigen::Matrix<float, 4, 1> SoVector4f;
	typedef SoVector4f SoQuaternion;

	//Matrix
	typedef Eigen::Matrix<float, 3, 3> SoMatrix3f;
	typedef Eigen::Matrix<float, 4, 4> SoMatrix4f;
};