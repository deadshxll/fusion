#include "worldToScreen.h"
#include "../../base.h"
#include "../logger.h"

#include <limits>

Vector4 CWorldToScreen::Multiply(Vector4 v, Matrix m) {
	return Vector4{
		v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30,
		v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31,
		v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32,
		v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33
	};
}

bool CWorldToScreen::WorldToScreen(Vector3 point, Matrix modelView, Matrix projection, int screenWidth, int screenHeight, Vector2 &screenPos) {
	// csp = Clip Space Position
	Vector4 csp = Multiply(
		Multiply(
			Vector4 {point.x, point.y, point.z, 1.0f},
			modelView
		),
		projection
	);

	// ndc = Native Device Coordinate
	Vector3 ndc{
		csp.x / csp.w,
		csp.y / csp.w,
		csp.z / csp.w
	};

	//Logger::Log("NDC.Z: " + std::to_string(ndc.z));

	if (ndc.z > 1 && ndc.z < 1.15) {
		screenPos = Vector2{
			((ndc.x + 1.0f) / 2.0f) * screenWidth,
			((1.0f - ndc.y) / 2.0f) * screenHeight,
		};
		return true;
	}

	return false;
}