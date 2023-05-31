#include "String.h"
#include "../../../java/java.h"

String::String(jobject instance)
{
	this->Class = Java::Env->FindClass("java/lang/String");
	this->Instance = instance;
}

String::String(std::string text)
{
	this->Class = Java::Env->FindClass("java/lang/String");
	this->Instance = (jobject)Java::Env->NewStringUTF(text.c_str());
}

jclass String::GetClass()
{
	return this->Class;
}

jobject String::GetInstance()
{
	return this->Instance;
}

std::string String::ToString()
{
	jstring jStr = (jstring)this->Instance;
	const char* nativeStr = Java::Env->GetStringUTFChars(jStr, nullptr);
	Java::Env->ReleaseStringUTFChars(jStr, nativeStr);
	return std::string(nativeStr);
}
