//
//  main.c
//  005-Stack
//
//  Created by Huangf on 2020/4/13.
//  Copyright © 2020 Huangf. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */

//顺序栈结构
typedef struct {
    SElemType data[MAXSIZE];
    int top;
}OrderStack;


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
