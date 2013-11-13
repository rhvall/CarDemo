//
//  MainViewController.h
//  OpenGLCoursework
//
//  Created by RHVT on 08/11/12.
//  Copyright (c) 2012 Mittra Software. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"

@interface MainViewController : UIViewController
                                <UITableViewDataSource, UITableViewDelegate>
{
    IBOutlet GLView *glView;
    IBOutlet UITableView *viewTbl;
    NSArray *arrList;
}

@property (strong, nonatomic) IBOutlet GLView *glView;
@property (strong, nonatomic) IBOutlet UITableView *viewTbl;
@property (strong, nonatomic) NSArray *arrList;

@end
