//
//  NSObject+Kt_Extension.m
//  KVOTest
//
//  Created by 黄方 on 2022/3/27.
//

#import "NSObject+Kt_Extension.h"
#import <NSObject+YSObserver.h>

@implementation NSObject (Kt_Extension)

- (void)kt_addObserverKeyPath:(NSString*)keyPath block:(Kt_Block_Observer)block
{
    [self kt_addObserver:self forKeyPath:keyPath block:block];
}

- (void)kt_addObserver:(NSObject*)observer forKeyPath:(NSString *)keyPath block:(Kt_Block_Observer)block
{
    NSArray *keys = [keyPath componentsSeparatedByString:@","];
    for (NSString *object in keys) {
        NSString *key = [object kt_removeSpace];
        
        [self ys_addObserver:observer forKeyPath:key withBlock:block];
    }
}

- (void)kt_addObserverKeyPath:(NSString*)keyPath onceBlock:(Kt_Block_Observer)block
{
    [self kt_addObserver:self forKeyPath:keyPath onceBlock:block];
}

- (void)kt_addObserver:(NSObject*)observer forKeyPath:(NSString *)keyPath onceBlock:(Kt_Block_Observer)block
{
    NSArray *keys = [keyPath componentsSeparatedByString:@","];
    for (NSString *object in keys) {
        NSString *key = [object kt_removeSpace];
        
        [self ys_addObserver:observer forKeyPath:key withOnceBlock:block];
    }
}

- (void)kt_removeObserverKeyPath:(NSString *)keyPath
{
    [self kt_removeObserver:self forKeyPath:keyPath];
}

- (void)kt_removeObserver:(NSObject*)observer forKeyPath:(NSString *)keyPath
{
    [self ys_removeObserver:observer forKeyPath:keyPath];
}

- (void)kt_removeAllObserverForKeyPath:(NSString *)keyPath
{
    [self ys_removeAllObserverForKeyPath:keyPath];
}

- (NSString *)kt_removeSpace
{
    return [(NSString *)self stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
}

@end
