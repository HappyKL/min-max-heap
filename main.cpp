#include"min_max_heap.h"
#include"studentInfo.h"
#include<string.h>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

vector<student> students;
min_max_heap<int> student_h(10);
int ArrayHeap[100];////////////////////////巨大坑点，，如果使用initial初始化方法，该数组与堆中数组一致（可以看initial内部方法），所以不能进行随意使用
int initSize = 0;//初始化堆时的数组及元素数

int flag_search;
char choose;
min_max_heap<int> h(10);

int Array[100];

int a;
char c;

void initial(); //读入学生信息
void menu();//菜单显示
void studentInfoQuery();//学生信息查询
void input();//输入模块

void initial() {//读入学生信息
	ifstream file("学生信息.txt");

	if (file.fail()) {
		printf("文件打开失败！\n");
		return;
	}
	else {
		char s[101];
		file.getline(s, 100);
		student student1;
		while (file >> student1.getStudentId() >> student1.getName() >> student1.getGender() >> student1.getBirthPlace() >> student1.getBirthDate() >> student1.getTelephone() >> student1.getGrade()) {
			//注意：不能使用file.eof()作为判断条件，否则会多读一次数据导致错误，当读取文件非字符型时，判断条件使用>>运算符，读取字符型可以使用file.peek()!=EOF作为判断条件【切记不能使用file.eof()】
			//student_h.insert(student1.getGrade());
			ArrayHeap[++initSize] = student1.getGrade();
			students.push_back(student1);
		}
		student_h.initialize(ArrayHeap, initSize);
	}
}

void menu() {//菜单显示
	printf("****************************************************************************************\n");
	printf("菜单 小大根交替堆实现双端优先队列\n");
	printf("** u 建立小大根交替堆\n");
	printf("** i 插入元素\n");
	printf("** b 删除最大值\n");
	printf("** s 删除最小值\n");
	printf("** g 得到最大值\n");
	printf("** h 得到最小值\n");
	printf("** r 根据成绩查询学生信息\n");
	printf("** q 退出\n");
	printf("****************************************************************************************\n");
}

void studentInfoQuery() {
	flag_search = 1;
	while (flag_search) {

		printf("*************************************\n");
		printf("** 选择查询方式\n");
		printf("** 1 查询最高成绩学生信息\n");
		printf("** 2 查询最低成绩学生信息\n");
		printf("** 3 根据具体成绩对学生信息进行查询\n");
		printf("** 4 查询前几名学生信息\n");
		printf("** 5 查询后几名学生信息\n");
		printf("** 6 查询正数名次学生信息\n");
		printf("** 7 查询倒数名次学生信息\n");
		printf("** 0 退出\n");
		printf("*************************************\n");
		getchar();
		scanf("%d", &a);
		int count;
		int max;
		int min;
		switch (a) {
		case 1:
			max = student_h.getMax();
			count = 0;
			for (int i = 0; i < students.size(); i++) {
				if (students.at(i).getGrade() == max) {
					count++;
					printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
			}
			if (count == 0) printf("没有此成绩的同学\n");
			break;
		case 2:
			min = student_h.getMin();
			count = 0;
			for (int i = 0; i < students.size(); i++) {
				if (students.at(i).getGrade() == min) {
					count++;
					printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
			}
			if (count == 0) printf("没有此成绩的同学\n");
			break;
		case 3:
			while (1) {
				printf("给出学生成绩(-1结束查询):");
				scanf("%d", &a);
				if (a == -1) break;
				if (a < 0 || a>100) {
					printf("输入不符合要求\n");
					break;
				}
				count = 0;
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() == a) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("没有此成绩的同学\n");
			}
			break;
		case 4:
			while (1) {
				printf("输入名次(-1结束查询):");
				scanf("%d", &a);
				if (a == -1) break;

				count = 0;
				flagPrint = false;//不打印过程
				for (int i = 1; i <= a; i++) {
					Array[i] = student_h.popMax();
				}

				int desGrade = Array[a];
				for (int i = 1; i <= a; i++) {
					student_h.insert(Array[i]);//插回去
											   //printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() >= desGrade) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("没有此名次的同学\n");
			}
			break;
		case 5:
			while (1) {
				printf("输入名次(-1结束查询):");
				scanf("%d", &a);
				if (a == -1) break;
				count = 0;
				flagPrint = false;//不打印过程
				for (int i = 1; i <= a; i++) {
					Array[i] = student_h.popMin();
					//printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				int desGrade = Array[a];
				for (int i = 1; i <= a; i++) {
					student_h.insert(Array[i]);//插回去
											   //printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() <= desGrade) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("没有此名次的同学\n");
			}
			break;
		case 6:
			while (1) {
				printf("输入名次(-1结束查询):");
				scanf("%d", &a);
				if (a == -1) break;
				count = 0;
				flagPrint = false;//不打印过程
				for (int i = 1; i <= a; i++) {
					Array[i] = student_h.popMax();
					//printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				int desGrade = Array[a];
				for (int i = 1; i <= a; i++) {
					student_h.insert(Array[i]);//插回去
											   //printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() == desGrade) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("没有此名次的同学\n");
			}
			break;

		case 7:
			while (1) {
				printf("输入名次(-1结束查询):");
				scanf("%d", &a);
				if (a == -1) break;
				count = 0;
				flagPrint = false;//不打印过程
				for (int i = 1; i <= a; i++) {
					Array[i] = student_h.popMin();
					//printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				int desGrade = Array[a];
				for (int i = 1; i <= a; i++) {
					student_h.insert(Array[i]);//插回去
											   //printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() == desGrade) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("没有此名次的同学\n");
			}
			break;
		case 0:
			flag_search = 0;
			break;
		default:
			printf("输入有误，请重新输入\n");
			break;
		}

	}
}


void input() {//输入，并根据输入选项进行相应的输出
	
	initSize = 0;//初始化数组元素个数
	cin >> choose;
	
	try {
		
		switch (choose) {
		case 'u':
			printf("建立小大根交替堆：\n");
			printf("请输入关键值:\n");
			getchar();
			while (1) {
				scanf("%d", &a);
				c = getchar();
				//h.insert(a);
				Array[++initSize] = a;//初始化数组
				if (c == '\n') break;
			}
			h.initialize(Array, initSize);
			cout << "建堆如下：" << endl << h << endl;
			//printf("按f回到主菜单\n");
			break;
		case 'i':
			printf("插入：");
			scanf("%d", &a);
			h.insert(a);
			break;
		case 'b':
			a = h.popMax();
			printf("删除元素为%d\n", a);
			break;
		case 's':
			a = h.popMin();
			printf("删除元素为%d\n", a);
			break;
		case 'h':
			h.getMin();
			break;

		case 'g':
			h.getMax();
			break;
		case 'r':
			studentInfoQuery();
			
			break;
		case 'q':
			return;
		default:
			printf("输入有误，请重新输入\n");
			break;
		}
	}
	catch (string s) {
		cout << s << endl;
	}
	catch (char* s) {
		cout << s << endl;
	}
}

int main() {
	initial();
	while (1) {
		menu();
		input();
	}
	return 0;

}