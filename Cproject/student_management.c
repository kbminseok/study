#include "student_management.h"
#define CLUB_BUDGET_LIMIT 0.2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h> 
#include <ctype.h>

int getValidScore() {
	char input[100];
	int score;

	while (1) {
		printf("점수를 입력하세요: ");
		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("입력 오류가 발생했습니다.\n");
			exit(EXIT_FAILURE);
		}

		char* endptr;
		score = strtol(input, &endptr, 10);

		// 변환에 실패하거나 변환 후에 남은 문자가 있는 경우
		if (*endptr != '\n' && *endptr != '\0') {
			printf("입력된 값이 올바르지 않습니다. 다시 입력해주세요.\n");
		}
		else if (score < 0 || score > 100) {
			printf("입력된 값은 0에서 100 사이의 숫자여야 합니다. 다시 입력해주세요.\n");
		}
		else {
			break;
		}
	}

	return score;
}
bool isLeapYear1(int year) {
	// 4로 나누어 떨어지면서 100으로 나누어 떨어지지 않거나, 400으로 나누어 떨어지면 윤년
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// 입력된 년월이 유효한지 확인하고, 해당 월의 일 수를 반환하는 함수
int getDaysInMonth(int year, int month) {
	// 1, 3, 5, 7, 8, 10, 12월은 31일
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		return 31;
	}
	// 4, 6, 9, 11월은 30일
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	// 2월은 윤년에 따라 29일 또는 28일
	else if (month == 2) {
		return isLeapYear(year) ? 29 : 28;
	}

	// 잘못된 월이 입력된 경우
	return -1;
}
bool isSnumDuplicate(int count, Student* student, int newSnum) {
	for (int i = 0; i <= count; i++) {
		if (student[i].snum == newSnum) {
			return 1; // 중복된 학번이 존재함
		}
	}
	return 0; // 중복된 학번이 없음
}
int is_korean_string(const wchar_t* str) {
	int koreanCount = 0;

	while (*str) {
		if (iswalpha(*str) && ((*str < L'가' || *str > L'힣'))) {
			// 알파벳이나 다른 문자가 있으면서, 한글이 아닌 경우
			return 0;
		}

		if (*str >= L'가' && *str <= L'힣') {
			koreanCount++;
		}

		str++;
	}

	return (koreanCount >= 2);  // 한글이 두 글자 이상이면 1 반환, 아니면 0 반환
}
int is_korean_string1(const wchar_t* str) {
	int koreanCount = 0;

	while (*str) {
		if (iswalpha(*str) && ((*str < L'가' || *str > L'힣'))) {
			// 알파벳이나 다른 문자가 있으면서, 한글이 아닌 경우
			return 0;
		}

		if (*str >= L'가' && *str <= L'힣') {
			koreanCount++;
		}

		str++;
	}

	return (koreanCount >= 2 && koreanCount < 4);  // 한글이 두 글자 이상이면 1 반환, 아니면 0 반환
}
bool isValidPhoneNumber(const char* phoneNumber) {
	// 전화번호의 길이가 11자리인지 확인
	if (strlen(phoneNumber) != 11) {
		return false;
	}

	// 전화번호의 처음 3자리가 "010"인지 확인
	if (strncmp(phoneNumber, "010", 3) != 0) {
		return false;
	}

	// 나머지 8자리가 숫자로 이루어져 있는지 확인
	for (int i = 3; i < 11; ++i) {
		if (!isdigit(phoneNumber[i])) {
			return false;
		}
	}

	// 모든 조건을 만족하면 유효한 전화번호로 판단
	return true;
}
int containsDigit(const char* str) {
	// 문자열을 순회하면서 숫자가 있는지 확인
	while (*str) {
		if (isdigit(*str)) {
			return 1;  // 숫자가 있으면 1 반환
		}
		str++;
	}
	return 0;  // 숫자가 없으면 0 반환
}
int inputInt(int min, int max) {
	char input[100];
	int value;
	char extra;

	while (1) {
		printf("입력하세요 (%d ~ %d): ", min, max);

		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("입력 오류가 발생했습니다.\n");
			exit(EXIT_FAILURE);
		}

		// 문자열에 엔터가 포함되어 있으면 제거
		size_t len = strlen(input);
		if (len > 0 && input[len - 1] == '\n') {
			input[len - 1] = '\0';
		}

		// 입력 받은 문자열을 정수로 변환
		if (sscanf(input, "%d %c", &value, &extra) == 1) {
			if (value >= min && value <= max) {
				break;
			}
			else {
				printf("잘못된 범위의 입력입니다. 다시 입력하세요.\n");
			}
		}
		else {
			printf("입력 오류가 발생했습니다. 다시 입력하세요.\n");
		}
	}

	return value;
}
void loadFromFile(int* count, Student* student, Timetable* timetable) {
	FILE* file1 = fopen("학생저장목록파일.txt", "rt");
	if (file1 != NULL) {
		fscanf(file1, "%d", count);
		// 기본 정보 및 시간표 정보 읽기
		for (int i = 0; i < *count; i++) {
			fscanf(file1, "%d", &student[i].snum);
			fwscanf(file1, L"%ls", student[i].sname);
			fscanf(file1, "%s", student[i].callnumber);
			fscanf(file1, "%d", &student[i].birth);//19890430 20020430
			fscanf(file1, "\t%c", &student[i].adress);
			fscanf(file1, "%d", &student[i].Kor);
			fscanf(file1, "%d", &student[i].Eng);
			fscanf(file1, "%d", &student[i].Math);
			fscanf(file1, "%f", &student[i].Avg);
			fscanf(file1, "%s", student[i].dong);
			fscanf(file1, "%s", student[i].vms);
			fscanf(file1, "%d", &student[i].clubBudget);
			fscanf(file1, "%s", &student[i].scoreclass);
			fscanf(file1, "\n");
		}
		fscanf(file1, "\n");

		printf("성공적으로 불러왔습니다.\n");
		system("pause");
	}
	else {
		if (*count == 0) {
			printf("새로운 상태로 시작합니다.\n");
		}
		else {
			printf("파일 불러오기에 실패했습니다. 알 수 없는 오류가 발생했습니다.\n");
			printf("새로운 상태로 시작합니다.\n");
			system("pause");
		}
	}

	fclose(file1);
}
void index() {
	system("mode con cols=300 lines = 500 | title 학생관리프로그램");
	printf("====================\n");
	printf("=학생 관리 프로그램=\n");
	printf("====================\n");
}
void mainmenu() {
	printf("1. 학생 정보\n");
	printf("2. 교과 활동\n");
	printf("3. 교과 외 활동\n");
	printf("4. 학습 편의 지원\n");
	printf("5. 교육 프로그램\n");
	printf("6. 종료\n");
}
void schoolmenu() {
	printf("1. 성적 출력\n");
	printf("2. 시간표 입력\n");
	printf("3. 시간표 출력\n");
	printf("4. 시간표 수정\n");
	printf("5. 메인메뉴로 돌아가기\n");
}
void notschoolmenu() {
	printf("1. 봉사활동 명단\n");
	printf("2. 동아리 명단\n");
	printf("3. 메인메뉴로 돌아가기\n");
}
void cleanstudy() {
	printf("1. 통학차량 배정\n");
	printf("2. 면담 일정\n");
	printf("3. 청소 구역 지정\n");
	printf("4. 수준별 학습 반 편성\n");
	printf("5. 메인메뉴로 돌아가기\n");
}
void dong() {
	printf("등록하실 동아리를 입력해주세요\n");
	printf("==========동아리 목록========= \n");
	printf("1.독서부, 2.영화부, 3.사진부\n");
}
void bongsa() {
	printf("등록하실 봉사활동을 입력해주세요\n");
	printf("==========봉사활동 목록========= \n");
	printf("1. 양로원, 2. 고아원, 3. 문화센터\n");
}
void printStudentInfo(Student student) {
	printf("학번: %d\n", student.snum);
	printf("이름: %ls\n", student.sname);
	printf("생년월일: %d\n", student.birth);
	printf("전화번호: %s\n", student.callnumber);
	printf("주소: %c\n", student.adress);
	printf("국어: %d\n", student.Kor);
	printf("영어: %d\n", student.Eng);
	printf("수학: %d\n", student.Math);
	printf("평균: %.2f\n", student.Avg);
	printf("봉사활동: %s\n", student.vms);
	printf("동아리: %s\n", student.dong);
	printf("\n");
}
void addStudent(int* count, Student* student) {
	setlocale(LC_ALL, "");
	char buffer[100];
	wchar_t bufferh[100];
	int readcount;

	printf("\n1. 학생 정보 입력\n");
	printf("2. 학생 정보 출력\n");
	printf("3. 학생 정보 수정\n");
	printf("4. 메인메뉴로 돌아가기\n");
	int input = inputInt(1, 4);
	if (input == 1) {
		if (*count == 50) {
			printf("이미 100명의 학생의 정보를 모두 추가 했습니다.\n");
			printf("더 이상 추가 할 수 없습니다.\n\n");
			system("pause");
		}
		else {
			system("cls");
			printf("===== 학생 정보 입력하기 [%d / 100] =====\n", *count + 1);
			printf("학번 (1반 1번 1001, 2반 1번 2001, 3반 1번 3001) : ");
			while (1) {
				int currentnum;
				int result = scanf("%d", &currentnum);
				if (result == 1) {
					if ((currentnum >= 1001 && currentnum <= 1010) ||
						(currentnum >= 2001 && currentnum <= 2010) ||
						(currentnum >= 3001 && currentnum <= 3013)) {

						if (0 == isSnumDuplicate(*count, student, currentnum)) {
							student[*count].snum = currentnum;
							break; // 중복되지 않은 유효한 학번이 입력됨
						}
						else {
							printf("오류: 이미 등록된 학번입니다. 다시 입력해주세요.\n");
							printf("학번 : (1반 1번 1001, 2반 1번 2001, 3반 1번 3001)");
						}
					}
					else {
						printf("오류: 학번 범위를 벗어났거나 잘못된 형식입니다. 다시 입력해주세요.\n");
						printf("학번 : (1반 1번 1001, 2반 1번 2001, 3반 1번 3001)");
					}
				}
				else {
					// 숫자가 아닌 값이 입력되었을 때의 처리
					printf("오류: 숫자를 입력하세요.\n");
					printf("학번 : (1반 1번 1001, 2반 1번 2001, 3반 1번 3001)");
				}

				// 입력 버퍼 비우기
				while (getchar() != '\n');
			}
			printf("이름 : ");
			while (1) {
				wint_t c;
				wscanf(L"%ls", student[*count].sname);

				while ((c = getwchar()) != L'\n' && c != WEOF);  // 입력 버퍼 비우기

				if (is_korean_string(student[*count].sname)) {
					break;
				}
				else {
					printf("오류: 올바른 한글 이름을 입력하세요.\n");
					printf("이름 : ");
				}
			}
			printf("생년월일 (19300101 ~ 20231231) : ");
			while (1) {
				int input;
				if (scanf("%d", &input) == 1) {
					int year = input / 10000;
					int month = (input % 10000) / 100;
					int day = input % 100;

					if (year >= 1930 && year <= 2023 && month >= 1 && month <= 12 && day >= 1 && day <= getDaysInMonth(year, month)) {
						student[*count].birth = input;
						break;
					}
					else {
						printf("오류: 올바른 범위의 생년월일을 입력하세요.\n");
						printf("생년월일 : (19300101 ~ 20231231)");
					}
				}
				else {
					int c;
					while ((c = getchar()) != '\n' && c != EOF); // 입력 버퍼 비우기

					printf("오류: 숫자가 아닌 값이 입력되었습니다. 다시 입력하세요.\n");
					printf("생년월일 : (19300101 ~ 20231231)");
				}
			}
			printf("전화번호 (11자리 전체입력) : ");
			while (1) {
				scanf("%s", student[*count].callnumber);

				if (isValidPhoneNumber(student[*count].callnumber)) {
					break;
				}
				else {
					printf("오류: 올바른 전화번호 형식이 아닙니다. 다시 입력하세요.\n");
					printf("전화번호 : ");
				}
			}
			while (getchar() != '\n');
			while (1) {
				char buffer[100];  // 충분한 크기의 문자열을 저장할 버퍼
				printf("학생 주소 (ex: a, b, c, ...) : ");
				if (scanf("%99s", buffer) == 1) {
					int c;
					// 입력 버퍼를 비우기 위해 개행 문자까지 모두 읽어서 처리
					while ((c = getchar()) != '\n' && c != EOF);

					// 입력된 값이 알파벳이고, 문자열 길이가 1이면 종료
					if (isalpha(buffer[0]) && buffer[1] == '\0') {
						student[*count].adress = buffer[0];
						break;
					}
					else {
						printf("오류: 알파벳 하나만 입력하세요.\n");
					}
				}
				else {
					int c;
					while ((c = getchar()) != '\n' && c != EOF); // 입력 버퍼 비우기
					printf("오류: 알파벳 하나만 입력하세요.\n");
				}
			}
			printf("국어 : ");
			student[*count].Kor = getValidScore();
			printf("영어 : ");
			student[*count].Eng = getValidScore();
			printf("수학 : ");
			student[*count].Math = getValidScore();
			bongsa();
			int vmsChoice = inputInt(1, 3);
			switch (vmsChoice) {
			case 1:
				strcpy(student[*count].vms, "양로원");
				break;
			case 2:
				strcpy(student[*count].vms, "고아원");
				break;
			case 3:
				strcpy(student[*count].vms, "문화 센터");
				break;
			default:
				printf("오류: 잘못된 선택입니다.\n");
				break;
			}
			dong();
			int dongChoice = inputInt(1, 3);
			switch (dongChoice) {
			case 1:
				strcpy(student[*count].dong, "독서부");
				break;
			case 2:
				strcpy(student[*count].dong, "사진부");
				break;
			case 3:
				strcpy(student[*count].dong, "영화부");
				break;
			default:
				printf("오류: 잘못된 선택입니다.\n");
				break;
			}

			student[*count].Avg = (float)(student[*count].Kor + student[*count].Eng + student[*count].Math) / 3.0f;
			(*count)++; // 한명 추가할때 마다 1씩 추가
			printf("등록이 완료되었습니다.\n");
			system("pause");
		}
	}
	else if (input == 2) {
		system("cls");
		printf("===== 학생 정보 출력하기 =====\n");
		printf("1. 전체 출력하기 \t 2. 선택 출력하기 3. 취소 \n");
		printf("원하는 메뉴를 입력하세요 : ");
		input = inputInt(1, 3);
		if (input == 1) {
			printAll(*count, student);
		}
		else if (input == 2) {
			printf("찾을 이름을 입력 하세요 : ");
			wchar_t name[20] = { NULL };
			wscanf(L"%ls", name);
			printName(*count, student, name);
		}
		else {
			system("cls");
		}
		system("pause");
	}
	else if (input == 3) {
		modifyStudentBySnum(*count, student);
	}
	else if (input == 4) {
		system("cls");
	}
}
int findStudentIndexBySnum(int count, Student* students, int targetSnum) {
	for (int i = 0; i < 100; ++i) {
		if (students[i].snum == targetSnum) {
			return i; // 해당 학번을 가진 학생의 인덱스 반환
		}
	}
	return -1; // 학번을 찾지 못한 경우 -1 반환
}
void modifyStudentInfo(int count, Student* student) {
	while (1) {
		char buffer[100];  // 충분한 크기의 문자열을 저장할 버퍼
		printf("수정할 주소 (ex: a, b, c, ...) : ");
		if (scanf("%99s", buffer) == 1) {
			int c;
			// 입력 버퍼를 비우기 위해 개행 문자까지 모두 읽어서 처리
			while ((c = getchar()) != '\n' && c != EOF);

			// 입력된 값이 알파벳이고, 문자열 길이가 1이면 종료
			if (isalpha(buffer[0]) && buffer[1] == '\0') {
				student->adress = buffer[0];
				break;
			}
			else {
				printf("오류: 알파벳 하나만 입력하세요.\n");
			}
		}
		else {
			int c;
			while ((c = getchar()) != '\n' && c != EOF); // 입력 버퍼 비우기
			printf("오류: 알파벳 하나만 입력하세요.\n");
		}
	}
	while (1) {
		printf("수정할 전화번호 : (11자리 전체입력)");
		char number[15];
		scanf("%s", number);

		if (isValidPhoneNumber(number)) {
			strcpy(student->callnumber, number);
			break;
		}
		else {
			printf("오류: 올바른 전화번호 형식이 아닙니다. 다시 입력하세요.\n");
		}
	}
}
void modifyStudentBySnum(int count, Student* students) {
	printf("\n");
	printf("수정할 학생의 학번을 입력하세요: ");

	int targetSnum = inputInt(1001, 3010);

	int studentIndex = findStudentIndexBySnum(count, students, targetSnum);

	if (studentIndex != -1) {
		// 학생을 찾았을 경우 해당 학생 정보 출력 및 수정
		printf("수정 전 학생 정보:\n");
		printStudentInfo(students[studentIndex]);

		// 학생 정보 수정 함수 호출
		modifyStudentInfo(count, &students[studentIndex]);

		printf("수정 후 학생 정보:\n");
		printStudentInfo(students[studentIndex]);
		system("pause");
	}
	else {
		printf("입력한 학번과 일치하는 학생을 찾을 수 없습니다.\n");
		system("pause");
	}
}
void printAll(int count, Student* student)
{
	printf("===== 학생 정보 전체 출력하기 =====\n");
	for (int i = 0; i < count; i++)
	{
		printf("학생 [%d/100]\n", i + 1);
		printf("학번 : %d 이름 : %ls 생년월일 : %d.%d.%d 주소 : %c 전화번호 : %.3s-%.4s-%.4s \n\n",
			student[i].snum, student[i].sname, (student[i].birth / 10000), (student[i].birth % 10000) / 100, student[i].birth % 100, student[i].adress, student[i].callnumber,
			student[i].callnumber + 3, student[i].callnumber + 7);
	}
	if (count == 0)
	{
		printf("등록된 학생 정보가 존재하지 않습니다.\n");
	}
}
void printName(int count, Student* student, wchar_t name[20])
{
	printf("===== 학생 정보 선택 출력하기(%ls) =====\n", name);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(name, student[i].sname) == 0)
		{
			printf("학번 : %d 이름 : %ls 생년월일 : %d.%d.%d 주소 : %c 전화번호 : %.3s-%.4s-%.4s \t \n\n",
				student[i].snum, student[i].sname, (student[i].birth / 10000), (student[i].birth % 10000) / 100, student[i].birth % 100, student[i].adress, student[i].callnumber,
				student[i].callnumber + 3, student[i].callnumber + 7);
			return;
		}
	}
	printf("찾는 학생이 존재하지 않습니다.\n");
}
void deleteStudentBySnum(int* count, Student* students) {
	for (int i = 0; i < *count; i++) {
		printf("%d ", students[i].snum);
		if (i == 9) {
			printf("\n");
		}
		if (i == 19) {
			printf("\n");
		}
	}
	printf("\n삭제할 학생의 학번을 입력하세요: ");
	int targetSnum = inputInt(0, 9999);

	int index = -1;



	// 입력받은 학번과 일치하는 학생의 인덱스 찾기
	for (int i = 0; i < *count; i++) {
		if (students[i].snum == targetSnum) {
			index = i;
			break;
		}
	}

	// 일치하는 학번을 찾았을 경우 삭제 진행
	if (index != -1) {
		// 삭제된 학생 뒤에 있는 학생들을 앞으로 이동
		memmove(&students[index], &students[index + 1], (*count - index - 1) * sizeof(Student));
		(*count)--;
		printf("학생이 삭제되었습니다.\n");
	}
	else {
		printf("입력한 학번과 일치하는 학생을 찾을 수 없습니다.\n");
	}
}
void deleteStudentBySname(int* count, Student* students) {
	for (int i = 0; i < *count; i++) {
		printf("%ls ", students[i].sname);
		if (i == 9) {
			printf("\n");
		}
		if (i == 19) {
			printf("\n");
		}
	}
	printf("\n");
	printf("삭제할 학생의 이름을 입력하세요: ");
	wchar_t targetSname[50] = { NULL };
	wscanf(L"%ls", targetSname);

	int index = -1;

	// 입력받은 이름과 일치하는 학생의 인덱스 찾기
	for (int i = 0; i < *count; i++) {
		if (strcmp(students[i].sname, targetSname) == 0) {
			index = i;
			break;
		}
	}

	// 일치하는 이름을 찾았을 경우 삭제 진행
	if (index != -1) {
		// 삭제된 학생 뒤에 있는 학생들을 앞으로 이동
		memmove(&students[index], &students[index + 1], (*count - index - 1) * sizeof(Student));
		(*count)--;
		printf("학생이 삭제되었습니다.\n");
	}
	else {
		printf("입력한 이름과 일치하는 학생을 찾을 수 없습니다.\n");
	}
}
void deleteStudent(int* count, Student* students) {
	printf("===== 학생 삭제하기 =====\n");
	printf("1. 학번으로 삭제하기\n");
	printf("2. 이름으로 삭제하기\n");
	printf("3. 취소\n");

	int input = inputInt(1, 3);

	if (input == 1) {
		// 학번으로 삭제 함수 호출
		deleteStudentBySnum(count, students);
	}
	else if (input == 2) {
		// 이름으로 삭제 함수 호출
		deleteStudentBySname(count, students);
	}
	else if (input == 3) {
		printf("취소되었습니다.\n");
	}

	// 배열을 정리하는 로직 추가
}
void printscoremenu(int count, Student* student) {
	system("cls");
	printf("===== 성적 정보 출력하기 =====\n");
	printf("1. 전체 출력하기 \t 2. 선택 출력하기 \n");
	printf("원하는 메뉴를 입력하세요 : ");
	int input = inputInt(1, 2);
	if (input == 1) {
		printscoreAll(count, student); // 오름차순 필요
		system("pause");
	}
	else {
		printf("찾을 이름을 입력 하세요 : ");
		wchar_t name[20];
		wscanf(L"%ls", name);
		printscore(count, student, name);
		system("pause");
	}
}
void printscoreAll(int count, Student* student)
{
	printf("===== 학생 정보 전체 출력하기 =====\n");
	for (int i = 0; i < count; i++)
	{
		printf("학생 [%d/30]\n", i + 1);
		printf("학번 : %d 이름 : %ls 국어 : %d \t 영어 : %d \t 수학 : %d \t [평균 점수 : %.1f] \n\n",
			student[i].snum, student[i].sname, student[i].Kor, student[i].Eng, student[i].Math, student[i].Avg);
	}
	if (count == 0)
	{
		printf("등록된 학생 정보가 존재하지 않습니다.\n");
		system("pause");
	}
}
void printscore(int count, Student* student, wchar_t name[20])
{
	printf("===== 학생 정보 선택 출력하기(%ls) =====\n", name);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(name, student[i].sname) == 0)
		{
			printf("학번 : %d 이름 : %ls 국어 : %d \t 영어 : %d \t 수학 : %d \t [평균 점수 : %.1f] \n\n",
				student[i].snum, student[i].sname, student[i].Kor, student[i].Eng, student[i].Math, student[i].Avg);
			return;
		}
	}
	printf("찾는 학생이 존재하지 않습니다.\n");
	system("pause");
}
void printClubAndVolunteerMenu(int count, Student* student) {
	printf("===== 학생 정보 출력하기 =====\n");
	printf("1. 동아리 출력\n2. 동아리 예산 초기화\n");
	printf("3. 동아리 예산 분배 \n4. 동아리 예산 출력\n5. 메인메뉴로 돌아가기\n");
	printf("원하는 메뉴를 입력하세요 : ");
	int input = inputInt(1, 6);
	if (input == 1) {
		printf("1. 동아리 명단 전체 출력\n");
		printf("2. 동아리 명단 선택 출력\n");
		int input = inputInt(1, 2);
		if (input == 1) {
			printAllClubs(count, student);
		}
		else {
			char dong[20];
			printf("동아리명을 입력하세요: \n 1 : 독서부, 2: 영화부, 3 : 사진부");
			input = inputInt(1, 3);
			switch (input) {
			case 1:
				strcpy(dong, "독서부");
				break;
			case 2:
				strcpy(dong, "영화부");
				break;
			case 3:
				strcpy(dong, "사진부");
				break;
			default:
				printf("잘못된 선택입니다.\n");
				return 1;
			}
			printClubMembers(count, student, dong);
		}
	}
	else if (input == 2) {
		initializeClubBudgets(student, count);
	}
	else if (input == 3) {
		// 사용자로부터 예산 총액 입력
		printf("동아리 예산의 총액을 입력하세요: ");
		int totalBudget = inputInt(0, 1000000);

		// 동아리 예산 분배 함수 호출
		distributeClubBudget(count, student, totalBudget, "독서부");
		distributeClubBudget(count, student, totalBudget, "영화부");
		distributeClubBudget(count, student, totalBudget, "사진부");
		printf("\n");
		printClubBudget(count, student, totalBudget);
	}
	else if (input == 4) {
		printClubBudget1(count, student);
	}
	else {}
	system("pause");
}
void printClubMembers(int count, Student* student, char dong[20]) {
	printf("=== 동아리 전체 명단 ===\n");

	for (int i = 0; i < count; ++i) {
		if (strcmp(student[i].dong, dong) == 0) {
			printf("학번: %d, 이름: %ls, 동아리: %s\n", student[i].snum, student[i].sname, student[i].dong);
		}
	}

	printf("=======================\n");
}
void printAllClubs(int count, Student* student) {
	printf("=== 동아리 전체 명단 ===\n");

	// 중복을 피하기 위한 배열
	char uniqueClubs[MAX_STUDENTS][20];
	int uniqueCount = 0;

	// 동아리 목록 수집
	for (int i = 0; i < count; ++i) {
		int isDuplicate = 0;
		for (int j = 0; j < uniqueCount; ++j) {
			if (strcmp(uniqueClubs[j], student[i].dong) == 0) {
				isDuplicate = 1;
				break;
			}
		}

		if (!isDuplicate) {
			strcpy(uniqueClubs[uniqueCount], student[i].dong);
			++uniqueCount;
		}
	}

	// 각 동아리별로 출력
	for (int i = 0; i < uniqueCount; ++i) {
		printf("=== 동아리명: %s ===\n", uniqueClubs[i]);
		for (int j = 0; j < count; ++j) {
			if (strcmp(student[j].dong, uniqueClubs[i]) == 0) {
				printf("학번: %d, 이름: %ls, 동아리: %s\n", student[j].snum, student[j].sname, student[j].dong);
			}
		}
		printf("=======================\n");
	}

	printf("=======================\n");
}
void initializeClubBudgets(Student* students, int count) {
	for (int i = 0; i < count; i++) {

		students[i].clubBudget = 0;    // 동아리 예산 초기화
	}
}
int isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// 각 월의 날짜 수 반영 
int daysInMonth(int year, int month) {
	switch (month) {
	case 2:
		return isLeapYear(year) ? 29 : 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		return 31;
	}
}
// 날짜 입력 함수
int inputDate(int* year, int* month, int* day) {
	printf("면담 시작 날짜 입력 (예: 2024. 01. 01.): ");
	int inputResult = scanf("%04d. %02d. %02d.", year, month, day);
	// 날짜 입력이 정수가 아니거나, 날짜가 잘못 입력된 경우에 오류 메시지 출력
	if (inputResult != 3 || *year <= 0 || *month <= 0 || *day <= 0 || *month > 12 || *day > daysInMonth(*year, *month)) {
		printf("\"날짜 정보 입력 오류\"\n");
		// 실패한 입력값 무시
		while (getchar() != '\n');
		printf("\n");
		return 0; // 날짜 입력을 실패하면 다시 입력받는 문구로 반복
	}
	else {
		return 1;  // 성공
	}
}
// 면담 시작 시간을 입력받는 함수
int inputMeetingHour(int* meetingHour) {
	printf("면담 시작 시간 입력 (예: 9 ~ 16): ");
	int inputResult = scanf("%d", meetingHour);

	// 입력값이 정수가 아니거나, 시간 범위를 벗어난 경우를 처리
	if (inputResult != 1 || *meetingHour < 9 || *meetingHour > 16) {
		printf("\"시간 정보 입력 오류\"\n");
		// 실패한 입력값 무시
		while (getchar() != '\n');
		printf("\n");
		return 0;

	}
	else {
		return 1;
	}
}
// 요일 계산 함수 (0: 토요일, 1: 일요일, ..., 6: 금요일 산출)
int day_of_week(int y, int m, int d) {
	static int t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
// 불가능한 요일을 입력받는 함수
// 요일 문자열을 숫자로 변환하는 함수
int weekdayStringToNumber(const char* weekdayStr) {
	int dayNumber = -1; // 기본적으로 -1로 초기화하여 잘못된 입력을 처리

	// 요일 문자열을 비교하여 해당하는 요일의 숫자를 반환
	if (strcmp(weekdayStr, "일") == 0) {
		dayNumber = 0;
	}
	else if (strcmp(weekdayStr, "월") == 0) {
		dayNumber = 1;
	}
	else if (strcmp(weekdayStr, "화") == 0) {
		dayNumber = 2;
	}
	else if (strcmp(weekdayStr, "수") == 0) {
		dayNumber = 3;
	}
	else if (strcmp(weekdayStr, "목") == 0) {
		dayNumber = 4;
	}
	else if (strcmp(weekdayStr, "금") == 0) {
		dayNumber = 5;
	}
	else if (strcmp(weekdayStr, "토") == 0) {
		dayNumber = 6;
	}
	else if (strcmp(weekdayStr, "없음") == 0) {
		dayNumber = 7;
	}

	return dayNumber; // 변환된 요일 숫자 반환
}
// 불가능한 요일을 입력받는 함수
int inputExcludeWeekday(int* excludeWeekday, int* excludeWeekday1) {
	printf("면담이 불가능한 요일 입력 (월요일: 월, ..., 금요일: 금, 없으면 없음): ");
	char weekdayStr[20]; // 최대 요일 문자열 길이는 3 (ex: 월)
	int inputResult = scanf("%7s", weekdayStr);
	int con = 0;

	// 입력값이 문자열이 아니거나, 요일 문자열이 아닌 경우를 처리
	if (inputResult != 1 || getchar() != '\n' || weekdayStringToNumber(weekdayStr) == -1) {
		printf("\"요일 정보 입력 오류\"\n");
		// 실패한 입력값 무시
		while (getchar() != '\n');
		printf("\n");
		return 0;
	}
	else if (weekdayStringToNumber(weekdayStr) == 7) {
		*excludeWeekday = weekdayStringToNumber(weekdayStr);
		return 1;
	}
	else {
		*excludeWeekday = weekdayStringToNumber(weekdayStr); // 요일 문자열을 숫자로 변환하여 저장
		con += 1;
	}
	if (con = 1) {
		printf("면담이 불가능한 요일 입력 (월요일: 월, ..., 금요일: 금): ");
		int inputResult = scanf("%7s", weekdayStr);
		if (inputResult != 1 || getchar() != '\n' || weekdayStringToNumber(weekdayStr) == -1) {
			printf("\"요일 정보 입력 오류\"\n");
			// 실패한 입력값 무시
			while (getchar() != '\n');
			printf("\n");
			return 0;
		}
		else if (weekdayStringToNumber(weekdayStr) == 7) {
			return 1;
		}
		else {
			*excludeWeekday1 = weekdayStringToNumber(weekdayStr); // 요일 문자열을 숫자로 변환하여 저장
			return 1;
		}
	}
}
// 불가능한 날짜를 입력받는 함수
int inputExcludeDate(int* excludeYear, int* excludeMonth, int* excludeDay) {
	printf("면담이 불가능한 날짜 입력 (예: 2024. 01. 01.): ");
	int inputResult = scanf("%d. %d. %d.", excludeYear, excludeMonth, excludeDay);

	// 입력값이 정수가 아니거나, 날짜가 잘못 입력된 경우에 오류 메시지 출력
	if (inputResult != 3 || *excludeYear <= 0 || *excludeMonth <= 0 || *excludeDay <= 0 || *excludeMonth > 12 || *excludeDay > daysInMonth(*excludeYear, *excludeMonth)) {
		printf("\"날짜 정보 입력 오류\"\n");
		// 실패한 입력값 무시
		while (getchar() != '\n');
		printf("\n");
		return 0; // 날짜 입력을 실패하면 다시 입력받는 문구로 반복
	}
	else {
		return 1;  // 성공
	}
}
// 랜덤으로 배열을 섞는 함수
void shuffleArray(int array[], int size) {
	srand(time(NULL));
	for (int i = size - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}
// 일정 생성 함수
void generateClassMeetingSchedule(int selectedClass, int classes[3][10], int startYear, int startMonth, int startDay, int meetingHour, int excludeWeekday, int excludeWeekday1, int excludeYear, int excludeMonth, int excludeDay, Student* student, int* count) {
	MeetingSchedule schedule[10];

	// 학생 10명 배치
	int studentOrder[10];
	for (int i = 0; i < 10; ++i) {
		studentOrder[i] = i;
	}
	shuffleArray(studentOrder, 10); // 학생 배열 랜덤

	int currentYear = startYear;
	int currentMonth = startMonth;
	int currentDay = startDay;
	int currentHour = meetingHour;

	for (int i = 0; i < 10; ++i) {
		int studentIndex = studentOrder[i];

		// 면담 불가능한 요일 또는 날짜인 경우 다음 날로 조정
		while (day_of_week(currentYear, currentMonth, currentDay) == excludeWeekday || day_of_week(currentYear, currentMonth, currentDay) == excludeWeekday1 ||
			(currentYear == excludeYear && currentMonth == excludeMonth && currentDay == excludeDay) ||
			day_of_week(currentYear, currentMonth, currentDay) == 0 || // 토요일
			day_of_week(currentYear, currentMonth, currentDay) == 6) { // 일요일

			currentDay += 1;
			// 해당 월의 일수를 초과하면 한 달 추가하고 1일로 지정
			if (currentDay > daysInMonth(currentYear, currentMonth)) {
				currentDay = 1;
				currentMonth += 1;
				// 월 수가 12월을 초과하면 한 연도를 추가하고 1월로 지정 
				if (currentMonth > 12) {
					currentMonth = 1;
					currentYear += 1;
				}
			}
		}


		schedule[i].year = currentYear;
		schedule[i].month = currentMonth;
		schedule[i].day = currentDay;
		schedule[i].hour = currentHour;
		schedule[i].snum = (selectedClass * 1000) + studentIndex + 1;

		currentHour += 1;

		// 시간 배정 후 하루 2시간 초과하면 다음날로 지정
		if (currentHour >= meetingHour + 2) {
			currentHour = meetingHour;
			currentDay += 1;

			// 날짜 배정 후 각 월의 마지막날 초과하면 다음달로 지정
			if (currentDay > daysInMonth(currentYear, currentMonth)) {
				currentDay = 1;
				currentMonth += 1;

				// 12월을 초과하면 다음 연도로 지정
				if (currentMonth > 12) {
					currentMonth = 1;
					currentYear += 1;
				}
			}
		}
	}
	// 면담일정 (결과) 출력
	printf("%d반 면담 일정\n", selectedClass);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < count; j++) {
			if (schedule[i].snum == student[j].snum) {
				printf("%04d. %02d. %02d. %s %02d시 %04d %ls 학생\n", schedule[i].year, schedule[i].month, schedule[i].day,day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 1 ? "월" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 2 ? "화" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 3 ? "수" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 4 ? "목" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 5 ? "금" : "토", schedule[i].hour, schedule[i].snum, student[j].sname);
			}
		}

	}
}
// 반 입력 함수
int inputClass(int* selectedClass) {
	printf("면담 일정 출력 (1반: 1, 2반: 2, 3반: 3): ");
	int inputResult = scanf("%d", selectedClass);

	// 반 입력이 정수가 아니거나, 반 범위가 잘못된 경우에는 오류 메시지 출력
	if (inputResult != 1 || *selectedClass < 1 || *selectedClass > 3 || getchar() != '\n') {
		printf("\"반 정보 입력 오류\"\n");
		// 실패한 입력값 무시
		while (getchar() != '\n');
		printf("\n");
		return 0;  // 실패
	}
	else {
		return 1;  // 성공
	}
}
int checkBirth(const char* birth)//0~9만 들어가야 함
{
	//19890430, 20020430
	if (birth[0] == '0') //00090430
	{
		return 0; //정상 아님을 의미함
	}
	for (int i = 0; i < 9; i++)
	{
		if (birth[i] < '0' || birth[i] >'9') //0부터 9가 아닌 경우
		{
			return 0;
		}
	}
	return 1; //정상임을 의미함

} // 생년월일 체크
int checkcall(const char* callnumber)
{
	if (callnumber[0] != '0' || callnumber[1] != 1)
	{
		return 0;
	}
	for (int i = 2; i < 11; i++)
	{
		if (callnumber[i] < '0' || callnumber[i] >'9') //0부터 9가 아닌 경우
		{
			return 0;
		}
	}
	return 1; //정상임을 의미함
} // 전화번호 체크

