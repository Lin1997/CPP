/*ѧ���ɼ�����ϵͳ*/
#include<stdlib.h>				//for system()
#include<fstream>
#include<cstring>
#include <iostream>
using namespace std;

enum logintype { Nologin, Stu, Tea, Adm };				//��½״̬
logintype state = Nologin;
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

class People
{
private:
	Name name;
	char Password[30];
public:
	People(char * name = "NoName", char * password = "0000");
	char *getName()
	{
		return name.getName();
	}
	virtual bool verify(char *input)
	{
		return !strcmp(input, Password);
	}
	virtual void resetpassword() = 0;
	virtual void ShowInf()const
	{
		cout << "���֣�" << name << endl;
	}
};
People::People(char * rname, char * password) :name(rname)
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

class Student :public People
{
private:
	struct Mark
	{
		int Chinese;
		int Math;
		int English;
	}mark;
public:
	Student(char * name = "NoName", char * password = "0000", Mark mark = { 0,0,0 }):People(name, password)
	{
		this->mark = mark;
	}
	virtual bool verify(char *password)
	{
		return People::verify(password);
	}
	virtual void resetpassword()
	{
	}
	virtual void ShowInf()const
	{
		People::ShowInf();
		cout << "������" << endl;
		cout << "���ģ�" << mark.Chinese << endl
			<< "��ѧ��" << mark.Math << endl
			<< "Ӣ�" << mark.English << endl;
	}
};

class Teacher :public People
{
private:
	char subject[10];
public:
	Teacher(char * name = "NoName", char * password = "0000",char * subject="UnDefined") :People(name, password)
	{
		if (subject)
		{
			strcpy(this->subject, subject);
		}
		else
		{
			cout << "subject����Ϊ�գ�" << endl;
		}
	}
	virtual bool verify(char *password)
	{
		return People::verify(password);
	}
	virtual void resetpassword()
	{}
	virtual void ShowInf()const
	{
		People::ShowInf();
		cout << "�ڿΣ�" << endl;
		cout << this->subject << endl;
	}
};

class Admin :public People
{
private:

public:
	Admin(char * name = "admin", char * password = "0000") :People(name, password)
	{
	}
	virtual void resetpassword()
	{
	}
	virtual void ShowInf()const
	{
		People::ShowInf();
	}
}admin;		//����Ա�˻�


struct StuNode
{
	Student stu;
	StuNode * pNext;
};
struct TeaNode
{
	Teacher tea;
	TeaNode * pNext;
};


class StuList
{
private:
	static StuNode * pHead;
public:
	StuList()
	{
	}
	~StuList()
	{
		StuNode *p = NULL;
		while (pHead)
		{
			p = pHead;
			pHead = pHead->pNext;
			delete p;
		}
		p = NULL;
	}
	static bool isempty()
	{
		return pHead == NULL;
	}
	static void add()
	{
		StuNode * p = new StuNode;
		if (pHead == NULL)
		{
			pHead = p;
			pHead->pNext = NULL;
		}
		else
		{
			p->pNext = pHead;
			pHead = p;
		}
	}
	static void del(StuNode * pStuNode)
	{
		if (pStuNode==NULL)
		{
			cout << "pStuNode����Ϊ�գ�" << endl;
			return;
		}
		else if (pStuNode == pHead)
		{
			StuNode *p = pHead;
			pHead = pHead->pNext;
			delete p;
			p = NULL;
		}
		else
		{
			StuNode *p = pHead;
			while (p->pNext != pStuNode)
			{
				p = p->pNext;
			}
			p->pNext = pStuNode->pNext;
			delete pStuNode;
			p = NULL;
		}
	}
	static void ShowAll()
	{
		if (pHead == NULL)
		{
			cout << "ѧ���б�Ϊ�գ�" << endl;
			return;
		}
		StuNode * p = pHead;
		while (p)
		{
			p->stu.ShowInf();
			p = p->pNext;
		}
	}
	static StuNode * SearchName(char * name)
	{
		if (name == NULL)
		{
			cout << "name����Ϊ�գ�������ֹ��" << endl;
			return NULL;
		}
		StuNode * p = pHead;
		while (p!=NULL && strcmp(p->stu.getName(),name)!=0)
		{
			p = p->pNext;
		}
		return p;
	}
};
StuNode * StuList::pHead = NULL;				//��ʼ��

class TeaList
{
private:
	static TeaNode * pHead;
public:
	TeaList()
	{
	}
	~TeaList()
	{
		TeaNode *p = NULL;
		while (pHead)
		{
			p = pHead;
			pHead = pHead->pNext;
			delete p;
		}
		p = NULL;
	}
	static bool isempty()
	{
		return pHead == NULL;
	}
	static void add()
	{
		TeaNode * p = new TeaNode;
		if (pHead == NULL)
		{
			pHead = p;
			pHead->pNext = NULL;
		}
		else
		{
			p->pNext = pHead;
			pHead = p;
		}
	}
	static void del(TeaNode * pTeaNode)
	{
		if (pTeaNode == NULL)
		{
			cout << "pTeaNode����Ϊ�գ�" << endl;
			return;
		}
		else if (pTeaNode == pHead)
		{
			TeaNode *p = pHead;
			pHead = pHead->pNext;
			delete p;
			p = NULL;
		}
		else
		{
			TeaNode *p = pHead;
			while (p->pNext != pTeaNode)
			{
				p = p->pNext;
			}
			p->pNext = pTeaNode->pNext;
			delete pTeaNode;
			p = NULL;
		}
	}
	static void ShowAll()
	{
		if (pHead == NULL)
		{
			cout << "��ʦ�б�Ϊ�գ�" << endl;
			return;
		}
		TeaNode * p = pHead;
		while (p)
		{
			p->tea.ShowInf();
			p = p->pNext;
		}
	}
	static TeaNode * SearchName(char * name)
	{
		if (name == NULL)
		{
			cout << "name����Ϊ�գ�������ֹ��" << endl;
			return NULL;
		}
		TeaNode * p = pHead;
		while (p != NULL && strcmp(p->tea.getName(), name) != 0)
		{
			p = p->pNext;
		}
		return p;
	}
};
TeaNode * TeaList::pHead = NULL;				//��ʼ��

void menu(logintype state);					//��ʾ�˵�����
logintype login();					//��½����
void encrypt();				//���ܺ���
void decrypt();				//���ܺ���

void menu(logintype type)
{
	system("cls");
	for (int i = 0; i < 48; i++)				//����
	{
		cout << ' ';
	}
	cout << "ѧ���ɼ�����ϵͳ" << endl;

	switch (type)
	{
	case Nologin:
		cout << "δ��¼" << endl;
		break;
	case Stu:
		cout << "���ܲ˵���" << endl;
		cout << "a.��ѯ�Լ��ĳɼ�\t\t"<< "b.��ѯȫ��ɼ�\t\t" << endl
			<< "c.�����ɼ�\t\t\t"<< "d.�޸�����\t\t" << endl
			<< "q.�˳�ϵͳ" << endl;
		break;
	case Tea:
		cout << "���ܲ˵���" << endl;
		cout << "a.¼��(����)ѧ���ɼ�\t"<< "b.��ѯȫ��ɼ�\t\t" << endl
			<< "c.�ɼ�����\t\t\t"<< "d.���ѧ��\t\t" << endl
			<< "e.ɾ��ѧ��\t\t\t"<< "f.����ȫ��ɼ�\t\t" << endl
			<< "g.�޸�����\t\t" << endl
			<< "q.�˳�ϵͳ" << endl;
		break;
	case Adm:
		cout << "���ܲ˵���" << endl;
		cout << "a.���ѧ��\t\t" << "b.ɾ��ѧ��\t\t" << endl
			<< "c.��ӽ�ʦ\t\t" << "d.ɾ����ʦ\t\t" << endl
			<< "q.�˳�ϵͳ" << endl;
		break;
	default:
		cout << "type��������" << endl;
	}
}

logintype login()
{
	char name[30];
	char password[30];
	if (StuList::isempty() && TeaList::isempty())
	{
		cout << "��ʦ�б��ѧ���б�Ϊ�գ����Թ���Ա�˻���½��" << endl;
	}
	for (int i = 2; i >= 0; i--)
	{
		cout << "�������˻�����" << endl;
		cin.getline(name, 30);
		cout << "���������룺" << endl;
		cin.getline(password, 30);
		StuNode *pStu = StuList::SearchName(name);
		TeaNode *pTea = TeaList::SearchName(name);
		if (pStu)
		{
			if (pStu->stu.verify(password))
			{
				cout << "��½�ɹ���" << endl;
				cout << "��ǰ�˻���" << pStu->stu.getName() << "(ѧ��)" << endl;
				return Stu;
			}
			else
			{
				cout << "�˻����������";
				cout << "ʣ��" << i << "�λ���" << endl;
			}
		}
		else if (pTea)
		{
			if (pTea->tea.verify(password))
			{
				cout << "��½�ɹ���" << endl;
				cout << "��ǰ�˻���" << pTea->tea.getName() << "(��ʦ)" << endl;
				return Tea;
			}
			else
			{
				cout << "�˻����������";
				cout << "ʣ��" << i << "�λ���" << endl;
			}
		}
		else
		{
			if (strcmp(admin.getName(), name) == 0 && admin.verify(password))
			{
				cout << "��½�ɹ���" << endl;
				cout << "��ǰ�˻���" << admin.getName() << "(����Ա)" << endl;
				return Adm;
			}
			else
			{
				cout << "�˻����������";
				cout << "ʣ��" << i << "�λ���" << endl;
			}
		}
	}
	cout << "����������࣬��¼ʧ�ܣ�" << endl;
	return Nologin;
}

int main()
{
	TeaList::add();
	menu(Nologin);
	state = login();
	system("pause");
	if (state == Nologin)
	{
		return 0;
	}
	char choice;
	do
	{
		menu(state);
		cout << "��ѡ�������" << endl;
		cin >> choice;
		if (state == Stu)
		{
			switch (choice)
			{
			case'a':cout << "����ɼ�" << endl;
				system("pause");
				break;
			case'b':cout << "��ѯȫ��ɼ�" << endl;
				system("pause");
				break;
			case'c':cout << "�ɼ�����" << endl;
				system("pause");
				break;
			case'd':cout << "���ѧ��" << endl;
				system("pause");
				break;
			case'e':cout << "ɾ��ѧ��" << endl;
				system("pause");
				break;
			case'f':cout << "����ȫ��ɼ�" << endl;
				system("pause");
				break;
			case'g':cout << "�޸�����" << endl;
				system("pause");
				break;
			case'q':cout << "�˳�ϵͳ" << endl;
				system("pause");
				break;
			default:
				cout << "�Ƿ����룡" << endl;
				system("pause");
			}
		}
	} while (choice != 'q');
	return 0;
}