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
}Unit, Type;     //���ڴ洢�ʻ��, sequence��ʾ����, freq��ʾ�õ��ʵ�Ƶ��
 
Unit verb[10000];   //�ṹ������
int numVerb = 0;    //�ñ�����ʾ��ͬ���ʵ�����
int newWord = 1;    //�õ������ڱ��һ�������Ƿ���¼���ʻ����
string text[100];   //����ı���ÿ��Ԫ�ش��һ��
int line = 0;       //����
string word = "";   //����
 
void readTxt(string file);     //���ж�ȡtxt�ı�
void textToword(Unit verb1[], string text1[], int line1);  //��text�ı����ݱ�Ϊ�������ʣ����洢
void save(string strr, Unit verb1[]);
bool com(int type, Type a, Type x);
void sortbyword(Unit verb1[], int numVerb1);     //����������
void sortbyfrequen(Unit verb1[], int numVerb1);  //��Ƶ������
void QuickSort(Type a[], int p, int r, int type);
bool cmp(int type, Type a, Type x );
int  Partition(Type a[], int p, int r, int type);
int  RandomizedPartition(Type a[], int p, int r, int type);
void Swap(Type a[], int i, int j);
int  Random(int p, int r);
void Print();
 
int main()
{
	string file = "test1.txt";   //�ļ���
	readTxt(file);
	textToword(verb, text, line);
    Print();
    system("pause");
	return 0;
}
 
//���ж�ȡtxt�ı�
void readTxt(string file)
{
    ifstream infile; 
    infile.open(file.data());   //���ļ����������ļ��������� 
    assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 
    while(getline(infile,text[line]))   //���д浽text
    {
		line++;
    }
    infile.close();             //�ر��ļ������� 
}

//��text�ı����ݱ�Ϊ�������ʣ����洢
void textToword(Unit verb1[], string text1[], int line1)
{
	string word1 = "";
    //��Ϊ��ά�������
	for(int i = 0; i < line1; i++)
	{
		for(int k = 0; k < text1[i].size()+1; k++)
		{
            //��ǰ�ַ�Ϊ��ĸ������word1�ϲ�
			if(((text1[i][k]>='a')&&( text1[i][k]<='z'))||((text1[i][k]>='A')&&(text1[i][k]<='Z')))
			{
				word1 += text1[i][k]; 
			}
            //��ǰ�ַ�������ĸ
			if(((text1[i][k]<'A')||(text1[i][k]>'Z'))&&((text1[i][k]<'a')||(text1[i][k]>'z')))
			{
                //��ǰ�ַ���Ϊ��
				if(word1 != "")
				{
					save(word1, verb1);
					word1 = ""; 
				}
			}
 
		}
	}
}
 
//�����ʱ��浽�ṹ������
void save(string strr, Unit verb1[])
{
	int newWord1 = 1;
	string str = strr;
	transform(str.begin(), str.end(), str.begin(), ::tolower);  //��д��ĸת��ΪСд��ĸ
    //�������еĽṹ�����飬�жϸõ����Ƿ�Ϊ�´�
	for(int i = 0; i < numVerb; i++)
	{
        //�����´�
		if(str == verb1[i].sequence)   
		{
			verb1[i].freq++; //�õ��ʴ�Ƶ+1
			newWord1 = 0;    //������0
		}
	}
	if(newWord1 == 1)  //���´ʣ���Ϊ��Ԫ�ز���ṹ������
	{
		verb1[numVerb].sequence = str; 
		verb1[numVerb].freq = 1;  
		numVerb++;
	}
}
 
//����������
void sortbyword( Unit verb1[], int numVerb1)
{
	QuickSort(verb1, 0, numVerb1-1, 1);
}
 
//����Ƶ����
void sortbyfrequen(  Unit verb1[], int numVerb1)
{
	QuickSort(verb1, 0, numVerb1-1, 3);
}
 
//type=1 ʱ����ĸ���� �� type=3 ʱ����Ƶ����
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
 
//��������1
void QuickSort(Type a[], int p, int r, int type)
{
	if (p < r)
	{
		int q = RandomizedPartition(a, p, r, type);
		QuickSort(a, p, q-1, type); 
		QuickSort(a, q+1, r, type); 
    }
}

//��������3
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

//��������2
int RandomizedPartition(Type a[],int p,int r, int type)
{	
	int i = Random(p,r);
	Swap(a,i,p);
	return Partition(a, p, r, type);
}

//����
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

//��ӡ���
void Print()
{
    int i;
    printf("����ĸ����\n" );
    sortbyword(verb, numVerb);
    cout.setf( ios::left );
    for( i=0;i<numVerb;i++ )
    {
        cout << "    " << setw(16) << verb[i].sequence << setw(5) << verb[i].freq << endl;	
    }
    cout << endl;
    printf("����Ƶ����\n" );
    sortbyfrequen( verb, numVerb );
    cout.setf( ios::left );
    for( i=0;i<numVerb;i++ )
    {
        cout << "    " << setw(16) << verb[i].sequence << setw(5) << verb[i].freq <<endl;	
    }
}