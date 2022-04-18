//
//  AudioStreamManagerObjC.h
//  NoteDetectr
//
//  Created by Zachary Moore on 4/16/22.
//  Copyright © 2022 Facebook. All rights reserved.
//

#ifndef AudioStreamManagerObjC_h
#define AudioStreamManagerObjC_h

#import <Foundation/Foundation.h>

@interface AudioStreamManagerObjC : NSObject

- (instancetype)init;

- (void)setEnabled:(BOOL)enabled;
- (void)clearObservers;
- (void)addObserver:(void (^)(float))observer;

@end

#endif /* AudioStreamManagerObjC_h */
