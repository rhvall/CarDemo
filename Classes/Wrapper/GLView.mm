//
//  GLView.mm
//  ArrowGL
//
//  Created by RHVT on 11/18/11.
//  Copyright (c) 2011 Mittra Software. All rights reserved.
//
//
//	           (\___/)
//             (o\ /o)
//            /|:.V.:|\
//		      \\::::://
//        -----`"" ""`-----

#import "GLView.h"

@implementation GLView

//----------------------------------------
//            CLASS METHODS
//----------------------------------------
#pragma mark -
#pragma mark CLASS METHODS

+(Class)layerClass
{
    return [CAEAGLLayer class];
}

//----------------------------------------
//            INIT AND DEALLOC
//----------------------------------------
#pragma mark -
#pragma mark INIT AND DEALLOC

-(id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame])
    {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)super.layer;
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        
        mContext = [[EAGLContext alloc] initWithAPI:api];
        
        if (!mContext || ![EAGLContext setCurrentContext:mContext])
        {
            DLog(@"Not possible to initilize the current Context");
            [self release];
            return nil;
        }
        
        DLog(@"Using OpenGL ES 2.0");
        
        int width = CGRectGetWidth(frame);
        int height = CGRectGetHeight(frame);
        
        trackBall = width / 3;
        screenSize = iVector2(width, height);
        centerPoint = screenSize / 2;
        
        mRenderer = new Renderer(width, height);
        
        if (!mRenderer->hasInitialized())
        {
            DLog(@"Not possible to initilize the current Renderer");
            [self release];
            return nil;
        }
        
        [mContext renderbufferStorage:GL_RENDERBUFFER
                         fromDrawable:eaglLayer];
        
        mRenderer->startProgram();
        mRenderer->generateDepthBuffer();
        
        [self drawView:nil];
        
        mTimestamp = CACurrentMediaTime();
        
        CADisplayLink *displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self
                                                  selector:@selector(drawView:)];
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop]
                          forMode:NSDefaultRunLoopMode];

        
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(didRotate:)
                                                     name:UIDeviceOrientationDidChangeNotification
                                                   object:nil];
        [self setMultipleTouchEnabled:YES];
        
        
    }
    return self;
}

-(void)dealloc
{
    if ([EAGLContext currentContext] == mContext)
    {
        [EAGLContext setCurrentContext:nil];
    }
    
    delete mRenderer;
    
    [mContext release]; 
    [super dealloc];
}

//----------------------------------------
//            IMPLEMENTATION
//----------------------------------------
#pragma mark -
#pragma mark IMPLEMENTATION

-(void)drawView:(CADisplayLink*)displayLink
{
    if (displayLink != nil)
    {
        float elapsedSeconds = displayLink.timestamp - mTimestamp;
        mTimestamp = displayLink.timestamp;
        mRenderer->updateScene(elapsedSeconds);
    }
    
    mRenderer->renderScene();
    
    [mContext presentRenderbuffer:GL_RENDERBUFFER];
}

-(void)didRotate:(NSNotification*)notification
{
}

//----------------------------------------
//            TOUCH RECOGNITION
//----------------------------------------
#pragma mark -
#pragma mark TOUCH RECOGNITION

-(void)touchesBegan:(NSSet *)touches 
          withEvent:(UIEvent *)event
{
//    UITouch *touch = [touches anyObject];
//    CGPoint location = [touch locationInView:self];
}

-(void)touchesEnded:(NSSet *)touches
          withEvent:(UIEvent *)event
{
//    UITouch* touch = [touches anyObject];
//    CGPoint location = [touch locationInView: self];
}

-(void)touchesMoved:(NSSet *)touches
          withEvent:(UIEvent *)event
{    
    if ([touches count] == 2)
    {
        UITouch *touch1 = [[touches allObjects] objectAtIndex:0];
        UITouch *touch2 = [[touches allObjects] objectAtIndex:1];
        
        CGPoint touch1I  = [touch1 previousLocationInView:self];
        CGPoint touch1F = [touch1 locationInView:self];
        
        CGPoint touch2I  = [touch2 previousLocationInView:self];
        CGPoint touch2F = [touch2 locationInView:self];
        
        float factor = 0.2f;
        Vector2 initialV1 = Vector2(touch1I.x * factor, touch1I.y * factor);
        Vector2 finalV1 = Vector2(touch1F.x * factor, touch1F.y * factor);
        
        Vector2 initialV2 = Vector2(touch2I.x * factor, touch2I.y * factor);
        Vector2 finalV2 = Vector2(touch2F.x * factor, touch2F.y * factor);
        
        Vector2 initialV3 = initialV1 - finalV1;
        Vector2 finalV3 = initialV2 - finalV2;

        mRenderer->updateCamera(doubleMiddle, initialV3, finalV3, centerPoint, trackBall);
        
    }
    else if ([touches count] == 1)
    {
        UITouch *touch = [touches anyObject];
        CGPoint previous  = [touch previousLocationInView:self];
        CGPoint current = [touch locationInView:self];
        
        Vector2 initial = Vector2(previous.x, previous.y);
        Vector2 final = Vector2(current.x, current.y);
        
        mRenderer->updateCamera(singleMiddle, final, initial, centerPoint, trackBall);
    }
}

-(void)changeObject:(int)selectedObject
{
    mRenderer->changeSelectedObject(selectedObject);
}

@end
