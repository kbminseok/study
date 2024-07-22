#include "student_management.h"
#define CLUB_BUDGET_LIMIT 0.2
#define MAX_CLUBS 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* CLUB_NAMES[MAX_CLUBS] = { "독서부","영화부","사진부" };
int getClubIndex(const char* dong) {
	for (int i = 0; i < MAX_CLUBS; ++i) {
		if (strcmp(dong, CLUB_NAMES[i]) == 0) {
			return i;
		}
	}
	return -1; // 찾지 못한 경우
}
void printClubBudget(int count, Student* student, int totalBudget) {
	// 각 동아리의 예산을 저장할 배열
	int clubBudgets[MAX_CLUBS] = { 0 };

	// 각 동아리의 예산 합산
	for (int i = 0; i < count; ++i) {
		int clubIndex = getClubIndex(student[i].dong);
		if (clubIndex != -1) {
			clubBudgets[clubIndex] += student[i].clubBudget;
		}
	}

	// 출력
	printf("동아리\t\t동아리 예산\n");
	printf("------------------------\n");

	for (int i = 0; i < MAX_CLUBS; ++i) {
		if (clubBudgets[i] >= 0) {
			printf("%s\t\t%d 원\n", CLUB_NAMES[i], clubBudgets[i]);
			totalBudget -= clubBudgets[i];
		}
	}
	printf("------------------------\n");
	printf("남은 예산 : %d\n", totalBudget);
	printf("\n");
}
void printClubBudget1(int count, Student* student) {
	// 각 동아리의 예산을 저장할 배열
	int clubBudgets[MAX_CLUBS] = { 0 };

	// 각 동아리의 예산 합산
	for (int i = 0; i < count; ++i) {
		int clubIndex = getClubIndex(student[i].dong);
		if (clubIndex != -1) {
			clubBudgets[clubIndex] += student[i].clubBudget;
		}
	}

	// 출력
	printf("동아리\t\t동아리 예산\n");
	printf("------------------------\n");

	for (int i = 0; i < MAX_CLUBS; ++i) {
		if (clubBudgets[i] >= 0) {
			printf("%s\t\t%d 원\n", CLUB_NAMES[i], clubBudgets[i]);
		}
	}
}
void distributeClubBudget(int count, Student* student, int totalBudget, char clubName[20]) {
	int clubExists = 0;
	for (int i = 0; i < count; i++) {
		if (strcmp(student[i].dong, clubName) == 0) {
			clubExists = 1;
			break;
		}
	}

	if (clubExists) {
		// 동아리 예산 분배 함수 호출
			// 각 학생에게 동일한 예산을 할당
		int baseBudget = totalBudget / count;

		baseBudget = (baseBudget / 100) * 100;

		// 입력받은 동아리와 이름이 같은 학생들에게 동일한 예산을 할당
		for (int i = 0; i < count; ++i) {
			if (strcmp(student[i].dong, clubName) == 0) {
				student[i].clubBudget = baseBudget;
			}
		}
		printf("%s 동아리에 예산이 분배되었습니다.\n", clubName);
	}
	else {
		printf("%s 동아리는 존재하지 않습니다. 예산을 분배하지 않습니다.\n", clubName);
	}


}
// 시간표 초기화 함수
void initializeTimetable(Timetable* timetable) {
	for (int cls = 0; cls < MAX_CLASSES; cls++) {
		for (int day = 0; day < MAX_DAYS; day++) {
			for (int period = 0; period < MAX_PERIODS; period++) {
				timetable->courses[cls][day][period][0] = '\0'; // 초기값으로 빈 문자열로 설정
			}
		}
	}
}
// 입력 받기 함수
int getInput(const char* prompt, int min, int max) {
	char input[100];
	int value;
	char extra;
	while (1) {
		printf("%s (%d ~ %d): ", prompt, min, max);

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
// 시간표에 강의 추가 함수 (겹치지 않도록)
bool addCourse(Timetable* timetable, int cls, int day, int startPeriod, int endPeriod, const char* courseName) {
	// 범위 내에 이미 강의가 있는지 확인
	for (int period = startPeriod; period <= endPeriod; period++) {
		if (timetable->courses[cls][day][period][0] != '\0') {
			printf("이미 해당 교시에 강의가 있습니다. 다른 교시를 선택하세요.\n");
			return false;  // 강의 추가 실패
		}
	}

	// 범위 내에 강의명 저장
	for (int period = startPeriod; period <= endPeriod; period++) {
		snprintf(timetable->courses[cls][day][period], sizeof(timetable->courses[cls][day][period]), "%s", courseName);
	}

	return true;  // 강의 추가 성공
}
// 시간표 출력 함수
void printTimetable(const Timetable* timetable, int cls) {
	printf("       월         화         수         목         금\n");
	for (int period = 0; period < MAX_PERIODS; period++) {
		printf("%d ", period + 1);
		for (int day = 0; day < MAX_DAYS; day++) {
			// 문자열이 비어있는 경우를 처리하여 출력
			if (timetable->courses[cls][day][period][0] != '\0') {
				printf("| %-8s ", timetable->courses[cls][day][period]);
			}
			else {
				printf("|          ");  // 비어있는 경우 공백 출력
			}
		}
		printf("|\n");
	}
}
// 강의 추가하기
// 수정된 강의 수정 함수
// 수정된 강의 수정 함수
void modifyCourse(Timetable* timetable, int cls) {
	int day, period;

	printf("수정 또는 삭제할 강의의 요일 입력: ");
	day = getInput("요일 입력", 1, 5);

	printf("수정 또는 삭제할 강의의 교시 입력: ");
	period = getInput("교시 입력", 1, 6);

	// 입력 받은 요일과 교시에 해당하는 강의 정보 출력
	if (timetable->courses[cls - 1][day - 1][period - 1][0] == '\0') {
		printf("등록된 강의가 없습니다. 수정 또는 삭제가 불가능합니다.\n");
		return;
	}

	printf("현재 강의: %s\n", timetable->courses[cls - 1][day - 1][period - 1]);

	// 수정 또는 삭제 선택
	printf("수정 또는 삭제할 내용을 선택하세요:\n");
	printf("1. 강의명 수정\n");
	printf("2. 강의 삭제\n");
	printf("3. 취소\n");

	int choice = getInput("선택", 1, 3);

	if (choice == 1) {
		char newCourseName[50];
		printf("새로운 강의명 입력: ");
		scanf("%s", newCourseName);

		// 강의명 수정
		snprintf(timetable->courses[cls - 1][day - 1][period - 1], sizeof(timetable->courses[cls - 1][day - 1][period - 1]), "%s", newCourseName);

		printf("강의가 수정되었습니다.\n");
	}
	else if (choice == 2) {
		// 삭제
		printf("정말로 삭제하시겠습니까? (1: 예, 2: 아니오): ");
		int deleteChoice = getInput("선택", 1, 2);

		if (deleteChoice == 1) {
			timetable->courses[cls - 1][day - 1][period - 1][0] = '\0';
			printf("강의가 삭제되었습니다.\n");
		}
		else {
			printf("삭제가 취소되었습니다.\n");
		}
	}
	else {
		printf("수정 또는 삭제가 취소되었습니다.\n");
	}
}
void addCourseMenu(Timetable* timetable) {
	int cls, day, startPeriod, endPeriod;
	char courseName[50];

	cls = getInput("반 입력", 1, 3);
	day = getInput("요일 입력", 1, 5);
	startPeriod = getInput("시작 교시 입력", 1, 6);
	endPeriod = getInput("종료 교시 입력", startPeriod, 6);

	printf("과목명 입력 : ");
	scanf("%s", courseName);

	bool added = addCourse(timetable, cls - 1, day - 1, startPeriod - 1, endPeriod - 1, courseName);
	if (added) {
		printf("강의가 추가되었습니다.\n");
	}
}
void inputZoneInfo(char zoneNames[][20], int zoneCounts[]) { // 청소구역 정보 입력받기
	for (int i = 0; i < 3; ++i) {
		printf("청소구역 %d의 이름 입력: ", i + 1);
		scanf("%s", zoneNames[i]);
		if (i > 0) {
			if (strcmp(zoneNames[i], zoneNames[i - 1]) == 0) {
				printf("중복된 청소구역입니다 다시 입력해주세요\n");
				i--;
				continue;
			}
		}

		// 필요한 인원 수 입력 및 오류 처리 추가
		do {
			int maxCount;
			if (i == 0) { // 청소구역 1에 최대 28명 입력 가능
				maxCount = 28;
			}
			else if (i == 1) { // 청소구역 2에 최대 '30-(청소구역 1 인원)-1'명 입력 가능 
				maxCount = 30 - zoneCounts[0] - 1;
			}
			else {// 청소구역 3에는 '30-(청소구역 1 인원)-(청소구역 2 인원)'명 입력 가능
				maxCount = 30 - zoneCounts[0] - zoneCounts[1];
			}

			printf("\"%s\" 청소에 필요한 인원 수 입력 (최대 %d명): ", zoneNames[i], maxCount);
			if (scanf("%d", &zoneCounts[i]) != 1 || zoneCounts[i] <= 0 || zoneCounts[i] > maxCount) { // 입력값이 정수가 아니거나 음수거나 최대 가능 인원을 초과하면
				printf("오류: %d 이상 %d 이하의 정수를 입력하세요.\n", 1, maxCount); // 최대 입력 가능 인원 안내
				while (getchar() != '\n'); // 입력 버퍼 비우기
			}
			else {
				break; // 올바른 입력일 경우 반복문 탈출
			}
		} while (1); // 올바른 입력이 될 때까지 반복
		printf("\n");
	}
}
void generateRandomPersonnel(int personnelList[], int totalPerson) { // 학번 랜덤 생성
	for (int i = 0; i < totalPerson; ++i) {
		personnelList[i] = (i / 10 + 1) * 1000 + (i % 10) + 1;
	}
}
void shufflePersonnel(int personnel[], int count) { // 학생 랜덤으로 섞기
	for (int i = count - 1; i > 0; --i) {
		int randomIndex = rand() % (i + 1);
		int temp = personnel[i];
		personnel[i] = personnel[randomIndex];
		personnel[randomIndex] = temp;
	}
}
void assignPersonnelToZones(int assignedPersonnel[][10], int personnelList[], int zoneCounts[]) { // 학생 청소구역에 배정하기
	int index = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < zoneCounts[i]; ++j) {
			assignedPersonnel[i][j] = personnelList[index++];
		}
	}
}
int isPersonSelected(int assignedPersonnel[][10], int zoneCounts[], int totalPerson, int personnelList[], int personIndex) { // 선정된 인원 판별
	for (int j = 0; j < 3; ++j) {
		for (int k = 0; k < zoneCounts[j]; ++k) {
			if (assignedPersonnel[j][k] == personnelList[personIndex]) {
				return 1; // 해당 인원이 선택됨
			}
		}
	}
	return 0; // 해당 인원이 선택되지 않음
}
void sortPersonnel(int personnelList[], int totalPerson) { // 오름차순 정렬
	for (int i = 0; i < totalPerson - 1; ++i) {
		for (int j = 0; j < totalPerson - i - 1; ++j) {
			if (personnelList[j] > personnelList[j + 1]) {
				int temp = personnelList[j];
				personnelList[j] = personnelList[j + 1];
				personnelList[j + 1] = temp;
			}
		}
	}
}
void printAssignedPersonnel(char zoneNames[][20], int zoneCounts[], int assignedPersonnel[][10], int totalPerson, int personnelList[], Student* student) { // 배정된 인원 출력
	printf("\n청소구역별 배정된 인원:\n");
	for (int i = 0; i < 3; ++i) {
		printf("[%s]\n", zoneNames[i]);

		// 청소구역에 배정된 인원 정렬
		sortPersonnel(assignedPersonnel[i], zoneCounts[i]);
		for (int j = 0; j < zoneCounts[i]; ++j) {
			for (int k = 0; k < 30; k++) {
				if (student[k].snum == assignedPersonnel[i][j]) {
					printf("  %02d. %d %ls", j + 1, assignedPersonnel[i][j], student[k].sname);
					printf("\n");
				}
			}
		}
		printf("\n");
	}

	// 청소구역에 배정되지 않은 인원 출력
	printf("배정되지 않은 인원:\n");
	int notSelectedCount = 0;
	int notSelectedList[MAX_STUDENTS]; // 배정되지 않은 인원을 담는 배열

	for (int i = 0; i < totalPerson; ++i) {
		if (!isPersonSelected(assignedPersonnel, zoneCounts, totalPerson, personnelList, i)) {
			notSelectedList[notSelectedCount++] = personnelList[i];
		}
	}

	// 배정되지 않은 인원을 정렬
	sortPersonnel(notSelectedList, notSelectedCount);

	// 배정되지 않은 인원을 출력
	for (int i = 0; i < notSelectedCount; ++i) {
		for (int j = 0; j < 30; j++) {
			if (student[j].snum == notSelectedList[i])
				printf("  %02d. %d %ls", i + 1, notSelectedList[i], student[j].sname);
		}
		printf("\n");

	}
	printf("\n");
}
char changeBigChar(char c)
{
	if (c >= 'a' && c <= 'z')
		return c - ('a' - 'A');
	else if (c >= 'A' && c <= 'Z')
		return c;
	else
		return '!';
}
void car(int count, Student* student)
{
	printf("===통학시 차량조정===\n");
	if (count > 0) {
		rewind(stdin);
		int addressList[26] = { NULL };
		//addressList[0]++; //a지역
		//addressList[1]++; //b지역
		//addressList[25]++; //z지역...

		for (int i = 0; i < count; i++)
		{
			rewind(stdin);
			char address;
			address = changeBigChar(student[i].adress);

			addressList[address - 'A']++;

		}

		for (int i = 0; i < 26; i++)
		{
			if (addressList[i] != 0)
			{
				printf("%c지역 %d명입니다\n", i + 'A', addressList[i]);
			}
		}
		for (int i = 0; i < 26; i++)
		{

			if (addressList[i] >= 4)
			{
				if (addressList[i] % 4 == 0)
					printf("%c지역 통학차량 %d대 배치필요\n", i + 'A', (addressList[i] / 4));
				else if (addressList[i] % 4 != 0)
					printf("%c지역 통학차량 %d대 배치필요\n", i + 'A', (addressList[i] / 4) + 1);
			}
			else if (addressList[i] <= 3 && addressList[i] > 0)
				printf("3명이하인 %c지역은 차량지원불가 통학비지원확인바람\n", i + 'A');

		}
	}
	else {
		printf("등록된 학생이 없습니다.\n");
	}
	system("pause");
}
void class1(int count, Student* student)
{
	printf("==방과후 자율학습배정 프로그램==\n");
	printf("==성적순으로 자율학습 반을배정합니다==\n");


	sortList(student, count);
	//평균값을 내림차순으로 정리하고 snum sname과연동시킨다
	for (int i = 0; i < count; i++)
	{
		if (i < 10)
		{
			strcpy(student[i].scoreclass, "A반");
			if (i == 0)
				printf("=============A반===========\n");
			printf("%d %ls ", student[i].snum, student[i].sname);
			if (i == 4)
			{
				printf("\n");
			}
			else if (i == 9)
				printf("\n");
		}

		else if (i < 20) {
			strcpy(student[i].scoreclass, "B반");
			if (i == 10)
				printf("=============B반===========\n");
			printf("%d %ls ", student[i].snum, student[i].sname);
			if (i == 14)
			{
				printf("\n");
			}
			else if (i == 19)
				printf("\n");
		}

		else
		{
			strcpy(student[i].scoreclass, "C반");
			if (i == 20) {
				printf("=============C반===========\n");
			}
			printf("%d %ls ", student[i].snum, student[i].sname);
			if (i == 24) {
				printf("\n");
			}
			else if (i == 29)
				printf("\n");
		}

	}
	bubbleList(student, count);
	system("pause");
}
void sortList(Student student[], int count)
{

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{
			if (student[j].Avg < student[j + 1].Avg)
			{
				Student temp = student[j];
				student[j] = student[j + 1];
				student[j + 1] = temp;
			}

		}

	}
}
void bubbleList(Student student[], int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{
			if (student[j].snum > student[j + 1].snum) // 학번을 기준으로 오름차순으로 수정
			{
				Student temp = student[j];
				student[j] = student[j + 1];
				student[j + 1] = temp;
			}
		}
	}
}
void menu() {
	printf("===학습목록===\n");
	printf("==1.맞춤법 퀴즈==\n");
	printf("==2.구구단 암기==\n");
	printf("==3.역사퀴즈==\n");
	printf("==4.되돌아가기==\n");
}
void spelling() {
	{
		printf("맞춤법문제를 제출합니다 정답인 번호를 입력하여 사용합니다\n");
		int OX;
		int a, b, c, sum;
		int	count = 0;
		{
			for (int i = 0; i < 11;)
			{
				printf("문제1번:\'짤다란 나무에 기대어있다\' 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("오답입니다! 매우 짧거나 생각보다 짧다.라는 뜻을 나타내는 표준어는 짤따랗다 입니다\n");
				else if (OX == 2) {
					printf("정답입니다\n");
					count++;
				}
				else if (OX != 1 && OX != 2)
					printf("잘못된입력\n");
				printf("문제2번:\'떡볶기\'는 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 2)
				{
					printf("정답입니다\n");
					count++;
				}
				else if (OX == 1)
					printf("오답입니다! 떡볶이'가 맞는표현입니다\n");
				else if (OX != 1 && OX != 2) {
					printf("잘못된입력\n");
				}

				printf("문제3번:\'뒤좇았다\'는 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("오답입니다! 쫒아가다는 급하게 따라가다라는뜻입니다\n");

				else if (OX == 2)
				{
					printf("정답입니다\n");
					count++;
				}
				else if (OX != 1 && OX != 2) {
					printf("잘못된입력\n");
				}
				printf("문제4번:\'궤짝\'은 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 1) {
					printf("정답입니다\n");
					count++;
				}
				else if (OX == 2)

					printf("궤를 속되게이르는말이 궤짝입니다\n");


				else if (OX != 1 && OX != 2) {
					printf("잘못된입력\n");
				}

				printf("문제5번:\'길게쭉 늘이고\'는 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 1) {
					printf("정답입니다 ‘늘이다’는 ‘길이를 길게하다\n");
					count++;
				}
				else if (OX == 2)

					printf("‘늘리다’는 ‘수효, 부피, 무게 등에 사용합니다\n");


				else if (OX != 1 && OX != 2) {
					printf("잘못된입력\n");
				}

				printf("문제6번:\'약이 적효를 보이다\'는 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("오답입니다  바로 나타나는 좋은 반응은 즉효로 써야 합니다.\n");


				else if (OX == 2)
				{
					printf("정답입니다 즉효입니다 \n");
					count++;
				}

				else if (OX != 1 && OX != 2) {
					printf("잘못된입력\n");
				}
				printf("문제7번:\'이파리\'는 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 1) {
					printf("정답입니다.\n");
					count++;

				}

				else if (OX == 2)
					printf("오답입니다  명사 잎에 접사 -아리가 붙은 단어입니다. \n");


				else if (OX != 1 && OX != 2) {
					printf("잘못된입력\n");
				}
				printf("문제8번:\'얼차레\'는 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("오답입니다 상급자가 하급자에게 고통을 주는 일은 얼차려입니다.\n");


				else if (OX == 2) {
					printf("정답입니다.\n");
					count++;
				}

				else if (OX != 1 && OX != 2) {
					printf("잘못된입력\n");
				}

				printf("문제9번:\'새초름하다\'는 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("오답입니다 새초롬하다'는 '새치름하다'와 같은 말로\n쌀쌀맞게 시치미를 떼는 태도가 있다는 뜻입니다.\n");


				else if (OX == 2) {
					printf("정답입니다.\n");
					count++;
				}

				else if (OX != 1 && OX != 2) {
					printf("잘못된입력\n");
				}
				printf("문제10번:\'골칫거리\'는 맞는표현이다1 아니다2\n");
				scanf("%d", &OX);
				if (OX == 1)
				{
					printf("정답입니다.\n");
					count++;
				}

				else if (OX == 2)
					printf("오답입니다. 골칫거리:일을 잘못하거나 말썽만 피워 언제나 애를 태우게 하는 사람이나 사물\n");

				else if (OX != 1 && OX != 2) {
					printf("잘못된입력\n");
				}
				printf("%d개맞췄습니다", count);
				printf("처음부터 다시푸시겠습니까 1번 예 2번 아니오[종료] ? ");
				int input = inputInt(1, 2);
				if (input == 1) {
					system("cls");
					continue;
				}
				else {
					break;
				}

			}

		}
	}
}
void saveAndExit(int count, Student* student, Timetable* timetable) {
	printf("프로그램을 종료합니다.\n");
	printf("저장 하시겠습니까 ? 1. 네 \t 2. 아니오 :");
	int input = inputInt(1, 2);
	if (input == 1) {
		FILE* file1 = fopen("학생저장목록파일.txt", "wt");
		if (file1 != NULL) {
			fprintf(file1, "%d\n", count);
			for (int i = 0; i < count; i++) {
				fprintf(file1, "%d\t", student[i].snum);
				fwprintf(file1, L"%ls\t", student[i].sname);
				fprintf(file1, "%s\t", student[i].callnumber);
				fprintf(file1, "%d\t", student[i].birth);
				fprintf(file1, "%c\t", student[i].adress);
				fprintf(file1, "%d\t", student[i].Kor);
				fprintf(file1, "%d\t", student[i].Eng);
				fprintf(file1, "%d\t", student[i].Math);
				fprintf(file1, "%f\t", student[i].Avg);
				fprintf(file1, "%s\t", student[i].dong);
				fprintf(file1, "%s\t", student[i].vms);
				fprintf(file1, "%d\t", student[i].clubBudget);
				fprintf(file1, "%s\t", student[i].scoreclass);
				fprintf(file1, "\n");
			}
			printf("저장이 성공적으로 완료 됬습니다\n");
		}
		else {
			printf("파일 저장에 실패 했습니다.");
		}

	}
	system("pause");
	exit(0);
}
/*	파일에서 문제와 답을 읽어 quiz배열에 저장하는 함수	*/
void ReadFileFix(Quiz* _pQuiz, char* _pFileName)
{
	int count = 0;
	FILE* pFile = fopen(_pFileName, "r");
	char buf[5];

	while (!feof(pFile))
	{
		fgets(_pQuiz[count].Question, sizeof(_pQuiz[count].Question) - 1, pFile);

		//	엔터키를 제거하는 부분
		{
			int l_len = strlen(_pQuiz[count].Question);

			_pQuiz[count].Question[l_len - 1] = '\0';	//	개행문자 자리에 널 문자를 삽입
		}

		fscanf(pFile, "%d", &_pQuiz[count].Answer);
		fgets(buf, 256, pFile);

		_pQuiz[count].IsUsed = 0;	//	문제는 풀지 않은 상태인 0으로 설정

		count++;
	}

	fclose(pFile);
}
/*	문제를 푸는 함수	*/
void GamePlay(Quiz* _pQuiz, const int _QuizNums)
{
	int Correct = 0;			//	맞은 문제의 개수
	int Miss = 0;				//	틀린 문제의 개수
	int QuizNumber = 0;			//	푼 문제의 개수
	int UserInput;

	//	문제를 모두 풀 때까지 반복
	while (1)
	{
		int l_randQuizNum = rand() % _QuizNums;	//	풀 문제를 결정

		//	풀었던 문제는 풀지 않는다. 다시 풀 문제를 결정
		if (_pQuiz[l_randQuizNum].IsUsed == 1)
			continue;

		QuizNumber++;
		printf("[%d]번. %s\n", QuizNumber, _pQuiz[l_randQuizNum].Question);
		printf("답을 입력 하시오 (1:O  2:X) => ");

		scanf("%d", &UserInput);

		//	입력한 답과 문제의 답이 일치하면
		if (UserInput == _pQuiz[l_randQuizNum].Answer)
		{
			printf("정답입니다.\n\n");
			Correct++;
		}

		//	입력한 답과 문제의 답이 일치하지 않으면
		else
		{
			printf("오답입니다.\n\n");
			Miss++;
		}

		_pQuiz[l_randQuizNum].IsUsed = 1;	//	문제를 풀었으므로 1로 설정

		//	모든 문제를 풀었는지 확인
		if (10 == QuizNumber)
			break;
	}
	printf("%d 문제 맟췄습니다\n", Correct);
	printf("%d 점 입니다.\n", Correct * 10);
	system("pause");
}
void shuffle(Problem arr[], int n) { // 순서 섞기
	if (n > 1) {
		int i;
		for (i = 0; i < n - 1; i++) {
			int j = i + rand() / (RAND_MAX / (n - i) + 1);
			Problem temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		}
	}
}
void clearBuffer() { // 버퍼 삭제
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
void history() {
	Problem problems[] = {
		{"역사적 사실을 연도 순으로 나열하세요.\n 1) 신해혁명\n 2) 3.1운동\n 3) 제1차세계대전\n 4) 소련창설\n 5) 베르사유조약\n", "13254"},
		{"다음 중 삼국시대 유물이 아닌 것은?\n 1) 금동미륵보살반가사유상\n 2) 서울 삼양동금동관음보살\n 3) 부여 수리석조여래좌상\n 4) 익산 고도리석조여래입상\n", "4"},
		{"다음 중 고려의 왕조에 속하지 않는 왕은?\n 1) 숙종\n 2) 인종\n 3) 중종\n 4) 고종\n", "3"},
		{"삼국시대에 대한 설명으로 잘못된 것을 고르시오\n 1) 선덕여왕은 최초의 여성군주이다\n 2) 가장 오래 즉위한 신라군주는 진흥왕이다\n 3) 고구려의 태조는 동명성왕이다\n 4) 백제의 수도는 위례성, 웅진, 사비이다\n", "2"},
		{"역사적 사실을 연도 순으로 입력하시오\n 1) 동학농민운동\n 2) 신미양요\n 3) 의화단운동\n 4) 강화도조약\n 5) 을미사변\n", "24153"},
		{"세계사의 사건을 연도 순으로 입력하세요\n 1) 포츠담선언\n 2) 뉴딜정책\n 3) 이스라엘 건국\n 4) 카이로회담\n 5) 뮌헨회담\n", "25413"}
	};

	int num_problems = sizeof(problems) / sizeof(problems[0]); // 저장된 문제 개수 계산

	while (true) {
		int count = 0;
		int input;

		shuffle(problems, num_problems);

		for (int i = 0; i < num_problems; i++) {
			printf("%s\n", problems[i].question);

			scanf("%d번", &input);
			clearBuffer(); // 입력 버퍼 비우기

			if (input == atoi(problems[i].answer)) {
				printf("정답입니다\n");
				count++;
			}
			else {
				printf("오답입니다.\n정답은 %s번\n\n", problems[i].answer);
			}
		}

		printf("%d개 맞췄습니다\n", count);

		while (true) {
			printf("처음부터 다시 푸시겠습니까?\n 1) 예 \n 2) 아니오[종료]\n\n");
			if (scanf("%d번", &input) != 1 || (input != 1 && input != 2)) {
				printf("잘못된 입력입니다. 다시 입력해주세요.\n");
				clearBuffer(); // 입력 버퍼 비우기
			}
			else {
				clearBuffer(); // 입력 버퍼 비우기
				break;
			}
		}

		if (input != 1) {
			break;
		}
	}
}
void rangob()
{
	int multi = 0;//점수계산 count대신사용 
	int a;//input으로 대체가능
	int numb[10];//1~9단
	int gob[10];//에 1~9를곱한다
	int jd[10];//본인이 정답을 입력하는값	
	int k = 0;//난수용함수 원래 선언한것있으면 지우면됨	
	srand(GetCurrentProcessId() + k);
	while (1) {
		printf("문제를 출력합니다\n");
		multi = 0;
		for (int i = 0; i < 10; i++)
		{
			numb[i] = rand() % 8 + 2;//각 따로 난수를적용, 23456789
			gob[i] = rand() % 8 + 2;// 23456789		
			for (int j = 0; j < i; j++)
			{

				if ((numb[i] == numb[j]) && (gob[i] == gob[j]))
				{
					i--;
					srand(GetCurrentProcessId() + k);
					k++;
					break;
				}
			}

		}

		for (int i = 0; i < 10; i++)
		{
			printf("%d번문제 %dx%d=?\n", i + 1, numb[i], gob[i]);
			int input = 0;
			do {
				printf("%s (%d-%d): ", "정수입력", 1, 100);
				input = inputInt(1, 100);

			} while (input < 1 || input > 100);
			jd[i] = input;
			if (numb[i] * gob[i] == jd[i])
			{
				multi++;//맞춘갯수를 계산한다
				printf("정답입니다\n");
			}
			else if (numb[i] * gob[i] != jd[i])
			{
				printf("오답입니다\n");
				printf("정답은 %d\n", numb[i] * gob[i]);
			}



		}


		printf("10개중 %d개를맞춰 %d점을얻었습니다\n", multi, multi * 10);

		printf("다시 푸시겠습니까?\n");
		printf("1. 네    2. 아니요\n");
		int input = inputInt(1, 2);
		if (input == 1)
			continue;
		else if (input == 2)
			break;
	}
}
void handleZoneInput(int* totalPerson, struct Student* student) {
	char zoneNames[3][20];
	int zoneCounts[3];

	inputZoneInfo(zoneNames, zoneCounts); // 청소구역 입력받기

	int personnelList[MAX_STUDENTS];
	generateRandomPersonnel(personnelList, MAX_STUDENTS); // 학번 랜덤 생성
	shufflePersonnel(personnelList, MAX_STUDENTS); // 학생 섞기

	int assignedPersonnel[MAX_STUDENTS];
	assignPersonnelToZones(assignedPersonnel, personnelList, zoneCounts); // 청소구역에 배정

	printAssignedPersonnel(zoneNames, zoneCounts, assignedPersonnel, MAX_STUDENTS, personnelList, student); // 전체 인원 출력

}
void handleOption3(int* totalPerson, struct Student* student) {
	system("cls");
	handleZoneInput(totalPerson, student);
	system("pause");
}
void option3(int* totalPerson, struct Student* student) {
	handleOption3(totalPerson, student);
}
void saveTimetableToFile(const char* filename, const Timetable* timetable) {
	FILE* file = fopen("학생 시간표 저장", "wb");

	if (file != NULL) {
		fwrite(timetable, sizeof(Timetable), 1, file);
		fclose(file);
	}
	else {
		printf("파일을 열 수 없습니다 (쓰기).\n");
	}
}
void loadTimetableFromFile(const char* filename, Timetable* timetable) {
	FILE* file = fopen("학생 시간표 저장", "rb");

	if (file != NULL) {
		fread(timetable, sizeof(Timetable), 1, file);
		fclose(file);
	}
	else {
		printf("파일을 열 수 없습니다 (읽기).\n");
	}
}
