/*学生成绩管理系统*/
#include<stdlib.h>				//for system()
#include<fstream>
#include<cstring>
#include <iostream>
using namespace std;

enum logintype { Nologin, Stu, Tea, Adm };				//登陆状态
class People;		//向前声明
People * user = NULL;												//当前用户
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
			cout << "请输入新密码：" << endl;
			cin.getline(Password, 30);
			if (strcmp(Password, "")==0)
			{
				strcpy(Password, "0000");
				cout << "密码不能为空，已设置为\"0000\"" << endl;
				system("pause");
			}
		}
	}
	virtual void ShowInf()const
	{
		cout << "名字：" << name;
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
	long ID;
public:
	static int num;	//已存学生个数
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
		cout << "请连续输入语文成绩，数学成绩和英语成绩：" << endl;
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
		cout << "\t学号：" << ID;
	}
	Mark getMark()
	{
		return mark;
	}
	void ShowMark()
	{
		cout << "语文：" << mark.Chinese << endl
			<< "数学：" << mark.Math << endl
			<< "英语：" << mark.English << endl;
	}
	void SaveMark()
	{
		ofstream outfile;
		char filename[30];
		strcpy(filename, "D:\\");
		strcat(filename, this->getName());
		strcat(filename, "的成绩单.txt");
		outfile.open(filename);
		Mark temp = this->getMark();
		outfile << this->getName() << "的成绩单：" << endl
			<< "语文：" << temp.Chinese << endl
			<< "数学：" << temp.Math << endl
			<< "英语：" << temp.English << endl;
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
		cout << "请输入学生名字：" << endl;
		cin.getline(p->stu.getName(), 30);
		if (*(p->stu.getName())=='\0')
		{
			cout << "账户名不能为空，操作取消！" << endl;
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
			cout << "搜索不到此人，操作取消！" << endl;
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
		for (temp1 = pHead; temp1 != NULL&&temp1->pNext != p1; temp1 = temp1->pNext)	//寻找p1前的节点的指针
		{
			continue;
		}
		for (temp2 = pHead; temp2 != NULL&&temp2->pNext != p2; temp2 = temp2->pNext)	//寻找p2前的节点的指针
		{
			continue;
		}
		if (temp1 == NULL&&temp2!=NULL)
		{
			if (p1 == pHead)		//p1是头结点
			{
				StuNode *temp = p2->pNext;		//备份
				pHead = p2;

				if (p1->pNext == p2)		//相邻
				{
					p2->pNext = p1;
				}
				else																//不相邻
				{
					p2->pNext = p1->pNext;
					temp2->pNext = p1;
				}
				p1->pNext = temp;
			}
		}
		else if (temp2 == NULL&&temp1!=NULL)
		{
			if (p2 == pHead)		//p2是头结点
			{
				StuNode *temp = p1->pNext;		//备份
				pHead = p1;

				if (p1->pNext == p2)		//相邻
				{
					p1->pNext = p2;
				}
				else									//不相邻
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
			cout << "学生列表为空！" << endl;
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
			cout << "请输入学生名字：" << endl;
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
		cout << "请输入学号：" << endl;
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
			cout << "subject参数为空！" << endl;
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
		infile.open("D:\\全班成绩.txt");	//尝试打开
		if (infile.good() == false)
		{
			cout << "文件不存在，操作取消！" << endl;
			system("pause");
			return;
		}
	}
	void ShowMarkAnalyze()
	{
		cout << "全班成绩单:" << endl;
		stulist.ShowAllMark();
		cout << "班级平均分情况：" << endl;
		cout << "语文：" << stulist.getClassChineseAverage() << "\t"
			<< "数学：" << stulist.getClassMathAverage() << "\t"
			<< "英语：" << stulist.getClassEnglishAverage() << endl;
		cout << "班级及格率：" << endl;
		cout << "语文：" << stulist.getClassChinesePassRate() * 100 << "%\t"
			<< "数学：" << stulist.getClassMathPassRate() * 100 << "%\t"
			<< "英语：" << stulist.getClassEnglishPassRate() * 100 << "%\t" << endl;
	}
	virtual void ShowInf()const
	{
		People::ShowInf();
		cout << "\t授课：";
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
		cout << "请输入教师名字：" << endl;
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
		cout << "删除成功！" << endl;
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
	TeaNode * SearchName(char * name)
	{
		if (name == NULL)
		{
			cout << "请输入学生名字：" << endl;
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
		cout << "学生列表：" << endl;
		stulist.ShowAll();
		cout << endl;
		cout << "教师列表：" << endl;
		tealist.ShowAll();
		cout << endl;
		system("pause");
	}
}admin;		//管理员账户

void menu(logintype state);					//显示菜单函数
void login();					//登陆函数
void SortWithID(StuList & stulist);
void SortWithMark(StuList & stulist);
void SetStuMark(char * StuName = NULL);
void loadfile();				//载入文件函数
void SaveAllMark();		//导出学生成绩单函数

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
		cout << "请登陆系统" << endl;
		break;
	case Stu:
		cout << "功能菜单：" << endl;
		cout << "a.查询自己的成绩\t\t"<< "b.查询全班成绩\t\t" << endl
			<< "c.导出成绩\t\t\t"<< "d.修改密码\t\t" << endl
			<< "q.退出系统" << endl;
		break;
	case Tea:
		cout << "功能菜单：" << endl;
		cout << "a.显示全班名单\t"<<"b.录入学生成绩"<< endl
			<<"c.查询全班成绩\t\t" << "d.成绩分析\t\t\t"<< endl
			<<"e.添加学生\t\t" << "f.删除学生\t\t\t"<<endl
			<<"g.导出全班成绩\t\t" << "h.修改密码\t\t" << endl
			<< "q.退出系统" << endl;
		break;
	case Adm:
		cout << "功能菜单：" << endl;
		cout <<"a.显示用户列表\t"<<"b.添加学生\t\t"<<endl
			<<"c.删除学生\t\t"<< "d.添加教师\t\t" << endl
			<<"e.删除教师\t\t" << "f.修改密码\t\t"<<endl
			<< "q.退出系统" << endl;
		break;
	default:
		cout << "type参数错误！" << endl;
	}
}

void login()
{
	char name[30];
	char password[30];
	if (stulist.isempty() && tealist.isempty())
	{
		cout << "老师列表和学生列表都为空，请以管理员账户登陆。" << endl;
	}
	for (int i = 2; i >= 0; i--)
	{
		cout << "请输入账户名：" << endl;
		cin.getline(name, 30);
		cout << "请输入密码：" << endl;
		cin.getline(password, 30);
		StuNode *pStu = stulist.SearchName(name);
		TeaNode *pTea = tealist.SearchName(name);
		if (pStu)
		{
			if (pStu->stu.verify(password))
			{
				cout << "登陆成功：" << endl;
				cout << "当前账户：" << pStu->stu.getName() << "(学生)" << endl;
				state = Stu;
				user = &pStu->stu;
				return;
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
				state = Tea;
				user = &pTea->tea;
				return;
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
				state = Adm;
				user = &admin;
				return;
			}
			else
			{
				cout << "账户或密码错误！";
				cout << "剩余" << i << "次机会" << endl;
			}
		}
	}
	cout << "错误次数过多，登录失败！" << endl;
	state=Nologin;
}
 
void SortWithID(StuList & stulist)
{
	/*选择排序法*/
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
			p1 = stulist.Swap(p1, min);	/*链表元素交换后，要重新确定当前确定好的小的元素*/
		}
	}
}

void SortWithMark(StuList & stulist)
{
	/*选择排序法*/
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
			p1 = stulist.Swap(p1, min,true);	/*链表元素交换后，要重新确定当前确定好的大的元素*/
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
		cout << "根据学号从小到大录入" << endl;
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
		cout << "文件不存在，操作取消！" << endl;
		system("pause");
		return;
	}
	/*读取个数*/
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
	/*开始计数*/
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
	/*结束计数*/
	//前2*sizeof(int)个字节存放个数
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
	outfile.open("D:\\全班成绩.txt");
	if (outfile.good() == false)
	{
		cout << "未知错误，保存失败" << endl;
		system("pause");
		return;
	}
	outfile << "学号\t" << "姓名\t" << "语文\t" << "数学\t" << "英语\t"<< "总分\t" << endl;
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
	cout << "载入文件..." << endl;
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
		cout << "请选择操作：" << endl;
		cin >> choice;
		while (cin.get() != '\n')
		{
			continue;
		}
		if (state == Stu)
		{
			switch (choice)
			{
			case'a':cout << "查询自己的成绩" << endl;
				((Student *)user)->ShowMark();
				system("pause");
				break;
			case'b':cout << "查询全班成绩" << endl;
				stulist.ShowAllMark();
				system("pause");
				break;
			case'c':cout << "导出成绩" << endl;
				SortWithMark(stulist);
				((Student*)user)->SaveMark();
				cout << "导出成功！" << endl;
				system("pause");
				break;
			case'd':cout << "修改密码" << endl;
				user->resetpassword();
				cout << "密码修改成功！" << endl;
				system("pause");
				break;
			case'q':cout << "退出系统" << endl;
				savefile();
				system("pause");
				break;
			default:
				cout << "非法输入！" << endl;
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
			case'b':cout << "录入成绩" << endl;
				SetStuMark();
				system("pause");
				break;
			case'c':cout << "查询全班成绩" << endl;
				stulist.ShowAllMark();
				system("pause");
				break;
			case'd':cout << "成绩分析" << endl;
				((Teacher*)user)->ShowMarkAnalyze();
				system("pause");
				break;
			case'e':
				cout << "添加学生" << endl;
				stulist.add();
				system("pause");
				break;
			case'f':cout << "删除学生" << endl;
				cout << "a.通过名字查找学生\t\tb.通过学号查找学生" << endl;
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
					cout << "非法输入！" << endl;
				break;
			case'g':cout << "导出全班成绩" << endl;
				SortWithMark(stulist);
				SaveAllMark();
				system("pause");
				break;
			case'h':cout << "修改密码" << endl;
				user->resetpassword();
				cout << "密码修改成功！" << endl;
				system("pause");
				break;
			case'q':cout << "退出系统" << endl;
				savefile();
				system("pause");
				break;
			default:
				cout << "非法输入！" << endl;
				system("pause");
			}
		}
		else if (state == Adm)
		{
			switch (choice)
			{
			case'a':cout << "显示用户列表" << endl;
				SortWithID(stulist);
				admin.ShowAll();
				break;
			case'b':cout << "添加学生" << endl;
				stulist.add();
				break;
			case'c':cout << "删除学生" << endl;
				cout << "a.通过名字查找学生\t\tb.通过学号查找学生" << endl;
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
					cout << "非法输入！" << endl;
				break;
			case'd':cout << "添加教师" << endl;
				tealist.add();
				break;
			case'e':cout << "删除教师" << endl;
				tealist.DelFromName();
				break;
			case'f':cout << "修改密码" << endl;
				user->resetpassword();
				cout << "密码修改成功！" << endl;
				system("pause");
				break;
			case'q':cout << "退出系统" << endl;
				savefile();
				system("pause");
				break;
			default:
				cout << "非法输入！" << endl;
				system("pause");
			}
		}
		else
		{
			cout << "未登录" << endl;
		}
	} while (choice != 'q');
	return 0;
}