//
//  GLView.h
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

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "mach/mach_time.h"
#import "Renderer.hpp"

@interface GLView : UIView
{
    float       mTimestamp;
    
    EAGLContext *mContext;
    
    Renderer    *mRenderer;
    
    Vector2 centerPoint;
    Vector2 screenSize;
    
    float trackBall;
}

-(void)drawView:(CADisplayLink *)displayLink;
-(void)didRotate:(NSNotification *)notification;
-(void)changeObject:(int)selectedObject;


@end
