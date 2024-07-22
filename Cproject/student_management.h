#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include<windows.h>

#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H
#define MAX_STUDENTS 30
#define CLUB_BUDGET_LIMIT 0.2  // ���Ƹ� ���� ���� ����
#define MAX_DAYS 5 //�ð�ǥ ����
#define MAX_PERIODS 6 //�ð�ǥ �ð�
#define MAX_CLASSES 3 //�ð�ǥ ��
#define numZones 3
#define MAX_CLEAN_ZONES 3
#define MAX_PARAGRAPHS 3
#define MAX_PARAGRAPH_LENGTH 200
typedef struct Quiz
{
	char Question[256];		//	������ ������ ���ڿ�
	int Answer;				//	������ ���� ���� ������ ����
	int IsUsed;				//	Ǯ���� �������� �ƴ����� ������ ����
}Quiz;

typedef struct { //����, ���� �Է� ���� ����ü
	char* question;
	char* answer;
} Problem;

typedef struct {
	char zoneName[20];
	int personnel;
} CleanZone;
typedef struct {
	char courses[MAX_CLASSES][MAX_DAYS][MAX_PERIODS][50]; // 5�� x 6������ ���Ǹ��� ����
} Timetable;
typedef struct {
	int year;
	int month;
	int day;
	int hour;
	int snum;
} MeetingSchedule;
typedef struct _Student {
	int snum; // �й�
	wchar_t sname[20]; //�̸�
	char adress; // �ּ�
	char callnumber[15]; // ��ȭ��ȣ
	char cleanadress[3]; // û�ұ���
	int birth; // �������
	int Kor; // ����
	int Eng; // ����
	int Math; // ����
	float Avg; // ���
	char vms[20]; // ����Ȱ��
	char dong[20]; // ���Ƹ�
	int clubBudget; // ���Ƹ� ����
	char scoreclass[20]; // ������
} Student;

void loadFromFile(int* count, Student* student); //���� �ҷ�����
int inputInt(int min, int max); //�Է½� �ּҰ� �ִ밪 �̿� ���� �Է½� ����ǵ���
int checkBirth(const char* birth); //������� ���� ����ó��
int checkcall(const char* callnumber); //��ȭ��ȣ ���� ����ó��
void addStudent(int* count, Student* student); //�л��߰�
void printAll(int count, Student* student); //�л� ���� ��ü ���
void printName(int count, Student* student, char name[20]); //�л� �̸� �Է¹޾� ���
void deleteStudent(int* count, Student* students); //�л� ���� ����
void deleteStudentBySnum(int* count, Student* students); //�л� �й����� ����
void deleteStudentBySname(int* count, Student* students); //�л� �̸����� ����
void modifyStudentInfo(Student* student); //�л� ���� ����
void modifyStudentBySnum(int* count, Student* students); //�л� ���� �й����� ã�� ����
void printStudentInfo(Student student); //�������� ���� �л� ������ �����ִ� �Լ�
void printscoremenu(int count, Student* student); //���� ���� ��� �޴�
void printscoreAll(int count, Student* student); //�л� ���� ��ü ���
void printscore(int count, Student* student, char name[20]); //�л� �̸� �Է¹޾� ���� ���
void index(); //���� ȭ��
void mainmenu(); //���� �޴�
void schoolmenu(); //���� �޴�
void notschoolmenu(); //���� �� �޴�
void cleanstudy(); // �н� �������� �޴�
void dong(); //���Ƹ� ���
void bongsa(); //����Ȱ�� ���
void printClubAndVolunteerMenu(int count, Student* student); // ���Ƹ� ����Ȱ�� �κ�
void printClubMembers(int count, Student* student, char dong[20]); // ���Ƹ� ã�Ƽ� ���
void printAllClubs(int count, Student* student); //���Ƹ� ��ü ��� ���
void printClubBudget(int count, Student* student); //���Ƹ� ����
void initializeClubBudgets(Student* students, int count); //���Ƹ� ���� �ʱ�ȭ
void distributeClubBudget(int count, Student* student, int totalBudget, char clubName[20]);// ���Ƹ� ���� �ʱ�ȭ
void handleZoneInput(int* totalPerson, struct Student* student); //û�ұ��� ���� �Լ�
void handleOption3(int* totalPerson, struct Student* student);//û�ұ��� ���� �Լ�
void option3(int* totalPerson, struct Student* student);//main.c���� û�ұ��� �Լ� �ҷ�����
void shufflePersonnel(int personnel[], int count); //û�ұ��� �ο� �� �л� ���� �Լ�
void inputZoneInfo(char zoneNames[][20], int zoneCounts[]); // û�ұ��� �̸��� �Է¹޴� �Լ�
void generateRandomPersonnel(int personnelList[], int totalPerson); //û�ұ��� �ο� �й��� �������� ����
void assignPersonnelToZones(int assignedPersonnel[][10], int personnelList[], int zoneCounts[]); //�л����� û�ұ��� ����
void printAssignedPersonnel(char zoneNames[][20], int zoneCounts[], int assignedPersonnel[][10]); //û�ұ��� ���� ���
void sortList(Student student[], int size);//��������� ������ ���������ι迭�ϴ��Լ�
void class1(int count, Student* student);//���������  �޾ƿ� �̸����������� a/b/c������ ����
void car(int count, Student* student);//����[a~z�����ν�]�� �޾Ƽ� �빮�ڷιٲٰ� 4���̻��������� ��������3�����ϴ� ������
char changeBigChar(char c); // �ּҰ˻�
bool isLeapYear1(int year); //������� ���� ���
int isLeapYear(int year); //���� ���
int daysInMonth(int year, int month); //�� ���� ��¥�� �ݿ�
int inputDate(int* year, int* month, int* day); //��� ��¥�� �Է��ϴ� �Լ�
int inputMeetingHour(int* meetingHour); //��� ���۽ð� �Է� �Լ�
int day_of_week(int y, int m, int d); //���� ��� �Լ�
int weekdayStringToNumber(const char* weekdayStr); //���� ���ڿ��� ���ڷ� ��ȯ�ϴ� �Լ�
int inputExcludeWeekday(int* excludeWeekday); //�Ұ����� ������ �Է¹޴� �Լ�
int inputExcludeDate(int* excludeYear, int* excludeMonth, int* excludeDay);//�Ұ����� ��¥�� �Է¹޴� �Լ�
void shuffleArray(int array[], int size); //�������� �迭�� ���� �Լ�
void generateClassMeetingSchedule(int selectedClass, int classes[3][10], int startYear, int startMonth, int startDay, int meetingHour, int excludeWeekday, int excludeYear, int excludeMonth, int excludeDay);//���� ���� �Լ�
int inputClass(int* selectedClass); //�� �Է� �Լ�
int findStudentIndexBySnum(int count, Student* students, int targetSnum); //�л� ���� �й����� ã��
void initializeTimetable(Timetable* timetable); //�ð�ǥ �ʱ�ȭ
int getInput(const char* prompt, int min, int max); //�ð�ǥ �Է� �ޱ�
bool addCourse(Timetable* timetable, int cls, int day, int startPeriod, int endPeriod, const char* courseName); //�ð�ǥ�� ���� �߰� ��ġ�� �ʵ���
void printTimetable(const Timetable* timetable, int cls); //�ð�ǥ ���
void addCourseMenu(Timetable* timetable); //���� �߰�
void saveTimetableToFile(const char* filename, const Timetable* timetable); //�ð�ǥ ���� �Լ�
void loadTimetableFromFile(const char* filename, Timetable* timetable); //�ð�ǥ �ҷ����� �Լ�
void modifyCourse(Timetable* timetable, int cls); // �ð�ǥ ����
void menu(); //�н� ���α׷� �޴�
void spelling(); // �����
void rangob(); //������
void history(); //���繮��
int getDaysInMonth(int year, int month);
/*	���Ͽ��� ������ ���� �о� quiz�迭�� �����ϴ� �Լ�	*/
void ReadFileFix(Quiz* _pQuiz, char* _pFileName);
/*	���Ͽ��� ������ ���� �о� quiz�迭�� �����ϴ� �Լ�	*/
void ReadFile1(Quiz* _pQuiz, char* _pFileName);
/*	������ Ǫ�� �Լ�	*/
void GamePlay(Quiz* _pQuiz, const int _QuizNums); //����� ����
void saveAndExit(int count, Student* student); //����κ�
void bubbleList(Student student[], int count);
#endif
