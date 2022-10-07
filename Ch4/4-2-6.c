// 目录树

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXNSIZE 261

typedef struct TreeNode* BinTree; 
struct TreeNode{
    char data[MAXNSIZE];
    BinTree child;
    BinTree sibling;
    int tag;
};

BinTree CreatTree(char s[], int tag){
    BinTree T = (BinTree)malloc(sizeof(struct TreeNode));
    strcpy(T->data, s);
    T->tag = tag;
    T->child = T->sibling = NULL;
    return T;
}
BinTree Insert(BinTree T, char s[], int tag){
    if(!T->child){
        T->child = CreatTree(s, tag);
        return T->child;
    }
    BinTree childNode = T->child, fatherNode = T;
																			// 注意在C语言中strcmp(s1, s2)比较时s1 > s2时，返回值可能是1,但一定大于0
    while(childNode != NULL && ((tag < childNode->tag) || (tag == childNode->tag && strcmp(s, childNode->data) > 0))){
        fatherNode = childNode;
        childNode = childNode->sibling;
    }

    if(!childNode){
        BinTree Node = CreatTree(s, tag);
        Node->sibling = fatherNode->sibling;
        fatherNode->sibling = Node;
        return Node;
    }
    if(!strcmp(childNode->data, s))
        return childNode;
    else{
        BinTree Node = CreatTree(s, tag);
        if(!strcmp(T->data, fatherNode->data)){
            Node->sibling = T->child;
            T->child = Node;
        }
        else{
            Node->sibling = fatherNode->sibling;
            fatherNode->sibling = Node;
        }
        return Node;
    }
}

void PreorderTraversal(BinTree T, int layer){
    int i;
    int childlayer, siblinglayer;
    if(T){    
        for(i = 0; i < layer; i++) printf("  ");
        childlayer = layer + 1;
        siblinglayer = layer;
        
        printf("%s\n", T->data);
        PreorderTraversal(T->child, childlayer);
        PreorderTraversal(T->sibling, siblinglayer);
    }
}

char* strmcpy(char source[], int bgn, int end){
    int length = end - bgn;
    char* s = (char*)malloc(sizeof(char) * (length + 1));
    s[length] = '\0';
    for(int i = 0; bgn < end; bgn++, i++)
        *(s + i) = *(source + bgn);
    return s;
}

int main(){
    int N, i, bgn, end, length;
    scanf("%d", &N);
    getchar();
    BinTree root = CreatTree((char*)"root", 1);
    BinTree pos;
    while(N--){
        char s1[MAXNSIZE];
        scanf("%s", s1);
        length = strlen(s1);
        pos = root;
        bgn = end = 0;

        for(i = 0; i < length; i++){
            if(s1[i] == '\\'){
                end = i;
                pos = Insert(pos, strmcpy(s1, bgn, end), 1);
                bgn = end + 1;
            }
        }
        if(s1[bgn] != '\0'){
            Insert(pos, strmcpy(s1, bgn, length), 0);
        }
    }
            PreorderTraversal(root, 0);
}

#include<iostream>
#include<cstdio>
using namespace std;

struct TreeNode{
	string str;
	TreeNode* child;	//左孩子
	TreeNode* sibling;	//右兄弟
	int priority;		//为0表示文件，为1表示目录 
}; 

typedef TreeNode* Position;
typedef Position BinTree;

//建树，也可以说是初始化的过程 
Position createNode(string s, int priority) {
	Position Node = new TreeNode;
	Node->str = s;
	Node->child = Node->sibling = NULL;
	Node->priority = priority;
	return Node;
}

//根据root的位置插入节点 
/*
插入节点前要想明白一个点，
如果该文件或目录还没有创建，那么创建的一定是其儿子节点。
如果已经创建完毕了，那么插入的位置一定在该节点的右子树中查找。

如
a/b
c/d 
1、从根节点插入a后，根节点左子树为a，a的左子树为b 
2、从根节点插入c时，发现其左子树已经被占据，那么就遍历其左子树的右子树
也就是根节点左子树的兄弟节点，直到找到合适的位置。遍历d时，也是同理。如果没有被占据，则直接创建儿子节点。 
*/ 
Position insert(BinTree root, string s, int priority) {
	if(root->child == NULL) {	//如果没有儿子，那么直接插入就可以了 
		root->child = createNode(s, priority);	
		return root->child;		//下一次插入从儿子开始 
	}
	//定义儿子节点和父亲节点。 
	Position tmpNode = root->child, father = root;
	//如果有儿子，则循链找插入位置
	//若待插入节点优先级更小或优先级一致但字典序更大，则继续循链
	//注意：边界条件为!=NULL，也就是到了链末尾
	while(tmpNode != NULL && ((priority<tmpNode->priority) || (tmpNode->priority == priority && s>tmpNode->str))) {
		father = tmpNode;
		tmpNode = tmpNode->sibling;
	}
	
	//退出循环的三种情况：
	//1、找到了链末尾	2、待插文件已存在	3、找到了应该插入的位置
		//情况1
	if(tmpNode == NULL) {
		Position Node = createNode(s, priority);
		Node->sibling = father->sibling;	//保存一下它的兄弟节点 
		father->sibling = Node; 
		return Node; 
	} 
		//情况2
	if(tmpNode->priority == priority && s==tmpNode->str)
		return tmpNode;
		//情况3
	else {
		Position Node = createNode(s, priority);
		if(father->str == root->str) {	//如果该点为根节点下的第一个节点 
			Node->sibling = father->child;
			father->child = Node;
		}
		else {
			Node->sibling = father->sibling;
			father->sibling = Node;
		}
		return Node; 
	}	 
} 	

//layer是层数，按层数输出空格 
void PreorderTraversal(BinTree BT, int layer) {
	int i;
	int childlayer, siblinglayer;
	if(BT) {
		for(i = 0; i < layer; i++) printf("  ");
		childlayer = layer+1;
		siblinglayer = layer;
		
		cout << BT->str << '\n';
		PreorderTraversal(BT->child, childlayer);
		PreorderTraversal(BT->sibling, siblinglayer);
	}
}
 

int main() {
	int N, i, bgn, end, j;
	string str;
	Position pos;		//说是指针，其实就是节点
	BinTree root = createNode("root", 1);
	scanf("%d\n", &N);
	for(i = 0; i < N; i++) {
		getline(cin, str); 
		pos = root; 
		bgn = end = 0;	//记录文件首字符和最后一个字符的位置
		
		for(j = 0; j < str.length(); j++) {
			if(str[j] == '\\') {
				end = j;
				pos = insert(pos, str.substr(bgn, end-bgn), 1);
				bgn = end+1;	//每次插入完成后更新起始字符位置 
			}
		}
		//读完所有目录后判断字符串中是否还有文件 如果有，读入文件 
		if(str[bgn] != '\0') {
			insert(pos, str.substr(bgn, str.length()-bgn), 0);
		} 
	} 
	PreorderTraversal(root, 0);	//前序遍历输出 
	return 0;
}

// root a d z a bc ab cd d c b
// root a d z a bc ab cd d c b