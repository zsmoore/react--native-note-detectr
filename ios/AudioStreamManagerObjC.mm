//
//  AudioStreamManagerObjC.m
//  NoteDetectr
//
//  Created by Zachary Moore on 4/16/22.
//  Copyright © 2022 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFAudio/AVAudioSession.h>
#import <AVFAudio/AVAudioEngine.h>
#import <AVFAudio/AVAudioFormat.h>
#import "AudioStreamManagerObjC.h"
#import "AudioStreamManager.hpp"
#import <memory>

@implementation AudioStreamManagerObjC {
    AVAudioEngine *engine;
    std::unique_ptr<AudioStreamManager> audioManager;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        audioManager.reset(new AudioStreamManager());
    }
    return self;
}

- (void)setEnabled:(BOOL)enabled {
    if (enabled) {
        [self openStreams];
    } else {
        [self closeStreams];
    }
}

- (void)clearObservers {
    self->audioManager->clearObservers();
}

- (void)addObserver:(void (^)(float))observer {
    self->audioManager->addObserver([observer](float freq) {
        observer(freq);
    });
}


- (void)closeStreams {
    [self ->engine stop];
}

- (void)openStreams {
    self->engine = [[AVAudioEngine alloc] init];
    AVAudioInputNode *input = [self->engine inputNode];
    AVAudioFormat *format = [input inputFormatForBus:0];
    [self->engine.inputNode installTapOnBus:0
                                 bufferSize:([format sampleRate] / 10)
                                     format:format
                                      block: ^(AVAudioPCMBuffer *buf, AVAudioTime *when) {
        float *audioData = [buf floatChannelData][0];
        int sampleCount = [buf frameLength];
        self->audioManager->onAudioReady(audioData, sampleCount, [format sampleRate]);
    }];
    
    [self->engine prepare];
    [self->engine startAndReturnError:nil];
}

@end
