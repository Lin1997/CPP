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
	People(char * name = NULL, char * password = "0000");
	~People();
	virtual void login() = 0;
	virtual void resetpassword() = 0;
	virtual void showinf()const
	{
		cout << "名字：" << pName << endl;
		cout << Password << endl;
	}
};

class Student :public People
{
private:
	int mark;
public:
	virtual void login();
	virtual void resetpassword();
	virtual void showinf()const
	{
		People::showinf();
		cout << "分数" << mark << endl;
	}
};

class Teacher :public People
{

};

class Admin :public People
{

};

class Stulist				//学生列表
{
private:
	static Student * pHead;
	Student *pNext;
public:
	Stulist()
	{
		if (pHead==NULL)
		{
			pHead = new Student;
			pNext = NULL;
		}
		else
		{
			Student * temp = pHead;
			pHead = new Student;
			pNext = temp;
		}
	}
	~Stulist()
	{
		while (pHead)
		{
			delete pHead;
			pHead = pNext;
		}
	}
	void show()
	{

	}
};
Student * pHead = NULL;

class Tealist				//老师列表
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

void Student::login()
{
}
void Student::resetpassword()
{
}

void Stulist::add()
{

}
void Stulist::del()
{

}

void menu();					//显示菜单函数
void encrypt();				//加密函数
void decrypt();				//解密函数
void login();

int main()
{
	People a("Lin");
	a.showinf();
	system("pause");
	return 0;
}