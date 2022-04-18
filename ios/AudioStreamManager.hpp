//
//  AudioStreamManager.hpp
//  NoteDetectr
//
//  Created by Zachary Moore on 4/16/22.
//  Copyright © 2022 Facebook. All rights reserved.
//

#ifndef AudioStreamManager_hpp
#define AudioStreamManager_hpp

#include <stdio.h>
#include <vector>
#include "Buffer.hpp"
#include "AudioCorrelator.hpp"

class AudioStreamManager {
public:
    AudioStreamManager();
    ~AudioStreamManager();
    void clearObservers();
    void addObserver(std::function<void(float frequency)> observer);
    void onAudioReady(float *data, int sampleCount, double sampleRate);
private:
    
    Buffer *mBuffer = nullptr;
    AudioCorrelator *mAudioCorrelator = nullptr;
    
    std::vector<std::function<void(float frequency)>> mObservers;
};

#endif /* AudioStreamManager_hpp */
