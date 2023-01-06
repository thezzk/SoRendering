#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>

#define SO_PRESET_COLOR_RED   SoColor(255, 0, 0, 255)
#define SO_PRESET_COLOR_GREEN SoColor(0, 255, 0, 255)
#define SO_PRESET_COLOR_BLUE  SoColor(0, 0, 255, 255)
#define SO_PRESET_COLOR_BLACK SoColor(0, 0, 0, 255)
#define SO_PRESET_COLOR_WHITE SoColor(255, 255, 255, 255)
#define uint unsigned int


namespace SoRendering
{
	constexpr float SO_PI = 3.14159265358979323846f;
	constexpr float SO_EPSILON = 0.000001f;
	constexpr float SO_DEG2RAD = SO_PI / 180.f;
	constexpr float SO_RAD2DEG = 180.f / SO_PI;

	//Vector
	typedef Eigen::Matrix<float, 2, 1> SoVector2f;
	typedef Eigen::Matrix<float, 3, 1> SoVector3f;
	typedef Eigen::Matrix<float, 4, 1> SoVector4f;
	typedef Eigen::Matrix<int, 4, 1> SoVector4i;
	typedef Eigen::Matrix<int, 3, 1> SoVector3i;
	typedef Eigen::Matrix<int, 2, 1> SoVector2i;
	
	typedef SoVector4f SoQuaternion;
	typedef SoVector4i SoColor;

	//Matrix
	typedef Eigen::Matrix<float, 3, 3> SoMatrix3f;
	typedef Eigen::Matrix<float, 4, 4> SoMatrix4f;
};