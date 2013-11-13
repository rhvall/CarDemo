//
//  MainViewController.m
//  OpenGLCoursework
//
//  Created by RHVT on 08/11/12.
//  Copyright (c) 2012 Mittra Software. All rights reserved.
//

#import "MainViewController.h"

@implementation MainViewController

@synthesize glView;
@synthesize viewTbl;
@synthesize arrList;

//----------------------------------------
//	INITIALIZATION
//----------------------------------------
#pragma mark -
#pragma mark INITIALIZATION

-(id)initWithNibName:(NSString *)nibNameOrNil
               bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        arrList = [[NSArray alloc] initWithObjects:@"Patas Traseras",
                   @"Patas Delanteras", @"Textura", nil];
    }
    return self;
}

-(void)dealloc
{
    [viewTbl release];
    [glView release];
    [super dealloc];
}
-(void)viewDidLoad
{
    [super viewDidLoad];
    
    CGRect fullScreen = [[UIScreen mainScreen] bounds];
    CGRect tableFrame = [viewTbl frame];
    CGRect available = CGRectMake(0, tableFrame.size.height, fullScreen.size.width, fullScreen.size.height - tableFrame.size.height);
//    CGRect available = [[UIScreen mainScreen] bounds];
//    DLog(@"(%f, %f, %f, %f)", available.origin.x, available.origin.y, available.size.width, available.size.height);
    glView = [[GLView alloc] initWithFrame:available];
    [self.view addSubview:glView];
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//----------------------------------------
//  TABLEVIEW LIFECYCLE
//----------------------------------------
#pragma mark -
#pragma mark TABLEVIEW LIFECYCLE

-(UITableViewCell *)tableView:(UITableView *)tableView
        cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *cellIdentifier = @"elementCell";
    
    UITableViewCell *aCellElement = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    
    if (aCellElement == nil)
    {
        aCellElement = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1
                                              reuseIdentifier:@"cell"];
    }
    
    aCellElement.textLabel.text = [arrList objectAtIndex:indexPath.row];
    aCellElement.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return aCellElement;
}

-(NSInteger)tableView:(UITableView *)tableView
numberOfRowsInSection:(NSInteger)section
{
    return [arrList count];
}

-(void)tableView:(UITableView *)tableView
didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [glView changeObject:indexPath.row];
}





@end
