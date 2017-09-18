#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<strstream>
#include<string>
#include<conio.h>
using namespace std;
class Student			//ѧ����
{
private:
	int work_number;	//����
	//string number;
	char number[15];	//ѧ��
	string name;
	int machine_number;	//����
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
class Checkin :public Student		//������
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
void student_insert()		//¼��ѧ����Ϣ
{
	fstream f2;
	Student stu;
	string str;
	string wordname;
	cout << "������ѧ����Ϣ�ļ�������C://students.txt��:";
	cin >> wordname;
	f2.open(wordname, ios::in);
	if (!f2) {
		cerr << "��ѧ����Ϣ�ļ�ʧ�ܣ�";
		exit(-1);
	}
	cout << "����¼����...���Ժ�" << endl << endl;
	getline(f2, str);
	while (getline(f2, str)) {
		istrstream str_in(str.c_str(), str.size());
		str_in >> stu;
		student.push_back(stu);
	}
	f2.close();
	cout << "������Ϣ¼����ϣ�" << endl;
}	
void check_insert()		//¼�������Ϣ
{
	fstream f1;
	Checkin temp;
	string str;
	string wordname;
	cout << "�����뿼����Ϣ�ļ�������C://kaoqin.dat��:";
	cin >> wordname;
	f1.open(wordname, ios::in);
	if (!f1) {
		cout << "�򿪿�����Ϣ�ļ�ʧ�ܣ�";
		exit(-1);
	}
	cout << "����¼����...���Ժ�" << endl << endl;
	while (getline(f1, str)) {
		istrstream str_in(str.c_str(), str.size());
		str_in >> temp;
		for (vector<Student>::iterator it = student.begin(); it != student.end(); it++) {
			if (it->get_work_number()==temp.get_num())	//�ù���������ѧ���Ϳ�����Ϣ
			{
				temp.set_students(it->get_work_number(), it->get_number(), it->get_name(), it->get_machine_number());
				check.push_back(temp);
			}
		}
	}
	f1.close();
	cout << "������Ϣ¼����ϣ�" << endl;
}
void whole_class()		//ͳ�Ƴ������
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
	cout << "ȫ�๲������:" << early << "�Σ�" << endl;
	cout << "ȫ�๲�гٵ�:" << late << "�Σ�" << endl;
}
void whole_student_display()		//��ʾѧ����Ϣ
{
	const vector<Student>::iterator it1 = student.begin();
	const vector<Student>::iterator it2 = student.end();
	for (vector<Student>::iterator it = it1; it != it2; it++)
	{
		it->display();
	}
	cout << "ѧ����Ϣ��ʾ��ϣ�" << endl;
}
void whole_check_display()		//��ʾ������Ϣ
{
	const vector<Checkin>::iterator it1 = check.begin();
	const vector<Checkin>::iterator it2 = check.end();
	for (vector<Checkin>::iterator it = it1; it != it2; it++)
	{
		it->display();
	}
	cout << "������Ϣ��ʾ��ϣ�" << endl;
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
		cout << "�Ҳ�����ѧ�ŵ�ͬѧ��" << endl;
	else {
		cout << "ѧ��Ϊ" << num << "��ͬѧ��������:" << early << "�Σ�" << endl;
		cout << "ѧ��Ϊ" << num << "��ͬѧ���гٵ�:" << late << "�Σ�" << endl;
		cout << "ѧ��Ϊ" << num << "��ͬѧ���п���:" << unattend << "�Σ�" << endl;
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
	cout << y << "��" << m << "��" << d << "�չ���������:" << early << "�Σ�" << endl;
	cout << y << "��" << m << "��" << d << "�չ������ٵ�:" << late << "�Σ�" << endl;
	cout << y << "��" << m << "��" << d << "�չ���������:" << unattend << "�Σ�" << endl;
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
		cout << "û�иù��ŵ�ͬѧ��" << endl;
	else {
		cout << "����Ϊ" << work << "��ͬѧ��������:" << early << "�Σ�" << endl;
		cout << "����Ϊ" << work << "��ͬѧ���гٵ�:" << late << "�Σ�" << endl;
		cout << "����Ϊ" << work << "��ͬѧ���п���:" << unattend << "�Σ�" << endl;
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
		cout << "û���ҵ���������ͬѧ����������ȷ������" << endl;
	else {
		cout << name << "��������:" << early << "�Σ�" << endl;
		cout << name << "���гٵ�:" << late << "�Σ�" << endl;
		cout << name << "���гٵ�:" << unattend << "�Σ�" << endl;
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
		cout << "*                      ��ӭ����ѧ����Ϣ¼�뼰����ϵͳ                         *" << endl;
		cout << "*                                                                             *" << endl;
		cout << "*******************************************************************************" << endl;
		cout << "                     ����ָ�ϣ�¼��ѧ���Ϳ�����Ϣ����ܲ�ѯ��" << endl;
		cout << "                                [0]�˳�ϵͳ" << endl;
		cout << "                                [1]¼��ѧ����Ϣ" << endl;
		cout << "                                [2]¼�뿼����Ϣ" << endl;
		cout << "                                [3]��ѯ�������" << endl;
		cout << "                                ������ѡ��";
		cin >> choose1;
		if (choose1 == 0)   //�˳�
			return;
		else if (choose1 == 1)
		{
			system("CLS");
			student_insert();
			cout << "[0]�˳�ϵͳ" << endl;
			cout << "[1]�������˵�" << endl;
			cout << "[2]��ʾѧ����Ϣ" << endl;
			cout << "������ѡ��";
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
		else if (choose1 == 2) {         //¼�뿼��
			system("CLS");
			check_insert();
			whole_class();
			cout << "[0]�˳�ϵͳ" << endl;
			cout << "[1]�������˵�" << endl;
			cout << "[2]��ʾ���ڼ�¼" << endl;
			cout << "������ѡ��";
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
			else cout << "��������ȷ���֣�" << endl;
		}

		else if (choose1 == 3) {        //���ڲ�ѯ
			system("CLS");
			cout << "*******************************************************************************" << endl;
			cout << "                                ��ѯ������Ϣ" << endl;
			cout << "*******************************************************************************" << endl;
			cout << "                       ���ڼ�¼����ϵͳ֮���������ѯ" << endl;
			cout << "                                [0]�˳�ϵͳ" << endl;
			cout << "                                [1]�������˵�" << endl;
			cout << "                                [2]��ѧ�Ų�ѯ" << endl;
			cout << "                                [3]�����Ų�ѯ" << endl;
			cout << "                                [4]��������ѯ" << endl;
			cout << "                                [5]��ʱ���ѯ" << endl;
			cout << "                                ������ѡ��";
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
				cout << "������ѧ��:";
				cin >> num;
				search_number(num);
				cout << "��������������˵�";
				_getch();
				system("CLS");
			}
			else if (choose2 == 3) 
			{
				cout << "�����빤��:";
				int choose_work;
				cin >> choose_work;
				search_work_number(choose_work);
				cout << "��������������˵�";
				_getch();
				system("CLS");
			}
			else if (choose2 == 4) 
			{
				cout << "����������:";
				string choose_name;
				cin >> choose_name;
				search_name(choose_name);
				cout << "��������������˵�";
				_getch();
				system("CLS");
			}
			else if (choose2 == 5) 
			{
				cout << "������ʱ�䣨��ȷ����,�м�ո������:";
				int y, m, d;
				cin >> y >> m >> d;
				search_time(y, m, d);
				cout << "��������������˵�";
				_getch();
				system("CLS");
			}
			else cout << "��������ȷ���֣�" << endl;
		}
		else cout << "��������ȷ���֣�" << endl;
	}
	system("pause");
}