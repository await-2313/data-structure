/*
        Time:   2026/2/15
        Author: await-2313
*/
// | Day1 | 串的定长数组实现 | 手写：串结构体定义+初始化+赋值+拼接+求长度 | 串拼接后长度计算正确，赋值无数组越界 |
// | Day2 | 串的基本操作 | 手写：串比较+求子串+定位子串（BF算法） | BF算法能正确找到子串首次出现位置，子串截取无越界 |
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100
typedef struct
{
    char data[MAX_SIZE];
    int length;
}String;
void init_string(String*s);
void assign_string(String* s,const char * str,int len);
String* concat_string(const String*s1,const String *s2);
int lengthString(const String *s);
int compareString(const String *s1, const String *s2);
void subString(const String *s, int pos, int len, String *sub);
int indexBF(const String *s, const String *t);

void test01()
{
    //测试串初始化、赋值、拼接
    String s;
    init_string(&s);
    
    printf("%s and length is %d \n",s.data,s.length);

    const char *str = "abcdefg";
    assign_string(&s,str,7);
    printf("%s and length is %d \n",s.data,s.length);

    String *t = concat_string(&s,&s);
    printf("%s and length is %d \n",t->data,t->length);

}
int main()
{
    test01();
    return 0;
}
void init_string(String*s)
{
    s->length = 0;
    s->data[0]='\0';
}
void assign_string(String* s,const char * str,int len)
{
    if(len>MAX_SIZE-1)
    {
        puts("error ! failed to assign_string");
        return;
    }
    for(int i=0;i<len;i++)
    {
        s->data[i] = str[i];
        s->length++;
    }
    s->data[len] = '\0';
}
String* concat_string(const String*s1,const String *s2)
{
    if(s1->length+s2->length>=MAX_SIZE)
    {
        puts("error ! failed to concat_string");
        return NULL;
    }
    String* r = (String*)malloc(sizeof(String));
    init_string(r);

    for(int i = 0;i<s1->length+s2->length;i++)
    {
        if(i<s1->length) r->data[i] = s1->data[i];
        else r->data[i] = s2->data[i-s1->length];
        r->length++;
    }
    r->data[s1->length+s2->length] = '\0';
    return r;
}
int lengthString(const String *s) {
    return s->length;
}
int compareString(const String *s1, const String *s2) {
    return strcmp(s1->data, s2->data);
}
void subString(const String *s, int pos, int len, String *sub) {
    if (pos < 0 || pos >= s->length || len < 0 || pos + len > s->length) {
        printf("子串截取越界\n");
        exit(1);
    }
    strncpy(sub->data, s->data + pos, len);
    sub->data[len] = '\0';
    sub->length = len;
}
int indexBF(const String *s, const String *t) {         //Brute Force  O(n*m)
    int i = 0, j = 0;
    while (i < s->length && j < t->length) {
        if (s->data[i] == t->data[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;  //从第i开始匹配，匹配到第j个后失败，则退回到 (i + j) - j 再取下一位 
            j = 0;
        }
    }
    if (j == t->length) {
        return i - j;
    }
    return -1;
}
