//
// Created by Zachary Moore on 4/16/22.
//

#ifndef ANDROID_AUDIOSTREAMMANAGER_H
#define ANDROID_AUDIOSTREAMMANAGER_H


#include <oboe/Oboe.h>
#include <vector>
#include <jni.h>
#include "AudioObserver.h"
#include "Buffer.h"
#include "AudioCorrelator.h"

class AudioStreamManager : public oboe::AudioStreamCallback {
public:
    AudioStreamManager();
    ~AudioStreamManager();

    void setEnabled(bool isEnabled);
    void clearObservers();
    void addObserver(std::unique_ptr<AudioObserver> observer);

    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeStream,
                                          void *audioData, int32_t numFrames) override;

    void onErrorBeforeClose(oboe::AudioStream *oboeStream, oboe::Result error) override;
    void onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) override;


private:
    static const char* TAG;

    Buffer *mBuffer = nullptr;
    AudioCorrelator *mAudioCorrelator = nullptr;

    std::vector<std::unique_ptr<AudioObserver>> mObservers;

    oboe::AudioStream *mRecordingStream = nullptr;

    bool mActive = false;

    oboe::AudioStreamBuilder *setupRecordingStreamParameters(
            oboe::AudioStreamBuilder *builder) const;
    void openStreams();
    void closeStreams();
    static void closeStream(oboe::AudioStream *stream);
};


#endif //ANDROID_AUDIOSTREAMMANAGER_H
