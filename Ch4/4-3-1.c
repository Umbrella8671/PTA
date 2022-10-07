// 家谱处理

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAMESIZE 200
#define STRSIZE  1000

typedef struct TNode* Position;
struct TNode{
    char name[NAMESIZE];
    int level;
    struct TNode* child;
    struct TNode* sibling;
};
typedef Position BinTree;
Position CreatTree(char *s, int level){
    BinTree BT = (BinTree)malloc(sizeof(struct TNode));
    strcpy(BT->name, s);
    BT->level = level;
    BT->child = BT->sibling = NULL;
    return BT;
}




Position CreatFamTree(BinTree root, char *s, int level){
    if(!root){
        root = CreatTree(s, level);
        return root;
    }
    Position childNode = root->child, fatherNode = root, siblingNode = NULL;
    
    // 兄弟的孩子
    if(childNode && childNode->sibling){
        siblingNode = childNode->sibling;
        while(siblingNode->sibling)
            siblingNode = siblingNode->sibling;
        fatherNode = siblingNode;
        childNode = fatherNode->child;
        while(childNode && (childNode->level <= level)){
            fatherNode = childNode;
            childNode = childNode->child;
        }
        if(!childNode){
            BinTree Node = CreatTree(s, level);
            if(fatherNode->level < level)
                fatherNode->child = Node;
            else{
                siblingNode = fatherNode->sibling;
                while(siblingNode){
                    fatherNode = siblingNode;
                    siblingNode = siblingNode->sibling;
                }
                fatherNode->sibling = Node;
            }
            return root;
        }else{
            siblingNode = fatherNode->sibling;
            while(siblingNode){
                fatherNode = siblingNode;
                siblingNode = siblingNode->sibling;
            }
            BinTree Node = CreatTree(s, level);
            fatherNode->sibling = Node;
            return root;
        }
    }

    // 自己的孩子
    while(childNode && (childNode->level <= level)){
        fatherNode = childNode;
        childNode = childNode->child;
    }

    if(!childNode){
        BinTree Node = CreatTree(s, level);
        if(fatherNode->level < level)
            fatherNode->child = Node;
        else{
            siblingNode = fatherNode->sibling;
            while(siblingNode){
                fatherNode = siblingNode;
                siblingNode = siblingNode->sibling;
            }
            fatherNode->sibling = Node;
        }
        return root;
    }else{
        siblingNode = fatherNode->sibling;
        while(siblingNode){
            fatherNode = siblingNode;
            siblingNode = siblingNode->sibling;
        }
        BinTree Node = CreatTree(s, level);
        fatherNode->sibling = Node;
        return root;
    }
}



BinTree CreateFamilyTree(int *i, int N){
    if(*i > N)
        return NULL;
    (*i)++;
    char name[NAMESIZE];
    getchar();
    scanf("%[^\n]", name);
    int length = strlen(name);
    int j, Cnt = 0;
    int level = 1;
    for(j = 0; name[j] == ' '; j++, Cnt++);
    level += (Cnt / 2);
    BinTree root;
    root = CreatTree(name + j, level);
    root->child =  CreateFamilyTree(i, N);
    root->sibling = CreateFamilyTree(i, N);
    return root;
}

Position Search(BinTree BT, char* name){
    if(BT){
        Position child, sibling;
        if(!strcmp(name, BT->name))
            return BT;
        child = Search(BT->child, name);
        sibling = Search(BT->sibling, name);
        if(child)
            return child;
        else
            return sibling;
    }else
        return NULL;
}
void judge(BinTree BT, int M){
    char name1[NAMESIZE], name2[NAMESIZE], str[NAMESIZE];
    Position ptr1, ptr2;
    while(M--){
        scanf("%s%s", name1, str);
        scanf("%s", str);
        if(!strcmp("an", str)){
            scanf("%s%s", str, str);
            scanf("%s", name2);
            ptr1 = Search(BT, name1);
            ptr2 = Search(BT->child, name2);
            if(ptr2)
                printf("True\n");
            else
                printf("False\n");
            continue;
        }
        if(!strcmp("the", str)){
            scanf("%s%s", str, str);
            scanf("%s", name2);
            ptr1 = Search(BT, name1);
            if(ptr1->child){
                if(!strcmp(ptr1->child->name, name2))
                    printf("True\n");
                else
                    printf("False\n");
            }
            else
                printf("False\n");
           
        }else{
            scanf("%s", str);
            if(!strcmp("child", str)){
                scanf("%s%s", str, name2);
                ptr1 = Search(BT, name2);
                if(ptr1->child){
                    if(!strcmp(ptr1->child->name, name1))
                        printf("True\n");
                    else
                        printf("False\n");
                }
                else
                    printf("False\n");
                    continue;
            }
            if(!strcmp("sibling", str)){
                scanf("%s%s", str, name2);
                ptr1 = Search(BT, name1);
                ptr2 = Search(BT, name2);
                if(ptr1->sibling){
                    if(!strcmp(ptr1->sibling->name, name2))
                        printf("True\n");
                    else
                        printf("False\n");
                    continue;
                }
                if(ptr2->sibling)
                    if(!strcmp(ptr2->sibling->name, name1))
                        printf("True\n");
                    else
                        printf("False\n");
                else
                    printf("False\n");
                
            }else{
                scanf("%s%s", str, name2);
                ptr2 = Search(BT, name2);
                ptr1 = Search(ptr2->child, name1);
                if(ptr1)
                    printf("True\n");
                else
                    printf("False\n");
            }
        }
    }
}
int main(){
    int N, M;
    scanf("%d%d", &N, &M);
    char name[NAMESIZE];
    int i = 1;
    BinTree T = CreateFamilyTree(&i, N);
    judge(T, M);
}