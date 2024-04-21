#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define MAX_SIZE 6 //// ���徲̬˳�����������
//
//typedef struct {
//	int data[MAX_SIZE]; // �洢���ݵ�����
//	int size; // ��ǰ�洢��Ԫ������
//}StaticList;


//typedef struct {
//    int* data;     // ָ��̬���������ָ��
//    int size;      // ��ǰ�洢��Ԫ������
//    int capacity;  // ��ǰ���������
//} DynamicList;

typedef int SLDateType;
typedef struct SeqList
{
	SLDateType* a; //������һ��ָ�������a
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
    assert(ps); // ���ԣ�ȷ�������˳���ָ��ǿ�

    if (ps->size == ps->capacity)
    { // �����ǰԪ������������������Ҫ����
        int newCapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;  // ������������ԣ������ǰ����Ϊ0�����ʼΪ4��������������

        SLDateType* temp = (SLDateType*)realloc(ps->a, newCapacity * sizeof(SLDateType)); // �������¶�̬�����ڴ�
        if (temp == NULL)
        { // ���realloc�Ƿ�ɹ���ע�������ǱȽϲ�����Ӧʹ�������Ⱥ�==
            perror("realloc failed"); // ����ڴ����ʧ�ܣ����������Ϣ
            exit(-1);  // �˳�����
        }

        ps->a = temp;  // ����˳��������ָ��
        ps->capacity = newCapacity;  // ����˳��������
    }
}


void SLPushBack(SL* ps, SLDateType x) {
    assert(ps); // ���ԣ�ȷ�������˳���ָ��ǿգ���������ÿ�ָ�뵼�³������

    SLCheckCapacity(ps); // ���˳���������Ƿ��㹻������������������

    ps->a[ps->size] = x; // ����Ԫ��x���������ĵ�ǰĩβλ�ã�ps->size��ָ����һ������λ�õ����� //����Ϊʲô��size������size-1���߱���أ���Ϊsize�Ĵ�С�������������һ����+1���±�

    ps->size++; // ����˳����Ԫ�ؼ���������1���Է�ӳ�������Ԫ��
}

void SLPopBack(SL* ps) {
    assert(ps); // ���ԣ�ȷ�������˳���ָ��ǿգ���������ÿ�ָ�뵼�³������

    //ps->a[ps->size - 1] = 0;  //�������˳������һ��Ԫ�ص����ݣ���������Ϊ 0��

    // �º͵Ĵ�����ʽ: ���˳����Ƿ�Ϊ�գ����Ϊ�����ӡ��Ϣ���˳�����
    /*if (ps->size == 0) {
        printf("˳����ѿ�\n");
        return;
    }*/

    // �����Ĵ�����ʽ: ʹ�ö���ȷ��˳���Ϊ�գ����Ϊ�ճ����ڵ���ģʽ�»��ж�ִ��
    assert(ps->size > 0); // ȷ��˳�����������һ��Ԫ�أ���ֹ����

    // ��ѡ���������: ���˳������һ��Ԫ�ص����ݣ���������Ϊ 0
    // ps->a[ps->size - 1] = 0;

    ps->size--; // ����˳���Ĵ�С���߼����Ƴ����һ��Ԫ��
}

// ��˳���Ŀ�ʼλ�ò���һ����Ԫ��
void SLPushFront(SL* ps, SLDateType x) {
    assert(ps);  // ���ԣ�ȷ�������˳���ָ��ǿ�

    SLCheckCapacity(ps);  // ���˳���������Ƿ��㹻������������������

    int end = ps->size - 1;  // ����˳������һ��Ԫ�ص�����λ��
    while (end >= 0) {
        ps->a[end + 1] = ps->a[end];  // ��Ԫ������ƶ�һ��λ��
        end--;  // ��ǰ�ƶ������������ƶ�ǰһ��Ԫ��
    }

    ps->a[0] = x;  // ��˳���ĵ�һ��λ�ò�����Ԫ��
    ps->size++;  // ����˳���Ĵ�С
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


//��posλ�ò�������
void SLInsert(SL* ps, int pos, SLDateType x)
{
	assert(ps);
	assert(pos >= 0);    // pos ��λ�ã��������Чλ��
	assert(pos <= ps->size);  // ���� ��=�� size �൱��β��
	SLCheckCapacity(ps); // ����
	int end = ps->size - 1;
	while (end >= pos)
	{
		ps->a[end + 1] = ps->a[end];
		end--;
	}
	ps->a[pos] = x;
	ps->size++;
}

//ɾ��posλ�õ�����

// ���� SLErase(ps,0) ����ͷɾ
// ���� SLErase(ps,ps-size-1)  ����βɾ

void SLErase(SL* ps, int pos)
{
	assert(ps);
	assert(pos >= 0);
	assert(pos < ps->size);
	assert(ps->size > 0);  //��� size �Ƿ�Ϊ��
	int begin = pos + 1;
	while (begin < ps->size)
	{
		ps->a[begin - 1] = ps->a[begin];
		begin++;
	}
	ps->size--;
}

// ����ĳһ�����ݵ�λ����
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

// begin ���� x ����ʼλ��
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
