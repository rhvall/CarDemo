//
//  AppDelegate.h
//  OpenGLCoursework
//
//  Created by RHVT on 11/20/11.
//  Copyright (c) 2011 Mittra Software. All rights reserved.
//
//
//	           (\___/)
//             (o\ /o)
//            /|:.V.:|\
//		      \\::::://
//        -----`"" ""`-----

#import <UIKit/UIKit.h>
#import "MainViewController.h"


@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    UIWindow *window;
    MainViewController *viewCller;
}

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) MainViewController *viewCller;

@end
