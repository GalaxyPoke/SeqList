#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define MAX_SIZE 6 //// 定义静态顺序表的最大容量
//
//typedef struct {
//	int data[MAX_SIZE]; // 存储数据的数组
//	int size; // 当前存储的元素数量
//}StaticList;


//typedef struct {
//    int* data;     // 指向动态分配数组的指针
//    int size;      // 当前存储的元素数量
//    int capacity;  // 当前数组的容量
//} DynamicList;

typedef int SLDateType;
typedef struct SeqList
{
	SLDateType* a; //声明了一个指向数组的a
	int size;
	int capacity;
}SL;

//void SLInit(SL ps)
//{
//	ps.a = NULL;
//	ps.size = ps.capacity = 0;
//}

void SLInit(SL* ps)
{
	ps->a = NULL;
	ps->size = 0;
	ps->capacity = 0;
}

void SLCheckCapacity(SL* ps)
{
    assert(ps); // 断言，确保传入的顺序表指针非空

    if (ps->size == ps->capacity)
    { // 如果当前元素数量等于容量，需要扩容
        int newCapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;  // 新容量计算策略：如果当前容量为0，则初始为4；否则容量翻倍

        SLDateType* temp = (SLDateType*)realloc(ps->a, newCapacity * sizeof(SLDateType)); // 尝试重新动态分配内存
        if (temp == NULL)
        { // 检查realloc是否成功，注意这里是比较操作，应使用两个等号==
            perror("realloc failed"); // 如果内存分配失败，输出错误消息
            exit(-1);  // 退出程序
        }

        ps->a = temp;  // 更新顺序表的数据指针
        ps->capacity = newCapacity;  // 更新顺序表的容量
    }
}


void SLPushBack(SL* ps, SLDateType x) {
    assert(ps); // 断言，确保传入的顺序表指针非空，避免解引用空指针导致程序崩溃

    SLCheckCapacity(ps); // 检查顺序表的容量是否足够，如果不足则进行扩容

    ps->a[ps->size] = x; // 将新元素x存放在数组的当前末尾位置，ps->size是指向下一个空闲位置的索引 //这里为什么用size而不用size-1或者别的呢，因为size的大小，就是数组最后一个数+1的下标

    ps->size++; // 更新顺序表的元素计数，增加1，以反映添加了新元素
}

void SLPopBack(SL* ps) {
    assert(ps); // 断言，确保传入的顺序表指针非空，避免解引用空指针导致程序崩溃

    //ps->a[ps->size - 1] = 0;  //用于清除顺序表最后一个元素的数据，将其设置为 0。

    // 温和的错误处理方式: 检查顺序表是否为空，如果为空则打印信息并退出函数
    /*if (ps->size == 0) {
        printf("顺序表已空\n");
        return;
    }*/

    // 暴力的错误处理方式: 使用断言确保顺序表不为空，如果为空程序在调试模式下会中断执行
    assert(ps->size > 0); // 确保顺序表中至少有一个元素，防止下溢

    // 可选的清除操作: 清除顺序表最后一个元素的数据，将其设置为 0
    // ps->a[ps->size - 1] = 0;

    ps->size--; // 减少顺序表的大小，逻辑上移除最后一个元素
}

// 在顺序表的开始位置插入一个新元素
void SLPushFront(SL* ps, SLDateType x) {
    assert(ps);  // 断言，确保传入的顺序表指针非空

    SLCheckCapacity(ps);  // 检查顺序表的容量是否足够，如果不足则进行扩容

    int end = ps->size - 1;  // 计算顺序表最后一个元素的索引位置
    while (end >= 0) {
        ps->a[end + 1] = ps->a[end];  // 将元素向后移动一个位置
        end--;  // 向前移动索引，继续移动前一个元素
    }

    ps->a[0] = x;  // 在顺序表的第一个位置插入新元素
    ps->size++;  // 更新顺序表的大小
}

void SLPopFront(SL* ps)
{
    assert(ps);
    assert(ps->size > 0);
    int begin = 1;
    while (begin < ps->size)
    {
        ps->a[begin - 1] = ps->a[begin];
        begin++;
    }
    ps->size--;
}


//在pos位置插入数据
void SLInsert(SL* ps, int pos, SLDateType x)
{
	assert(ps);
	assert(pos >= 0);    // pos 的位置，因该在有效位置
	assert(pos <= ps->size);  // 等于 “=” size 相当于尾插
	SLCheckCapacity(ps); // 扩容
	int end = ps->size - 1;
	while (end >= pos)
	{
		ps->a[end + 1] = ps->a[end];
		end--;
	}
	ps->a[pos] = x;
	ps->size++;
}

//删除pos位置的数据

// 其中 SLErase(ps,0) 就是头删
// 其中 SLErase(ps,ps-size-1)  就是尾删

void SLErase(SL* ps, int pos)
{
	assert(ps);
	assert(pos >= 0);
	assert(pos < ps->size);
	assert(ps->size > 0);  //检查 size 是否为空
	int begin = pos + 1;
	while (begin < ps->size)
	{
		ps->a[begin - 1] = ps->a[begin];
		begin++;
	}
	ps->size--;
}

// 查找某一个数据的位置是
int SLFind(SL* ps, SLDateType x)
{
	assert(ps);
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->a[i] == x)
		{
			return i;
		}
	}
	return -1;
}

// begin 查找 x 的起始位置
int SLFinds(SL* ps, SLDateType x, int begin)
{
	assert(ps);
	for (int i = begin; i < ps->size; i++)
	{
		if (ps->a[i] == x)
		{
			return i;
		}
	}
	return -1;
}
