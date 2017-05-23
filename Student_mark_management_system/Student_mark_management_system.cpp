/*学生成绩管理系统*/
#include<stdlib.h>				//for system()
#include<fstream>
#include<cstring>
#include <iostream>
using namespace std;

/*								类声明								*/
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
		cout << "名字：" << pName << endl;
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
		cout << "分数" << Mark << endl;
	}
};

class Teacher :public People
{

};

class Admin :public People
{

};

class StuNode				//学生列表
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

class TeaNode				//老师列表
{

};

/*								类成员函数实现								*/	
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
			cout << "申请内存失败！操作取消。" << endl;
			return;
		}
	}
	else
	{
		cout << "pName参数为空！操作取消。" << endl;
		return;
	}
	//Password
	if (password)
	{
		strcpy(Password, password);
	}
	else
	{
		cout << "Password参数为空！操作取消。" << endl;
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


void menu();					//显示菜单函数
void encrypt();				//加密函数
void decrypt();				//解密函数
void login();

int main()
{
	StuNode a[5];
	StuNode::showall();
	system("pause");
	return 0;
}