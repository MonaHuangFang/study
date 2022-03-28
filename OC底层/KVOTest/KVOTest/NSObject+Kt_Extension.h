//
//  NSObject+Kt_Extension.h
//  KVOTest
//
//  Created by 黄方 on 2022/3/27.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSObject (Kt_Extension)

typedef void (^Kt_Block_Observer)(id _Nullable newVal, id _Nullable oldVal);
/** 为对象添加 KVO 观察者是自己*/
- (void)kt_addObserverKeyPath:(NSString*)keyPath block:(Kt_Block_Observer)block;
/** 为对象添加 KVO 观察者是 observer */
- (void)kt_addObserver:(NSObject*)observer forKeyPath:(NSString *)keyPath block:(Kt_Block_Observer)block;
/** 为对象添加一次 KVO 并且只执行一次 对象 观察者是自己*/
- (void)kt_addObserverKeyPath:(NSString*)keyPath onceBlock:(Kt_Block_Observer)block;
/** 为对象添加一次 KVO 并且只执行一次 对象 观察者是 observer */
- (void)kt_addObserver:(NSObject*)observer forKeyPath:(NSString *)keyPath onceBlock:(Kt_Block_Observer)block;
/** 为对象移除 KVO, 观察者是自己 */
- (void)kt_removeObserverKeyPath:(NSString *)keyPath;
/** 为对象移除 KVO, 观察者是 observer */
- (void)kt_removeObserver:(NSObject*)observer forKeyPath:(NSString *)keyPath;
/** 为对象移除所有通过此分类添加的 KVO 对象 */
- (void)kt_removeAllObserverForKeyPath:(NSString *)keyPath;

@end

NS_ASSUME_NONNULL_END
