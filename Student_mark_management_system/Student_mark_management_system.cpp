/*学生成绩管理系统*/
#include<stdlib.h>				//for system()
#include<fstream>
#include<cstring>
#include <iostream>
using namespace std;

enum logintype { Nologin, Stu, Tea, Adm };				//登陆状态
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
				cout << "申请内存失败！操作取消。" << endl;
				return;
			}
		}
		else
		{
			cout << "pName参数为空！操作取消。" << endl;
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
		cout << "名字：" << name << endl;
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
		cout << "Password参数为空！操作取消。" << endl;
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
		cout << "分数：" << endl;
		cout << "语文：" << mark.Chinese << endl
			<< "数学：" << mark.Math << endl
			<< "英语：" << mark.English << endl;
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
			cout << "subject参数为空！" << endl;
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
		cout << "授课：" << endl;
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
}admin;		//管理员账户


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
			cout << "pStuNode参数为空！" << endl;
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
			cout << "学生列表为空！" << endl;
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
			cout << "name参数为空！操作终止。" << endl;
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
StuNode * StuList::pHead = NULL;				//初始化

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
			cout << "pTeaNode参数为空！" << endl;
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
			cout << "老师列表为空！" << endl;
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
			cout << "name参数为空！操作终止。" << endl;
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
TeaNode * TeaList::pHead = NULL;				//初始化

void menu(logintype state);					//显示菜单函数
logintype login();					//登陆函数
void encrypt();				//加密函数
void decrypt();				//解密函数

void menu(logintype type)
{
	system("cls");
	for (int i = 0; i < 48; i++)				//标题
	{
		cout << ' ';
	}
	cout << "学生成绩管理系统" << endl;

	switch (type)
	{
	case Nologin:
		cout << "未登录" << endl;
		break;
	case Stu:
		cout << "功能菜单：" << endl;
		cout << "a.查询自己的成绩\t\t"<< "b.查询全班成绩\t\t" << endl
			<< "c.导出成绩\t\t\t"<< "d.修改密码\t\t" << endl
			<< "q.退出系统" << endl;
		break;
	case Tea:
		cout << "功能菜单：" << endl;
		cout << "a.录入(导入)学生成绩\t"<< "b.查询全班成绩\t\t" << endl
			<< "c.成绩分析\t\t\t"<< "d.添加学生\t\t" << endl
			<< "e.删除学生\t\t\t"<< "f.导出全班成绩\t\t" << endl
			<< "g.修改密码\t\t" << endl
			<< "q.退出系统" << endl;
		break;
	case Adm:
		cout << "功能菜单：" << endl;
		cout << "a.添加学生\t\t" << "b.删除学生\t\t" << endl
			<< "c.添加教师\t\t" << "d.删除教师\t\t" << endl
			<< "q.退出系统" << endl;
		break;
	default:
		cout << "type参数错误！" << endl;
	}
}

logintype login()
{
	char name[30];
	char password[30];
	if (StuList::isempty() && TeaList::isempty())
	{
		cout << "老师列表和学生列表都为空，请以管理员账户登陆。" << endl;
	}
	for (int i = 2; i >= 0; i--)
	{
		cout << "请输入账户名：" << endl;
		cin.getline(name, 30);
		cout << "请输入密码：" << endl;
		cin.getline(password, 30);
		StuNode *pStu = StuList::SearchName(name);
		TeaNode *pTea = TeaList::SearchName(name);
		if (pStu)
		{
			if (pStu->stu.verify(password))
			{
				cout << "登陆成功：" << endl;
				cout << "当前账户：" << pStu->stu.getName() << "(学生)" << endl;
				return Stu;
			}
			else
			{
				cout << "账户或密码错误！";
				cout << "剩余" << i << "次机会" << endl;
			}
		}
		else if (pTea)
		{
			if (pTea->tea.verify(password))
			{
				cout << "登陆成功：" << endl;
				cout << "当前账户：" << pTea->tea.getName() << "(教师)" << endl;
				return Tea;
			}
			else
			{
				cout << "账户或密码错误！";
				cout << "剩余" << i << "次机会" << endl;
			}
		}
		else
		{
			if (strcmp(admin.getName(), name) == 0 && admin.verify(password))
			{
				cout << "登陆成功：" << endl;
				cout << "当前账户：" << admin.getName() << "(管理员)" << endl;
				return Adm;
			}
			else
			{
				cout << "账户或密码错误！";
				cout << "剩余" << i << "次机会" << endl;
			}
		}
	}
	cout << "错误次数过多，登录失败！" << endl;
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
		cout << "请选择操作：" << endl;
		cin >> choice;
		if (state == Stu)
		{
			switch (choice)
			{
			case'a':cout << "导入成绩" << endl;
				system("pause");
				break;
			case'b':cout << "查询全班成绩" << endl;
				system("pause");
				break;
			case'c':cout << "成绩分析" << endl;
				system("pause");
				break;
			case'd':cout << "添加学生" << endl;
				system("pause");
				break;
			case'e':cout << "删除学生" << endl;
				system("pause");
				break;
			case'f':cout << "导出全班成绩" << endl;
				system("pause");
				break;
			case'g':cout << "修改密码" << endl;
				system("pause");
				break;
			case'q':cout << "退出系统" << endl;
				system("pause");
				break;
			default:
				cout << "非法输入！" << endl;
				system("pause");
			}
		}
	} while (choice != 'q');
	return 0;
}