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
	People(char * name = NULL, char * password = "0000");
	~People();
	virtual void login() = 0;
	virtual void resetpassword() = 0;
	virtual void showinf()const
	{
		cout << "���֣�" << pName << endl;
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
		cout << "����" << mark << endl;
	}
};

class Teacher :public People
{

};

class Admin :public People
{

};

class Stulist				//ѧ���б�
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

class Tealist				//��ʦ�б�
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

void menu();					//��ʾ�˵�����
void encrypt();				//���ܺ���
void decrypt();				//���ܺ���
void login();

int main()
{
	People a("Lin");
	a.showinf();
	system("pause");
	return 0;
}