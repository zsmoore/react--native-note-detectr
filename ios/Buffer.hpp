//
//  Buffer.hpp
//  NoteDetectr
//
//  Created by Zachary Moore on 4/16/22.
//  Copyright © 2022 Facebook. All rights reserved.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include <stdio.h>
#include <cstdint>
#include <memory>
#include <vector>

class Buffer {
public:
    Buffer(double sampleRate);
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

#endif /* Buffer_hpp */
