#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <math.h>
#include <iterator>
#include <cctype>
 
using namespace std;
 
typedef struct Unit
{
    string sequence;
    int freq;
}Unit, Type;     //用于存储词汇表, sequence表示单词, freq表示该单词的频率
 
Unit verb[10000];   //结构体数组
int numVerb = 0;    //该变量表示不同单词的数量
int newWord = 1;    //该单词用于标记一个单词是否收录进词汇表中
string text[100];   //存放文本，每个元素存放一行
int line = 0;       //行数
string word = "";   //单词
 
void readTxt(string file);     //按行读取txt文本
void textToword(Unit verb1[], string text1[], int line1);  //把text文本内容变为单个单词，并存储
void save(string strr, Unit verb1[]);
bool com(int type, Type a, Type x);
void sortbyword(Unit verb1[], int numVerb1);     //按单词排序
void sortbyfrequen(Unit verb1[], int numVerb1);  //按频率排序
void QuickSort(Type a[], int p, int r, int type);
bool cmp(int type, Type a, Type x );
int  Partition(Type a[], int p, int r, int type);
int  RandomizedPartition(Type a[], int p, int r, int type);
void Swap(Type a[], int i, int j);
int  Random(int p, int r);
void Print();
 
int main()
{
	string file = "test1.txt";   //文件名
	readTxt(file);
	textToword(verb, text, line);
    Print();
    system("pause");
	return 0;
}
 
//按行读取txt文本
void readTxt(string file)
{
    ifstream infile; 
    infile.open(file.data());   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
    while(getline(infile,text[line]))   //按行存到text
    {
		line++;
    }
    infile.close();             //关闭文件输入流 
}

//把text文本内容变为单个单词，并存储
void textToword(Unit verb1[], string text1[], int line1)
{
	string word1 = "";
    //作为二维数组遍历
	for(int i = 0; i < line1; i++)
	{
		for(int k = 0; k < text1[i].size()+1; k++)
		{
            //当前字符为字母，则与word1合并
			if(((text1[i][k]>='a')&&( text1[i][k]<='z'))||((text1[i][k]>='A')&&(text1[i][k]<='Z')))
			{
				word1 += text1[i][k]; 
			}
            //当前字符不是字母
			if(((text1[i][k]<'A')||(text1[i][k]>'Z'))&&((text1[i][k]<'a')||(text1[i][k]>'z')))
			{
                //当前字符不为空
				if(word1 != "")
				{
					save(word1, verb1);
					word1 = ""; 
				}
			}
 
		}
	}
}
 
//将单词保存到结构体数组
void save(string strr, Unit verb1[])
{
	int newWord1 = 1;
	string str = strr;
	transform(str.begin(), str.end(), str.begin(), ::tolower);  //大写字母转换为小写字母
    //遍历已有的结构体数组，判断该单词是否为新词
	for(int i = 0; i < numVerb; i++)
	{
        //不是新词
		if(str == verb1[i].sequence)   
		{
			verb1[i].freq++; //该单词词频+1
			newWord1 = 0;    //变量置0
		}
	}
	if(newWord1 == 1)  //是新词，作为新元素插入结构体数组
	{
		verb1[numVerb].sequence = str; 
		verb1[numVerb].freq = 1;  
		numVerb++;
	}
}
 
//按单词排序
void sortbyword( Unit verb1[], int numVerb1)
{
	QuickSort(verb1, 0, numVerb1-1, 1);
}
 
//按词频排序
void sortbyfrequen(  Unit verb1[], int numVerb1)
{
	QuickSort(verb1, 0, numVerb1-1, 3);
}
 
//type=1 时按字母排序 ， type=3 时按词频排序
bool cmp(int type, Type a, Type x)
{
	if(type == 1)
	{
		const char *str1 = a.sequence.data();
		const char *str2 = x.sequence.data();
		if( strcmp( str1,str2 )<0 )
			return true;
		else
			return false;
	}
    else if( type==2 )
	{
		const char *str1 = a.sequence.data();
		const char *str2 = x.sequence.data();
		if( strcmp( str1,str2 )>0 )
			return true;
		else
			return false;
	}
    else if( type==3 )
	{
		if( a.freq > x.freq )
			return true;
		else
			return false;
	}
    else if( type==4 )
	{
		if( a.freq < x.freq )
			return true;
		else
			return false;
	}
    else
		return false;
}
 
//快速排序1
void QuickSort(Type a[], int p, int r, int type)
{
	if (p < r)
	{
		int q = RandomizedPartition(a, p, r, type);
		QuickSort(a, p, q-1, type); 
		QuickSort(a, q+1, r, type); 
    }
}

//快速排序3
int Partition(Type a[], int p, int r, int type)
{       
	int i = p, j = r + 1; 
    Type x = a[p];
 
    while (true) 
    {
		while (cmp(type, a[++i], x ) && i < r);
		while (cmp(type+1, a[--j], x ));
        if (i >= j) break; 
        Swap(a, i, j);
    }
    a[p] = a[j];
    a[j] = x;
    return j;
}

//快速排序2
int RandomizedPartition(Type a[],int p,int r, int type)
{	
	int i = Random(p,r);
	Swap(a,i,p);
	return Partition(a, p, r, type);
}

//交换
void Swap(Type a[], int i, int j)
{
	Type temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
 
int Random(int p, int r)
{
	return rand()%(r-p)+p;
}

//打印输出
void Print()
{
    int i;
    printf("按字母排序：\n" );
    sortbyword(verb, numVerb);
    cout.setf( ios::left );
    for( i=0;i<numVerb;i++ )
    {
        cout << "    " << setw(16) << verb[i].sequence << setw(5) << verb[i].freq << endl;	
    }
    cout << endl;
    printf("按词频排序：\n" );
    sortbyfrequen( verb, numVerb );
    cout.setf( ios::left );
    for( i=0;i<numVerb;i++ )
    {
        cout << "    " << setw(16) << verb[i].sequence << setw(5) << verb[i].freq <<endl;	
    }
}