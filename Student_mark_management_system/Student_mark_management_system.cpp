/*ѧ���ɼ�����ϵͳ*/
#include<stdlib.h>				//for system()
#include<fstream>
#include<cstring>
#include <iostream>
using namespace std;

/*								������								*/
class People
{
private:
	char * pName;
	char Password[30];
public:
	People(char * name = "NoName", char * password = "0000");
	~People();
	virtual void login() = 0;
	virtual void resetpassword() = 0;
	virtual void showinf()const
	{
		cout << "���֣�" << pName << endl;
	}
};

class Student :public People
{
private:
	int Mark;
public:
	Student(char * name = "NoName", char * password = "0000",int mark=0);
	virtual void login();
	virtual void resetpassword();
	virtual void showinf()const
	{
		People::showinf();
		cout << "����" << Mark << endl;
	}
};

class Teacher :public People
{

};

class Admin :public People
{

};

class StuNode				//ѧ���б�
{
private:
	Student data;
	static StuNode * pHead;
	StuNode *pNext;
public:
	StuNode()
	{
		if (pHead==NULL)
		{
			pHead = this;
			pNext = NULL;
		}
		else
		{
			StuNode * temp = pHead;
			pHead = this;
			pNext = temp;
		}
	}
	~StuNode()
	{
	}
	static void showall()
	{
		StuNode * temp = pHead;
		while (temp)
		{
			temp->data.showinf();
			temp = temp->pNext;
		}
	}
};
StuNode * StuNode::pHead = NULL;

class TeaNode				//��ʦ�б�
{

};

/*								���Ա����ʵ��								*/	
People::People(char * name, char * password) :pName(NULL)
{
	//pName
	if (name)
	{
		pName = new char[strlen(name) + 1];
		if (pName)
		{
			strcpy(pName, name);
		}
		else
		{
			cout << "�����ڴ�ʧ�ܣ�����ȡ����" << endl;
			return;
		}
	}
	else
	{
		cout << "pName����Ϊ�գ�����ȡ����" << endl;
		return;
	}
	//Password
	if (password)
	{
		strcpy(Password, password);
	}
	else
	{
		cout << "Password����Ϊ�գ�����ȡ����" << endl;
	}
}
People::~People()
{
	if (pName)
	{
		delete[] pName;
	}
	pName = NULL;
}

Student::Student(char * name, char * password, int mark):People(name,password)
{
	Mark = mark;
}
void Student::login()
{
}
void Student::resetpassword()
{
}


void menu();					//��ʾ�˵�����
void encrypt();				//���ܺ���
void decrypt();				//���ܺ���
void login();

int main()
{
	StuNode a[5];
	StuNode::showall();
	system("pause");
	return 0;
}