//
// Created by bytedance on 2021/2/10.
//

#include <jni.h>
#include <iostream>

void crashTest(JNIEnv *env, jobject thiz);

static JNINativeMethod gMethods[] = {
        {"nativeCrashTest", "()V", (void *) crashTest},
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jclass mainActivityClass = env->FindClass("com/hiro/nativecrashtest/MainActivity");
    if (mainActivityClass == nullptr) {
        return JNI_ERR;
    }
    // 动态注册 kotlin/java 方法
    env->RegisterNatives(mainActivityClass, gMethods, sizeof(gMethods) / sizeof(JNINativeMethod));
    return JNI_VERSION_1_6;
}

void crashTest(JNIEnv *env, jobject thiz) {
    // trigger native crash
    std::string *str = nullptr;
    str->data();
}