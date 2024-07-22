#include "student_management.h"

int main()
{
	_wsetlocale(LC_ALL, L"korean");
	Student student[100];
	int count = 0; //학생 수
	int totalPerson = 0; //청소구역 관련 학생 수 세기
	int personnelList[30]; //청소구역 관련 학생 랜덤 생성
	char zoneNames[3][20] = { NULL, NULL, NULL }; //청소구역
	int zoneCounts[3]; //청소구역 개수
	int assignedPersonnel[3][10]; //청소구역 3개
	int classes[3][10]; // 총 3반, 각 반당 10명
	int startYear, startMonth, startDay; // 면담 시작 연월일
	int meetingHour; // 면담 시작 시간
	int excludeWeekday; // 불가능한 요일
	int excludeWeekday1; // 불가능한 요일
	int excludeYear, excludeMonth, excludeDay; // 불가능한 날짜
	int selectedClass; // 일정 출력할 반 선정
	Timetable mytimetable; // 시간표

	initializeTimetable(&mytimetable);// 시간표 초기화
	srand(time(NULL));
	Student students[10];
	printf("===== 학생 성적 관리 프로그램 =====\n");
	printf("1. 파일 불러오기 \t 2. 새로 만들기  \n"); /*새로 만들기 띄어쓰기*/
	printf("원하는 메뉴를 입력하세요 : ");
	int input = inputInt(1, 2);
	printf("\n\n");
	if (input == 1) {
		loadFromFile(&count, student);
	}
	else if (input == 2) {
		printf("새로운 상태로 시작합니다.");
	}
	while (1)
	{
		system("cls");
		index();
		mainmenu();
		input = inputInt(1, 6); // 함수에 최소값 1 최대값 6으로 설정 
		printf("\n\n");
		if (input == 1) // 메인메뉴 선택 1일시 학생정보 입력
		{
			printf("1. 학생 정보\n");
			printf("2. 학생 삭제\n");
			printf("3. 메인메뉴로 돌아가기\n");
			input = inputInt(1, 3);
			if (input == 1) {
				addStudent(&count, student);
			}
			else if (input == 2) {
				printf("===== 학생 삭제하기 =====\n");
				printf("1. 학번으로 삭제하기\n");
				printf("2. 이름으로 삭제하기\n");
				printf("3. 취소\n");

				int deleteOption = inputInt(1, 3);

				if (deleteOption == 1) {
					// 학번으로 삭제 함수 호출
					deleteStudentBySnum(&count, student);
					system("pause");
				}
				else if (deleteOption == 2) {
					// 이름으로 삭제 함수 호출
					deleteStudentBySname(&count, student);
					system("pause");
				}
				else if (deleteOption == 3) {
					printf("취소되었습니다.\n");
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
				// 파일에서 시간표를 불러와 출력
				loadTimetableFromFile("timetable.bin", &mytimetable);
				printTimetable(&mytimetable, getInput("반 입력", 1, 3) - 1);
				system("pause");
				while (getchar() != '\n');
			}
			else if (input == 4) {
				system("cls");
				loadTimetableFromFile("timetable.bin", &mytimetable);
				printf("반을 선택하세요: ");
				printTimetable(&mytimetable, getInput("반 입력", 1, 3) - 1);
				int cls = getInput("반 입력", 1, 3);
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
				while (!inputDate(&startYear, &startMonth, &startDay)); // 연월일 입력에 오류가 없으면
				while (!inputMeetingHour(&meetingHour)); // 면담 시작 시간에 오류가 없으면
				while (!inputExcludeWeekday(&excludeWeekday, &excludeWeekday1)); // 불가능한 요일 입력에 오류가 없으면
				while (!inputExcludeDate(&excludeYear, &excludeMonth, &excludeDay)); // 불가능한 날짜 입력에 오류가 없으면
				while (!inputClass(&selectedClass)); // 출력할 반 입력에 오류가 없으면

				generateClassMeetingSchedule(selectedClass, classes, startYear, startMonth, startDay, meetingHour, excludeWeekday, excludeWeekday1, excludeYear, excludeMonth, excludeDay, &student, count); // 면담 일정 생성
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
				Quiz* quiz = NULL;	//	문제와 답들을 저장할 배열
				int UserInput = 0;
				int QuizNums = 0;	//	문제의 개수
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

				quiz = (Quiz*)malloc(sizeof(Quiz) * QuizNums);	//	문제의 개수만큼 배열을 할당

				ReadFileFix(quiz, "Quiz.txt");

				srand((unsigned)time(NULL));

				GamePlay(quiz, QuizNums);
				Sleep(1000);

				free(quiz);		//	동적할당 해제

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
			printf("종료 하시겠습니까? 1.종료 2.취소\n");
			input = inputInt(1, 2);
			if (input == 1) {
				saveAndExit(count, student);
			}
			else {
				printf("종료를 취소합니다.\n");
				system("pause");
				system("cls");
			}
		}
	}
	return 0;
}
