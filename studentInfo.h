#pragma once
#include<string>
using namespace std;
class student {
	public:
		student(const int Grade = -1) {};
		
		~student() {}
		char* getName() {
			return name;
		}
		char* getTelephone() {
			return telephone;
		}
		char* getStudentId() {
			return studentID;
		}
		char* getBirthDate() {
			return birthDate;
		}
		char* getBirthPlace() {
			return birthPlace;
		}
		char* getGender() {
			return gender;
		}
		int& getGrade() {
			return grade;
		}

		void setName(char *x_name) {
			strcpy(name, x_name);
		}
		void setTelephone(char* x_telephone) {
			strcpy(telephone, x_telephone);
			//telephone = x_telephone;
		}
		void setStudentId(char* x_studentID) {
			strcpy(studentID, x_studentID);
			//studentID = x_studentID;
		}
		void setBirthDate(char* x_birthDate) {
			strcpy(birthDate , x_birthDate);
		}
		void setBirthPlace(char* x_birthPlace) {
			strcpy(birthPlace , x_birthPlace);
		}
		void setGender(char* x_Gender) {
			strcpy(gender , x_Gender);
		}
		void setGrade(int x_grade) {
			grade = x_grade;
		}
		friend bool operator<(const student& s1, const student& s2);
		friend bool operator>(const student& s1, const student& s2);
		friend bool operator<=(const student& s1, const student& s2);
		friend bool operator>=(const student& s1, const student& s2);
		friend bool operator==(const student& s1, const student& s2);
		friend bool operator!=(const student& s1, const student& s2);
		//int operator=(const student& s1);
		const student& operator=(const student& s1);
		const student& operator=(int s);
		
	private:
		char name[100];
		char telephone[12];
		char studentID[20];
		char birthDate[20];
		char birthPlace[100];
		char gender[2];
		int grade;
};

const student& student::operator=(const student& s) {
	if (this != &s) {
		strcpy(this->birthDate, s.birthDate);
		strcpy(this->birthPlace, s.birthPlace);
		strcpy(this->gender, s.gender);
		//strcpy(this->grade, s.birthDate);
		strcpy(this->name, s.name);
		strcpy(this->studentID, s.studentID);
		strcpy(this->telephone, s.telephone);
		this->grade = s.grade;
	}
	return *this;
}

const student& student::operator=(const int s) {
	this->grade = s;
	return *this;
}

bool operator<(const student& s1, const student& s2) {
	return s1.grade < s2.grade;
}
bool operator>(const student& s1, const student& s2) {
	return s1.grade>s2.grade;
}
bool operator<=(const student& s1, const student& s2) {
	return s1.grade <= s2.grade;
}
bool operator>=(const student& s1, const student& s2) {
	return s1.grade >= s2.grade;
}
bool operator==(const student& s1, const student& s2) {
	return s1.grade == s2.grade;
}
bool operator!=(const student& s1, const student& s2) {
	return s1.grade != s2.grade;
}


ostream& operator<<(ostream& out, student& x) {//<<运算符重载,<<输出成绩

	out <<x.getGrade();
	//out << endl;
	return out;
}
