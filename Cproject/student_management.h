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
#define CLUB_BUDGET_LIMIT 0.2  // 동아리 예산 상한 비율
#define MAX_DAYS 5 //시간표 요일
#define MAX_PERIODS 6 //시간표 시간
#define MAX_CLASSES 3 //시간표 반
#define numZones 3
#define MAX_CLEAN_ZONES 3
#define MAX_PARAGRAPHS 3
#define MAX_PARAGRAPH_LENGTH 200
typedef struct Quiz
{
	char Question[256];		//	문제를 저장할 문자열
	int Answer;				//	문제에 대한 답을 저장할 변수
	int IsUsed;				//	풀었던 문제인지 아닌지를 저장할 변수
}Quiz;

typedef struct { //질문, 정답 입력 위한 구조체
	char* question;
	char* answer;
} Problem;

typedef struct {
	char zoneName[20];
	int personnel;
} CleanZone;
typedef struct {
	char courses[MAX_CLASSES][MAX_DAYS][MAX_PERIODS][50]; // 5일 x 6교시의 강의명을 저장
} Timetable;
typedef struct {
	int year;
	int month;
	int day;
	int hour;
	int snum;
} MeetingSchedule;
typedef struct _Student {
	int snum; // 학번
	wchar_t sname[20]; //이름
	char adress; // 주소
	char callnumber[15]; // 전화번호
	char cleanadress[3]; // 청소구역
	int birth; // 생년월일
	int Kor; // 국어
	int Eng; // 영어
	int Math; // 수학
	float Avg; // 평균
	char vms[20]; // 봉사활동
	char dong[20]; // 동아리
	int clubBudget; // 동아리 예산
	char scoreclass[20]; // 성적반
} Student;

void loadFromFile(int* count, Student* student); //파일 불러오기
int inputInt(int min, int max); //입력시 최소값 최대값 이용 문자 입력시 종료되도록
int checkBirth(const char* birth); //생년월일 형식 예외처리
int checkcall(const char* callnumber); //전화번호 형식 예외처리
void addStudent(int* count, Student* student); //학생추가
void printAll(int count, Student* student); //학생 정보 전체 출력
void printName(int count, Student* student, char name[20]); //학생 이름 입력받아 출력
void deleteStudent(int* count, Student* students); //학생 삭제 로직
void deleteStudentBySnum(int* count, Student* students); //학생 학번으로 삭제
void deleteStudentBySname(int* count, Student* students); //학생 이름으로 삭제
void modifyStudentInfo(Student* student); //학생 정보 수정
void modifyStudentBySnum(int* count, Student* students); //학생 정보 학번으로 찾아 수정
void printStudentInfo(Student student); //정보수정 관련 학생 정보를 보여주는 함수
void printscoremenu(int count, Student* student); //성적 선택 출력 메뉴
void printscoreAll(int count, Student* student); //학생 성적 전체 출력
void printscore(int count, Student* student, char name[20]); //학생 이름 입력받아 성적 출력
void index(); //메인 화면
void mainmenu(); //메인 메뉴
void schoolmenu(); //교과 메뉴
void notschoolmenu(); //교과 외 메뉴
void cleanstudy(); // 학습 편의지원 메뉴
void dong(); //동아리 목록
void bongsa(); //봉사활동 목록
void printClubAndVolunteerMenu(int count, Student* student); // 동아리 봉사활동 부분
void printClubMembers(int count, Student* student, char dong[20]); // 동아리 찾아서 출력
void printAllClubs(int count, Student* student); //동아리 전체 명단 출력
void printClubBudget(int count, Student* student); //동아리 예산
void initializeClubBudgets(Student* students, int count); //동아리 예산 초기화
void distributeClubBudget(int count, Student* student, int totalBudget, char clubName[20]);// 동아리 예산 초기화
void handleZoneInput(int* totalPerson, struct Student* student); //청소구역 관련 함수
void handleOption3(int* totalPerson, struct Student* student);//청소구역 관련 함수
void option3(int* totalPerson, struct Student* student);//main.c에서 청소구역 함수 불러오기
void shufflePersonnel(int personnel[], int count); //청소구역 부여 때 학생 섞는 함수
void inputZoneInfo(char zoneNames[][20], int zoneCounts[]); // 청소구역 이름을 입력받는 함수
void generateRandomPersonnel(int personnelList[], int totalPerson); //청소구역 부여 학번을 랜덤으로 생성
void assignPersonnelToZones(int assignedPersonnel[][10], int personnelList[], int zoneCounts[]); //학생에게 청소구역 배정
void printAssignedPersonnel(char zoneNames[][20], int zoneCounts[], int assignedPersonnel[][10]); //청소구역 관련 출력
void sortList(Student student[], int size);//평균점수를 점수를 높은순으로배열하는함수
void class1(int count, Student* student);//평균점수를  받아와 이름순으로정렬 a/b/c순으로 배정
void car(int count, Student* student);//지역[a~z까지인식]를 받아서 대문자로바꾸고 4명이상인지역은 차량지원3명이하는 지원금
char changeBigChar(char c); // 주소검색
bool isLeapYear1(int year); //면담일정 윤년 계산
int isLeapYear(int year); //윤년 계산
int daysInMonth(int year, int month); //각 월에 날짜수 반영
int inputDate(int* year, int* month, int* day); //면담 날짜를 입력하는 함수
int inputMeetingHour(int* meetingHour); //면담 시작시간 입력 함수
int day_of_week(int y, int m, int d); //요일 계산 함수
int weekdayStringToNumber(const char* weekdayStr); //요일 문자열을 숫자로 변환하는 함수
int inputExcludeWeekday(int* excludeWeekday); //불가능한 요일을 입력받는 함수
int inputExcludeDate(int* excludeYear, int* excludeMonth, int* excludeDay);//불가능한 날짜를 입력받는 함수
void shuffleArray(int array[], int size); //랜덤으로 배열을 섞는 함수
void generateClassMeetingSchedule(int selectedClass, int classes[3][10], int startYear, int startMonth, int startDay, int meetingHour, int excludeWeekday, int excludeYear, int excludeMonth, int excludeDay);//일정 생성 함수
int inputClass(int* selectedClass); //반 입력 함수
int findStudentIndexBySnum(int count, Student* students, int targetSnum); //학생 정보 학번으로 찾기
void initializeTimetable(Timetable* timetable); //시간표 초기화
int getInput(const char* prompt, int min, int max); //시간표 입력 받기
bool addCourse(Timetable* timetable, int cls, int day, int startPeriod, int endPeriod, const char* courseName); //시간표에 강의 추가 겹치지 않도록
void printTimetable(const Timetable* timetable, int cls); //시간표 출력
void addCourseMenu(Timetable* timetable); //강의 추가
void saveTimetableToFile(const char* filename, const Timetable* timetable); //시간표 저장 함수
void loadTimetableFromFile(const char* filename, Timetable* timetable); //시간표 불러오기 함수
void modifyCourse(Timetable* timetable, int cls); // 시간표 수정
void menu(); //학습 프로그램 메뉴
void spelling(); // 맞춤법
void rangob(); //구구단
void history(); //역사문제
int getDaysInMonth(int year, int month);
/*	파일에서 문제와 답을 읽어 quiz배열에 저장하는 함수	*/
void ReadFileFix(Quiz* _pQuiz, char* _pFileName);
/*	파일에서 문제와 답을 읽어 quiz배열에 저장하는 함수	*/
void ReadFile1(Quiz* _pQuiz, char* _pFileName);
/*	문제를 푸는 함수	*/
void GamePlay(Quiz* _pQuiz, const int _QuizNums); //맞춤법 퀴즈
void saveAndExit(int count, Student* student); //저장부분
void bubbleList(Student student[], int count);
#endif
