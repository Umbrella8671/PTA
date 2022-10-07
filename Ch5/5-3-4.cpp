/*2019/10/12 迷你搜索引擎 STL重构*/
#include<string>
#include<cstdio>
#include<vector>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
string fileName[100];
string file[100][100];//第i个文件第j行
const int MAXTABLESIZE = 300009;
struct nodeB
{
	int fileNum;
	set<int> line;
};
struct nodeA
{	
	int lastFile;
	int lastLine;
	string word;
	vector<nodeB> arrayB;
};
/*Hash*/
struct HashTbl
{
	int TableSize;
	nodeA* Cells;
};
typedef struct HashTbl* HashTable;
HashTable CreateTable()
{
	int i;
	HashTable H = new HashTbl;
	H->TableSize = MAXTABLESIZE;
	H->Cells = new nodeA[MAXTABLESIZE];
	for(i=0; i<H->TableSize; i++)
	{
		H->Cells[i].lastFile = -1;
		H->Cells[i].lastLine = -1;
	}
	return H;
}
int Hash(string Key, int P)
{
	int i,len,N;
    unsigned int h = 0;
	for(i=0; i<N; i++)
	{
		h = (h<<5) + (Key[i] - 'a');
	}
	return (h&(32*32*32-1))%P;
}
int Find(HashTable H, string Key)//线形探测法解决冲突
{
	int newPos, curPos,cnt = 0;//cnt表示冲突次数
	newPos = curPos = Hash(Key, H->TableSize);
	while((H->Cells[newPos].lastFile!=-1)&&(H->Cells[newPos].word!=Key))
	{
		cnt++;
		newPos = curPos + cnt;
		if(newPos>=H->TableSize)
			newPos-=H->TableSize;
	}
	return newPos;
}
void Insert(HashTable H, string Key, int file, int line)
{
	nodeB* tmp;
	int pos = Find(H,Key);
	if(H->Cells[pos].lastFile==-1)//表示这个位置为空,那么要先插入单词，再插入文件和行号
	{
		H->Cells[pos].lastFile = file;
		H->Cells[pos].lastLine = line;
		H->Cells[pos].word = Key;//printf("插入了%s\n",Key.c_str());
		tmp = new nodeB;
		tmp->fileNum = file; tmp->line.insert(line);
		H->Cells[pos].arrayB.push_back(*tmp);
	}
	else if(H->Cells[pos].lastFile!=file)
	{
		H->Cells[pos].lastFile = file;
		H->Cells[pos].lastLine = line;
		tmp = new nodeB;
		tmp->fileNum = file; tmp->line.insert(line);
		H->Cells[pos].arrayB.push_back(*tmp);
	}
	else if(H->Cells[pos].lastLine!=line)
	{
		H->Cells[pos].arrayB[H->Cells[pos].arrayB.size()-1].line.insert(line);
	}
}
/*Hash*/
void readFile(HashTable H)
{
	int N,i,j,k;
	string str,buff;
	scanf("%d",&N);getchar();
	char *cstr,*p;
	for(i=0; i<N; i++)//i是文件的编号从0~N-1
	{
		getline(cin,fileName[i]);j = 0;//j代表行号
		while(getline(cin,str), str != "#")
		{
			file[i][j] = str;
			cstr = new char[str.size()+1];
			strcpy(cstr,str.c_str());
			p = strtok(cstr," ");
			while(p!=NULL)
			{
				for(k=0; k<strlen(p); k++)
				{
					if((p[k]>='A')&&(p[k]<='Z'))
					{
						p[k] = p[k] + 32;
					}
				}
				Insert(H,p,i,j);
				p = strtok(NULL," ");
			}
			j++;
		}
	}
}
void Intersect(vector<nodeB> &v1, vector<nodeB> &v2, vector<nodeB> &v)
{
	vector<nodeB>::iterator it1,it2;
	set<int>::iterator it3,it4;
	it1 = v1.begin(); it2 = v2.begin();
	while(it1!=v1.end()&&it2!=v2.end())
	{
		if(it1->fileNum==it2->fileNum)
		{
			nodeB* tmp = new nodeB;
			tmp->fileNum = it1->fileNum;
			for(it3 = it1->line.begin();it3!=it1->line.end();it3++)
			{
				tmp->line.insert(*it3);
			}
			for(it4 = it2->line.begin();it4!=it2->line.end();it4++)
			{
				tmp->line.insert(*it4);
			}
			v.push_back(*tmp);
			it1++;it2++;
		}
		else if(it1->fileNum<it2->fileNum)
		{
			it1++;
		}
		else
		{
			it2++;
		}
	}
}
void query(HashTable H)
{
	int i,k; string str;
	char* cstr,*p;
	string buff[10];
	getline(cin,str);
	cstr = new char[str.size()+1];
	strcpy(cstr,str.c_str());
	p = strtok(cstr," ");//printf("%s\n", p);
	int cnt = 0;
	while(p!=NULL)
	{
		char* tmp;tmp = p;
		while(*tmp!='\0')
		{
			if(*tmp>='A'&&*tmp<='Z')
			{
				*tmp = *tmp+32;
			}
			tmp++;
		}
		buff[cnt] = p;//cout<<buff[cnt]<<endl;
		cnt++;
		p = strtok(NULL," ");
	}
	vector<nodeB> vi;int pos;vector<nodeB> v;
	for(i=0; i<cnt; i++)
	{
		pos = Find(H,buff[i]);//cout<<"单词是"<<H->Cells[pos].word<<endl;
		if(i==0)
		{
			vi.insert(vi.begin(),H->Cells[pos].arrayB.begin(),H->Cells[pos].arrayB.end());
		}
		else
		{
			Intersect(vi,H->Cells[pos].arrayB,v);
			vi.clear();
			vi.insert(vi.begin(),v.begin(),v.end());
			v.clear();
		}
	}
	cout<<vi.size()<<endl;
	if(vi.size()==0)
	{
		printf("Not Found\n");
		return;
	}
	for(auto it = vi.begin(); it!=vi.end(); it++)
	{
        printf("%s\n",fileName[it->fileNum].c_str());
		for(auto it5=it->line.begin(); it5!=it->line.end(); it5++)
		{
            printf("%s\n",file[it->fileNum][*it5].c_str());
		}
	}
}
int main()
{
	HashTable H = CreateTable();
	readFile(H);
	int M;
	scanf("%d",&M);getchar();
	for(int i=0; i<M;i++)
	{
		query(H);
	}
	return 0;
}