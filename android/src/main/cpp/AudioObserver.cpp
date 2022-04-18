//
// Created by Zachary Moore on 4/16/22.
//

#include "AudioObserver.h"
#include <Android/log.h>

AudioObserver::AudioObserver(JavaVM *jvm,
                             JNIEnv *env,
                             jobject originalObserver) {
    mJvm = jvm;
    mObject = env->NewWeakGlobalRef(originalObserver);
    jclass clazz = env->GetObjectClass(mObject);
    mFrequencyMethodID = env->GetMethodID(clazz, "onAudioReady", "(F)V");
}

AudioObserver::~AudioObserver() {
    if(mJvm == nullptr) {
        return;
    }
    JNIEnv *jniEnv;
    // Guaranteed since we don't detach
    mJvm->GetEnv((void **) &jniEnv, JNI_VERSION_1_6);
    jniEnv->DeleteWeakGlobalRef(mObject);
    // keep thread open while observer exists
    mJvm->DetachCurrentThread();
}

void AudioObserver::callSelf(float frequency) {
    JNIEnv *jniEnv;
    int getEnvStat = mJvm->GetEnv((void **) &jniEnv, JNI_VERSION_1_6);

    initializeEnv(&jniEnv, getEnvStat);

    if (jniEnv->IsSameObject(mObject, nullptr)) {
        // object was garbage collected
        return;
    }

    jniEnv->CallVoidMethod(mObject, mFrequencyMethodID, frequency);

    exceptionCheck(jniEnv);

}

void AudioObserver::initializeEnv(JNIEnv **p_env, int getEnvStat) {
    if (getEnvStat == JNI_EDETACHED) {
        __android_log_print(ANDROID_LOG_ERROR, "AudioObserver", "detached");
        JavaVMAttachArgs args;
        args.version = JNI_VERSION_1_6;
        args.name = nullptr;
        args.group = nullptr;
        mJvm->AttachCurrentThread(p_env, &args);
    }
}

void AudioObserver::exceptionCheck(JNIEnv *env) {
    if (env->ExceptionCheck()) {
        __android_log_print(ANDROID_LOG_ERROR, "AudioObserver", "exception occurred");
        env->ExceptionDescribe();
    }
}
