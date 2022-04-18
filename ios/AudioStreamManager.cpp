//
//  AudioStreamManager.cpp
//  NoteDetectr
//
//  Created by Zachary Moore on 4/16/22.
//  Copyright © 2022 Facebook. All rights reserved.
//
#include "AudioStreamManager.hpp"
#include <limits>

AudioStreamManager::AudioStreamManager() {
    mAudioCorrelator = new AudioCorrelator();
}

AudioStreamManager::~AudioStreamManager() {
    delete mBuffer;
    delete mAudioCorrelator;
}

void AudioStreamManager::addObserver(std::function<void(float frequency)> observer) {
    mObservers.push_back(observer);
}

void AudioStreamManager::clearObservers() {
    if (!mObservers.empty()) {
        mObservers.clear();
    }
}

void AudioStreamManager::onAudioReady(float *data, int sampleCount, double sampleRate) {
    if (mObservers.empty()) {
        return;
    }
    if (mBuffer == nullptr) {
        mBuffer = new Buffer(sampleRate);
    }
    
    if (!mBuffer->addToBuffer(data, sampleCount)) {
        float frequency = mAudioCorrelator->getFundamentalFrequency(data, sampleCount, sampleRate);
        if (frequency < 350) {
            for (auto &observer: mObservers) {
                observer(frequency);
            }
        }
        mBuffer->flushBuffer();
    }
}
