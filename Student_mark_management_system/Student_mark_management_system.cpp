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
	virtual void resetpassword();
	virtual void showinf()const
	{
		People::showinf();
		cout << "����" << Mark << endl;
	}
};

class Teacher :public People
{
private:
	
public:
	Teacher(char * name = "NoName", char * password = "0000");
	virtual void resetpassword();
	virtual void showinf()const
	{
		People::showinf();
	}
};

class Admin :public People
{
private:

public:
	Admin(char * name = "NoName", char * password = "0000");
	virtual void resetpassword();
	virtual void showinf()const
	{
		Admin::showinf();
	}
};
Admin admin;		//����Ա�˻�

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
	static bool isempty()
	{
		return pHead == NULL ? true : false;
	}
	static void searchnameName(char * name)
	{
		StuNode * temp = pHead;
		while (temp != NULL && strcmp(temp->data.getName(),name) != 0)
		{
			temp = temp->pNext;
		}
		if (temp)
		{
			cout << "�ҵ�����Ϊ\"" << name << "\"��ѧ��" << endl;
		}
		else
		{
			cout << "û���ҵ�����Ϊ\"" << name << "\"��ѧ����" << endl;
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
private:
	Teacher data;
	static TeaNode * pHead;
	TeaNode *pNext;
public:
	TeaNode()
	{
		if (pHead == NULL)
		{
			pHead = this;
			pNext = NULL;
		}
		else
		{
			TeaNode * temp = pHead;
			pHead = this;
			pNext = temp;
		}
	}
	~TeaNode()
	{
	}
	static bool isempty()
	{
		return pHead == NULL ? true : false;
	}
	static void searchnameName(char * name)
	{
		TeaNode * temp = pHead;
		while (temp != NULL && strcmp(temp->data.getName(), name) != 0)
		{
			temp = temp->pNext;
		}
		if (temp)
		{
			cout << "�ҵ�����Ϊ\"" << name << "\"����ʦ" << endl;
		}
		else
		{
			cout << "û���ҵ�����Ϊ\"" << name << "\"����ʦ��" << endl;
		}
	}
	static void showall()
	{
		TeaNode * temp = pHead;
		while (temp)
		{
			temp->data.showinf();
			temp = temp->pNext;
		}
	}
};
TeaNode * TeaNode::pHead = NULL;

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
void Student::resetpassword()
{
}

enum menutype { first, second, third };
void menu(menutype type);					//��ʾ�˵�����
bool login();					//��½����
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

bool login()
{
	if (StuNode::isempty()&&StuNode::isempty())
	{
		cout << "�û��б�Ϊ�գ����Թ���Ա�˻���¼ϵͳ��" << endl
			<< "���������Ա���ƣ�" << endl;
		char name[30];
		cin.getline(name, 30);
		cout << "���������룺" << endl;
		char password[30];

		
	}
	cout << "�������û�����" << endl;
	char name[30];
	cin.getline(name, 30);

	return false;
}
int main()
{
	
	menu(first);
	system("pause");
	return 0;
}