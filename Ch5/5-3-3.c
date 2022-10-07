// 基于词频的文件相似度

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define FILENUMBERWORD 10000//估计的一个文件内的单词数
typedef char * ElementType;
struct word
{
	ElementType str;
	struct word * Next;
};
typedef struct word * Word;
struct hashtable  //一个散列表代表一个文件
{
	Word file;
	int tablesize;//散列表表长
	int num;//记录文件内单词总数
};
typedef struct hashtable * HashTable;
void Scan(HashTable H);
void Insert(HashTable H, ElementType s);
int Find(HashTable H, ElementType s);
int Hash(ElementType s, int tablesize);
int main()
{
	int N, M;
	scanf("%d\n", &N);
	int i, j;
	HashTable * H; //创建散列表指针数组，文件i对应下标i-1的散列表
	H = (HashTable *)malloc(N * sizeof(HashTable));
	for (i = 0; i < N; i++)
	{
		H[i] = (HashTable)malloc(sizeof(struct hashtable));
		H[i]->file = (Word)malloc(FILENUMBERWORD * sizeof(struct word));
		H[i]->tablesize = 101;
		H[i]->num = 0;//初始化每个文件内单词数=0
		for (j = 0; j < FILENUMBERWORD; j++)
		{
			(H[i]->file)[j].str = (ElementType)malloc(11 * sizeof(char));
			(H[i]->file)[j].str[0] = '\0';
			(H[i]->file)[j].Next = NULL;
		}
	}
	//逐个扫描读入文件
	for (i = 0; i < N; i++)
	{
		Scan(H[i]);
	}
	int f1, f2;
	int ret;
	scanf("%d\n", &M);
	Word w;
	int sumsame = 0;
	int t;
	for (i = 0; i < M; i++)
	{
		sumsame = 0;//记录两个文件共有的单词数
		scanf("%d %d", &f1, &f2);
		if (H[f1 - 1]->num > H[f2 - 1]->num) { t = f1; f1 = f2; f2 = t; }//选择2个文件中单词数少的那个文件进行遍历
		//遍历文件1，对文件1内的每个单词在文件2中查找，找到了即为重复出现单词，没有找到则未重复
		for (j = 0; j < H[f1 - 1]->tablesize; j++)
		{
			w = H[f1 - 1]->file[j].Next;
			while (w != NULL)
			{
				ret = Find(H[f2 - 1], w->str);
				if (ret == 1) { sumsame++; }
				w = w->Next;
			}
		}
		//
		//printf("%d %d\n", H[f1 - 1]->num, H[f2 - 1]->num);
		//
		printf("%.1f%%\n", 100.0*sumsame / (double)(H[f1 - 1]->num + H[f2 - 1]->num - sumsame));
	}
	return 0;
}
//扫描读入每个文件
void Scan(HashTable H)
{
	ElementType s, sw;
	s = (ElementType)malloc(5000 * sizeof(char));
	sw = (ElementType)malloc(5000 * sizeof(char));
	gets(s);
	while (strcmp(s, "#") != 0) //一行中只给出一个字符#表示文件结束
	{
		int i = 0, j = 0;
		int flag = 0;
		while (1)
		{
			if (s[i] >= 'A'&&s[i] <= 'Z' || s[i] >= 'a'&&s[i] <= 'z')
			{
				flag = 1;
				if (s[i] >= 'A'&&s[i] <= 'Z')//大写字母转化成小写字母
				{
					s[i] = s[i] - 'A' + 'a';
				}
				sw[j] = s[i];
				j++;
			}
			else
			{
				if (flag == 1)//读入英文字母后，读入非英文字母表示一个单词输入结束
				{
					flag = 0;
					sw[j] = '\0';
					if (strlen(sw) > 10) { sw[10] = '\0'; }//长度超过10只考虑前10个字母
					if (strlen(sw) >= 3)//一个单词字母长度不小于3
					{
						Insert(H, sw);//向散列表中插入单词
					}
					j = 0;//下一个单词从头开始记录
					if (s[i] == '\0') { break; }
				}
				else {  //考虑没有有效单词的情况，不加这个最后一个测试点通不过
					if (s[i] == '\0') { sw[j] = '\0'; break; }
				}
			}
			i++;
		}
		gets(s);
	}
}
//向散列表中插入单词
void Insert(HashTable H, ElementType s)
{
	int r;
	r = Find(H, s);
	int index = Hash(s, H->tablesize);
	if (r == 1);
	else
	{
		Word p, q;
		p = (Word)malloc(sizeof(struct word));
		p->str = (ElementType)malloc(12 * sizeof(char));
		strcpy(p->str, s);
		q = H->file[index].Next;
		p->Next = q;
		H->file[index].Next = p;
		H->num++;
	}
}
//在散列表中查找单词s，找到返回1，没找到返回0
int Find(HashTable H, ElementType s)
{
	int i;
	int index = Hash(s, H->tablesize);
	Word p;
	p = H->file[index].Next;
	while (p != NULL)
	{
		if (strcmp(p->str, s) == 0)
		{
			return 1;
		}
		p = p->Next;
	}
	return 0;
}
//散列函数计算
int Hash(ElementType s, int tablesize)
{
	unsigned int h = 0;
	int i = 0;
	while (s[i] != '\0')
	{
		h = h * 32 + s[i] - 'a';
		i++;
	}
	return h % tablesize;
}
