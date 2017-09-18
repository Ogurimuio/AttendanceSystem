#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<strstream>
#include<string>
#include<conio.h>
using namespace std;
class Student			//学生类
{
private:
	int work_number;	//工号
	//string number;
	char number[15];	//学号
	string name;
	int machine_number;	//机号
public:
	int get_work_number() { return work_number; }
	char* get_number() { return number; }
	//string get_number() { return number; }
	string get_name() { return name; }
	int get_machine_number() { return machine_number; }
	void display() {
		cout << work_number << '\t' << number << '\t' << name << '\t' << machine_number << '\t';
	}
	void set_students(int work, char* num,string name1, int machine) {
		work_number = work;
		for (int i = 0; i < 14; i++) {
			number[i] = num[i];
		}
		number[14] = '\0';
		//number = num;
		name = name1;
		machine_number = machine;
	}
	friend istream& operator >> (istream& in, Student & stu);
};
istream& operator >> (istream& in, Student & stu)
{
	in >> stu.work_number;
	for (int i = 0; i < 14; i++)
		in >> stu.number[i];
	stu.number[14] = '\0';
	//in >> stu.number;
	in >> stu.name;
	in >> stu.machine_number;
	return in;
}
vector<Student> student;
class Checkin :public Student		//考勤类
{
private:
	int num, year, month, day, hour, min, s;
	int one, two, three, four;
public:
	int get_num() { return num; }
	friend istream& operator >> (istream& in, Checkin & check);
	void set_students(int work, char* num, string name1, int machine) {
		Student::set_students(work, num, name1, machine);
	}
	void display() {
		Student::display();
		cout << year << '-' << month << '-' << day << '\t' << hour << ':' << min << ':' << s << endl;
	}
	int get_year() { return year; }
	int get_month() { return month; }
	int get_day() { return day; }
	int get_hour() { return hour; }
	int get_min() { return min; }
	int get_s() { return s; }
};
istream& operator >> (istream& in, Checkin & check)
{
	char a;
	in >> check.num >> check.year >>a;
	//in >> a;
	in >> check.month >> a;
	//in >> a;
	in >> check.day >> check.hour >> a;
	//in >> a;
	in >> check.min >> a;
	//in >> a;
	in >> check.s >> check.one >> check.two >> check.three >> check.four;
	return in;
}
vector<Checkin> check;
void student_insert()		//录入学生信息
{
	fstream f2;
	Student stu;
	string str;
	string wordname;
	cout << "请输入学生信息文件名（如C://students.txt）:";
	cin >> wordname;
	f2.open(wordname, ios::in);
	if (!f2) {
		cerr << "打开学生信息文件失败！";
		exit(-1);
	}
	cout << "正在录入中...请稍候" << endl << endl;
	getline(f2, str);
	while (getline(f2, str)) {
		istrstream str_in(str.c_str(), str.size());
		str_in >> stu;
		student.push_back(stu);
	}
	f2.close();
	cout << "考勤信息录入完毕！" << endl;
}	
void check_insert()		//录入出勤信息
{
	fstream f1;
	Checkin temp;
	string str;
	string wordname;
	cout << "请输入考勤信息文件名（如C://kaoqin.dat）:";
	cin >> wordname;
	f1.open(wordname, ios::in);
	if (!f1) {
		cout << "打开考勤信息文件失败！";
		exit(-1);
	}
	cout << "正在录入中...请稍候" << endl << endl;
	while (getline(f1, str)) {
		istrstream str_in(str.c_str(), str.size());
		str_in >> temp;
		for (vector<Student>::iterator it = student.begin(); it != student.end(); it++) {
			if (it->get_work_number()==temp.get_num())	//用工号来连接学生和考勤信息
			{
				temp.set_students(it->get_work_number(), it->get_number(), it->get_name(), it->get_machine_number());
				check.push_back(temp);
			}
		}
	}
	f1.close();
	cout << "考勤信息录入完毕！" << endl;
}
void whole_class()		//统计出勤情况
{
	const vector<Checkin>::iterator it1 = check.begin();
	const vector<Checkin>::iterator it2 = check.end();
	int early = 0, late = 0;
	for (vector<Checkin>::iterator it = it1; it != it2; it++) {
		//it->display();
		if ((it->get_hour() == 11) && (it->get_min() > 10) && (it->get_min() < 40))
			early++;
		if ((it->get_hour() == 8) && (it->get_min() > 0) && (it->get_min() < 30))
			late++;
	}
	cout << "全班共有早退:" << early << "次！" << endl;
	cout << "全班共有迟到:" << late << "次！" << endl;
}
void whole_student_display()		//显示学生信息
{
	const vector<Student>::iterator it1 = student.begin();
	const vector<Student>::iterator it2 = student.end();
	for (vector<Student>::iterator it = it1; it != it2; it++)
	{
		it->display();
	}
	cout << "学生信息显示完毕！" << endl;
}
void whole_check_display()		//显示出勤信息
{
	const vector<Checkin>::iterator it1 = check.begin();
	const vector<Checkin>::iterator it2 = check.end();
	for (vector<Checkin>::iterator it = it1; it != it2; it++)
	{
		it->display();
	}
	cout << "考勤信息显示完毕！" << endl;
}
void search_number(char* num)
{
	const vector<Checkin>::iterator it1 = check.begin();
	const vector<Checkin>::iterator it2 = check.end();
	int early = 0, late = 0, software = 0, aa[30], unattend = 0;
	for (int i = 0; i < 30; i++)
		aa[i] = 0;
	for (vector<Checkin>::iterator it = it1; it != it2; it++) {
		if /*(it->get_number()==num)*/(strcmp(it->get_number(), num) == 0) {
			it->display();
			software++;
			aa[it->get_day() - 1]++;
			if ((it->get_hour() == 11) && (it->get_min() > 10) && (it->get_min() < 40))
				early++;
			if ((it->get_hour() == 8) && (it->get_min() > 0) && (it->get_min() < 30))
				late++;
		}
	}
	for (int i = 0; i < 30; i++) {
		if (aa[i] == 0 || aa[i] == 1)
			unattend++;
	}
	if (software == 0)
		cout << "找不到该学号的同学！" << endl;
	else {
		cout << "学号为" << num << "的同学共有早退:" << early << "次！" << endl;
		cout << "学号为" << num << "的同学共有迟到:" << late << "次！" << endl;
		cout << "学号为" << num << "的同学共有旷课:" << unattend << "次！" << endl;
	}
}
void search_time(int y, int m, int d)
{
	const vector<Checkin>::iterator it1 = check.begin();
	const vector<Checkin>::iterator it2 = check.end();
	int early = 0, late = 0, a[61], unattend = 0;
	for (int i = 0; i < 61; i++)
		a[i] = 0;
	for (vector<Checkin>::iterator it = it1; it != it2; it++) {
		if ((it->get_year() == y) && (it->get_month() == m) && (it->get_day() == d)) {
			it->display();
			a[it->get_work_number() - 401]++;
			if ((it->get_hour() == 11) && (it->get_min() > 10) && (it->get_min() < 40))
				early++;
			if ((it->get_hour() == 8) && (it->get_min() > 0) && (it->get_min() < 30))
				late++;
		}
	}
	for (int i = 0; i < 61; i++) {
		if (a[i] == 0 || a[i] == 1)
			unattend++;
	}
	cout << y << "年" << m << "月" << d << "日共发生早退:" << early << "次！" << endl;
	cout << y << "年" << m << "月" << d << "日共发生迟到:" << late << "次！" << endl;
	cout << y << "年" << m << "月" << d << "日共发生旷课:" << unattend << "次！" << endl;
}
void search_work_number(int work)
{
	const vector<Checkin>::iterator it1 = check.begin();
	const vector<Checkin>::iterator it2 = check.end();
	int early = 0, late = 0, software = 0, aa[30], unattend = 0;
	for (int i = 0; i < 30; i++)
		aa[i] = 0;
	for (vector<Checkin>::iterator it = it1; it != it2; it++) {
		if (it->get_work_number() == work) {
			it->display();
			software++;
			aa[it->get_day() - 1]++;
			if ((it->get_hour() == 11) && (it->get_min() > 10) && (it->get_min() < 40))
				early++;
			if ((it->get_hour() == 8) && (it->get_min() > 0) && (it->get_min() < 30))
				late++;
		}
	}
	for (int i = 0; i < 30; i++) {
		if (aa[i] == 0 || aa[i] == 1)
			unattend++;
	}
	if (software == 0)
		cout << "没有该工号的同学！" << endl;
	else {
		cout << "工号为" << work << "的同学共有早退:" << early << "次！" << endl;
		cout << "工号为" << work << "的同学共有迟到:" << late << "次！" << endl;
		cout << "工号为" << work << "的同学共有旷课:" << unattend << "次！" << endl;
	}
}
void search_name(string name)
{
	const vector<Checkin>::iterator it1 = check.begin();
	const vector<Checkin>::iterator it2 = check.end();
	int early = 0, late = 0, software = 0, aa[30], unattend = 0;
	for (int i = 0; i < 30; i++)
		aa[i] = 0;
	for (vector<Checkin>::iterator it = it1; it != it2; it++) {
		if (it->get_name() == name) {
			it->display();
			software++;
			aa[it->get_day() - 1]++;
			if ((it->get_hour() == 11) && (it->get_min() > 10) && (it->get_min() < 40))
				early++;
			if ((it->get_hour() == 8) && (it->get_min() > 0) && (it->get_min() < 30))
				late++;
		}
	}
	for (int i = 0; i < 30; i++) {
		if (aa[i] == 0 || aa[i] == 1)
			unattend++;
	}
	if (software == 0)
		cout << "没有找到该姓名的同学！请输入正确姓名！" << endl;
	else {
		cout << name << "共有早退:" << early << "次！" << endl;
		cout << name << "共有迟到:" << late << "次！" << endl;
		cout << name << "共有迟到:" << unattend << "次！" << endl;
	}
}
void main()
{
	int choose1, choose2,choose3;
	char num[15];
	//student_insert();
	//check_insert();
	while (1) {
		cout << "*******************************************************************************" << endl;
		cout << "*                                                                             *" << endl;
		cout << "*                      欢迎进入学生信息录入及考勤系统                         *" << endl;
		cout << "*                                                                             *" << endl;
		cout << "*******************************************************************************" << endl;
		cout << "                     操作指南（录入学生和考勤信息后才能查询）" << endl;
		cout << "                                [0]退出系统" << endl;
		cout << "                                [1]录入学生信息" << endl;
		cout << "                                [2]录入考勤信息" << endl;
		cout << "                                [3]查询考勤情况" << endl;
		cout << "                                请输入选择：";
		cin >> choose1;
		if (choose1 == 0)   //退出
			return;
		else if (choose1 == 1)
		{
			system("CLS");
			student_insert();
			cout << "[0]退出系统" << endl;
			cout << "[1]返回主菜单" << endl;
			cout << "[2]显示学生信息" << endl;
			cout << "请输入选择：";
			cin >> choose3;
			if (choose3 == 0)
				return;
			else if (choose3 == 1) {
				system("CLS");
				continue;
			}
			else if (choose3 == 2)
			{
				whole_student_display();
			}
		}
		else if (choose1 == 2) {         //录入考勤
			system("CLS");
			check_insert();
			whole_class();
			cout << "[0]退出系统" << endl;
			cout << "[1]返回主菜单" << endl;
			cout << "[2]显示考勤记录" << endl;
			cout << "请输入选择：";
			cin >> choose3;
			if (choose3 == 0)
				return;
			else if (choose3 == 1) {
				system("CLS");
				continue;
			}
			else if (choose3 == 2)
			{
				whole_check_display();
			}
			else cout << "请输入正确数字！" << endl;
		}

		else if (choose1 == 3) {        //考勤查询
			system("CLS");
			cout << "*******************************************************************************" << endl;
			cout << "                                查询考勤信息" << endl;
			cout << "*******************************************************************************" << endl;
			cout << "                       考勤记录处理系统之考勤情况查询" << endl;
			cout << "                                [0]退出系统" << endl;
			cout << "                                [1]返回主菜单" << endl;
			cout << "                                [2]按学号查询" << endl;
			cout << "                                [3]按工号查询" << endl;
			cout << "                                [4]按姓名查询" << endl;
			cout << "                                [5]按时间查询" << endl;
			cout << "                                请输入选择：";
			cin >> choose2;
			if (choose2 == 0)
				return;
			else if (choose2 == 1) 
			{
				system("CLS");
				continue;
			}
			else if (choose2 == 2) 
			{
				cout << "请输入学号:";
				cin >> num;
				search_number(num);
				cout << "按任意键返回主菜单";
				_getch();
				system("CLS");
			}
			else if (choose2 == 3) 
			{
				cout << "请输入工号:";
				int choose_work;
				cin >> choose_work;
				search_work_number(choose_work);
				cout << "按任意键返回主菜单";
				_getch();
				system("CLS");
			}
			else if (choose2 == 4) 
			{
				cout << "请输入姓名:";
				string choose_name;
				cin >> choose_name;
				search_name(choose_name);
				cout << "按任意键返回主菜单";
				_getch();
				system("CLS");
			}
			else if (choose2 == 5) 
			{
				cout << "请输入时间（精确到日,中间空格隔开）:";
				int y, m, d;
				cin >> y >> m >> d;
				search_time(y, m, d);
				cout << "按任意键返回主菜单";
				_getch();
				system("CLS");
			}
			else cout << "请输入正确数字！" << endl;
		}
		else cout << "请输入正确数字！" << endl;
	}
	system("pause");
}