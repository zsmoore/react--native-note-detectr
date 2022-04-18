//
// Created by Zachary Moore on 4/10/22.
//

#ifndef ANDROID_BUFFER_H
#define ANDROID_BUFFER_H

#include <cstdint>
#include <memory>
#include <vector>

class Buffer {
public:
    Buffer(int32_t sampleRate);
    ~Buffer();

    bool addToBuffer(float *data, int32_t numElements);
    void flushBuffer();

    float* getData();
    int32_t getBufferSize() const;

private:
    int32_t mMaxSize;

    float *mBuffer = nullptr;
    int32_t mCurrentSize;
};



#endif //ANDROID_BUFFER_H
