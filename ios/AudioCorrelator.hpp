//
//  AudioCorrelator.hpp
//  NoteDetectr
//
//  Created by Zachary Moore on 4/16/22.
//  Copyright © 2022 Facebook. All rights reserved.
//

#ifndef AudioCorrelator_hpp
#define AudioCorrelator_hpp

#include <stdio.h>
#include <cstdint>

class AudioCorrelator {
public:
    float getFundamentalFrequency(float *audioData, int32_t numSamples, int32_t sampleRate);

private:
    float mSumOld = 0;
    float mThreshold = 0;

    static float *autoCorrelationWithShiftingLag(const float *audioData, int32_t numSamples);
    static float autoCorrelate(const float *audioData,  int32_t numSamples, int32_t lag);
    static float *scaleToMax(float *audioData, int32_t numSamples);
    float getFrequency(const float *audioData, int32_t numSamples, int32_t sampleRate);
    static float getFundamentalFrequency(float frequency);
};

#endif /* AudioCorrelator_hpp */
