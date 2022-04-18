//
// Created by Zachary Moore on 4/16/22.
//

#include <limits>
#include <cmath>
#include "AudioCorrelator.h"

float AudioCorrelator::getFundamentalFrequency(float *audioData, int32_t numSamples,
                                               int32_t sampleRate) {
    float *autoCorrelation = autoCorrelationWithShiftingLag(audioData, numSamples);
    float *normalized = scaleToMax(autoCorrelation, numSamples);
    float freq = getFrequency(normalized, numSamples, sampleRate);
    return getFundamentalFrequency(freq);
}

float *AudioCorrelator::autoCorrelationWithShiftingLag(const float *audioData,int32_t numSamples) {
    auto *autoCorrelation = new float[numSamples];
    for (int32_t lag = 0; lag < numSamples; lag++) {
        *(autoCorrelation + lag) = autoCorrelate(audioData, numSamples, lag);
    }
    return autoCorrelation;
}

float AudioCorrelator::autoCorrelate(const float *audioData,  int32_t numSamples, int32_t lag) {
    float sum = 0;
    for (int i = 0; i <= numSamples - lag; i++) {
        float sampleAtIndex = *(audioData + i);
        float sampleAtIndexPlusLag = *(audioData + (i + lag));
        sum += (sampleAtIndex * sampleAtIndexPlusLag);
    }
    return sum;
}

float *AudioCorrelator::scaleToMax(float *audioData, int32_t numSamples) {
    float max = std::numeric_limits<float>::min();
    for (int i = 0; i < numSamples; i++) {
        if (*(audioData + i) > max) {
            max = *(audioData + i);
        }
    }
    max = abs(max);
    for (int i = 0; i < numSamples; i++) {
        *(audioData + i) = (*(audioData + i) / max);
    }

    return audioData;
}

float AudioCorrelator::getFrequency(const float *audioData, int32_t numSamples,
                                    int32_t sampleRate) {
    float sum = 0;
    int32_t pdState = 0;
    float period = 0;

    for (int i = 0; i < numSamples; i++) {
        mSumOld = sum;
        sum = *(audioData + i);

        if (pdState == 2 && sum - mSumOld <= 0) {
            period = (float) i;
            pdState = 3;
        }

        if (pdState == 1 && sum > mThreshold && sum - mSumOld > 0) {
            pdState = 2;
        }

        if (i == 0) {
            mThreshold = sum * 0.5f;
            pdState = 1;
        }
    }

    return (float) sampleRate / period;
}

float AudioCorrelator::getFundamentalFrequency(float frequency) {
    for (int i = 1; i <= 5; i++) {
        float currentHarmonic = frequency / (float) i;
        if (currentHarmonic < 350) {
            return currentHarmonic;
        }
    }
    return frequency;
}
