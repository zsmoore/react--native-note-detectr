//
// Created by Zachary Moore on 4/10/22.
//

#include "Buffer.h"

Buffer::Buffer(int32_t sampleRate) {
    mMaxSize = sampleRate / 10;
    mCurrentSize = 0;
    mBuffer = new float[mMaxSize];
}

Buffer::~Buffer() {
    delete[] mBuffer;
}

void Buffer::flushBuffer() {
    mCurrentSize = 0;
}

bool Buffer::addToBuffer(float *data, int32_t numElements) {
    if (numElements + mCurrentSize > mMaxSize) {
        return false;
    }
    memcpy(mBuffer + mCurrentSize, data, numElements * sizeof(float));
    mCurrentSize += numElements;
    return true;
}

float* Buffer::getData() {
    return mBuffer;
}

int32_t Buffer::getBufferSize() const {
    return mCurrentSize;
}
