#include "student_management.h"

int main()
{
	_wsetlocale(LC_ALL, L"korean");
	Student student[100];
	int count = 0; //�л� ��
	int totalPerson = 0; //û�ұ��� ���� �л� �� ����
	int personnelList[30]; //û�ұ��� ���� �л� ���� ����
	char zoneNames[3][20] = { NULL, NULL, NULL }; //û�ұ���
	int zoneCounts[3]; //û�ұ��� ����
	int assignedPersonnel[3][10]; //û�ұ��� 3��
	int classes[3][10]; // �� 3��, �� �ݴ� 10��
	int startYear, startMonth, startDay; // ��� ���� ������
	int meetingHour; // ��� ���� �ð�
	int excludeWeekday; // �Ұ����� ����
	int excludeWeekday1; // �Ұ����� ����
	int excludeYear, excludeMonth, excludeDay; // �Ұ����� ��¥
	int selectedClass; // ���� ����� �� ����
	Timetable mytimetable; // �ð�ǥ

	initializeTimetable(&mytimetable);// �ð�ǥ �ʱ�ȭ
	srand(time(NULL));
	Student students[10];
	printf("===== �л� ���� ���� ���α׷� =====\n");
	printf("1. ���� �ҷ����� \t 2. ���� �����  \n"); /*���� ����� ����*/
	printf("���ϴ� �޴��� �Է��ϼ��� : ");
	int input = inputInt(1, 2);
	printf("\n\n");
	if (input == 1) {
		loadFromFile(&count, student);
	}
	else if (input == 2) {
		printf("���ο� ���·� �����մϴ�.");
	}
	while (1)
	{
		system("cls");
		index();
		mainmenu();
		input = inputInt(1, 6); // �Լ��� �ּҰ� 1 �ִ밪 6���� ���� 
		printf("\n\n");
		if (input == 1) // ���θ޴� ���� 1�Ͻ� �л����� �Է�
		{
			printf("1. �л� ����\n");
			printf("2. �л� ����\n");
			printf("3. ���θ޴��� ���ư���\n");
			input = inputInt(1, 3);
			if (input == 1) {
				addStudent(&count, student);
			}
			else if (input == 2) {
				printf("===== �л� �����ϱ� =====\n");
				printf("1. �й����� �����ϱ�\n");
				printf("2. �̸����� �����ϱ�\n");
				printf("3. ���\n");

				int deleteOption = inputInt(1, 3);

				if (deleteOption == 1) {
					// �й����� ���� �Լ� ȣ��
					deleteStudentBySnum(&count, student);
					system("pause");
				}
				else if (deleteOption == 2) {
					// �̸����� ���� �Լ� ȣ��
					deleteStudentBySname(&count, student);
					system("pause");
				}
				else if (deleteOption == 3) {
					printf("��ҵǾ����ϴ�.\n");
				}
			}
			else if (input == 3) {
				system("cls");
			}
		}
		else if (input == 2) {
			schoolmenu();
			input = inputInt(1, 5);
			if (input == 1) {
				printscoremenu(count, student);
			}
			else if (input == 2) {
				system("cls");
				addCourseMenu(&mytimetable);
				saveTimetableToFile("timetable.bin", &mytimetable);
				system("pause");
				while (getchar() != '\n');
			}
			else if (input == 3) {
				system("cls");
				// ���Ͽ��� �ð�ǥ�� �ҷ��� ���
				loadTimetableFromFile("timetable.bin", &mytimetable);
				printTimetable(&mytimetable, getInput("�� �Է�", 1, 3) - 1);
				system("pause");
				while (getchar() != '\n');
			}
			else if (input == 4) {
				system("cls");
				loadTimetableFromFile("timetable.bin", &mytimetable);
				printf("���� �����ϼ���: ");
				printTimetable(&mytimetable, getInput("�� �Է�", 1, 3) - 1);
				int cls = getInput("�� �Է�", 1, 3);
				modifyCourse(&mytimetable, cls);
				saveTimetableToFile("timetable.bin", &mytimetable);
				system("pause");
				while (getchar() != '\n');
			}
			else {
				system("cls");
			}
		}
		else if (input == 3) {
			printClubAndVolunteerMenu(count, student);
		}
		else if (input == 4) {
			cleanstudy();
			input = inputInt(1, 5);
			if (input == 1) {
				car(count, student);
			}
			else if (input == 2) {
				while (!inputDate(&startYear, &startMonth, &startDay)); // ������ �Է¿� ������ ������
				while (!inputMeetingHour(&meetingHour)); // ��� ���� �ð��� ������ ������
				while (!inputExcludeWeekday(&excludeWeekday, &excludeWeekday1)); // �Ұ����� ���� �Է¿� ������ ������
				while (!inputExcludeDate(&excludeYear, &excludeMonth, &excludeDay)); // �Ұ����� ��¥ �Է¿� ������ ������
				while (!inputClass(&selectedClass)); // ����� �� �Է¿� ������ ������

				generateClassMeetingSchedule(selectedClass, classes, startYear, startMonth, startDay, meetingHour, excludeWeekday, excludeWeekday1, excludeYear, excludeMonth, excludeDay, &student, count); // ��� ���� ����
				system("pause");
			}
			else if (input == 3) {
				system("cls");
				totalPerson = count;
				option3(&totalPerson, student);
			}
			else if (input == 4) {
				system("cls");
				class1(count, student);
			}
			else if (input == 5) {
				system("cls");
			}
		}
		else if (input == 5) {
			menu();
			input = inputInt(1, 4);
			if (input == 1) {
				system("cls");
				Quiz* quiz = NULL;	//	������ ����� ������ �迭
				int UserInput = 0;
				int QuizNums = 0;	//	������ ����
				char buf[256];

				FILE* pFile = NULL;
				fopen_s(&pFile, "Quiz.txt", "r");

				while (!feof(pFile))
				{
					fgets(buf, 256, pFile);
					QuizNums++;
				}
				QuizNums /= 2;
				fclose(pFile);

				quiz = (Quiz*)malloc(sizeof(Quiz) * QuizNums);	//	������ ������ŭ �迭�� �Ҵ�

				ReadFileFix(quiz, "Quiz.txt");

				srand((unsigned)time(NULL));

				GamePlay(quiz, QuizNums);
				Sleep(1000);

				free(quiz);		//	�����Ҵ� ����

				system("puase");
			}
			else if (input == 2) {
				system("cls");
				rangob();
			}
			else if (input == 3) {
				system("cls");
				history();
			}
			else if (input == 4) {}
		}
		else if (input == 6) {
			printf("���� �Ͻðڽ��ϱ�? 1.���� 2.���\n");
			input = inputInt(1, 2);
			if (input == 1) {
				saveAndExit(count, student);
			}
			else {
				printf("���Ḧ ����մϴ�.\n");
				system("pause");
				system("cls");
			}
		}
	}
	return 0;
}
