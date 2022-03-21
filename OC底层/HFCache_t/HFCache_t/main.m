//
//  main.m
//  HFCache_t
//
//  Created by 黄方 on 2022/3/12.
//

#import <Foundation/Foundation.h>
#import "HFPerson.h"
#import <objc/runtime.h>

typedef uint32_t mask_t;

struct hf_bucket_t {
    SEL _sel;
    IMP _imp;
};

struct hf_cache_t {
    struct hf_bucket_t *       _buckets;
    mask_t                     _mask;
    uint16_t                   _flags;
    uint16_t                   _occupied;
};

struct hf_class_data_bits_t {
    uintptr_t bits;
};

struct hf_objc_class {
    Class ISA;
    Class superclass;
    struct hf_cache_t cache;             // formerly cache pointer and vtable
    struct hf_class_data_bits_t bits;
};

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        HFPerson *p  = [HFPerson alloc];
        Class pClass = [HFPerson class];
        [p say1];
        [p say2];
//        [p say3];
//        [p say4];
        
        struct hf_objc_class *hf_pClass = (__bridge struct hf_objc_class *)pClass;
        NSLog(@"%hu - %u",hf_pClass->cache._occupied,hf_pClass->cache._mask);
        for (mask_t i = 0; i<hf_pClass->cache._mask; i++) {
            struct hf_bucket_t bucket = hf_pClass->cache._buckets[i];
            NSLog(@"%@-%p",NSStringFromSelector(bucket._sel),bucket._imp);
        }
        NSLog(@"Hello, World!");
    }
    return 0;
}
