//
// Created by Zachary Moore on 4/16/22.
//

#ifndef ANDROID_AUDIOCORRELATOR_H
#define ANDROID_AUDIOCORRELATOR_H

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


#endif //ANDROID_AUDIOCORRELATOR_H
