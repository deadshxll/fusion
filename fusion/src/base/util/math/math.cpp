#include "math.h"

#include <cmath>

float Math::wrapAngleTo180(float angle)
{
	angle = std::fmod(angle, 360.0f);
	if (angle >= 180.0f) {
		angle -= 360.0f;
	}

	if (angle < -180.0f) {
		angle += 360.0f;
	}

	return angle;
}

Vector2 Math::vec_wrapAngleTo180(Vector2 angle)
{
	return Vector2{
		wrapAngleTo180(angle.x),
		wrapAngleTo180(angle.y),
	};
}

float Math::coterminal(float angle) {
	return std::fmod(angle, 180) < 0 ? angle + 170 : angle;
}


float Math::magnitude(Vector3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Math::crossProduct(Vector3 v1, Vector3 v2)
{
	return Vector3{
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

float Math::shortestDistance(Vector3 p, Vector3 a, Vector3 b)
{

	Vector3 ab{ b.x - a.x, b.y - a.y, b.z - a.z };
	Vector3 cp = crossProduct(
		Vector3{p.x - a.x, p.y - a.y, p.z - a.z},
		ab
	);

	return magnitude(cp) / magnitude(ab);
}

Vector2 Math::getAngles(Vector3 pos, Vector3 pos1)
{
	double d_x = pos1.x - pos.x;
	double d_y = pos1.y - pos.y;
	double d_z = pos1.z - pos.z;

	double hypothenuse = sqrt(d_x * d_x + d_z * d_z);
	float yaw = radiantsToDeg(atan2(d_z, d_x)) - 90.f;
	float pitch = radiantsToDeg(-atan2(d_y, hypothenuse));

	return Vector2(yaw, pitch);
}

float Math::radiantsToDeg(float x)
{
	return x * 180.f / PI;
}

float Math::degToRadiants(float x)
{
	return x * PI / 180.f;
}

