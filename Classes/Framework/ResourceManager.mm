//
//  ResourceManager.m
//  CarDemo
//
//  Created by RHVT on 27/11/12.
//  Copyright (c) 2012 Mittra Software. All rights reserved.
//

#import "ResourceManager.h"

string ResourceManager::getResourcePath()
{
    NSString *bundlePath = [[NSBundle mainBundle] resourcePath];
    return [bundlePath UTF8String];
}

GLuint ResourceManager::generateTexture(const std::string &name)
{
    GLuint texture;
    glGenTextures(1, &texture);
  
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    NSString *basePath = [[NSString alloc] initWithUTF8String:name.c_str()];
    
    NSBundle *mainBundle = [NSBundle mainBundle];
    NSString *fullPath = [mainBundle pathForResource:basePath
                                              ofType:@"png"];
    UIImage *uiImage = [[UIImage alloc] initWithContentsOfFile:fullPath];
    CGImageRef cgImage = uiImage.CGImage;
    
    GLuint width = CGImageGetWidth(cgImage);
    GLuint height = CGImageGetHeight(cgImage);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void *imageData = malloc(height * width * 4);
    CGContextRef context = CGBitmapContextCreate(imageData, width, height, 8, 4 * width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);
    CGContextClearRect(context, CGRectMake(0, 0, width, height));
    CGContextTranslateCTM(context, 0, height - height);
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), cgImage);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBlendFunc(GL_ONE, GL_SRC_COLOR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    CGContextRelease(context);
    
    free(imageData);
    [uiImage release];
    
    
    
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}