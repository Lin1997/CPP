/*ѧ���ɼ�����ϵͳ*/
#include<stdlib.h>				//for system()
#include<fstream>
#include<cstring>
#include <iostream>
using namespace std;

/*								������								*/
class Name
{
private:
	char *pName;
public:
	Name(char * name = "NoName"):pName(NULL)
	{
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
	}
	~Name()
	{
		if (pName)
		{
			delete[] pName;
		}
		pName = NULL;
	}
	char * getName()
	{
		return pName;
	}
	friend ostream & operator<<(ostream & os, const Name &name);
	friend istream &operator>>(istream & is, const Name &name);
	friend istream &getline(istream &is, const Name &name);
};

class People
{
private:
	Name Name;
	char Password[30];
public:
	People(char * name = "NoName", char * password = "0000");
	char *getName()
	{
		return Name.getName();
	}
	virtual bool login() = 0;
	virtual void resetpassword() = 0;
	virtual void showinf()const
	{
		cout << "���֣�" << Name << endl;
	}
};

class Student :public People
{
private:
	int Mark;
public:
	Student(char * name = "NoName", char * password = "0000",int mark=0);
	virtual bool login();
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
	void searchname(char * name)
	{
		StuNode * temp = pHead;
		while (strcmp(temp->data.getName(),name) != 0 && temp != NULL)
		{
			temp = temp->pNext;
		}
		if (temp)
		{
			cout << "�ҵ�����Ϊ" << temp->data.getName() << "��ѧ��" << endl;
		}
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
ostream & operator<<(ostream & os, const Name &name)
{
	cout << name.pName;
	return os;
}
istream &operator>>(istream & is, const Name &name)
{
	char temp[30];
	cin.getline(temp, 30);
	strcpy(name.pName, temp);
	return is;
}
istream &getline(istream &is, const Name &name)
{
	char temp[30];
	cin.getline(temp, 30);
	strcpy(name.pName, temp);
	return is;
}

People::People(char * name, char * password) :Name(name)
{
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

Student::Student(char * name, char * password, int mark):People(name,password)
{
	Mark = mark;
}
bool Student::login()
{
	cout << "�������û�����" << endl;
	char name[30];
	cin.getline(name, 30);
	return false;
}
void Student::resetpassword()
{
}

enum menutype { first, second, third };
void menu(menutype type);					//��ʾ�˵�����
void encrypt();				//���ܺ���
void decrypt();				//���ܺ���

void menu(menutype type)
{
	switch (type)
	{
	case first:
		for (int i = 0; i < 48; i++)				//����
		{
			cout << ' ';
		}
		cout << "ѧ���ɼ�����ϵͳ" << endl;
		break;
	case second:

		break;
	case third:

		break;
	default:
		cout << "type��������" << endl;
	}
}

int main()
{
	menu(first);
	StuNode a[5];
	StuNode::showall();
	Name b;
	cout << b << endl;
	getline(cin, b);
	cout << b << endl;
	system("pause");
	return 0;
}