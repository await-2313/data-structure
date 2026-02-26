/*
        Time:   2026/2/20
        Author: await-2313   
*/
/*
| Day3 | 串的模式匹配（KMP算法） | 手写：求next数组+KMP核心匹配函数 | KMP算法匹配结果和BF一致，能解释next数组的作用（减少回溯） |
| Day4 | 串的链式存储实现 | 手写：链式串结构体+初始化+遍历+拼接 | 链式串拼接后遍历正确，理解定长数组vs链式存储的优缺点 |
| Day5 | 串操作复习 | 闭卷手写定长串/KMP/链式串核心代码 | 代码无语法错误，编译运行通过 |
| Day6 | 串操作错题修正 | 整理KMP next数组计算错误、子串截取越界的错误，重新实现 | 错误点标注原因，修正后代码运行正确 |
| Day7 | 串综合练习 | 手写：KMP算法实现字符串替换+判断字符串是否为回文 | 字符串替换逻辑正确，回文判断无误 |
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#define CAPACITY_STR   50
typedef struct{
    char data[CAPACITY_STR];
    int length;
}String;
void init_string(String*s);
void assign_string(String* s,const char * str,int len);
int* kmp_build_next(const char*pattern,int pat_len);
int kmp_index(const char* text,int text_len,const char * pattern,int pat_len);
void test01() {
    // 定义测试用例：{主串, 模式串, 预期结果}
    typedef struct {
        const char *text;
        const char *pat;
        int expected;
        int text_len;
        int pat_len;
    } TestCase;

    TestCase cases[] = {
        // 用例1：常规匹配（核心场景）
        {"abababc", "ababc", 2,7,5},
        // 用例2：无匹配
        {"hello world", "kmp", -1,11,3},
        // 用例3：模式串是主串前缀
        {"abcde123", "abc", 0,8,3},
        // 用例4：模式串是主串后缀
        {"123abcde", "cde", 5,8,3},
        // 用例5：重复字符模式串
        {"aaaaaabbbbb", "aa", 0,11,2},
        // 用例6：模式串与主串完全相等
        {"testkmp", "testkmp", 0,7,7},
        // 用例7：模式串长度大于主串
        {"abc", "abcd", -1,3,4},
        // 用例8：模式串在主串中间（重复字符）
        {"abababab", "abab", 0,8,4}
    };

    int caseCount = sizeof(cases) / sizeof(TestCase);
    printf("===== KMP算法测试（test01）=====\n");
    for (int i = 0; i < caseCount; i++) {
        printf("\n【测试用例%d】\n", i+1);
        printf("主串：%s\n", cases[i].text);
        printf("模式串：%s\n", cases[i].pat);
        printf("模式串next:\n");
        {
            int * next = kmp_build_next(cases[i].pat,cases[i].pat_len);
            for(int g = 0;g<cases[i].pat_len;g++)
                printf("%d ",next[g]);
            printf("\n模式串长度:%d 主串长度： %d\n",cases[i].pat_len,cases[i].text_len);
            free(next);
        }
        printf("预期结果：%d\n", cases[i].expected);
        
        int actual = kmp_index(cases[i].text,cases[i].text_len ,cases[i].pat,cases[i].pat_len);
        printf("实际结果：%d\n", actual);
        
        // 验证结果是否正确
        if (actual == cases[i].expected) {
            printf("✅ 测试通过\n");
        } else {
            printf("❌ 测试失败\n");
        }
        
        
    }
    printf("\n===== 测试结束 =====\n");
}
int main()
{
    SetConsoleOutputCP(65001);
    test01();
    return 0;
}

void init_string(String*s)
{
    if(!s)
    {
        puts("error init_string");
        return;
    }
    s->data[0] = '\0';
    s->length = 0;
}
void assign_string(String* s,const char * str,int len)
{
    if(len>CAPACITY_STR-1)
    {
        puts("error ! assign_string");
        return;
    }
    for(int i=0;i<=len;i++)
    {
        s->data[i] = str[i];
    }
    s->length = len;
    s->data[s->length] = '\0';
}
int* kmp_build_next(const char*pattern,int pat_len)
{
    /*
        next[i] 表示：
            模式串的子串 pattern[0...i]（从第0个字符到第i个字符，共i+1个字符）中，匹配串的前缀下标
    */
    int * next = (int*)malloc(sizeof(int)*pat_len);
    next[0] = -1; //

    int i = 0;  //主循环索引
    int j = -1; // j : 当前最长相等真前后缀的前缀最后一个下标（初始无匹配，为-1）

    while(i<pat_len-1)
    {
        
        if(j == -1 || pattern[i] == pattern[j+1])
        {
            j++;
            i++;
            if (pattern[i] != pattern[j]) {
                next[i] = j;
            } else {
                next[i] = next[j];
            }
        }else{
            j = next[j];
        }
    }
    return next;
}
int kmp_index(const char* text,int text_len,const char * pattern,int pat_len)
{
    if(!text || !pattern || text_len<pat_len) return -1;
    
    int* next = kmp_build_next(pattern,pat_len);
    int i=0,j=0;
    while(i<text_len&&j<pat_len)
    {
        if(j == -1 || text[i] == pattern[j])
        {
            i++;
            j++;
            
        }else{
            j = next[j];
        }
    }
    if(j == pat_len)
    {
        free(next);
        next = NULL;
        return i-j;
    }
    return -1;  //匹配失败
    
}


//  0123456
//  ABCDABX
//  ABCDABD


