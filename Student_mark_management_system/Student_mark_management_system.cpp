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

class People
{
private:
	char name[30];
	char Password[30];
public:
	People(char * name = "NoName", char * password = "0000");
	char *getName()
	{
		return name;
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
			if (strcmp(Password, "")==0)
			{
				strcpy(Password, "0000");
				cout << "���벻��Ϊ�գ�������Ϊ\"0000\"" << endl;
				system("pause");
			}
		}
	}
	virtual void ShowInf()const
	{
		cout << "���֣�" << name;
	}
};
People::People(char * rname, char * password)
{
	if (rname)
	{
		strcpy(name, rname);
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
public:
	static int num;	//�Ѵ�ѧ������
	Student(char * name = "NoName", char * password = "0000",long id=num,Mark mark = { 0,0,0 }) :People(name, password)
	{
		this->mark = mark;
		ID = id;
		num++;
	}
	~Student()
	{
	}
	long getID()
	{
		return ID;
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
	int getSumMark()
	{
		return mark.Chinese + mark.Math + mark.English;
	}
	double getAverageMark()
	{
		return getSumMark() / 3.0;
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
		cout << "\tѧ�ţ�" << ID;
	}
	Mark getMark()
	{
		return mark;
	}
	void ShowMark()
	{
		cout << "���ģ�" << mark.Chinese << endl
			<< "��ѧ��" << mark.Math << endl
			<< "Ӣ�" << mark.English << endl;
	}
	void SaveMark()
	{
		ofstream outfile;
		char filename[30];
		strcpy(filename, "D:\\");
		strcat(filename, this->getName());
		strcat(filename, "�ĳɼ���.txt");
		outfile.open(filename);
		Mark temp = this->getMark();
		outfile << this->getName() << "�ĳɼ�����" << endl
			<< "���ģ�" << temp.Chinese << endl
			<< "��ѧ��" << temp.Math << endl
			<< "Ӣ�" << temp.English << endl;
		outfile.close();
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
	void ShowAllMark()
	{
		SortWithMark(stulist);
		StuNode *p = pHead;
		while (p != NULL)
		{
			p->stu.ShowInf();
			cout << "\t\t" << endl;
			p->stu.ShowMark();
			cout << endl;
			p = p->pNext;
		}
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
		if (*(p->stu.getName())=='\0')
		{
			cout << "�˻�������Ϊ�գ�����ȡ����" << endl;
			stulist.del(p);
			return;
		}
		p->stu.resetpassword();
	}
	void add(Student &stu)
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
		p->stu = stu;
	}
	void del(StuNode * pStuNode)
	{
		if (pStuNode == NULL)
		{
			cout << "�����������ˣ�����ȡ����" << endl;
			system("pause");
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
	void DelFromName(char * name = NULL)
	{
		del(stulist.SearchName(name));
	}
	void DelFromID(long id)
	{
		del(stulist.SearchID(id));
	}
	void DelFromID()
	{
		del(stulist.SearchID());
	}
	StuNode *Swap(StuNode *p1, StuNode *p2,bool FromMark=false)
	{
		StuNode *temp1;
		StuNode *temp2;
		for (temp1 = pHead; temp1 != NULL&&temp1->pNext != p1; temp1 = temp1->pNext)	//Ѱ��p1ǰ�Ľڵ��ָ��
		{
			continue;
		}
		for (temp2 = pHead; temp2 != NULL&&temp2->pNext != p2; temp2 = temp2->pNext)	//Ѱ��p2ǰ�Ľڵ��ָ��
		{
			continue;
		}
		if (temp1 == NULL&&temp2!=NULL)
		{
			if (p1 == pHead)		//p1��ͷ���
			{
				StuNode *temp = p2->pNext;		//����
				pHead = p2;

				if (p1->pNext == p2)		//����
				{
					p2->pNext = p1;
				}
				else																//������
				{
					p2->pNext = p1->pNext;
					temp2->pNext = p1;
				}
				p1->pNext = temp;
			}
		}
		else if (temp2 == NULL&&temp1!=NULL)
		{
			if (p2 == pHead)		//p2��ͷ���
			{
				StuNode *temp = p1->pNext;		//����
				pHead = p1;

				if (p1->pNext == p2)		//����
				{
					p1->pNext = p2;
				}
				else									//������
				{
					p1->pNext = p2->pNext;
					temp1->pNext = p2;
				}
				p2->pNext = temp;
			}
		}
		else
		{
			temp1->pNext = p2;
			temp2->pNext = p1;
		}
		if (FromMark == false)
		{
			return p2;
		}
		else
		{
			return p1;
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
			cout << endl;
			p = p->pNext;
		}
	}
	StuNode * SearchName(char * name = NULL)
	{
		if (name == NULL)
		{
			cout << "������ѧ�����֣�" << endl;
			char rname[30];
			cin.getline(rname, 30);
			return SearchName(rname);
		}
		StuNode * p = pHead;
		while (p != NULL && strcmp(p->stu.getName(), name) != 0)
		{
			p = p->pNext;
		}
		return p;
	}
	StuNode * SearchID(long id)
	{
		StuNode *p = pHead;
		while (p != NULL && id != p->stu.getID())
		{
			p = p->pNext;
		}
		return p;
	}
	StuNode * SearchID()
	{
		long id;
		cout << "������ѧ�ţ�" << endl;
		cin >> id;
		return SearchID(id);
	}
	double getClassChineseAverage()
	{
		StuNode *p = pHead;
		double ChineseSum = 0;
		int PeopleNum = 0;
		while (p)
		{
			ChineseSum += p->stu.getMark().Chinese;
			PeopleNum++;
			p = p->pNext;
		}
		return ChineseSum / PeopleNum;
	}
	double getClassMathAverage()
	{
		StuNode *p = pHead;
		double MathSum = 0;
		int PeopleNum = 0;
		while (p)
		{
			MathSum += p->stu.getMark().Math;
			PeopleNum++;
			p = p->pNext;
		}
		return MathSum / PeopleNum;
	}
	double getClassEnglishAverage()
	{
		StuNode *p = pHead;
		double EnglishSum = 0;
		int PeopleNum = 0;
		while (p)
		{
			EnglishSum += p->stu.getMark().English;
			PeopleNum++;
			p = p->pNext;
		}
		return EnglishSum / PeopleNum;
	}
	double getClassChinesePassRate()
	{
		StuNode *p = pHead;
		int PeopleNum = 0;
		int PassPeople = 0;
		while (p)
		{
			if (p->stu.getMark().Chinese >= 60)
			{
				PassPeople++;
			}
			PeopleNum++;
			p = p->pNext;
		}
		return PassPeople/PeopleNum;
	}
	double getClassMathPassRate()
	{
		StuNode *p = pHead;
		int PeopleNum = 0;
		int PassPeople = 0;
		while (p)
		{
			if (p->stu.getMark().Math >= 60)
			{
				PassPeople++;
			}
			PeopleNum++;
			p = p->pNext;
		}
		return PassPeople / PeopleNum;
	}
	double getClassEnglishPassRate()
	{
		StuNode *p = pHead;
		int PeopleNum = 0;
		int PassPeople = 0;
		while (p)
		{
			if (p->stu.getMark().English >= 60)
			{
				PassPeople++;
			}
			PeopleNum++;
			p = p->pNext;
		}
		return PassPeople / PeopleNum;
	}
	friend void savefile();
	friend void SaveAllMark();
	friend void SortWithID(StuList & stulist);
	friend void SortWithMark(StuList & stulist);
	friend void SetStuMark(char * StuName);
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
	virtual bool verify(char *password)
	{
		return People::verify(password);
	}
	virtual void resetpassword(char *newpassword=NULL)
	{
		People::resetpassword(newpassword);
	}
	void LoadAllMark()
	{
		ifstream infile;
		infile.open("D:\\ȫ��ɼ�.txt");	//���Դ�
		if (infile.good() == false)
		{
			cout << "�ļ������ڣ�����ȡ����" << endl;
			system("pause");
			return;
		}
	}
	void ShowMarkAnalyze()
	{
		cout << "ȫ��ɼ���:" << endl;
		stulist.ShowAllMark();
		cout << "�༶ƽ���������" << endl;
		cout << "���ģ�" << stulist.getClassChineseAverage() << "\t"
			<< "��ѧ��" << stulist.getClassMathAverage() << "\t"
			<< "Ӣ�" << stulist.getClassEnglishAverage() << endl;
		cout << "�༶�����ʣ�" << endl;
		cout << "���ģ�" << stulist.getClassChinesePassRate() * 100 << "%\t"
			<< "��ѧ��" << stulist.getClassMathPassRate() * 100 << "%\t"
			<< "Ӣ�" << stulist.getClassEnglishPassRate() * 100 << "%\t" << endl;
	}
	virtual void ShowInf()const
	{
		People::ShowInf();
		cout << "\t�ڿΣ�";
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
	void add(Teacher &tea)
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
		p->tea = tea;
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
		cout << "ɾ���ɹ���" << endl;
		system("pause");
	}
	void DelFromName(char *name=NULL)
	{
		del(tealist.SearchName(name));
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
			cout << "������ѧ�����֣�" << endl;
			char rname[30];
			cin.getline(rname, 30);
			SearchName(rname);
		}
		TeaNode * p = pHead;
		while (p != NULL && strcmp(p->tea.getName(), name) != 0)
		{
			p = p->pNext;
		}
		return p;
	}
	friend void savefile();
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
void SortWithID(StuList & stulist);
void SortWithMark(StuList & stulist);
void SetStuMark(char * StuName = NULL);
void loadfile();				//�����ļ�����
void SaveAllMark();		//����ѧ���ɼ�������

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
		cout << "���½ϵͳ" << endl;
		break;
	case Stu:
		cout << "���ܲ˵���" << endl;
		cout << "a.��ѯ�Լ��ĳɼ�\t\t"<< "b.��ѯȫ��ɼ�\t\t" << endl
			<< "c.�����ɼ�\t\t\t"<< "d.�޸�����\t\t" << endl
			<< "q.�˳�ϵͳ" << endl;
		break;
	case Tea:
		cout << "���ܲ˵���" << endl;
		cout << "a.��ʾȫ������\t"<<"b.¼��ѧ���ɼ�"<< endl
			<<"c.��ѯȫ��ɼ�\t\t" << "d.�ɼ�����\t\t\t"<< endl
			<<"e.���ѧ��\t\t" << "f.ɾ��ѧ��\t\t\t"<<endl
			<<"g.����ȫ��ɼ�\t\t" << "h.�޸�����\t\t" << endl
			<< "q.�˳�ϵͳ" << endl;
		break;
	case Adm:
		cout << "���ܲ˵���" << endl;
		cout <<"a.��ʾ�û��б�\t"<<"b.���ѧ��\t\t"<<endl
			<<"c.ɾ��ѧ��\t\t"<< "d.��ӽ�ʦ\t\t" << endl
			<<"e.ɾ����ʦ\t\t" << "f.�޸�����\t\t"<<endl
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
 
void SortWithID(StuList & stulist)
{
	/*ѡ������*/
	for (StuNode *p1 = stulist.pHead; p1->pNext != NULL; p1 = p1->pNext)
	{
		StuNode *min = p1;
		for (StuNode * p2 = p1->pNext; p2!=NULL;p2 = p2->pNext)
		{
			if (p1->stu.getID() > p2->stu.getID())
			{
				min = p2;
			}
		}
		if (min != p1)
		{
			p1 = stulist.Swap(p1, min);	/*����Ԫ�ؽ�����Ҫ����ȷ����ǰȷ���õ�С��Ԫ��*/
		}
	}
}

void SortWithMark(StuList & stulist)
{
	/*ѡ������*/
	for (StuNode *p1 = stulist.pHead; p1->pNext != NULL; p1 = p1->pNext)
	{
		StuNode *min = p1;
		for (StuNode * p2 = p1->pNext; p2 != NULL; p2 = p2->pNext)
		{
			if (p1->stu.getSumMark() < p2->stu.getSumMark())
			{
				min = p2;
			}
		}
		if (min != p1)
		{
			p1 = stulist.Swap(p1, min,true);	/*����Ԫ�ؽ�����Ҫ����ȷ����ǰȷ���õĴ��Ԫ��*/
		}
	}
}

void SetStuMark(char * StuName)
{
	if (StuName)
	{
		stulist.SearchName(StuName)->stu.SetStuMark();
	}
	else
	{
		cout << "����ѧ�Ŵ�С����¼��" << endl;
		SortWithID(stulist);
		StuNode *p = stulist.pHead;
		while (p)
		{
			p->stu.ShowInf();
			cout << endl;
			p->stu.SetStuMark();
			p = p->pNext;
		}
	}
}

void loadfile()
{
	ifstream infile;
	infile.open("D:\\userlist.data",ios_base::binary|ios_base::in);
	if (infile.good() == false)
	{
		cout << "�ļ������ڣ�����ȡ����" << endl;
		system("pause");
		return;
	}
	/*��ȡ����*/
	int StuSum = 0, TeaSum = 0;
	infile.read((char*)&StuSum, sizeof(int));
	infile.read((char*)&TeaSum, sizeof(int));
	Student stutemp;
	Teacher teatemp;
	for (; StuSum > 0; StuSum--)
	{
		infile.read((char*)&stutemp, sizeof(StuNode) - sizeof(StuNode*));
		stulist.add(stutemp);
	}
	for (; TeaSum > 0; TeaSum--)
	{
		infile.read((char*)&teatemp, sizeof(TeaNode) - sizeof(TeaNode*));
		tealist.add(teatemp);
	}
	Student::num--;
	infile.read((char*)&admin, sizeof(admin));
	infile.close();
}

void savefile()
{
	ofstream outfile;
	outfile.open("D:\\userlist.data", ios_base::binary | ios_base::out);
	StuNode *pStu = stulist.pHead;
	TeaNode *pTea = tealist.pHead;
	/*��ʼ����*/
	int StuSum = 0;
	int TeaSum = 0;
	while (pStu)
	{
		StuSum++;
		pStu = pStu->pNext;
	}
	while (pTea)
	{
		TeaSum++;
		pTea = pTea->pNext;
	}
	pStu = stulist.pHead;
	pTea = tealist.pHead;
	/*��������*/
	//ǰ2*sizeof(int)���ֽڴ�Ÿ���
	outfile.write((char*)&StuSum, sizeof(int));
	outfile.write((char*)&TeaSum, sizeof(int));
	while (pStu != NULL&&outfile.good())
	{
		outfile.write((char*)pStu, sizeof(StuNode) - sizeof(StuNode*));
		pStu = pStu->pNext;
	}
	while (pTea != NULL&&outfile.good())
	{
		outfile.write((char*)pTea, sizeof(TeaNode) - sizeof(TeaNode*));
		pTea = pTea->pNext;
	}
	outfile.write((char*)&admin, sizeof(admin));
	outfile.close();
}

void SaveAllMark()
{
	ofstream outfile;
	outfile.open("D:\\ȫ��ɼ�.txt");
	if (outfile.good() == false)
	{
		cout << "δ֪���󣬱���ʧ��" << endl;
		system("pause");
		return;
	}
	outfile << "ѧ��\t" << "����\t" << "����\t" << "��ѧ\t" << "Ӣ��\t"<< "�ܷ�\t" << endl;
	SortWithMark(stulist);
	StuNode *p = stulist.pHead;
	while (p)
	{
		outfile << p->stu.getID() << "\t" << p->stu.getName() << "\t"
			<< p->stu.getMark().Chinese << "\t" << p->stu.getMark().Math << "\t" << p->stu.getMark().English << "\t"
			<< p->stu.getSumMark() << endl;
		p = p->pNext;
	}
}

int main()
{
	cout << "�����ļ�..." << endl;
	loadfile();
	SortWithID(stulist);
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
				((Student *)user)->ShowMark();
				system("pause");
				break;
			case'b':cout << "��ѯȫ��ɼ�" << endl;
				stulist.ShowAllMark();
				system("pause");
				break;
			case'c':cout << "�����ɼ�" << endl;
				SortWithMark(stulist);
				((Student*)user)->SaveMark();
				cout << "�����ɹ���" << endl;
				system("pause");
				break;
			case'd':cout << "�޸�����" << endl;
				user->resetpassword();
				cout << "�����޸ĳɹ���" << endl;
				system("pause");
				break;
			case'q':cout << "�˳�ϵͳ" << endl;
				savefile();
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
			case'a':
				SortWithID(stulist);
				stulist.ShowAll();
				system("pause");
				break;
			case'b':cout << "¼��ɼ�" << endl;
				SetStuMark();
				system("pause");
				break;
			case'c':cout << "��ѯȫ��ɼ�" << endl;
				stulist.ShowAllMark();
				system("pause");
				break;
			case'd':cout << "�ɼ�����" << endl;
				((Teacher*)user)->ShowMarkAnalyze();
				system("pause");
				break;
			case'e':
				cout << "���ѧ��" << endl;
				stulist.add();
				system("pause");
				break;
			case'f':cout << "ɾ��ѧ��" << endl;
				cout << "a.ͨ�����ֲ���ѧ��\t\tb.ͨ��ѧ�Ų���ѧ��" << endl;
				char mode;
				cin >> mode;
				while (cin.get() != '\n')
				{
					continue;
				}
				if (mode == 'a')
					stulist.DelFromName();
				else if (mode == 'b')
					stulist.DelFromID();
				else
					cout << "�Ƿ����룡" << endl;
				break;
			case'g':cout << "����ȫ��ɼ�" << endl;
				SortWithMark(stulist);
				SaveAllMark();
				system("pause");
				break;
			case'h':cout << "�޸�����" << endl;
				user->resetpassword();
				cout << "�����޸ĳɹ���" << endl;
				system("pause");
				break;
			case'q':cout << "�˳�ϵͳ" << endl;
				savefile();
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
				SortWithID(stulist);
				admin.ShowAll();
				break;
			case'b':cout << "���ѧ��" << endl;
				stulist.add();
				break;
			case'c':cout << "ɾ��ѧ��" << endl;
				cout << "a.ͨ�����ֲ���ѧ��\t\tb.ͨ��ѧ�Ų���ѧ��" << endl;
				char mode;
				cin >> mode;
				while (cin.get() != '\n')
				{
					continue;
				}
				if (mode == 'a')
					stulist.DelFromName();
				else if (mode == 'b')
					stulist.DelFromID();
				else
					cout << "�Ƿ����룡" << endl;
				break;
			case'd':cout << "��ӽ�ʦ" << endl;
				tealist.add();
				break;
			case'e':cout << "ɾ����ʦ" << endl;
				tealist.DelFromName();
				break;
			case'f':cout << "�޸�����" << endl;
				user->resetpassword();
				cout << "�����޸ĳɹ���" << endl;
				system("pause");
				break;
			case'q':cout << "�˳�ϵͳ" << endl;
				savefile();
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