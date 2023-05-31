#include "FloatBuffer.h"

#include "../../../java/java.h"
#include "../../../util/logger.h"

#include <vector>

FloatBuffer::FloatBuffer(jobject obj)
{
	this->Instance = obj;
	this->Class = Java::Env->FindClass("java/nio/FloatBuffer");
	this->MethodIDs["get"] = Java::Env->GetMethodID(this->Class, "get", "(I)F");
}

Matrix FloatBuffer::GetMatrix()
{
	std::vector<float> arr;
	for (int i = 0; i < 16; i++)
	{
		arr.push_back(Java::Env->CallFloatMethod(this->GetInstance(), this->MethodIDs["get"], i));
	}

	Matrix m;

	m.m00 = arr[0];
	m.m01 = arr[1];
	m.m02 = arr[2];
	m.m03 = arr[3];
	m.m10 = arr[4];
	m.m11 = arr[5];
	m.m12 = arr[6];
	m.m13 = arr[7];
	m.m20 = arr[8];
	m.m21 = arr[9];
	m.m22 = arr[10];
	m.m23 = arr[11];
	m.m30 = arr[12];
	m.m31 = arr[13];
	m.m32 = arr[14];
	m.m33 = arr[15];

	return m;
}


jclass FloatBuffer::GetClass()
{
	return this->Class;
}

jobject FloatBuffer::GetInstance()
{
	return this->Instance;
}