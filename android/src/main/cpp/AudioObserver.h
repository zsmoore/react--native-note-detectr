//
// Created by Zachary Moore on 4/16/22.
//

#ifndef ANDROID_AUDIOOBSERVER_H
#define ANDROID_AUDIOOBSERVER_H

#include <jni.h>

class AudioObserver {
public:
    AudioObserver(JavaVM *jvm, JNIEnv *env, jobject originalObserver);
    ~AudioObserver();
    void callSelf(float frequency);

private:
    JavaVM *mJvm;
    jweak mObject = nullptr;
    jmethodID mFrequencyMethodID = nullptr;

    void initializeEnv(JNIEnv **p_env, int getEnvStat);
    static void exceptionCheck(JNIEnv *env);
};


#endif //ANDROID_AUDIOOBSERVER_H
