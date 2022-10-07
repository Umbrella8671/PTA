// 线性探测法查找函数

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXTABLESIZE 100000     // 允许开辟最大的散列表长度
#define ERROR -1

typedef int ElementType;    //关键词类型
typedef int index;      //散列地址类型
typedef index Position;     // 数据所在位置类型

// 散列单元状态类型，对应：有合法元素、空单元、有已删除元素
typedef enum{Legitimate, Empty, Deleted} EntryType;

typedef struct HashEntry Cell;  //散列表单元类型
struct HashEntry{
    ElementType Data; // 元素
    EntryType info; // 单元状态
};
typedef struct TblNode *HashTable;  //散列表类型
struct TblNode{
    int TableSize;  //表的最大长度
    Cell* Cells;    //存放散列单元数据
};

Position Hash(ElementType Key, int TableSize){}

Position Find(HashTable H, ElementType Key){
    Position CurrentPos, NewPos;
    NewPos = CurrentPos = Hash(Key, H->TableSize);
    while(H->Cells[NewPos].info != Empty &&
        H->Cells[NewPos].Data != Key){
            NewPos++;
            if(NewPos >= H->TableSize)
                NewPos -= H->TableSize;
            if(NewPos == CurrentPos)
                return ERROR;
    }
    return NewPos;
}
