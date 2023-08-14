#include "java.h"

JavaVM* vm;
jobject classLoader;
jmethodID mid_findClass;

void setupClassLoader()
{
    jclass c_Thread = Java::Env->FindClass("java/lang/Thread");
    jclass c_Map = Java::Env->FindClass("java/util/Map");
    jclass c_Set = Java::Env->FindClass("java/util/Set");
    jclass c_ClassLoader = Java::Env->FindClass("java/lang/ClassLoader");

    jmethodID mid_getAllStackTraces = Java::Env->GetStaticMethodID(c_Thread, "getAllStackTraces", "()Ljava/util/Map;");
    jmethodID mid_keySet = Java::Env->GetMethodID(c_Map, "keySet", "()Ljava/util/Set;");
    jmethodID mid_toArray = Java::Env->GetMethodID(c_Set, "toArray", "()[Ljava/lang/Object;");
    jmethodID mid_getContextClassLoader = Java::Env->GetMethodID(c_Thread, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
    mid_findClass = Java::Env->GetMethodID(c_ClassLoader, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    jmethodID mid_currentThread = Java::Env->GetStaticMethodID(c_Thread, "currentThread", "()Ljava/lang/Thread;");

    jobject obj_stackTracesMap = Java::Env->CallStaticObjectMethod(c_Thread, mid_getAllStackTraces);
    jobject obj_threadsSet = Java::Env->CallObjectMethod(obj_stackTracesMap, mid_keySet);

    jobjectArray threads = (jobjectArray)Java::Env->CallObjectMethod(obj_threadsSet, mid_toArray);
    jint szThreads = Java::Env->GetArrayLength(threads);

    for (int i = 0; i < szThreads; i++)
    {
        jobject thread = Java::Env->GetObjectArrayElement(threads, i);
        jobject classLoaderObj = Java::Env->CallObjectMethod(thread, mid_getContextClassLoader);

        if (classLoaderObj) {
            
            jstring className = Java::Env->NewStringUTF("net.minecraft.client.Minecraft");
            jobject minecraftClass = Java::Env->CallObjectMethod(classLoaderObj, mid_findClass, className);

            if (minecraftClass)
            {
                classLoader = classLoaderObj;

                Java::Env->DeleteLocalRef(minecraftClass);

                break;
            }
        }

        Java::Env->DeleteLocalRef(thread);
    }

    Java::Env->DeleteLocalRef(threads);
    Java::Env->DeleteLocalRef(obj_stackTracesMap);
    Java::Env->DeleteLocalRef(obj_threadsSet);
    Java::Env->DeleteLocalRef(c_Thread);
    Java::Env->DeleteLocalRef(c_Map);
    Java::Env->DeleteLocalRef(c_Set);
    Java::Env->DeleteLocalRef(c_ClassLoader);

    Java::Initialized = true;
}

void Java::Init()
{
    Java::Initialized = false;

    // Check if there is any Java VMs in the injected thread
    jsize count;
    if (JNI_GetCreatedJavaVMs(&vm, 1, &count) != JNI_OK || count == 0)
        return;


    jint res = vm->GetEnv((void**)&Java::Env, JNI_VERSION_1_6);

    if (res == JNI_EDETACHED)
        res = vm->AttachCurrentThread((void**)&Java::Env, nullptr);

    if (res != JNI_OK)
        return;

    if (Java::Env == nullptr)
        vm->DestroyJavaVM();

    vm->GetEnv((void**)&Java::tiEnv, JVMTI_VERSION);
    setupClassLoader();
}

void Java::Kill()
{
    vm->DetachCurrentThread();
}

bool Java::AssignClass(std::string name, jclass &out)
{
    jstring className = Java::Env->NewStringUTF(name.c_str());
    jobject findClass = Java::Env->CallObjectMethod(classLoader, mid_findClass, className);

    if (findClass)
    {
        out = (jclass)findClass;
        return true;
    }
        
    return false;
}

jclass Java::findClass(JNIEnv* p_env, jvmtiEnv* p_tienv, const std::string& path)
{
    jint class_count = 0;
    jclass* classes = nullptr;
    jclass foundclass = nullptr;
    p_tienv->GetLoadedClasses(&class_count, &classes);
    for (int i = 0; i < class_count; ++i)
    {
        char* signature_buffer = nullptr;
        p_tienv->GetClassSignature(classes[i], &signature_buffer, nullptr);
        std::string signature = signature_buffer;
        p_tienv->Deallocate((unsigned char*)signature_buffer);
        signature = signature.substr(1);
        signature.pop_back();
        if (signature == path)
        {
            foundclass = (jclass)p_env->NewLocalRef(classes[i]);
        }
        p_env->DeleteLocalRef(classes[i]);
    }
    p_tienv->Deallocate((unsigned char*)classes);
    return foundclass;
}
