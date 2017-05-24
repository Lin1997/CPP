/*ѧ���ɼ�����ϵͳ*/
#include<stdlib.h>				//for system()
#include<fstream>
#include<cstring>
#include <iostream>
using namespace std;

enum logintype { Nologin, Stu, Tea, Adm };				//��½״̬
class People;		//��ǰ����
People * user = NULL;												//��ǰ�û�
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
		cout << "����name(debug)" << endl;
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
	virtual void resetpassword(char * newpassword=NULL)
	{
		if (newpassword)
		{
			strcpy(Password, newpassword);
		}
		else
		{
			cout << "�����������룺" << endl;
			cin.getline(Password, 30);
			if (strcmp(Password, ""))
			{
				strcpy(Password, "0000");
				cout << "���벻��Ϊ�գ�������Ϊ\"0000\"" << endl;
			}
		}
	}
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
	long ID;
	static int num;	//�Ѵ�ѧ������
public:
	Student(char * name = "NoName", char * password = "0000",long id=num,Mark mark = { 0,0,0 }) :People(name, password)
	{
		this->mark = mark;
		ID = id;
		num++;
	}
	void SetStuMark(int Chinese,int Math, int English)
	{
		mark.Chinese = Chinese;
		mark.Math = Math;
		mark.English = English;
	}
	void SetStuMark()
	{
		int Chinese, Math, English;
		cout << "�������������ĳɼ�����ѧ�ɼ���Ӣ��ɼ���" << endl;
		cin >> Chinese >> Math >> English;
		SetStuMark(Chinese, Math, English);
	}
	virtual bool verify(char *password)
	{
		return People::verify(password);
	}
	virtual void resetpassword(char * newpassword=NULL)
	{
		People::resetpassword(newpassword);
	}
	virtual void ShowInf()const
	{
		People::ShowInf();
		cout << "ѧ�ţ�" << ID << endl;
		cout << "\t����" << endl;
		cout << "���ģ�" << mark.Chinese << endl
			<< "��ѧ��" << mark.Math << endl
			<< "Ӣ�" << mark.English << endl;
	}
};
int Student::num = 1;

struct StuNode
{
	Student stu;
	StuNode * pNext;
};
class StuList
{
private:
	StuNode * pHead;
public:
	StuList()
	{
		pHead = NULL;
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
	bool isempty()
	{
		return pHead == NULL;
	}
	void add()
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
		cout << "������ѧ�����֣�" << endl;
		cin.getline(p->stu.getName(), 30);
		p->stu.resetpassword();
	}
	void del(StuNode * pStuNode)
	{
		if (pStuNode == NULL)
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
	void ShowAll()
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
	StuNode * SearchName(char * name = NULL)
	{
		if (name == NULL)
		{
			cout << "������ѧ�����֣�" << endl;
			cin.getline(name, 30);
			StuList::SearchName(name);
		}
		StuNode * p = pHead;
		while (p != NULL && strcmp(p->stu.getName(), name) != 0)
		{
			p = p->pNext;
		}
		return p;
	}
}stulist;

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
	void SetStuMark(char * StuName=NULL)
	{
		if (StuName)
		{
			stulist.SearchName(StuName)->stu.SetStuMark();
		}
		else
		{
			cout << "����ѧ�Ŵ�С����¼��" << endl;
		}
	}
	virtual bool verify(char *password)
	{
		return People::verify(password);
	}
	virtual void resetpassword(char *newpassword=NULL)
	{
		People::resetpassword(newpassword);
	}
	virtual void ShowInf()const
	{
		People::ShowInf();
		cout << "�ڿΣ�" << endl;
		cout << this->subject << endl;
	}
};
struct TeaNode
{
	Teacher tea;
	TeaNode * pNext;
};
class TeaList
{
private:
	TeaNode * pHead;
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
	bool isempty()
	{
		return pHead == NULL;
	}
	void add()
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
		cout << "�������ʦ���֣�" << endl;
		cin.getline(p->tea.getName(), 30);
		p->tea.resetpassword();
	}
	void del(TeaNode * pTeaNode)
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
	void ShowAll()
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
	TeaNode * SearchName(char * name)
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
}tealist;

class Admin :public People
{
private:

public:
	Admin(char * name = "admin", char * password = "0000") :People(name, password)
	{
	}
	virtual void resetpassword(char *newpassword=NULL)
	{
		People::resetpassword(newpassword);
	}
	virtual void ShowInf()const
	{
		People::ShowInf();
	}
	void ShowAll()
	{
		cout << "ѧ���б�" << endl;
		stulist.ShowAll();
		cout << endl;
		cout << "��ʦ�б�" << endl;
		tealist.ShowAll();
		cout << endl;
		system("pause");
	}
}admin;		//����Ա�˻�

void menu(logintype state);					//��ʾ�˵�����
void login();					//��½����
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
		cout <<"a.��ʾ�û��б�\t\t"<<"b.���ѧ��\t\t"<<endl
			<<"c.ɾ��ѧ��\t\t"<< "d.��ӽ�ʦ\t\t" << endl
			<<"e.ɾ����ʦ\t\t" << endl
			<< "q.�˳�ϵͳ" << endl;
		break;
	default:
		cout << "type��������" << endl;
	}
}

void login()
{
	char name[30];
	char password[30];
	if (stulist.isempty() && tealist.isempty())
	{
		cout << "��ʦ�б��ѧ���б�Ϊ�գ����Թ���Ա�˻���½��" << endl;
	}
	for (int i = 2; i >= 0; i--)
	{
		cout << "�������˻�����" << endl;
		cin.getline(name, 30);
		cout << "���������룺" << endl;
		cin.getline(password, 30);
		StuNode *pStu = stulist.SearchName(name);
		TeaNode *pTea = tealist.SearchName(name);
		if (pStu)
		{
			if (pStu->stu.verify(password))
			{
				cout << "��½�ɹ���" << endl;
				cout << "��ǰ�˻���" << pStu->stu.getName() << "(ѧ��)" << endl;
				state = Stu;
				user = &pStu->stu;
				return;
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
				state = Tea;
				user = &pTea->tea;
				return;
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
				state = Adm;
				user = &admin;
				return;
			}
			else
			{
				cout << "�˻����������";
				cout << "ʣ��" << i << "�λ���" << endl;
			}
		}
	}
	cout << "����������࣬��¼ʧ�ܣ�" << endl;
	state=Nologin;
}

int main()
{
	menu(Nologin);
	login();
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
		while (cin.get() != '\n')
		{
			continue;
		}
		if (state == Stu)
		{
			switch (choice)
			{
			case'a':cout << "��ѯ�Լ��ĳɼ�" << endl;
				system("pause");
				break;
			case'b':cout << "��ѯȫ��ɼ�" << endl;
				system("pause");
				break;
			case'c':cout << "�����ɼ�" << endl;
				system("pause");
				break;
			case'd':cout << "�޸�����" << endl;
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
		else if (state == Tea)
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
			case'd':
				cout << "���ѧ��" << endl;
				stulist.add();
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
		else if (state == Adm)
		{
			switch (choice)
			{
			case'a':cout << "��ʾ�û��б�" << endl;
				admin.ShowAll();
				break;
			case'b':cout << "���ѧ��" << endl;
				stulist.add();
				break;
			case'c':cout << "ɾ��ѧ��" << endl;
				system("pause");
				break;
			case'd':cout << "��ӽ�ʦ" << endl;
				system("pause");
				break;
			case'e':cout << "ɾ����ʦ" << endl;
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
		else
		{
			cout << "δ��¼" << endl;
		}
	} while (choice != 'q');
	return 0;
}