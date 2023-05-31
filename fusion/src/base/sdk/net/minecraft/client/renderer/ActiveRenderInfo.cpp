#include "ActiveRenderInfo.h"

#include "../../../../../java/java.h"
#include "../../../../sdk.h"
#include "../../../../java/nio/FloatBuffer.h"
#include "../../../../../util/logger.h"

CActiveRenderInfo::CActiveRenderInfo()
{
	Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", this->Class);
	this->FieldIDs["PROJECTION"] = Java::Env->GetStaticFieldID(this->Class, "PROJECTION", "Ljava/nio/FloatBuffer;");
	this->FieldIDs["MODELVIEW"] = Java::Env->GetStaticFieldID(this->Class, "MODELVIEW", "Ljava/nio/FloatBuffer;");
}

jclass CActiveRenderInfo::GetClass()
{
	return this->Class;
}

jobject CActiveRenderInfo::GetInstance()
{
	return NULL;
}

Matrix CActiveRenderInfo::ProjectionMatrix()
{
	jobject projection = Java::Env->GetStaticObjectField(this->GetClass(), this->FieldIDs["PROJECTION"]);
	Matrix m = FloatBuffer::FloatBuffer(projection).GetMatrix();
	Java::Env->DeleteLocalRef(projection);
	return m;
}

Matrix CActiveRenderInfo::ModelViewMatrix()
{
	jobject modelView = Java::Env->GetStaticObjectField(this->GetClass(), this->FieldIDs["MODELVIEW"]);
	Matrix m = FloatBuffer::FloatBuffer(modelView).GetMatrix();
	Java::Env->DeleteLocalRef(modelView);
	return m;
}

