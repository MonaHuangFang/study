//
//  main.c
//  008-StackWork
//
//  Created by 黄方 on 2020/4/21.
//  Copyright © 2020 黄方. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
题目:• 去除重复字母(LeetCode-困难)
给你一个仅包含小写字母的字符串，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证返回结果的字典序最小（要求不能打乱其他字符的相对位置）
示例1:
输入:"bcabc"
输出:"abc"

示例2:
输入:"cbacdcbc"
输出:"acdb"
*/

char *removeDuplicateLetters(char *s){
    if (s==NULL || strlen(s)==0) {
        return "";
    }
    if (strlen(s) == 1) {
        return s;
    }
    
    //创建record数组，用来记录s中每个字符出现的次数
    char record[26] = {0};
    int len = (int)strlen(s);
    for (int i = 0; i<len; i++) {
        record[s[i] - 'a']++;
    }
    
    //申请一个字符串stack;(用栈的特性来进行stack字符串的数据进出)
    char *stack = (char*)malloc((len+1) * sizeof(char));
    memset(stack, 0, (len+1) * sizeof(char));
    int top = -1;
    
    for (int i = 0; i<len; i++) {
        int isExist = 0;
        //获取当前字母是否以存在stack中
        for (int j = 0; j<=top; j++) {
            if (s[i] == stack[j]) {
                isExist = 1;
                break;
            }
        }
        
        if (isExist) {
            //当s[i]已存在stack中，该字母记录的次数减1，遍历下一个字母
            record[s[i]-'a']--;
        }else{
            //比较字母s[i]和stack[top],如果stack[top]大于s[i]，且record中stack[top]的次数大于0,stack[top]出栈，循环比较，直到不再满足上面的条件或top等于-1,跳出循环
            while (top >-1 && s[i]<stack[top] && record[stack[top]-'a']>0) {
                top--;
            }
            top++;
            //s[i]入栈
            stack[top] = s[i];
            record[s[i]- 'a']--;
        }
    }
    //结束栈顶添加字符结束符
    stack[++top] = '\0';
    return stack;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    char *s ;
    s = removeDuplicateLetters("bcabc");
    printf("%s\n",s);
    
    s = removeDuplicateLetters("zab");
    printf("%s\n",s);

    s = removeDuplicateLetters("cbacdcbc");
    printf("%s\n",s);
    return 0;
}
