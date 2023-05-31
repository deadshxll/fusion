#include "Set.h"
#include "../../../java/java.h"

Set::Set(jobject jset)
{
	this->Instance = jset;

	this->Class = Java::Env->FindClass("java/util/Set");
	this->MethodIDs["toArray"] = Java::Env->GetMethodID(this->Class, "toArray", "()[Ljava/util/Object;");
}

jclass Set::GetClass()
{
	return this->Class;
}

jobject Set::GetInstance()
{
	return this->Instance;
}

jobjectArray Set::toArray()
{
	return (jobjectArray)Java::Env->CallObjectMethod(this->Instance, this->MethodIDs["toArray"]);
}
