//
//  VideoDecoderRenderer.h
//  Moonlight
//
//  Created by Cameron Gutman on 10/18/14.
//  Copyright (c) 2014 Moonlight Stream. All rights reserved.
//

@import AVFoundation;

#import "ConnectionCallbacks.h"

#include "Limelight.h"

#if TARGET_OS_IPHONE
typedef UIView MoonshineRenderView;
#else
typedef NSView MoonshineRenderView;
#endif

// Moonshine: fan out decoded sample buffers to an optional second consumer
// (the native magnifier loupe). The sink is invoked on the decode thread for
// every frame, immediately after the frame is enqueued into the display layer.
// isKeyFrame is YES for IDR frames — the loupe runs its own decoder and must
// start from a keyframe.
typedef void (^MoonshineFrameSink)(CMSampleBufferRef _Nonnull sampleBuffer, BOOL isKeyFrame);
void MoonshineSetFrameSink(MoonshineFrameSink _Nullable sink);

@interface VideoDecoderRenderer : NSObject

- (id)initWithView:(MoonshineRenderView*)view callbacks:(id<ConnectionCallbacks>)callbacks streamAspectRatio:(float)aspectRatio useFramePacing:(BOOL)useFramePacing;

- (void)setupWithVideoFormat:(int)videoFormat width:(int)videoWidth height:(int)videoHeight frameRate:(int)frameRate;
- (void)start;
- (void)stop;
- (void)setHdrMode:(BOOL)enabled;

- (int)submitDecodeBuffer:(unsigned char *)data length:(int)length bufferType:(int)bufferType decodeUnit:(PDECODE_UNIT)du;

@end
