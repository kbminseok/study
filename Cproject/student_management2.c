#include "student_management.h"
#define CLUB_BUDGET_LIMIT 0.2
#define MAX_CLUBS 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* CLUB_NAMES[MAX_CLUBS] = { "������","��ȭ��","������" };
int getClubIndex(const char* dong) {
	for (int i = 0; i < MAX_CLUBS; ++i) {
		if (strcmp(dong, CLUB_NAMES[i]) == 0) {
			return i;
		}
	}
	return -1; // ã�� ���� ���
}
void printClubBudget(int count, Student* student, int totalBudget) {
	// �� ���Ƹ��� ������ ������ �迭
	int clubBudgets[MAX_CLUBS] = { 0 };

	// �� ���Ƹ��� ���� �ջ�
	for (int i = 0; i < count; ++i) {
		int clubIndex = getClubIndex(student[i].dong);
		if (clubIndex != -1) {
			clubBudgets[clubIndex] += student[i].clubBudget;
		}
	}

	// ���
	printf("���Ƹ�\t\t���Ƹ� ����\n");
	printf("------------------------\n");

	for (int i = 0; i < MAX_CLUBS; ++i) {
		if (clubBudgets[i] >= 0) {
			printf("%s\t\t%d ��\n", CLUB_NAMES[i], clubBudgets[i]);
			totalBudget -= clubBudgets[i];
		}
	}
	printf("------------------------\n");
	printf("���� ���� : %d\n", totalBudget);
	printf("\n");
}
void printClubBudget1(int count, Student* student) {
	// �� ���Ƹ��� ������ ������ �迭
	int clubBudgets[MAX_CLUBS] = { 0 };

	// �� ���Ƹ��� ���� �ջ�
	for (int i = 0; i < count; ++i) {
		int clubIndex = getClubIndex(student[i].dong);
		if (clubIndex != -1) {
			clubBudgets[clubIndex] += student[i].clubBudget;
		}
	}

	// ���
	printf("���Ƹ�\t\t���Ƹ� ����\n");
	printf("------------------------\n");

	for (int i = 0; i < MAX_CLUBS; ++i) {
		if (clubBudgets[i] >= 0) {
			printf("%s\t\t%d ��\n", CLUB_NAMES[i], clubBudgets[i]);
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
		// ���Ƹ� ���� �й� �Լ� ȣ��
			// �� �л����� ������ ������ �Ҵ�
		int baseBudget = totalBudget / count;

		baseBudget = (baseBudget / 100) * 100;

		// �Է¹��� ���Ƹ��� �̸��� ���� �л��鿡�� ������ ������ �Ҵ�
		for (int i = 0; i < count; ++i) {
			if (strcmp(student[i].dong, clubName) == 0) {
				student[i].clubBudget = baseBudget;
			}
		}
		printf("%s ���Ƹ��� ������ �й�Ǿ����ϴ�.\n", clubName);
	}
	else {
		printf("%s ���Ƹ��� �������� �ʽ��ϴ�. ������ �й����� �ʽ��ϴ�.\n", clubName);
	}


}
// �ð�ǥ �ʱ�ȭ �Լ�
void initializeTimetable(Timetable* timetable) {
	for (int cls = 0; cls < MAX_CLASSES; cls++) {
		for (int day = 0; day < MAX_DAYS; day++) {
			for (int period = 0; period < MAX_PERIODS; period++) {
				timetable->courses[cls][day][period][0] = '\0'; // �ʱⰪ���� �� ���ڿ��� ����
			}
		}
	}
}
// �Է� �ޱ� �Լ�
int getInput(const char* prompt, int min, int max) {
	char input[100];
	int value;
	char extra;
	while (1) {
		printf("%s (%d ~ %d): ", prompt, min, max);

		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("�Է� ������ �߻��߽��ϴ�.\n");
			exit(EXIT_FAILURE);
		}

		// ���ڿ��� ���Ͱ� ���ԵǾ� ������ ����
		size_t len = strlen(input);
		if (len > 0 && input[len - 1] == '\n') {
			input[len - 1] = '\0';
		}

		// �Է� ���� ���ڿ��� ������ ��ȯ
		if (sscanf(input, "%d %c", &value, &extra) == 1) {
			if (value >= min && value <= max) {
				break;
			}
			else {
				printf("�߸��� ������ �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
			}
		}
		else {
			printf("�Է� ������ �߻��߽��ϴ�. �ٽ� �Է��ϼ���.\n");
		}
	}

	return value;
}
// �ð�ǥ�� ���� �߰� �Լ� (��ġ�� �ʵ���)
bool addCourse(Timetable* timetable, int cls, int day, int startPeriod, int endPeriod, const char* courseName) {
	// ���� ���� �̹� ���ǰ� �ִ��� Ȯ��
	for (int period = startPeriod; period <= endPeriod; period++) {
		if (timetable->courses[cls][day][period][0] != '\0') {
			printf("�̹� �ش� ���ÿ� ���ǰ� �ֽ��ϴ�. �ٸ� ���ø� �����ϼ���.\n");
			return false;  // ���� �߰� ����
		}
	}

	// ���� ���� ���Ǹ� ����
	for (int period = startPeriod; period <= endPeriod; period++) {
		snprintf(timetable->courses[cls][day][period], sizeof(timetable->courses[cls][day][period]), "%s", courseName);
	}

	return true;  // ���� �߰� ����
}
// �ð�ǥ ��� �Լ�
void printTimetable(const Timetable* timetable, int cls) {
	printf("       ��         ȭ         ��         ��         ��\n");
	for (int period = 0; period < MAX_PERIODS; period++) {
		printf("%d ", period + 1);
		for (int day = 0; day < MAX_DAYS; day++) {
			// ���ڿ��� ����ִ� ��츦 ó���Ͽ� ���
			if (timetable->courses[cls][day][period][0] != '\0') {
				printf("| %-8s ", timetable->courses[cls][day][period]);
			}
			else {
				printf("|          ");  // ����ִ� ��� ���� ���
			}
		}
		printf("|\n");
	}
}
// ���� �߰��ϱ�
// ������ ���� ���� �Լ�
// ������ ���� ���� �Լ�
void modifyCourse(Timetable* timetable, int cls) {
	int day, period;

	printf("���� �Ǵ� ������ ������ ���� �Է�: ");
	day = getInput("���� �Է�", 1, 5);

	printf("���� �Ǵ� ������ ������ ���� �Է�: ");
	period = getInput("���� �Է�", 1, 6);

	// �Է� ���� ���ϰ� ���ÿ� �ش��ϴ� ���� ���� ���
	if (timetable->courses[cls - 1][day - 1][period - 1][0] == '\0') {
		printf("��ϵ� ���ǰ� �����ϴ�. ���� �Ǵ� ������ �Ұ����մϴ�.\n");
		return;
	}

	printf("���� ����: %s\n", timetable->courses[cls - 1][day - 1][period - 1]);

	// ���� �Ǵ� ���� ����
	printf("���� �Ǵ� ������ ������ �����ϼ���:\n");
	printf("1. ���Ǹ� ����\n");
	printf("2. ���� ����\n");
	printf("3. ���\n");

	int choice = getInput("����", 1, 3);

	if (choice == 1) {
		char newCourseName[50];
		printf("���ο� ���Ǹ� �Է�: ");
		scanf("%s", newCourseName);

		// ���Ǹ� ����
		snprintf(timetable->courses[cls - 1][day - 1][period - 1], sizeof(timetable->courses[cls - 1][day - 1][period - 1]), "%s", newCourseName);

		printf("���ǰ� �����Ǿ����ϴ�.\n");
	}
	else if (choice == 2) {
		// ����
		printf("������ �����Ͻðڽ��ϱ�? (1: ��, 2: �ƴϿ�): ");
		int deleteChoice = getInput("����", 1, 2);

		if (deleteChoice == 1) {
			timetable->courses[cls - 1][day - 1][period - 1][0] = '\0';
			printf("���ǰ� �����Ǿ����ϴ�.\n");
		}
		else {
			printf("������ ��ҵǾ����ϴ�.\n");
		}
	}
	else {
		printf("���� �Ǵ� ������ ��ҵǾ����ϴ�.\n");
	}
}
void addCourseMenu(Timetable* timetable) {
	int cls, day, startPeriod, endPeriod;
	char courseName[50];

	cls = getInput("�� �Է�", 1, 3);
	day = getInput("���� �Է�", 1, 5);
	startPeriod = getInput("���� ���� �Է�", 1, 6);
	endPeriod = getInput("���� ���� �Է�", startPeriod, 6);

	printf("����� �Է� : ");
	scanf("%s", courseName);

	bool added = addCourse(timetable, cls - 1, day - 1, startPeriod - 1, endPeriod - 1, courseName);
	if (added) {
		printf("���ǰ� �߰��Ǿ����ϴ�.\n");
	}
}
void inputZoneInfo(char zoneNames[][20], int zoneCounts[]) { // û�ұ��� ���� �Է¹ޱ�
	for (int i = 0; i < 3; ++i) {
		printf("û�ұ��� %d�� �̸� �Է�: ", i + 1);
		scanf("%s", zoneNames[i]);
		if (i > 0) {
			if (strcmp(zoneNames[i], zoneNames[i - 1]) == 0) {
				printf("�ߺ��� û�ұ����Դϴ� �ٽ� �Է����ּ���\n");
				i--;
				continue;
			}
		}

		// �ʿ��� �ο� �� �Է� �� ���� ó�� �߰�
		do {
			int maxCount;
			if (i == 0) { // û�ұ��� 1�� �ִ� 28�� �Է� ����
				maxCount = 28;
			}
			else if (i == 1) { // û�ұ��� 2�� �ִ� '30-(û�ұ��� 1 �ο�)-1'�� �Է� ���� 
				maxCount = 30 - zoneCounts[0] - 1;
			}
			else {// û�ұ��� 3���� '30-(û�ұ��� 1 �ο�)-(û�ұ��� 2 �ο�)'�� �Է� ����
				maxCount = 30 - zoneCounts[0] - zoneCounts[1];
			}

			printf("\"%s\" û�ҿ� �ʿ��� �ο� �� �Է� (�ִ� %d��): ", zoneNames[i], maxCount);
			if (scanf("%d", &zoneCounts[i]) != 1 || zoneCounts[i] <= 0 || zoneCounts[i] > maxCount) { // �Է°��� ������ �ƴϰų� �����ų� �ִ� ���� �ο��� �ʰ��ϸ�
				printf("����: %d �̻� %d ������ ������ �Է��ϼ���.\n", 1, maxCount); // �ִ� �Է� ���� �ο� �ȳ�
				while (getchar() != '\n'); // �Է� ���� ����
			}
			else {
				break; // �ùٸ� �Է��� ��� �ݺ��� Ż��
			}
		} while (1); // �ùٸ� �Է��� �� ������ �ݺ�
		printf("\n");
	}
}
void generateRandomPersonnel(int personnelList[], int totalPerson) { // �й� ���� ����
	for (int i = 0; i < totalPerson; ++i) {
		personnelList[i] = (i / 10 + 1) * 1000 + (i % 10) + 1;
	}
}
void shufflePersonnel(int personnel[], int count) { // �л� �������� ����
	for (int i = count - 1; i > 0; --i) {
		int randomIndex = rand() % (i + 1);
		int temp = personnel[i];
		personnel[i] = personnel[randomIndex];
		personnel[randomIndex] = temp;
	}
}
void assignPersonnelToZones(int assignedPersonnel[][10], int personnelList[], int zoneCounts[]) { // �л� û�ұ����� �����ϱ�
	int index = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < zoneCounts[i]; ++j) {
			assignedPersonnel[i][j] = personnelList[index++];
		}
	}
}
int isPersonSelected(int assignedPersonnel[][10], int zoneCounts[], int totalPerson, int personnelList[], int personIndex) { // ������ �ο� �Ǻ�
	for (int j = 0; j < 3; ++j) {
		for (int k = 0; k < zoneCounts[j]; ++k) {
			if (assignedPersonnel[j][k] == personnelList[personIndex]) {
				return 1; // �ش� �ο��� ���õ�
			}
		}
	}
	return 0; // �ش� �ο��� ���õ��� ����
}
void sortPersonnel(int personnelList[], int totalPerson) { // �������� ����
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
void printAssignedPersonnel(char zoneNames[][20], int zoneCounts[], int assignedPersonnel[][10], int totalPerson, int personnelList[], Student* student) { // ������ �ο� ���
	printf("\nû�ұ����� ������ �ο�:\n");
	for (int i = 0; i < 3; ++i) {
		printf("[%s]\n", zoneNames[i]);

		// û�ұ����� ������ �ο� ����
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

	// û�ұ����� �������� ���� �ο� ���
	printf("�������� ���� �ο�:\n");
	int notSelectedCount = 0;
	int notSelectedList[MAX_STUDENTS]; // �������� ���� �ο��� ��� �迭

	for (int i = 0; i < totalPerson; ++i) {
		if (!isPersonSelected(assignedPersonnel, zoneCounts, totalPerson, personnelList, i)) {
			notSelectedList[notSelectedCount++] = personnelList[i];
		}
	}

	// �������� ���� �ο��� ����
	sortPersonnel(notSelectedList, notSelectedCount);

	// �������� ���� �ο��� ���
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
	printf("===���н� ��������===\n");
	if (count > 0) {
		rewind(stdin);
		int addressList[26] = { NULL };
		//addressList[0]++; //a����
		//addressList[1]++; //b����
		//addressList[25]++; //z����...

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
				printf("%c���� %d���Դϴ�\n", i + 'A', addressList[i]);
			}
		}
		for (int i = 0; i < 26; i++)
		{

			if (addressList[i] >= 4)
			{
				if (addressList[i] % 4 == 0)
					printf("%c���� �������� %d�� ��ġ�ʿ�\n", i + 'A', (addressList[i] / 4));
				else if (addressList[i] % 4 != 0)
					printf("%c���� �������� %d�� ��ġ�ʿ�\n", i + 'A', (addressList[i] / 4) + 1);
			}
			else if (addressList[i] <= 3 && addressList[i] > 0)
				printf("3�������� %c������ ���������Ұ� ���к�����Ȯ�ιٶ�\n", i + 'A');

		}
	}
	else {
		printf("��ϵ� �л��� �����ϴ�.\n");
	}
	system("pause");
}
void class1(int count, Student* student)
{
	printf("==����� �����н����� ���α׷�==\n");
	printf("==���������� �����н� ���������մϴ�==\n");


	sortList(student, count);
	//��հ��� ������������ �����ϰ� snum sname��������Ų��
	for (int i = 0; i < count; i++)
	{
		if (i < 10)
		{
			strcpy(student[i].scoreclass, "A��");
			if (i == 0)
				printf("=============A��===========\n");
			printf("%d %ls ", student[i].snum, student[i].sname);
			if (i == 4)
			{
				printf("\n");
			}
			else if (i == 9)
				printf("\n");
		}

		else if (i < 20) {
			strcpy(student[i].scoreclass, "B��");
			if (i == 10)
				printf("=============B��===========\n");
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
			strcpy(student[i].scoreclass, "C��");
			if (i == 20) {
				printf("=============C��===========\n");
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
			if (student[j].snum > student[j + 1].snum) // �й��� �������� ������������ ����
			{
				Student temp = student[j];
				student[j] = student[j + 1];
				student[j + 1] = temp;
			}
		}
	}
}
void menu() {
	printf("===�н����===\n");
	printf("==1.����� ����==\n");
	printf("==2.������ �ϱ�==\n");
	printf("==3.��������==\n");
	printf("==4.�ǵ��ư���==\n");
}
void spelling() {
	{
		printf("����������� �����մϴ� ������ ��ȣ�� �Է��Ͽ� ����մϴ�\n");
		int OX;
		int a, b, c, sum;
		int	count = 0;
		{
			for (int i = 0; i < 11;)
			{
				printf("����1��:\'©�ٶ� ������ �����ִ�\' �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("�����Դϴ�! �ſ� ª�ų� �������� ª��.��� ���� ��Ÿ���� ǥ�ؾ�� ©������ �Դϴ�\n");
				else if (OX == 2) {
					printf("�����Դϴ�\n");
					count++;
				}
				else if (OX != 1 && OX != 2)
					printf("�߸����Է�\n");
				printf("����2��:\'������\'�� �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 2)
				{
					printf("�����Դϴ�\n");
					count++;
				}
				else if (OX == 1)
					printf("�����Դϴ�! ������'�� �´�ǥ���Դϴ�\n");
				else if (OX != 1 && OX != 2) {
					printf("�߸����Է�\n");
				}

				printf("����3��:\'�����Ҵ�\'�� �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("�����Դϴ�! �i�ư��ٴ� ���ϰ� ���󰡴ٶ�¶��Դϴ�\n");

				else if (OX == 2)
				{
					printf("�����Դϴ�\n");
					count++;
				}
				else if (OX != 1 && OX != 2) {
					printf("�߸����Է�\n");
				}
				printf("����4��:\'��¦\'�� �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 1) {
					printf("�����Դϴ�\n");
					count++;
				}
				else if (OX == 2)

					printf("�˸� �ӵǰ��̸��¸��� ��¦�Դϴ�\n");


				else if (OX != 1 && OX != 2) {
					printf("�߸����Է�\n");
				}

				printf("����5��:\'����� ���̰�\'�� �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 1) {
					printf("�����Դϴ� �����̴١��� �����̸� ����ϴ�\n");
					count++;
				}
				else if (OX == 2)

					printf("���ø��١��� ����ȿ, ����, ���� � ����մϴ�\n");


				else if (OX != 1 && OX != 2) {
					printf("�߸����Է�\n");
				}

				printf("����6��:\'���� ��ȿ�� ���̴�\'�� �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("�����Դϴ�  �ٷ� ��Ÿ���� ���� ������ ��ȿ�� ��� �մϴ�.\n");


				else if (OX == 2)
				{
					printf("�����Դϴ� ��ȿ�Դϴ� \n");
					count++;
				}

				else if (OX != 1 && OX != 2) {
					printf("�߸����Է�\n");
				}
				printf("����7��:\'���ĸ�\'�� �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 1) {
					printf("�����Դϴ�.\n");
					count++;

				}

				else if (OX == 2)
					printf("�����Դϴ�  ��� �ٿ� ���� -�Ƹ��� ���� �ܾ��Դϴ�. \n");


				else if (OX != 1 && OX != 2) {
					printf("�߸����Է�\n");
				}
				printf("����8��:\'������\'�� �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("�����Դϴ� ����ڰ� �ϱ��ڿ��� ������ �ִ� ���� �������Դϴ�.\n");


				else if (OX == 2) {
					printf("�����Դϴ�.\n");
					count++;
				}

				else if (OX != 1 && OX != 2) {
					printf("�߸����Է�\n");
				}

				printf("����9��:\'���ʸ��ϴ�\'�� �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 1)
					printf("�����Դϴ� ���ʷ��ϴ�'�� '��ġ���ϴ�'�� ���� ����\n�ҽҸ°� ��ġ�̸� ���� �µ��� �ִٴ� ���Դϴ�.\n");


				else if (OX == 2) {
					printf("�����Դϴ�.\n");
					count++;
				}

				else if (OX != 1 && OX != 2) {
					printf("�߸����Է�\n");
				}
				printf("����10��:\'��ĩ�Ÿ�\'�� �´�ǥ���̴�1 �ƴϴ�2\n");
				scanf("%d", &OX);
				if (OX == 1)
				{
					printf("�����Դϴ�.\n");
					count++;
				}

				else if (OX == 2)
					printf("�����Դϴ�. ��ĩ�Ÿ�:���� �߸��ϰų� ���鸸 �ǿ� ������ �ָ� �¿�� �ϴ� ����̳� �繰\n");

				else if (OX != 1 && OX != 2) {
					printf("�߸����Է�\n");
				}
				printf("%d��������ϴ�", count);
				printf("ó������ �ٽ�Ǫ�ðڽ��ϱ� 1�� �� 2�� �ƴϿ�[����] ? ");
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
	printf("���α׷��� �����մϴ�.\n");
	printf("���� �Ͻðڽ��ϱ� ? 1. �� \t 2. �ƴϿ� :");
	int input = inputInt(1, 2);
	if (input == 1) {
		FILE* file1 = fopen("�л�����������.txt", "wt");
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
			printf("������ ���������� �Ϸ� ����ϴ�\n");
		}
		else {
			printf("���� ���忡 ���� �߽��ϴ�.");
		}

	}
	system("pause");
	exit(0);
}
/*	���Ͽ��� ������ ���� �о� quiz�迭�� �����ϴ� �Լ�	*/
void ReadFileFix(Quiz* _pQuiz, char* _pFileName)
{
	int count = 0;
	FILE* pFile = fopen(_pFileName, "r");
	char buf[5];

	while (!feof(pFile))
	{
		fgets(_pQuiz[count].Question, sizeof(_pQuiz[count].Question) - 1, pFile);

		//	����Ű�� �����ϴ� �κ�
		{
			int l_len = strlen(_pQuiz[count].Question);

			_pQuiz[count].Question[l_len - 1] = '\0';	//	���๮�� �ڸ��� �� ���ڸ� ����
		}

		fscanf(pFile, "%d", &_pQuiz[count].Answer);
		fgets(buf, 256, pFile);

		_pQuiz[count].IsUsed = 0;	//	������ Ǯ�� ���� ������ 0���� ����

		count++;
	}

	fclose(pFile);
}
/*	������ Ǫ�� �Լ�	*/
void GamePlay(Quiz* _pQuiz, const int _QuizNums)
{
	int Correct = 0;			//	���� ������ ����
	int Miss = 0;				//	Ʋ�� ������ ����
	int QuizNumber = 0;			//	Ǭ ������ ����
	int UserInput;

	//	������ ��� Ǯ ������ �ݺ�
	while (1)
	{
		int l_randQuizNum = rand() % _QuizNums;	//	Ǯ ������ ����

		//	Ǯ���� ������ Ǯ�� �ʴ´�. �ٽ� Ǯ ������ ����
		if (_pQuiz[l_randQuizNum].IsUsed == 1)
			continue;

		QuizNumber++;
		printf("[%d]��. %s\n", QuizNumber, _pQuiz[l_randQuizNum].Question);
		printf("���� �Է� �Ͻÿ� (1:O  2:X) => ");

		scanf("%d", &UserInput);

		//	�Է��� ��� ������ ���� ��ġ�ϸ�
		if (UserInput == _pQuiz[l_randQuizNum].Answer)
		{
			printf("�����Դϴ�.\n\n");
			Correct++;
		}

		//	�Է��� ��� ������ ���� ��ġ���� ������
		else
		{
			printf("�����Դϴ�.\n\n");
			Miss++;
		}

		_pQuiz[l_randQuizNum].IsUsed = 1;	//	������ Ǯ�����Ƿ� 1�� ����

		//	��� ������ Ǯ������ Ȯ��
		if (10 == QuizNumber)
			break;
	}
	printf("%d ���� ������ϴ�\n", Correct);
	printf("%d �� �Դϴ�.\n", Correct * 10);
	system("pause");
}
void shuffle(Problem arr[], int n) { // ���� ����
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
void clearBuffer() { // ���� ����
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
void history() {
	Problem problems[] = {
		{"������ ����� ���� ������ �����ϼ���.\n 1) ��������\n 2) 3.1�\n 3) ��1���������\n 4) �ҷ�â��\n 5) ������������\n", "13254"},
		{"���� �� �ﱹ�ô� ������ �ƴ� ����?\n 1) �ݵ��̸�����ݰ�������\n 2) ���� ��絿�ݵ���������\n 3) �ο� �������������»�\n 4) �ͻ� �������������Ի�\n", "4"},
		{"���� �� ����� ������ ������ �ʴ� ����?\n 1) ����\n 2) ����\n 3) ����\n 4) ����\n", "3"},
		{"�ﱹ�ô뿡 ���� �������� �߸��� ���� ���ÿ�\n 1) ���������� ������ ���������̴�\n 2) ���� ���� ������ �Ŷ��ִ� ������̴�\n 3) ������ ������ �������̴�\n 4) ������ ������ ���ʼ�, ����, ����̴�\n", "2"},
		{"������ ����� ���� ������ �Է��Ͻÿ�\n 1) ���г�ο\n 2) �Ź̾��\n 3) ��ȭ�ܿ\n 4) ��ȭ������\n 5) ���̻纯\n", "24153"},
		{"������� ����� ���� ������ �Է��ϼ���\n 1) �����㼱��\n 2) ������å\n 3) �̽��� �Ǳ�\n 4) ī�̷�ȸ��\n 5) ����ȸ��\n", "25413"}
	};

	int num_problems = sizeof(problems) / sizeof(problems[0]); // ����� ���� ���� ���

	while (true) {
		int count = 0;
		int input;

		shuffle(problems, num_problems);

		for (int i = 0; i < num_problems; i++) {
			printf("%s\n", problems[i].question);

			scanf("%d��", &input);
			clearBuffer(); // �Է� ���� ����

			if (input == atoi(problems[i].answer)) {
				printf("�����Դϴ�\n");
				count++;
			}
			else {
				printf("�����Դϴ�.\n������ %s��\n\n", problems[i].answer);
			}
		}

		printf("%d�� ������ϴ�\n", count);

		while (true) {
			printf("ó������ �ٽ� Ǫ�ðڽ��ϱ�?\n 1) �� \n 2) �ƴϿ�[����]\n\n");
			if (scanf("%d��", &input) != 1 || (input != 1 && input != 2)) {
				printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
				clearBuffer(); // �Է� ���� ����
			}
			else {
				clearBuffer(); // �Է� ���� ����
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
	int multi = 0;//������� count��Ż�� 
	int a;//input���� ��ü����
	int numb[10];//1~9��
	int gob[10];//�� 1~9�����Ѵ�
	int jd[10];//������ ������ �Է��ϴ°�	
	int k = 0;//�������Լ� ���� �����Ѱ������� ������	
	srand(GetCurrentProcessId() + k);
	while (1) {
		printf("������ ����մϴ�\n");
		multi = 0;
		for (int i = 0; i < 10; i++)
		{
			numb[i] = rand() % 8 + 2;//�� ���� ����������, 23456789
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
			printf("%d������ %dx%d=?\n", i + 1, numb[i], gob[i]);
			int input = 0;
			do {
				printf("%s (%d-%d): ", "�����Է�", 1, 100);
				input = inputInt(1, 100);

			} while (input < 1 || input > 100);
			jd[i] = input;
			if (numb[i] * gob[i] == jd[i])
			{
				multi++;//���᰹���� ����Ѵ�
				printf("�����Դϴ�\n");
			}
			else if (numb[i] * gob[i] != jd[i])
			{
				printf("�����Դϴ�\n");
				printf("������ %d\n", numb[i] * gob[i]);
			}



		}


		printf("10���� %d�������� %d����������ϴ�\n", multi, multi * 10);

		printf("�ٽ� Ǫ�ðڽ��ϱ�?\n");
		printf("1. ��    2. �ƴϿ�\n");
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

	inputZoneInfo(zoneNames, zoneCounts); // û�ұ��� �Է¹ޱ�

	int personnelList[MAX_STUDENTS];
	generateRandomPersonnel(personnelList, MAX_STUDENTS); // �й� ���� ����
	shufflePersonnel(personnelList, MAX_STUDENTS); // �л� ����

	int assignedPersonnel[MAX_STUDENTS];
	assignPersonnelToZones(assignedPersonnel, personnelList, zoneCounts); // û�ұ����� ����

	printAssignedPersonnel(zoneNames, zoneCounts, assignedPersonnel, MAX_STUDENTS, personnelList, student); // ��ü �ο� ���

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
	FILE* file = fopen("�л� �ð�ǥ ����", "wb");

	if (file != NULL) {
		fwrite(timetable, sizeof(Timetable), 1, file);
		fclose(file);
	}
	else {
		printf("������ �� �� �����ϴ� (����).\n");
	}
}
void loadTimetableFromFile(const char* filename, Timetable* timetable) {
	FILE* file = fopen("�л� �ð�ǥ ����", "rb");

	if (file != NULL) {
		fread(timetable, sizeof(Timetable), 1, file);
		fclose(file);
	}
	else {
		printf("������ �� �� �����ϴ� (�б�).\n");
	}
}
