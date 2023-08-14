#include "patcher.h"
#include "miniz.h"
#include "data.h"
#include <functional>

namespace Patcher
{
	namespace
	{
		void loadJar(jobject classLoader, const unsigned char* jarBytes, size_t size)
		{
			mz_zip_archive archive{};
			if (!mz_zip_reader_init_mem(&archive, jarBytes, size, 0))
			{
				return;
			}
			mz_uint file_number = mz_zip_reader_get_num_files(&archive);
			for (mz_uint i = 0; i < file_number; i++)
			{

				if (!mz_zip_reader_is_file_supported(&archive, i) || mz_zip_reader_is_file_a_directory(&archive, i)) 
					continue;

				char str[256] = { 0 };
				mz_zip_reader_get_filename(&archive, i, str, 256);
				std::string filename(str);

				if (filename.substr(filename.size() - 6) != ".class")
					continue;

				size_t classBytes_size = 0;
				unsigned char* classBytes = (unsigned char*)mz_zip_reader_extract_to_heap(&archive, i, &classBytes_size, 0);
				if (!classBytes)
				{
					mz_zip_reader_end(&archive);
					return;
				}

				jclass jaclass = Java::Env->DefineClass(nullptr, classLoader, (const jbyte*)classBytes, classBytes_size);
				if(jaclass)Java::Env->DeleteLocalRef(jaclass);
				mz_free(classBytes);
			}
			mz_zip_reader_end(&archive);
			return;
		}

		void gc()
		{
			jclass System_class = Java::Env->FindClass("java/lang/System");
			jmethodID gcID = Java::Env->GetStaticMethodID(System_class, "gc", "()V");
			Java::Env->CallStaticVoidMethod(System_class, gcID);
			Java::Env->DeleteLocalRef(System_class);
		}

		jobject newClassLoader()
		{
			jclass urlClass = Java::Env->FindClass("java/net/URL");
			jmethodID urlContructor = Java::Env->GetMethodID(urlClass, "<init>", "(Ljava/lang/String;)V");
			jstring str = Java::Env->NewStringUTF("file://ftp.yoyodyne.com/pub/files/foobar.txt");
			jobject url = Java::Env->NewObject(urlClass, urlContructor, str);
			jobjectArray urls = Java::Env->NewObjectArray(1, urlClass, url);
			jclass URLClassLoaderClass = Java::Env->FindClass("java/net/URLClassLoader");
			jmethodID URLClassLoaderContructor = Java::Env->GetMethodID(URLClassLoaderClass, "<init>", "([Ljava/net/URL;)V");
			jobject URLClassLoader = Java::Env->NewObject(URLClassLoaderClass, URLClassLoaderContructor, urls);

			Java::Env->DeleteLocalRef(urlClass);
			Java::Env->DeleteLocalRef(url);
			Java::Env->DeleteLocalRef(str);
			Java::Env->DeleteLocalRef(urls);
			Java::Env->DeleteLocalRef(URLClassLoaderClass);

			return URLClassLoader;
		}

		void retransformClasses()
		{
			Java::tiEnv->RetransformClasses(1, &EntityRenderer_class);
		}

		void JNICALL ClassFileLoadHook
		(
			jvmtiEnv* jvmti_env, 
			JNIEnv* jni_env, 
			jclass class_being_redefined, 
			jobject loader, 
			const char* name, 
			jobject protection_domain, 
			jint class_data_len, 
			const unsigned char* class_data, 
			jint* new_class_data_len, 
			unsigned char** new_class_data
		)
		{
			std::function<void(const std::string&, const std::string&)> patchClass = [=](const std::string& patchMethod, const std::string& methodToPatch)
			{
				jclass ClassPatcherClass = Java::findClass(jni_env, jvmti_env, "io/github/lefraudeur/ClassPatcher");
				jbyteArray original_class_bytes = jni_env->NewByteArray(class_data_len);
				jni_env->SetByteArrayRegion(original_class_bytes, 0, class_data_len, (const jbyte*)class_data);

				jmethodID patchMethodID = jni_env->GetStaticMethodID(ClassPatcherClass, patchMethod.c_str(), "([BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)[B");
				jstring methodToPatchStr = jni_env->NewStringUTF(methodToPatch.c_str());
				jstring ThreadContextClassName = jni_env->NewStringUTF("org/apache/logging/log4j/ThreadContext");
				jstring emptyMapName = jni_env->NewStringUTF("EMPTY_MAP");

				jbyteArray new_class_bytes = (jbyteArray)jni_env->CallStaticObjectMethod(
					ClassPatcherClass,
					patchMethodID,
					original_class_bytes,
					methodToPatchStr,
					ThreadContextClassName,
					emptyMapName
				);

				jni_env->DeleteLocalRef(ClassPatcherClass);
				jni_env->DeleteLocalRef(methodToPatchStr);
				jni_env->DeleteLocalRef(ThreadContextClassName);
				jni_env->DeleteLocalRef(emptyMapName);

				jni_env->DeleteLocalRef(original_class_bytes);
				*new_class_data_len = jni_env->GetArrayLength(new_class_bytes);
				jvmti_env->Allocate(*new_class_data_len, new_class_data);
				jni_env->GetByteArrayRegion(new_class_bytes, 0, *new_class_data_len, (jbyte*)*new_class_data);
				jni_env->DeleteLocalRef(new_class_bytes);
			};

			if (jni_env->IsSameObject(class_being_redefined, EntityRenderer_class))
			{
				patchClass("patchEntityRenderer", "getMouseOver");
			}
		}
	}
	void Init()
	{
		jvmtiCapabilities capabilities{};
		capabilities.can_retransform_classes = JVMTI_ENABLE;
		Java::tiEnv->AddCapabilities(&capabilities);
		jvmtiEventCallbacks callbacks{};
		callbacks.ClassFileLoadHook = &ClassFileLoadHook;
		Java::tiEnv->SetEventCallbacks(&callbacks, sizeof(jvmtiEventCallbacks));
		Java::tiEnv->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, NULL);

		//here I am using an empty map, already in the game, to hide and store my cheat data, the getMouseOver than accesses this map (see asm folder)
		Java::AssignClass("net.minecraft.client.renderer.EntityRenderer", EntityRenderer_class);
		jclass ThreadContext_class = Java::findClass(Java::Env, Java::tiEnv, "org/apache/logging/log4j/ThreadContext");
		jfieldID EMPTY_MAP_ID = Java::Env->GetStaticFieldID(ThreadContext_class, "EMPTY_MAP", "Ljava/util/Map;");
		original_EMPTY_MAP = Java::Env->GetStaticObjectField(EntityRenderer_class, EMPTY_MAP_ID);
		

		jclass hashmap_class = Java::Env->FindClass("java/util/HashMap");
		jmethodID constructor = Java::Env->GetMethodID(hashmap_class, "<init>", "()V");
		EMPTY_MAP = Java::Env->NewObject(hashmap_class, constructor);
		Java::Env->SetStaticObjectField(ThreadContext_class, EMPTY_MAP_ID, EMPTY_MAP);
		Java::Env->DeleteLocalRef(hashmap_class);
		Java::Env->DeleteLocalRef(ThreadContext_class);

		put("reach_distance", "3.0");

		jobject classLoader = newClassLoader();
		loadJar(classLoader, data, sizeof(data));

		retransformClasses();
		Java::tiEnv->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_CLASS_FILE_LOAD_HOOK, NULL);

		Java::Env->DeleteLocalRef(classLoader);
		gc();
		//delete classLoader ref and call garbage collector, so that our patcher class gets unloaded
	}
	void Kill()
	{
		retransformClasses();

		jclass ThreadContext_class = Java::findClass(Java::Env, Java::tiEnv, "org/apache/logging/log4j/ThreadContext");
		jfieldID EMPTY_MAP_ID = Java::Env->GetStaticFieldID(ThreadContext_class, "EMPTY_MAP", "Ljava/util/Map;");
		Java::Env->SetStaticObjectField(ThreadContext_class, EMPTY_MAP_ID, original_EMPTY_MAP);

		Java::Env->DeleteLocalRef(ThreadContext_class);
		Java::Env->DeleteLocalRef(original_EMPTY_MAP);
		Java::Env->DeleteLocalRef(EMPTY_MAP);
		Java::Env->DeleteLocalRef(EntityRenderer_class);
	}
	void put(const std::string& key, const std::string& value)
	{
		jclass map_class = Java::Env->FindClass("java/util/Map");
		jmethodID putID = Java::Env->GetMethodID(map_class, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
		Java::Env->DeleteLocalRef(map_class);

		jstring k = Java::Env->NewStringUTF(key.c_str());
		jstring v = Java::Env->NewStringUTF(value.c_str());
		jobject rs = Java::Env->CallObjectMethod(EMPTY_MAP, putID, k, v);

		Java::Env->DeleteLocalRef(k);
		Java::Env->DeleteLocalRef(v);
		Java::Env->DeleteLocalRef(rs);
	}
}
