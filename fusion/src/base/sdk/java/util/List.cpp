#include "List.h"
#include "../../../java/java.h"

List::List(jobject jlist)
{
	this->Instance = jlist;

	this->Class = Java::Env->FindClass("java/util/List");
	this->MethodIDs["toArray"] = Java::Env->GetMethodID(this->Class, "toArray", "()[Ljava/lang/Object;");
}

jclass List::GetClass()
{
	return this->Class;
}

jobject List::GetInstance()
{
	return this->Instance;
}

jobjectArray List::toArray()
{
	return (jobjectArray) Java::Env->CallObjectMethod(this->GetInstance(), this->MethodIDs["toArray"]);
}
