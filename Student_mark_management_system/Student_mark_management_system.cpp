/*学生成绩管理系统*/
#include<stdlib.h>				//for system()
#include<fstream>
#include<cstring>
#include <iostream>
using namespace std;

/*								类声明								*/
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
		cout << "名字：" << Name << endl;
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
		cout << "分数" << Mark << endl;
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
Admin admin;		//管理员账户

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
			cout << "找到名字为\"" << name << "\"的学生" << endl;
		}
		else
		{
			cout << "没有找到名字为\"" << name << "\"的学生！" << endl;
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

class TeaNode				//老师列表
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
			cout << "找到名字为\"" << name << "\"的老师" << endl;
		}
		else
		{
			cout << "没有找到名字为\"" << name << "\"的老师！" << endl;
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

/*								类成员函数实现								*/	
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
		cout << "Password参数为空！操作取消。" << endl;
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
void menu(menutype type);					//显示菜单函数
bool login();					//登陆函数
void encrypt();				//加密函数
void decrypt();				//解密函数

void menu(menutype type)
{
	switch (type)
	{
	case first:
		for (int i = 0; i < 48; i++)				//标题
		{
			cout << ' ';
		}
		cout << "学生成绩管理系统" << endl;
		break;
	case second:

		break;
	case third:

		break;
	default:
		cout << "type参数错误！" << endl;
	}
}

bool login()
{
	if (StuNode::isempty()&&StuNode::isempty())
	{
		cout << "用户列表为空，请以管理员账户登录系统！" << endl
			<< "请输入管理员名称：" << endl;
		char name[30];
		cin.getline(name, 30);
		cout << "请输入密码：" << endl;
		char password[30];

		
	}
	cout << "请输入用户名：" << endl;
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