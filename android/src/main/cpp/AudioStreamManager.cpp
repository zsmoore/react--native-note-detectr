//
// Created by Zachary Moore on 4/16/22.
//

#include "AudioStreamManager.h"
#include <android/log.h>
#include <limits>

AudioStreamManager::AudioStreamManager() {
    mAudioCorrelator = new AudioCorrelator();
}

AudioStreamManager::~AudioStreamManager() {
    closeStreams();
    delete mBuffer;
    delete mAudioCorrelator;
}

void AudioStreamManager::addObserver(std::unique_ptr<AudioObserver> observer) {
    mObservers.push_back(std::move(observer));
}

void AudioStreamManager::clearObservers() {
    if (!mObservers.empty()) {
        mObservers.clear();
    }
}

void AudioStreamManager::setEnabled(bool isEnabled) {
    if (isEnabled != mActive) {
        mActive = isEnabled;
        if (mActive) {
            openStreams();
        } else {
            closeStreams();
        }
    }
}

oboe::DataCallbackResult
AudioStreamManager::onAudioReady(oboe::AudioStream *oboeStream, void *audioData,
                                 int32_t numFrames) {
    if (mObservers.empty()) {
        return oboe::DataCallbackResult::Continue;
    }
    if (mBuffer == nullptr) {
        mBuffer = new Buffer(oboeStream->getSampleRate());
    }

    auto *inputFloats = static_cast<float *>(audioData);
    // Add to buffer, if not successful call observers and flush buffer
    if (!mBuffer->addToBuffer(inputFloats, numFrames)) {
        float frequency = mAudioCorrelator->getFundamentalFrequency(mBuffer->getData(),
                                                                    mBuffer->getBufferSize(),
                                                                    oboeStream->getSampleRate());
        for (auto &observer: mObservers) {
            if (frequency < 350) {
                observer->callSelf(frequency);
            }
        }
        mBuffer->flushBuffer();
    }

    return oboe::DataCallbackResult::Continue;
}

void AudioStreamManager::closeStreams() {
    closeStream(mRecordingStream);
}

void AudioStreamManager::openStreams() {
    oboe::AudioStreamBuilder inBuilder;
    setupRecordingStreamParameters(&inBuilder);
    inBuilder.openStream(&mRecordingStream);
    mRecordingStream->requestStart();
}

const char* AudioStreamManager::TAG = "AudioStreamManager";

void AudioStreamManager::closeStream(oboe::AudioStream *stream) {
    if (stream) {
        oboe::Result result = stream->close();
        if (result != oboe::Result::OK) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "Error closing stream. %s", oboe::convertToText(result));
        }
        __android_log_print(ANDROID_LOG_WARN, TAG, "Stream closed");
    }
}

oboe::AudioStreamBuilder *AudioStreamManager::setupRecordingStreamParameters(
        oboe::AudioStreamBuilder *builder) const {
    return builder->setFormat(oboe::AudioFormat::Float)
            ->setDirection(oboe::Direction::Input)
            ->setSharingMode(oboe::SharingMode::Exclusive)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setCallback((AudioStreamCallback *) this)
    ->setChannelCount(1);
}

void AudioStreamManager::onErrorBeforeClose(oboe::AudioStream *oboeStream, oboe::Result error) {
    AudioStreamErrorCallback::onErrorBeforeClose(oboeStream, error);
}

void AudioStreamManager::onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) {
    AudioStreamErrorCallback::onErrorAfterClose(oboeStream, error);
}
