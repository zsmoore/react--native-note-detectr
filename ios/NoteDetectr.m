#import "NoteDetectr.h"
#import "AudioStreamManagerObjC.h"
#import <React/RCTLog.h>

@implementation NoteDetectr {
    AudioStreamManagerObjC *manager;
    NSMutableArray<NSString *> *eventsToPushTo;
}

- (NSArray<NSString *> *)supportedEvents {
    if (eventsToPushTo == nil) {
        eventsToPushTo = [[NSMutableArray alloc] init];
    }
    return eventsToPushTo;
}

RCT_EXPORT_METHOD(startStream) {
    if (self->manager == nil) {
        self->manager = [[AudioStreamManagerObjC alloc] init];
    }
}

RCT_EXPORT_METHOD(setEnabled) {
    if (self->manager == nil) {
        RCTLogInfo(@"Tried to enable when manager is nil");
        return;
    }
    [self->manager setEnabled:true];
}

RCT_EXPORT_METHOD(endStream) {
  if (self->manager == nil) {
    RCTLogInfo(@"Tried to endStream when manager is nil");
    return;
  }
  [self->manager setEnabled:false];
}

RCT_EXPORT_METHOD(clearObservers) {
    if (self->manager == nil) {
        RCTLogInfo(@"Tried to clear observers when manager is nil");
        return;
    }
    [self->manager clearObservers];
}

RCT_EXPORT_METHOD(listenToStream:(NSString *)frequencyEventId) {
    if (self->manager == nil) {
      RCTLogInfo(@"Tried to add observers when manager is nil");
      return;
    }
    
    if (eventsToPushTo == nil) {
        eventsToPushTo = [[NSMutableArray alloc] init];
    }
    [eventsToPushTo addObject:frequencyEventId];
    
    __unsafe_unretained typeof(self) weakSelf = self;
    [self->manager addObserver:^(float frequency) {
      [weakSelf sendFrequencyAudioEvent:frequencyEventId data:frequency];
    }];
}

- (void)sendFrequencyAudioEvent:(NSString *)eventToPushTo data:(float)data {
  [self sendEventWithName:eventToPushTo
                     body:@{@"FREQUENCY_DATA": [NSNumber numberWithFloat:data]}];
}

RCT_EXPORT_MODULE(ABC)

@end
