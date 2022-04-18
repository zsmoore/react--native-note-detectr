//
// Created by Zachary Moore on 4/16/22.
//
#include <jni.h>
#include <android/log.h>

#include <memory>
#include "AudioStreamManager.h"

static AudioStreamManager *manager = nullptr;
static JavaVM *jvm = nullptr;

extern "C" {
JNIEXPORT jboolean JNICALL
Java_com_reactnativenotedetectr_NoteDetectrModule_create(JNIEnv *env,
                                                         jobject) {
    if (manager == nullptr) {
        env->GetJavaVM(&jvm);
        manager = new AudioStreamManager();
    }

    return (manager != nullptr) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT void JNICALL
Java_com_reactnativenotedetectr_NoteDetectrModule_delete(JNIEnv *env,
                                                         jobject) {
    if (manager) {
        manager->setEnabled(false);
        delete manager;
        manager = nullptr;
    }
}

JNIEXPORT jboolean JNICALL
Java_com_reactnativenotedetectr_NoteDetectrModule_setEnabled(JNIEnv *env,
                                                             jobject,
                                                             jboolean isEnabled) {
    if (manager == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "react-native-note-detectr", "Did not create manager");
        return JNI_FALSE;
    }
    manager->setEnabled(isEnabled);
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL
Java_com_reactnativenotedetectr_NoteDetectrModule_addObserver(JNIEnv *env,
                                                              jobject,
                                                              jobject observer) {
    if (manager == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "react-native-note-detectr", "Did not create manager");
        return JNI_FALSE;
    }
    manager->addObserver(std::make_unique<AudioObserver>(jvm, env, observer));
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL
Java_com_reactnativenotedetectr_NoteDetectrModule_clearObservers(JNIEnv *env,
                                                                 jobject) {
    if (manager == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "react-native-note-detectr", "Did not create manager");
        return JNI_FALSE;
    }
    manager->clearObservers();
    return JNI_TRUE;
}
}
