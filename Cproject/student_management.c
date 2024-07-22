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
		printf("������ �Է��ϼ���: ");
		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("�Է� ������ �߻��߽��ϴ�.\n");
			exit(EXIT_FAILURE);
		}

		char* endptr;
		score = strtol(input, &endptr, 10);

		// ��ȯ�� �����ϰų� ��ȯ �Ŀ� ���� ���ڰ� �ִ� ���
		if (*endptr != '\n' && *endptr != '\0') {
			printf("�Էµ� ���� �ùٸ��� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n");
		}
		else if (score < 0 || score > 100) {
			printf("�Էµ� ���� 0���� 100 ������ ���ڿ��� �մϴ�. �ٽ� �Է����ּ���.\n");
		}
		else {
			break;
		}
	}

	return score;
}
bool isLeapYear1(int year) {
	// 4�� ������ �������鼭 100���� ������ �������� �ʰų�, 400���� ������ �������� ����
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// �Էµ� ����� ��ȿ���� Ȯ���ϰ�, �ش� ���� �� ���� ��ȯ�ϴ� �Լ�
int getDaysInMonth(int year, int month) {
	// 1, 3, 5, 7, 8, 10, 12���� 31��
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		return 31;
	}
	// 4, 6, 9, 11���� 30��
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	// 2���� ���⿡ ���� 29�� �Ǵ� 28��
	else if (month == 2) {
		return isLeapYear(year) ? 29 : 28;
	}

	// �߸��� ���� �Էµ� ���
	return -1;
}
bool isSnumDuplicate(int count, Student* student, int newSnum) {
	for (int i = 0; i <= count; i++) {
		if (student[i].snum == newSnum) {
			return 1; // �ߺ��� �й��� ������
		}
	}
	return 0; // �ߺ��� �й��� ����
}
int is_korean_string(const wchar_t* str) {
	int koreanCount = 0;

	while (*str) {
		if (iswalpha(*str) && ((*str < L'��' || *str > L'�R'))) {
			// ���ĺ��̳� �ٸ� ���ڰ� �����鼭, �ѱ��� �ƴ� ���
			return 0;
		}

		if (*str >= L'��' && *str <= L'�R') {
			koreanCount++;
		}

		str++;
	}

	return (koreanCount >= 2);  // �ѱ��� �� ���� �̻��̸� 1 ��ȯ, �ƴϸ� 0 ��ȯ
}
int is_korean_string1(const wchar_t* str) {
	int koreanCount = 0;

	while (*str) {
		if (iswalpha(*str) && ((*str < L'��' || *str > L'�R'))) {
			// ���ĺ��̳� �ٸ� ���ڰ� �����鼭, �ѱ��� �ƴ� ���
			return 0;
		}

		if (*str >= L'��' && *str <= L'�R') {
			koreanCount++;
		}

		str++;
	}

	return (koreanCount >= 2 && koreanCount < 4);  // �ѱ��� �� ���� �̻��̸� 1 ��ȯ, �ƴϸ� 0 ��ȯ
}
bool isValidPhoneNumber(const char* phoneNumber) {
	// ��ȭ��ȣ�� ���̰� 11�ڸ����� Ȯ��
	if (strlen(phoneNumber) != 11) {
		return false;
	}

	// ��ȭ��ȣ�� ó�� 3�ڸ��� "010"���� Ȯ��
	if (strncmp(phoneNumber, "010", 3) != 0) {
		return false;
	}

	// ������ 8�ڸ��� ���ڷ� �̷���� �ִ��� Ȯ��
	for (int i = 3; i < 11; ++i) {
		if (!isdigit(phoneNumber[i])) {
			return false;
		}
	}

	// ��� ������ �����ϸ� ��ȿ�� ��ȭ��ȣ�� �Ǵ�
	return true;
}
int containsDigit(const char* str) {
	// ���ڿ��� ��ȸ�ϸ鼭 ���ڰ� �ִ��� Ȯ��
	while (*str) {
		if (isdigit(*str)) {
			return 1;  // ���ڰ� ������ 1 ��ȯ
		}
		str++;
	}
	return 0;  // ���ڰ� ������ 0 ��ȯ
}
int inputInt(int min, int max) {
	char input[100];
	int value;
	char extra;

	while (1) {
		printf("�Է��ϼ��� (%d ~ %d): ", min, max);

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
void loadFromFile(int* count, Student* student, Timetable* timetable) {
	FILE* file1 = fopen("�л�����������.txt", "rt");
	if (file1 != NULL) {
		fscanf(file1, "%d", count);
		// �⺻ ���� �� �ð�ǥ ���� �б�
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

		printf("���������� �ҷ��Խ��ϴ�.\n");
		system("pause");
	}
	else {
		if (*count == 0) {
			printf("���ο� ���·� �����մϴ�.\n");
		}
		else {
			printf("���� �ҷ����⿡ �����߽��ϴ�. �� �� ���� ������ �߻��߽��ϴ�.\n");
			printf("���ο� ���·� �����մϴ�.\n");
			system("pause");
		}
	}

	fclose(file1);
}
void index() {
	system("mode con cols=300 lines = 500 | title �л��������α׷�");
	printf("====================\n");
	printf("=�л� ���� ���α׷�=\n");
	printf("====================\n");
}
void mainmenu() {
	printf("1. �л� ����\n");
	printf("2. ���� Ȱ��\n");
	printf("3. ���� �� Ȱ��\n");
	printf("4. �н� ���� ����\n");
	printf("5. ���� ���α׷�\n");
	printf("6. ����\n");
}
void schoolmenu() {
	printf("1. ���� ���\n");
	printf("2. �ð�ǥ �Է�\n");
	printf("3. �ð�ǥ ���\n");
	printf("4. �ð�ǥ ����\n");
	printf("5. ���θ޴��� ���ư���\n");
}
void notschoolmenu() {
	printf("1. ����Ȱ�� ���\n");
	printf("2. ���Ƹ� ���\n");
	printf("3. ���θ޴��� ���ư���\n");
}
void cleanstudy() {
	printf("1. �������� ����\n");
	printf("2. ��� ����\n");
	printf("3. û�� ���� ����\n");
	printf("4. ���غ� �н� �� ��\n");
	printf("5. ���θ޴��� ���ư���\n");
}
void dong() {
	printf("����Ͻ� ���Ƹ��� �Է����ּ���\n");
	printf("==========���Ƹ� ���========= \n");
	printf("1.������, 2.��ȭ��, 3.������\n");
}
void bongsa() {
	printf("����Ͻ� ����Ȱ���� �Է����ּ���\n");
	printf("==========����Ȱ�� ���========= \n");
	printf("1. ��ο�, 2. ��ƿ�, 3. ��ȭ����\n");
}
void printStudentInfo(Student student) {
	printf("�й�: %d\n", student.snum);
	printf("�̸�: %ls\n", student.sname);
	printf("�������: %d\n", student.birth);
	printf("��ȭ��ȣ: %s\n", student.callnumber);
	printf("�ּ�: %c\n", student.adress);
	printf("����: %d\n", student.Kor);
	printf("����: %d\n", student.Eng);
	printf("����: %d\n", student.Math);
	printf("���: %.2f\n", student.Avg);
	printf("����Ȱ��: %s\n", student.vms);
	printf("���Ƹ�: %s\n", student.dong);
	printf("\n");
}
void addStudent(int* count, Student* student) {
	setlocale(LC_ALL, "");
	char buffer[100];
	wchar_t bufferh[100];
	int readcount;

	printf("\n1. �л� ���� �Է�\n");
	printf("2. �л� ���� ���\n");
	printf("3. �л� ���� ����\n");
	printf("4. ���θ޴��� ���ư���\n");
	int input = inputInt(1, 4);
	if (input == 1) {
		if (*count == 50) {
			printf("�̹� 100���� �л��� ������ ��� �߰� �߽��ϴ�.\n");
			printf("�� �̻� �߰� �� �� �����ϴ�.\n\n");
			system("pause");
		}
		else {
			system("cls");
			printf("===== �л� ���� �Է��ϱ� [%d / 100] =====\n", *count + 1);
			printf("�й� (1�� 1�� 1001, 2�� 1�� 2001, 3�� 1�� 3001) : ");
			while (1) {
				int currentnum;
				int result = scanf("%d", &currentnum);
				if (result == 1) {
					if ((currentnum >= 1001 && currentnum <= 1010) ||
						(currentnum >= 2001 && currentnum <= 2010) ||
						(currentnum >= 3001 && currentnum <= 3013)) {

						if (0 == isSnumDuplicate(*count, student, currentnum)) {
							student[*count].snum = currentnum;
							break; // �ߺ����� ���� ��ȿ�� �й��� �Էµ�
						}
						else {
							printf("����: �̹� ��ϵ� �й��Դϴ�. �ٽ� �Է����ּ���.\n");
							printf("�й� : (1�� 1�� 1001, 2�� 1�� 2001, 3�� 1�� 3001)");
						}
					}
					else {
						printf("����: �й� ������ ����ų� �߸��� �����Դϴ�. �ٽ� �Է����ּ���.\n");
						printf("�й� : (1�� 1�� 1001, 2�� 1�� 2001, 3�� 1�� 3001)");
					}
				}
				else {
					// ���ڰ� �ƴ� ���� �ԷµǾ��� ���� ó��
					printf("����: ���ڸ� �Է��ϼ���.\n");
					printf("�й� : (1�� 1�� 1001, 2�� 1�� 2001, 3�� 1�� 3001)");
				}

				// �Է� ���� ����
				while (getchar() != '\n');
			}
			printf("�̸� : ");
			while (1) {
				wint_t c;
				wscanf(L"%ls", student[*count].sname);

				while ((c = getwchar()) != L'\n' && c != WEOF);  // �Է� ���� ����

				if (is_korean_string(student[*count].sname)) {
					break;
				}
				else {
					printf("����: �ùٸ� �ѱ� �̸��� �Է��ϼ���.\n");
					printf("�̸� : ");
				}
			}
			printf("������� (19300101 ~ 20231231) : ");
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
						printf("����: �ùٸ� ������ ��������� �Է��ϼ���.\n");
						printf("������� : (19300101 ~ 20231231)");
					}
				}
				else {
					int c;
					while ((c = getchar()) != '\n' && c != EOF); // �Է� ���� ����

					printf("����: ���ڰ� �ƴ� ���� �ԷµǾ����ϴ�. �ٽ� �Է��ϼ���.\n");
					printf("������� : (19300101 ~ 20231231)");
				}
			}
			printf("��ȭ��ȣ (11�ڸ� ��ü�Է�) : ");
			while (1) {
				scanf("%s", student[*count].callnumber);

				if (isValidPhoneNumber(student[*count].callnumber)) {
					break;
				}
				else {
					printf("����: �ùٸ� ��ȭ��ȣ ������ �ƴմϴ�. �ٽ� �Է��ϼ���.\n");
					printf("��ȭ��ȣ : ");
				}
			}
			while (getchar() != '\n');
			while (1) {
				char buffer[100];  // ����� ũ���� ���ڿ��� ������ ����
				printf("�л� �ּ� (ex: a, b, c, ...) : ");
				if (scanf("%99s", buffer) == 1) {
					int c;
					// �Է� ���۸� ���� ���� ���� ���ڱ��� ��� �о ó��
					while ((c = getchar()) != '\n' && c != EOF);

					// �Էµ� ���� ���ĺ��̰�, ���ڿ� ���̰� 1�̸� ����
					if (isalpha(buffer[0]) && buffer[1] == '\0') {
						student[*count].adress = buffer[0];
						break;
					}
					else {
						printf("����: ���ĺ� �ϳ��� �Է��ϼ���.\n");
					}
				}
				else {
					int c;
					while ((c = getchar()) != '\n' && c != EOF); // �Է� ���� ����
					printf("����: ���ĺ� �ϳ��� �Է��ϼ���.\n");
				}
			}
			printf("���� : ");
			student[*count].Kor = getValidScore();
			printf("���� : ");
			student[*count].Eng = getValidScore();
			printf("���� : ");
			student[*count].Math = getValidScore();
			bongsa();
			int vmsChoice = inputInt(1, 3);
			switch (vmsChoice) {
			case 1:
				strcpy(student[*count].vms, "��ο�");
				break;
			case 2:
				strcpy(student[*count].vms, "��ƿ�");
				break;
			case 3:
				strcpy(student[*count].vms, "��ȭ ����");
				break;
			default:
				printf("����: �߸��� �����Դϴ�.\n");
				break;
			}
			dong();
			int dongChoice = inputInt(1, 3);
			switch (dongChoice) {
			case 1:
				strcpy(student[*count].dong, "������");
				break;
			case 2:
				strcpy(student[*count].dong, "������");
				break;
			case 3:
				strcpy(student[*count].dong, "��ȭ��");
				break;
			default:
				printf("����: �߸��� �����Դϴ�.\n");
				break;
			}

			student[*count].Avg = (float)(student[*count].Kor + student[*count].Eng + student[*count].Math) / 3.0f;
			(*count)++; // �Ѹ� �߰��Ҷ� ���� 1�� �߰�
			printf("����� �Ϸ�Ǿ����ϴ�.\n");
			system("pause");
		}
	}
	else if (input == 2) {
		system("cls");
		printf("===== �л� ���� ����ϱ� =====\n");
		printf("1. ��ü ����ϱ� \t 2. ���� ����ϱ� 3. ��� \n");
		printf("���ϴ� �޴��� �Է��ϼ��� : ");
		input = inputInt(1, 3);
		if (input == 1) {
			printAll(*count, student);
		}
		else if (input == 2) {
			printf("ã�� �̸��� �Է� �ϼ��� : ");
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
			return i; // �ش� �й��� ���� �л��� �ε��� ��ȯ
		}
	}
	return -1; // �й��� ã�� ���� ��� -1 ��ȯ
}
void modifyStudentInfo(int count, Student* student) {
	while (1) {
		char buffer[100];  // ����� ũ���� ���ڿ��� ������ ����
		printf("������ �ּ� (ex: a, b, c, ...) : ");
		if (scanf("%99s", buffer) == 1) {
			int c;
			// �Է� ���۸� ���� ���� ���� ���ڱ��� ��� �о ó��
			while ((c = getchar()) != '\n' && c != EOF);

			// �Էµ� ���� ���ĺ��̰�, ���ڿ� ���̰� 1�̸� ����
			if (isalpha(buffer[0]) && buffer[1] == '\0') {
				student->adress = buffer[0];
				break;
			}
			else {
				printf("����: ���ĺ� �ϳ��� �Է��ϼ���.\n");
			}
		}
		else {
			int c;
			while ((c = getchar()) != '\n' && c != EOF); // �Է� ���� ����
			printf("����: ���ĺ� �ϳ��� �Է��ϼ���.\n");
		}
	}
	while (1) {
		printf("������ ��ȭ��ȣ : (11�ڸ� ��ü�Է�)");
		char number[15];
		scanf("%s", number);

		if (isValidPhoneNumber(number)) {
			strcpy(student->callnumber, number);
			break;
		}
		else {
			printf("����: �ùٸ� ��ȭ��ȣ ������ �ƴմϴ�. �ٽ� �Է��ϼ���.\n");
		}
	}
}
void modifyStudentBySnum(int count, Student* students) {
	printf("\n");
	printf("������ �л��� �й��� �Է��ϼ���: ");

	int targetSnum = inputInt(1001, 3010);

	int studentIndex = findStudentIndexBySnum(count, students, targetSnum);

	if (studentIndex != -1) {
		// �л��� ã���� ��� �ش� �л� ���� ��� �� ����
		printf("���� �� �л� ����:\n");
		printStudentInfo(students[studentIndex]);

		// �л� ���� ���� �Լ� ȣ��
		modifyStudentInfo(count, &students[studentIndex]);

		printf("���� �� �л� ����:\n");
		printStudentInfo(students[studentIndex]);
		system("pause");
	}
	else {
		printf("�Է��� �й��� ��ġ�ϴ� �л��� ã�� �� �����ϴ�.\n");
		system("pause");
	}
}
void printAll(int count, Student* student)
{
	printf("===== �л� ���� ��ü ����ϱ� =====\n");
	for (int i = 0; i < count; i++)
	{
		printf("�л� [%d/100]\n", i + 1);
		printf("�й� : %d �̸� : %ls ������� : %d.%d.%d �ּ� : %c ��ȭ��ȣ : %.3s-%.4s-%.4s \n\n",
			student[i].snum, student[i].sname, (student[i].birth / 10000), (student[i].birth % 10000) / 100, student[i].birth % 100, student[i].adress, student[i].callnumber,
			student[i].callnumber + 3, student[i].callnumber + 7);
	}
	if (count == 0)
	{
		printf("��ϵ� �л� ������ �������� �ʽ��ϴ�.\n");
	}
}
void printName(int count, Student* student, wchar_t name[20])
{
	printf("===== �л� ���� ���� ����ϱ�(%ls) =====\n", name);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(name, student[i].sname) == 0)
		{
			printf("�й� : %d �̸� : %ls ������� : %d.%d.%d �ּ� : %c ��ȭ��ȣ : %.3s-%.4s-%.4s \t \n\n",
				student[i].snum, student[i].sname, (student[i].birth / 10000), (student[i].birth % 10000) / 100, student[i].birth % 100, student[i].adress, student[i].callnumber,
				student[i].callnumber + 3, student[i].callnumber + 7);
			return;
		}
	}
	printf("ã�� �л��� �������� �ʽ��ϴ�.\n");
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
	printf("\n������ �л��� �й��� �Է��ϼ���: ");
	int targetSnum = inputInt(0, 9999);

	int index = -1;



	// �Է¹��� �й��� ��ġ�ϴ� �л��� �ε��� ã��
	for (int i = 0; i < *count; i++) {
		if (students[i].snum == targetSnum) {
			index = i;
			break;
		}
	}

	// ��ġ�ϴ� �й��� ã���� ��� ���� ����
	if (index != -1) {
		// ������ �л� �ڿ� �ִ� �л����� ������ �̵�
		memmove(&students[index], &students[index + 1], (*count - index - 1) * sizeof(Student));
		(*count)--;
		printf("�л��� �����Ǿ����ϴ�.\n");
	}
	else {
		printf("�Է��� �й��� ��ġ�ϴ� �л��� ã�� �� �����ϴ�.\n");
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
	printf("������ �л��� �̸��� �Է��ϼ���: ");
	wchar_t targetSname[50] = { NULL };
	wscanf(L"%ls", targetSname);

	int index = -1;

	// �Է¹��� �̸��� ��ġ�ϴ� �л��� �ε��� ã��
	for (int i = 0; i < *count; i++) {
		if (strcmp(students[i].sname, targetSname) == 0) {
			index = i;
			break;
		}
	}

	// ��ġ�ϴ� �̸��� ã���� ��� ���� ����
	if (index != -1) {
		// ������ �л� �ڿ� �ִ� �л����� ������ �̵�
		memmove(&students[index], &students[index + 1], (*count - index - 1) * sizeof(Student));
		(*count)--;
		printf("�л��� �����Ǿ����ϴ�.\n");
	}
	else {
		printf("�Է��� �̸��� ��ġ�ϴ� �л��� ã�� �� �����ϴ�.\n");
	}
}
void deleteStudent(int* count, Student* students) {
	printf("===== �л� �����ϱ� =====\n");
	printf("1. �й����� �����ϱ�\n");
	printf("2. �̸����� �����ϱ�\n");
	printf("3. ���\n");

	int input = inputInt(1, 3);

	if (input == 1) {
		// �й����� ���� �Լ� ȣ��
		deleteStudentBySnum(count, students);
	}
	else if (input == 2) {
		// �̸����� ���� �Լ� ȣ��
		deleteStudentBySname(count, students);
	}
	else if (input == 3) {
		printf("��ҵǾ����ϴ�.\n");
	}

	// �迭�� �����ϴ� ���� �߰�
}
void printscoremenu(int count, Student* student) {
	system("cls");
	printf("===== ���� ���� ����ϱ� =====\n");
	printf("1. ��ü ����ϱ� \t 2. ���� ����ϱ� \n");
	printf("���ϴ� �޴��� �Է��ϼ��� : ");
	int input = inputInt(1, 2);
	if (input == 1) {
		printscoreAll(count, student); // �������� �ʿ�
		system("pause");
	}
	else {
		printf("ã�� �̸��� �Է� �ϼ��� : ");
		wchar_t name[20];
		wscanf(L"%ls", name);
		printscore(count, student, name);
		system("pause");
	}
}
void printscoreAll(int count, Student* student)
{
	printf("===== �л� ���� ��ü ����ϱ� =====\n");
	for (int i = 0; i < count; i++)
	{
		printf("�л� [%d/30]\n", i + 1);
		printf("�й� : %d �̸� : %ls ���� : %d \t ���� : %d \t ���� : %d \t [��� ���� : %.1f] \n\n",
			student[i].snum, student[i].sname, student[i].Kor, student[i].Eng, student[i].Math, student[i].Avg);
	}
	if (count == 0)
	{
		printf("��ϵ� �л� ������ �������� �ʽ��ϴ�.\n");
		system("pause");
	}
}
void printscore(int count, Student* student, wchar_t name[20])
{
	printf("===== �л� ���� ���� ����ϱ�(%ls) =====\n", name);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(name, student[i].sname) == 0)
		{
			printf("�й� : %d �̸� : %ls ���� : %d \t ���� : %d \t ���� : %d \t [��� ���� : %.1f] \n\n",
				student[i].snum, student[i].sname, student[i].Kor, student[i].Eng, student[i].Math, student[i].Avg);
			return;
		}
	}
	printf("ã�� �л��� �������� �ʽ��ϴ�.\n");
	system("pause");
}
void printClubAndVolunteerMenu(int count, Student* student) {
	printf("===== �л� ���� ����ϱ� =====\n");
	printf("1. ���Ƹ� ���\n2. ���Ƹ� ���� �ʱ�ȭ\n");
	printf("3. ���Ƹ� ���� �й� \n4. ���Ƹ� ���� ���\n5. ���θ޴��� ���ư���\n");
	printf("���ϴ� �޴��� �Է��ϼ��� : ");
	int input = inputInt(1, 6);
	if (input == 1) {
		printf("1. ���Ƹ� ��� ��ü ���\n");
		printf("2. ���Ƹ� ��� ���� ���\n");
		int input = inputInt(1, 2);
		if (input == 1) {
			printAllClubs(count, student);
		}
		else {
			char dong[20];
			printf("���Ƹ����� �Է��ϼ���: \n 1 : ������, 2: ��ȭ��, 3 : ������");
			input = inputInt(1, 3);
			switch (input) {
			case 1:
				strcpy(dong, "������");
				break;
			case 2:
				strcpy(dong, "��ȭ��");
				break;
			case 3:
				strcpy(dong, "������");
				break;
			default:
				printf("�߸��� �����Դϴ�.\n");
				return 1;
			}
			printClubMembers(count, student, dong);
		}
	}
	else if (input == 2) {
		initializeClubBudgets(student, count);
	}
	else if (input == 3) {
		// ����ڷκ��� ���� �Ѿ� �Է�
		printf("���Ƹ� ������ �Ѿ��� �Է��ϼ���: ");
		int totalBudget = inputInt(0, 1000000);

		// ���Ƹ� ���� �й� �Լ� ȣ��
		distributeClubBudget(count, student, totalBudget, "������");
		distributeClubBudget(count, student, totalBudget, "��ȭ��");
		distributeClubBudget(count, student, totalBudget, "������");
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
	printf("=== ���Ƹ� ��ü ��� ===\n");

	for (int i = 0; i < count; ++i) {
		if (strcmp(student[i].dong, dong) == 0) {
			printf("�й�: %d, �̸�: %ls, ���Ƹ�: %s\n", student[i].snum, student[i].sname, student[i].dong);
		}
	}

	printf("=======================\n");
}
void printAllClubs(int count, Student* student) {
	printf("=== ���Ƹ� ��ü ��� ===\n");

	// �ߺ��� ���ϱ� ���� �迭
	char uniqueClubs[MAX_STUDENTS][20];
	int uniqueCount = 0;

	// ���Ƹ� ��� ����
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

	// �� ���Ƹ����� ���
	for (int i = 0; i < uniqueCount; ++i) {
		printf("=== ���Ƹ���: %s ===\n", uniqueClubs[i]);
		for (int j = 0; j < count; ++j) {
			if (strcmp(student[j].dong, uniqueClubs[i]) == 0) {
				printf("�й�: %d, �̸�: %ls, ���Ƹ�: %s\n", student[j].snum, student[j].sname, student[j].dong);
			}
		}
		printf("=======================\n");
	}

	printf("=======================\n");
}
void initializeClubBudgets(Student* students, int count) {
	for (int i = 0; i < count; i++) {

		students[i].clubBudget = 0;    // ���Ƹ� ���� �ʱ�ȭ
	}
}
int isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// �� ���� ��¥ �� �ݿ� 
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
// ��¥ �Է� �Լ�
int inputDate(int* year, int* month, int* day) {
	printf("��� ���� ��¥ �Է� (��: 2024. 01. 01.): ");
	int inputResult = scanf("%04d. %02d. %02d.", year, month, day);
	// ��¥ �Է��� ������ �ƴϰų�, ��¥�� �߸� �Էµ� ��쿡 ���� �޽��� ���
	if (inputResult != 3 || *year <= 0 || *month <= 0 || *day <= 0 || *month > 12 || *day > daysInMonth(*year, *month)) {
		printf("\"��¥ ���� �Է� ����\"\n");
		// ������ �Է°� ����
		while (getchar() != '\n');
		printf("\n");
		return 0; // ��¥ �Է��� �����ϸ� �ٽ� �Է¹޴� ������ �ݺ�
	}
	else {
		return 1;  // ����
	}
}
// ��� ���� �ð��� �Է¹޴� �Լ�
int inputMeetingHour(int* meetingHour) {
	printf("��� ���� �ð� �Է� (��: 9 ~ 16): ");
	int inputResult = scanf("%d", meetingHour);

	// �Է°��� ������ �ƴϰų�, �ð� ������ ��� ��츦 ó��
	if (inputResult != 1 || *meetingHour < 9 || *meetingHour > 16) {
		printf("\"�ð� ���� �Է� ����\"\n");
		// ������ �Է°� ����
		while (getchar() != '\n');
		printf("\n");
		return 0;

	}
	else {
		return 1;
	}
}
// ���� ��� �Լ� (0: �����, 1: �Ͽ���, ..., 6: �ݿ��� ����)
int day_of_week(int y, int m, int d) {
	static int t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
// �Ұ����� ������ �Է¹޴� �Լ�
// ���� ���ڿ��� ���ڷ� ��ȯ�ϴ� �Լ�
int weekdayStringToNumber(const char* weekdayStr) {
	int dayNumber = -1; // �⺻������ -1�� �ʱ�ȭ�Ͽ� �߸��� �Է��� ó��

	// ���� ���ڿ��� ���Ͽ� �ش��ϴ� ������ ���ڸ� ��ȯ
	if (strcmp(weekdayStr, "��") == 0) {
		dayNumber = 0;
	}
	else if (strcmp(weekdayStr, "��") == 0) {
		dayNumber = 1;
	}
	else if (strcmp(weekdayStr, "ȭ") == 0) {
		dayNumber = 2;
	}
	else if (strcmp(weekdayStr, "��") == 0) {
		dayNumber = 3;
	}
	else if (strcmp(weekdayStr, "��") == 0) {
		dayNumber = 4;
	}
	else if (strcmp(weekdayStr, "��") == 0) {
		dayNumber = 5;
	}
	else if (strcmp(weekdayStr, "��") == 0) {
		dayNumber = 6;
	}
	else if (strcmp(weekdayStr, "����") == 0) {
		dayNumber = 7;
	}

	return dayNumber; // ��ȯ�� ���� ���� ��ȯ
}
// �Ұ����� ������ �Է¹޴� �Լ�
int inputExcludeWeekday(int* excludeWeekday, int* excludeWeekday1) {
	printf("����� �Ұ����� ���� �Է� (������: ��, ..., �ݿ���: ��, ������ ����): ");
	char weekdayStr[20]; // �ִ� ���� ���ڿ� ���̴� 3 (ex: ��)
	int inputResult = scanf("%7s", weekdayStr);
	int con = 0;

	// �Է°��� ���ڿ��� �ƴϰų�, ���� ���ڿ��� �ƴ� ��츦 ó��
	if (inputResult != 1 || getchar() != '\n' || weekdayStringToNumber(weekdayStr) == -1) {
		printf("\"���� ���� �Է� ����\"\n");
		// ������ �Է°� ����
		while (getchar() != '\n');
		printf("\n");
		return 0;
	}
	else if (weekdayStringToNumber(weekdayStr) == 7) {
		*excludeWeekday = weekdayStringToNumber(weekdayStr);
		return 1;
	}
	else {
		*excludeWeekday = weekdayStringToNumber(weekdayStr); // ���� ���ڿ��� ���ڷ� ��ȯ�Ͽ� ����
		con += 1;
	}
	if (con = 1) {
		printf("����� �Ұ����� ���� �Է� (������: ��, ..., �ݿ���: ��): ");
		int inputResult = scanf("%7s", weekdayStr);
		if (inputResult != 1 || getchar() != '\n' || weekdayStringToNumber(weekdayStr) == -1) {
			printf("\"���� ���� �Է� ����\"\n");
			// ������ �Է°� ����
			while (getchar() != '\n');
			printf("\n");
			return 0;
		}
		else if (weekdayStringToNumber(weekdayStr) == 7) {
			return 1;
		}
		else {
			*excludeWeekday1 = weekdayStringToNumber(weekdayStr); // ���� ���ڿ��� ���ڷ� ��ȯ�Ͽ� ����
			return 1;
		}
	}
}
// �Ұ����� ��¥�� �Է¹޴� �Լ�
int inputExcludeDate(int* excludeYear, int* excludeMonth, int* excludeDay) {
	printf("����� �Ұ����� ��¥ �Է� (��: 2024. 01. 01.): ");
	int inputResult = scanf("%d. %d. %d.", excludeYear, excludeMonth, excludeDay);

	// �Է°��� ������ �ƴϰų�, ��¥�� �߸� �Էµ� ��쿡 ���� �޽��� ���
	if (inputResult != 3 || *excludeYear <= 0 || *excludeMonth <= 0 || *excludeDay <= 0 || *excludeMonth > 12 || *excludeDay > daysInMonth(*excludeYear, *excludeMonth)) {
		printf("\"��¥ ���� �Է� ����\"\n");
		// ������ �Է°� ����
		while (getchar() != '\n');
		printf("\n");
		return 0; // ��¥ �Է��� �����ϸ� �ٽ� �Է¹޴� ������ �ݺ�
	}
	else {
		return 1;  // ����
	}
}
// �������� �迭�� ���� �Լ�
void shuffleArray(int array[], int size) {
	srand(time(NULL));
	for (int i = size - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}
// ���� ���� �Լ�
void generateClassMeetingSchedule(int selectedClass, int classes[3][10], int startYear, int startMonth, int startDay, int meetingHour, int excludeWeekday, int excludeWeekday1, int excludeYear, int excludeMonth, int excludeDay, Student* student, int* count) {
	MeetingSchedule schedule[10];

	// �л� 10�� ��ġ
	int studentOrder[10];
	for (int i = 0; i < 10; ++i) {
		studentOrder[i] = i;
	}
	shuffleArray(studentOrder, 10); // �л� �迭 ����

	int currentYear = startYear;
	int currentMonth = startMonth;
	int currentDay = startDay;
	int currentHour = meetingHour;

	for (int i = 0; i < 10; ++i) {
		int studentIndex = studentOrder[i];

		// ��� �Ұ����� ���� �Ǵ� ��¥�� ��� ���� ���� ����
		while (day_of_week(currentYear, currentMonth, currentDay) == excludeWeekday || day_of_week(currentYear, currentMonth, currentDay) == excludeWeekday1 ||
			(currentYear == excludeYear && currentMonth == excludeMonth && currentDay == excludeDay) ||
			day_of_week(currentYear, currentMonth, currentDay) == 0 || // �����
			day_of_week(currentYear, currentMonth, currentDay) == 6) { // �Ͽ���

			currentDay += 1;
			// �ش� ���� �ϼ��� �ʰ��ϸ� �� �� �߰��ϰ� 1�Ϸ� ����
			if (currentDay > daysInMonth(currentYear, currentMonth)) {
				currentDay = 1;
				currentMonth += 1;
				// �� ���� 12���� �ʰ��ϸ� �� ������ �߰��ϰ� 1���� ���� 
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

		// �ð� ���� �� �Ϸ� 2�ð� �ʰ��ϸ� �������� ����
		if (currentHour >= meetingHour + 2) {
			currentHour = meetingHour;
			currentDay += 1;

			// ��¥ ���� �� �� ���� �������� �ʰ��ϸ� �����޷� ����
			if (currentDay > daysInMonth(currentYear, currentMonth)) {
				currentDay = 1;
				currentMonth += 1;

				// 12���� �ʰ��ϸ� ���� ������ ����
				if (currentMonth > 12) {
					currentMonth = 1;
					currentYear += 1;
				}
			}
		}
	}
	// ������� (���) ���
	printf("%d�� ��� ����\n", selectedClass);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < count; j++) {
			if (schedule[i].snum == student[j].snum) {
				printf("%04d. %02d. %02d. %s %02d�� %04d %ls �л�\n", schedule[i].year, schedule[i].month, schedule[i].day,day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 1 ? "��" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 2 ? "ȭ" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 3 ? "��" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 4 ? "��" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 5 ? "��" : "��", schedule[i].hour, schedule[i].snum, student[j].sname);
			}
		}

	}
}
// �� �Է� �Լ�
int inputClass(int* selectedClass) {
	printf("��� ���� ��� (1��: 1, 2��: 2, 3��: 3): ");
	int inputResult = scanf("%d", selectedClass);

	// �� �Է��� ������ �ƴϰų�, �� ������ �߸��� ��쿡�� ���� �޽��� ���
	if (inputResult != 1 || *selectedClass < 1 || *selectedClass > 3 || getchar() != '\n') {
		printf("\"�� ���� �Է� ����\"\n");
		// ������ �Է°� ����
		while (getchar() != '\n');
		printf("\n");
		return 0;  // ����
	}
	else {
		return 1;  // ����
	}
}
int checkBirth(const char* birth)//0~9�� ���� ��
{
	//19890430, 20020430
	if (birth[0] == '0') //00090430
	{
		return 0; //���� �ƴ��� �ǹ���
	}
	for (int i = 0; i < 9; i++)
	{
		if (birth[i] < '0' || birth[i] >'9') //0���� 9�� �ƴ� ���
		{
			return 0;
		}
	}
	return 1; //�������� �ǹ���

} // ������� üũ
int checkcall(const char* callnumber)
{
	if (callnumber[0] != '0' || callnumber[1] != 1)
	{
		return 0;
	}
	for (int i = 2; i < 11; i++)
	{
		if (callnumber[i] < '0' || callnumber[i] >'9') //0���� 9�� �ƴ� ���
		{
			return 0;
		}
	}
	return 1; //�������� �ǹ���
} // ��ȭ��ȣ üũ

