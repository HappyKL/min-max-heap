#include"min_max_heap.h"
#include"studentInfo.h"
#include<string.h>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

vector<student> students;
min_max_heap<int> student_h(10);
int ArrayHeap[100];////////////////////////�޴�ӵ㣬�����ʹ��initial��ʼ�����������������������һ�£����Կ�initial�ڲ������������Բ��ܽ�������ʹ��
int initSize = 0;//��ʼ����ʱ�����鼰Ԫ����

int flag_search;
char choose;
min_max_heap<int> h(10);

int Array[100];

int a;
char c;

void initial(); //����ѧ����Ϣ
void menu();//�˵���ʾ
void studentInfoQuery();//ѧ����Ϣ��ѯ
void input();//����ģ��

void initial() {//����ѧ����Ϣ
	ifstream file("ѧ����Ϣ.txt");

	if (file.fail()) {
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	else {
		char s[101];
		file.getline(s, 100);
		student student1;
		while (file >> student1.getStudentId() >> student1.getName() >> student1.getGender() >> student1.getBirthPlace() >> student1.getBirthDate() >> student1.getTelephone() >> student1.getGrade()) {
			//ע�⣺����ʹ��file.eof()��Ϊ�ж��������������һ�����ݵ��´��󣬵���ȡ�ļ����ַ���ʱ���ж�����ʹ��>>���������ȡ�ַ��Ϳ���ʹ��file.peek()!=EOF��Ϊ�ж��������мǲ���ʹ��file.eof()��
			//student_h.insert(student1.getGrade());
			ArrayHeap[++initSize] = student1.getGrade();
			students.push_back(student1);
		}
		student_h.initialize(ArrayHeap, initSize);
	}
}

void menu() {//�˵���ʾ
	printf("****************************************************************************************\n");
	printf("�˵� С��������ʵ��˫�����ȶ���\n");
	printf("** u ����С��������\n");
	printf("** i ����Ԫ��\n");
	printf("** b ɾ�����ֵ\n");
	printf("** s ɾ����Сֵ\n");
	printf("** g �õ����ֵ\n");
	printf("** h �õ���Сֵ\n");
	printf("** r ���ݳɼ���ѯѧ����Ϣ\n");
	printf("** q �˳�\n");
	printf("****************************************************************************************\n");
}

void studentInfoQuery() {
	flag_search = 1;
	while (flag_search) {

		printf("*************************************\n");
		printf("** ѡ���ѯ��ʽ\n");
		printf("** 1 ��ѯ��߳ɼ�ѧ����Ϣ\n");
		printf("** 2 ��ѯ��ͳɼ�ѧ����Ϣ\n");
		printf("** 3 ���ݾ���ɼ���ѧ����Ϣ���в�ѯ\n");
		printf("** 4 ��ѯǰ����ѧ����Ϣ\n");
		printf("** 5 ��ѯ����ѧ����Ϣ\n");
		printf("** 6 ��ѯ��������ѧ����Ϣ\n");
		printf("** 7 ��ѯ��������ѧ����Ϣ\n");
		printf("** 0 �˳�\n");
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
			if (count == 0) printf("û�д˳ɼ���ͬѧ\n");
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
			if (count == 0) printf("û�д˳ɼ���ͬѧ\n");
			break;
		case 3:
			while (1) {
				printf("����ѧ���ɼ�(-1������ѯ):");
				scanf("%d", &a);
				if (a == -1) break;
				if (a < 0 || a>100) {
					printf("���벻����Ҫ��\n");
					break;
				}
				count = 0;
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() == a) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("û�д˳ɼ���ͬѧ\n");
			}
			break;
		case 4:
			while (1) {
				printf("��������(-1������ѯ):");
				scanf("%d", &a);
				if (a == -1) break;

				count = 0;
				flagPrint = false;//����ӡ����
				for (int i = 1; i <= a; i++) {
					Array[i] = student_h.popMax();
				}

				int desGrade = Array[a];
				for (int i = 1; i <= a; i++) {
					student_h.insert(Array[i]);//���ȥ
											   //printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() >= desGrade) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("û�д����ε�ͬѧ\n");
			}
			break;
		case 5:
			while (1) {
				printf("��������(-1������ѯ):");
				scanf("%d", &a);
				if (a == -1) break;
				count = 0;
				flagPrint = false;//����ӡ����
				for (int i = 1; i <= a; i++) {
					Array[i] = student_h.popMin();
					//printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				int desGrade = Array[a];
				for (int i = 1; i <= a; i++) {
					student_h.insert(Array[i]);//���ȥ
											   //printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() <= desGrade) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("û�д����ε�ͬѧ\n");
			}
			break;
		case 6:
			while (1) {
				printf("��������(-1������ѯ):");
				scanf("%d", &a);
				if (a == -1) break;
				count = 0;
				flagPrint = false;//����ӡ����
				for (int i = 1; i <= a; i++) {
					Array[i] = student_h.popMax();
					//printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				int desGrade = Array[a];
				for (int i = 1; i <= a; i++) {
					student_h.insert(Array[i]);//���ȥ
											   //printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() == desGrade) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("û�д����ε�ͬѧ\n");
			}
			break;

		case 7:
			while (1) {
				printf("��������(-1������ѯ):");
				scanf("%d", &a);
				if (a == -1) break;
				count = 0;
				flagPrint = false;//����ӡ����
				for (int i = 1; i <= a; i++) {
					Array[i] = student_h.popMin();
					//printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				int desGrade = Array[a];
				for (int i = 1; i <= a; i++) {
					student_h.insert(Array[i]);//���ȥ
											   //printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
				}
				for (int i = 0; i < students.size(); i++) {
					if (students.at(i).getGrade() == desGrade) {
						count++;
						printf("%s %s %s %s %s %s %d\n", students.at(i).getStudentId(), students.at(i).getName(), students.at(i).getGender(), students.at(i).getBirthDate(), students.at(i).getBirthPlace(), students.at(i).getTelephone(), students.at(i).getGrade());
					}
				}
				if (count == 0) printf("û�д����ε�ͬѧ\n");
			}
			break;
		case 0:
			flag_search = 0;
			break;
		default:
			printf("������������������\n");
			break;
		}

	}
}


void input() {//���룬����������ѡ�������Ӧ�����
	
	initSize = 0;//��ʼ������Ԫ�ظ���
	cin >> choose;
	
	try {
		
		switch (choose) {
		case 'u':
			printf("����С�������ѣ�\n");
			printf("������ؼ�ֵ:\n");
			getchar();
			while (1) {
				scanf("%d", &a);
				c = getchar();
				//h.insert(a);
				Array[++initSize] = a;//��ʼ������
				if (c == '\n') break;
			}
			h.initialize(Array, initSize);
			cout << "�������£�" << endl << h << endl;
			//printf("��f�ص����˵�\n");
			break;
		case 'i':
			printf("���룺");
			scanf("%d", &a);
			h.insert(a);
			break;
		case 'b':
			a = h.popMax();
			printf("ɾ��Ԫ��Ϊ%d\n", a);
			break;
		case 's':
			a = h.popMin();
			printf("ɾ��Ԫ��Ϊ%d\n", a);
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
			printf("������������������\n");
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