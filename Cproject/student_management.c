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
		printf("Á¡¼ö¸¦ ÀÔ·ÂÇÏ¼¼¿ä: ");
		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("ÀÔ·Â ¿À·ù°¡ ¹ß»ıÇß½À´Ï´Ù.\n");
			exit(EXIT_FAILURE);
		}

		char* endptr;
		score = strtol(input, &endptr, 10);

		// º¯È¯¿¡ ½ÇÆĞÇÏ°Å³ª º¯È¯ ÈÄ¿¡ ³²Àº ¹®ÀÚ°¡ ÀÖ´Â °æ¿ì
		if (*endptr != '\n' && *endptr != '\0') {
			printf("ÀÔ·ÂµÈ °ªÀÌ ¿Ã¹Ù¸£Áö ¾Ê½À´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇØÁÖ¼¼¿ä.\n");
		}
		else if (score < 0 || score > 100) {
			printf("ÀÔ·ÂµÈ °ªÀº 0¿¡¼­ 100 »çÀÌÀÇ ¼ıÀÚ¿©¾ß ÇÕ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇØÁÖ¼¼¿ä.\n");
		}
		else {
			break;
		}
	}

	return score;
}
bool isLeapYear1(int year) {
	// 4·Î ³ª´©¾î ¶³¾îÁö¸é¼­ 100À¸·Î ³ª´©¾î ¶³¾îÁöÁö ¾Ê°Å³ª, 400À¸·Î ³ª´©¾î ¶³¾îÁö¸é À±³â
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// ÀÔ·ÂµÈ ³â¿ùÀÌ À¯È¿ÇÑÁö È®ÀÎÇÏ°í, ÇØ´ç ¿ùÀÇ ÀÏ ¼ö¸¦ ¹İÈ¯ÇÏ´Â ÇÔ¼ö
int getDaysInMonth(int year, int month) {
	// 1, 3, 5, 7, 8, 10, 12¿ùÀº 31ÀÏ
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		return 31;
	}
	// 4, 6, 9, 11¿ùÀº 30ÀÏ
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	// 2¿ùÀº À±³â¿¡ µû¶ó 29ÀÏ ¶Ç´Â 28ÀÏ
	else if (month == 2) {
		return isLeapYear(year) ? 29 : 28;
	}

	// Àß¸øµÈ ¿ùÀÌ ÀÔ·ÂµÈ °æ¿ì
	return -1;
}
bool isSnumDuplicate(int count, Student* student, int newSnum) {
	for (int i = 0; i <= count; i++) {
		if (student[i].snum == newSnum) {
			return 1; // Áßº¹µÈ ÇĞ¹øÀÌ Á¸ÀçÇÔ
		}
	}
	return 0; // Áßº¹µÈ ÇĞ¹øÀÌ ¾øÀ½
}
int is_korean_string(const wchar_t* str) {
	int koreanCount = 0;

	while (*str) {
		if (iswalpha(*str) && ((*str < L'°¡' || *str > L'ÆR'))) {
			// ¾ËÆÄºªÀÌ³ª ´Ù¸¥ ¹®ÀÚ°¡ ÀÖÀ¸¸é¼­, ÇÑ±ÛÀÌ ¾Æ´Ñ °æ¿ì
			return 0;
		}

		if (*str >= L'°¡' && *str <= L'ÆR') {
			koreanCount++;
		}

		str++;
	}

	return (koreanCount >= 2);  // ÇÑ±ÛÀÌ µÎ ±ÛÀÚ ÀÌ»óÀÌ¸é 1 ¹İÈ¯, ¾Æ´Ï¸é 0 ¹İÈ¯
}
int is_korean_string1(const wchar_t* str) {
	int koreanCount = 0;

	while (*str) {
		if (iswalpha(*str) && ((*str < L'°¡' || *str > L'ÆR'))) {
			// ¾ËÆÄºªÀÌ³ª ´Ù¸¥ ¹®ÀÚ°¡ ÀÖÀ¸¸é¼­, ÇÑ±ÛÀÌ ¾Æ´Ñ °æ¿ì
			return 0;
		}

		if (*str >= L'°¡' && *str <= L'ÆR') {
			koreanCount++;
		}

		str++;
	}

	return (koreanCount >= 2 && koreanCount < 4);  // ÇÑ±ÛÀÌ µÎ ±ÛÀÚ ÀÌ»óÀÌ¸é 1 ¹İÈ¯, ¾Æ´Ï¸é 0 ¹İÈ¯
}
bool isValidPhoneNumber(const char* phoneNumber) {
	// ÀüÈ­¹øÈ£ÀÇ ±æÀÌ°¡ 11ÀÚ¸®ÀÎÁö È®ÀÎ
	if (strlen(phoneNumber) != 11) {
		return false;
	}

	// ÀüÈ­¹øÈ£ÀÇ Ã³À½ 3ÀÚ¸®°¡ "010"ÀÎÁö È®ÀÎ
	if (strncmp(phoneNumber, "010", 3) != 0) {
		return false;
	}

	// ³ª¸ÓÁö 8ÀÚ¸®°¡ ¼ıÀÚ·Î ÀÌ·ç¾îÁ® ÀÖ´ÂÁö È®ÀÎ
	for (int i = 3; i < 11; ++i) {
		if (!isdigit(phoneNumber[i])) {
			return false;
		}
	}

	// ¸ğµç Á¶°ÇÀ» ¸¸Á·ÇÏ¸é À¯È¿ÇÑ ÀüÈ­¹øÈ£·Î ÆÇ´Ü
	return true;
}
int containsDigit(const char* str) {
	// ¹®ÀÚ¿­À» ¼øÈ¸ÇÏ¸é¼­ ¼ıÀÚ°¡ ÀÖ´ÂÁö È®ÀÎ
	while (*str) {
		if (isdigit(*str)) {
			return 1;  // ¼ıÀÚ°¡ ÀÖÀ¸¸é 1 ¹İÈ¯
		}
		str++;
	}
	return 0;  // ¼ıÀÚ°¡ ¾øÀ¸¸é 0 ¹İÈ¯
}
int inputInt(int min, int max) {
	char input[100];
	int value;
	char extra;

	while (1) {
		printf("ÀÔ·ÂÇÏ¼¼¿ä (%d ~ %d): ", min, max);

		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("ÀÔ·Â ¿À·ù°¡ ¹ß»ıÇß½À´Ï´Ù.\n");
			exit(EXIT_FAILURE);
		}

		// ¹®ÀÚ¿­¿¡ ¿£ÅÍ°¡ Æ÷ÇÔµÇ¾î ÀÖÀ¸¸é Á¦°Å
		size_t len = strlen(input);
		if (len > 0 && input[len - 1] == '\n') {
			input[len - 1] = '\0';
		}

		// ÀÔ·Â ¹ŞÀº ¹®ÀÚ¿­À» Á¤¼ö·Î º¯È¯
		if (sscanf(input, "%d %c", &value, &extra) == 1) {
			if (value >= min && value <= max) {
				break;
			}
			else {
				printf("Àß¸øµÈ ¹üÀ§ÀÇ ÀÔ·ÂÀÔ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇÏ¼¼¿ä.\n");
			}
		}
		else {
			printf("ÀÔ·Â ¿À·ù°¡ ¹ß»ıÇß½À´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇÏ¼¼¿ä.\n");
		}
	}

	return value;
}
void loadFromFile(int* count, Student* student, Timetable* timetable) {
	FILE* file1 = fopen("ÇĞ»ıÀúÀå¸ñ·ÏÆÄÀÏ.txt", "rt");
	if (file1 != NULL) {
		fscanf(file1, "%d", count);
		// ±âº» Á¤º¸ ¹× ½Ã°£Ç¥ Á¤º¸ ÀĞ±â
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

		printf("¼º°øÀûÀ¸·Î ºÒ·¯¿Ô½À´Ï´Ù.\n");
		system("pause");
	}
	else {
		if (*count == 0) {
			printf("»õ·Î¿î »óÅÂ·Î ½ÃÀÛÇÕ´Ï´Ù.\n");
		}
		else {
			printf("ÆÄÀÏ ºÒ·¯¿À±â¿¡ ½ÇÆĞÇß½À´Ï´Ù. ¾Ë ¼ö ¾ø´Â ¿À·ù°¡ ¹ß»ıÇß½À´Ï´Ù.\n");
			printf("»õ·Î¿î »óÅÂ·Î ½ÃÀÛÇÕ´Ï´Ù.\n");
			system("pause");
		}
	}

	fclose(file1);
}
void index() {
	system("mode con cols=300 lines = 500 | title ÇĞ»ı°ü¸®ÇÁ·Î±×·¥");
	printf("====================\n");
	printf("=ÇĞ»ı °ü¸® ÇÁ·Î±×·¥=\n");
	printf("====================\n");
}
void mainmenu() {
	printf("1. ÇĞ»ı Á¤º¸\n");
	printf("2. ±³°ú È°µ¿\n");
	printf("3. ±³°ú ¿Ü È°µ¿\n");
	printf("4. ÇĞ½À ÆíÀÇ Áö¿ø\n");
	printf("5. ±³À° ÇÁ·Î±×·¥\n");
	printf("6. Á¾·á\n");
}
void schoolmenu() {
	printf("1. ¼ºÀû Ãâ·Â\n");
	printf("2. ½Ã°£Ç¥ ÀÔ·Â\n");
	printf("3. ½Ã°£Ç¥ Ãâ·Â\n");
	printf("4. ½Ã°£Ç¥ ¼öÁ¤\n");
	printf("5. ¸ŞÀÎ¸Ş´º·Î µ¹¾Æ°¡±â\n");
}
void notschoolmenu() {
	printf("1. ºÀ»çÈ°µ¿ ¸í´Ü\n");
	printf("2. µ¿¾Æ¸® ¸í´Ü\n");
	printf("3. ¸ŞÀÎ¸Ş´º·Î µ¹¾Æ°¡±â\n");
}
void cleanstudy() {
	printf("1. ÅëÇĞÂ÷·® ¹èÁ¤\n");
	printf("2. ¸é´ã ÀÏÁ¤\n");
	printf("3. Ã»¼Ò ±¸¿ª ÁöÁ¤\n");
	printf("4. ¼öÁØº° ÇĞ½À ¹İ Æí¼º\n");
	printf("5. ¸ŞÀÎ¸Ş´º·Î µ¹¾Æ°¡±â\n");
}
void dong() {
	printf("µî·ÏÇÏ½Ç µ¿¾Æ¸®¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä\n");
	printf("==========µ¿¾Æ¸® ¸ñ·Ï========= \n");
	printf("1.µ¶¼­ºÎ, 2.¿µÈ­ºÎ, 3.»çÁøºÎ\n");
}
void bongsa() {
	printf("µî·ÏÇÏ½Ç ºÀ»çÈ°µ¿À» ÀÔ·ÂÇØÁÖ¼¼¿ä\n");
	printf("==========ºÀ»çÈ°µ¿ ¸ñ·Ï========= \n");
	printf("1. ¾ç·Î¿ø, 2. °í¾Æ¿ø, 3. ¹®È­¼¾ÅÍ\n");
}
void printStudentInfo(Student student) {
	printf("ÇĞ¹ø: %d\n", student.snum);
	printf("ÀÌ¸§: %ls\n", student.sname);
	printf("»ı³â¿ùÀÏ: %d\n", student.birth);
	printf("ÀüÈ­¹øÈ£: %s\n", student.callnumber);
	printf("ÁÖ¼Ò: %c\n", student.adress);
	printf("±¹¾î: %d\n", student.Kor);
	printf("¿µ¾î: %d\n", student.Eng);
	printf("¼öÇĞ: %d\n", student.Math);
	printf("Æò±Õ: %.2f\n", student.Avg);
	printf("ºÀ»çÈ°µ¿: %s\n", student.vms);
	printf("µ¿¾Æ¸®: %s\n", student.dong);
	printf("\n");
}
void addStudent(int* count, Student* student) {
	setlocale(LC_ALL, "");
	char buffer[100];
	wchar_t bufferh[100];
	int readcount;

	printf("\n1. ÇĞ»ı Á¤º¸ ÀÔ·Â\n");
	printf("2. ÇĞ»ı Á¤º¸ Ãâ·Â\n");
	printf("3. ÇĞ»ı Á¤º¸ ¼öÁ¤\n");
	printf("4. ¸ŞÀÎ¸Ş´º·Î µ¹¾Æ°¡±â\n");
	int input = inputInt(1, 4);
	if (input == 1) {
		if (*count == 50) {
			printf("ÀÌ¹Ì 100¸íÀÇ ÇĞ»ıÀÇ Á¤º¸¸¦ ¸ğµÎ Ãß°¡ Çß½À´Ï´Ù.\n");
			printf("´õ ÀÌ»ó Ãß°¡ ÇÒ ¼ö ¾ø½À´Ï´Ù.\n\n");
			system("pause");
		}
		else {
			system("cls");
			printf("===== ÇĞ»ı Á¤º¸ ÀÔ·ÂÇÏ±â [%d / 100] =====\n", *count + 1);
			printf("ÇĞ¹ø (1¹İ 1¹ø 1001, 2¹İ 1¹ø 2001, 3¹İ 1¹ø 3001) : ");
			while (1) {
				int currentnum;
				int result = scanf("%d", &currentnum);
				if (result == 1) {
					if ((currentnum >= 1001 && currentnum <= 1010) ||
						(currentnum >= 2001 && currentnum <= 2010) ||
						(currentnum >= 3001 && currentnum <= 3013)) {

						if (0 == isSnumDuplicate(*count, student, currentnum)) {
							student[*count].snum = currentnum;
							break; // Áßº¹µÇÁö ¾ÊÀº À¯È¿ÇÑ ÇĞ¹øÀÌ ÀÔ·ÂµÊ
						}
						else {
							printf("¿À·ù: ÀÌ¹Ì µî·ÏµÈ ÇĞ¹øÀÔ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇØÁÖ¼¼¿ä.\n");
							printf("ÇĞ¹ø : (1¹İ 1¹ø 1001, 2¹İ 1¹ø 2001, 3¹İ 1¹ø 3001)");
						}
					}
					else {
						printf("¿À·ù: ÇĞ¹ø ¹üÀ§¸¦ ¹ş¾î³µ°Å³ª Àß¸øµÈ Çü½ÄÀÔ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇØÁÖ¼¼¿ä.\n");
						printf("ÇĞ¹ø : (1¹İ 1¹ø 1001, 2¹İ 1¹ø 2001, 3¹İ 1¹ø 3001)");
					}
				}
				else {
					// ¼ıÀÚ°¡ ¾Æ´Ñ °ªÀÌ ÀÔ·ÂµÇ¾úÀ» ¶§ÀÇ Ã³¸®
					printf("¿À·ù: ¼ıÀÚ¸¦ ÀÔ·ÂÇÏ¼¼¿ä.\n");
					printf("ÇĞ¹ø : (1¹İ 1¹ø 1001, 2¹İ 1¹ø 2001, 3¹İ 1¹ø 3001)");
				}

				// ÀÔ·Â ¹öÆÛ ºñ¿ì±â
				while (getchar() != '\n');
			}
			printf("ÀÌ¸§ : ");
			while (1) {
				wint_t c;
				wscanf(L"%ls", student[*count].sname);

				while ((c = getwchar()) != L'\n' && c != WEOF);  // ÀÔ·Â ¹öÆÛ ºñ¿ì±â

				if (is_korean_string(student[*count].sname)) {
					break;
				}
				else {
					printf("¿À·ù: ¿Ã¹Ù¸¥ ÇÑ±Û ÀÌ¸§À» ÀÔ·ÂÇÏ¼¼¿ä.\n");
					printf("ÀÌ¸§ : ");
				}
			}
			printf("»ı³â¿ùÀÏ (19300101 ~ 20231231) : ");
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
						printf("¿À·ù: ¿Ã¹Ù¸¥ ¹üÀ§ÀÇ »ı³â¿ùÀÏÀ» ÀÔ·ÂÇÏ¼¼¿ä.\n");
						printf("»ı³â¿ùÀÏ : (19300101 ~ 20231231)");
					}
				}
				else {
					int c;
					while ((c = getchar()) != '\n' && c != EOF); // ÀÔ·Â ¹öÆÛ ºñ¿ì±â

					printf("¿À·ù: ¼ıÀÚ°¡ ¾Æ´Ñ °ªÀÌ ÀÔ·ÂµÇ¾ú½À´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇÏ¼¼¿ä.\n");
					printf("»ı³â¿ùÀÏ : (19300101 ~ 20231231)");
				}
			}
			printf("ÀüÈ­¹øÈ£ (11ÀÚ¸® ÀüÃ¼ÀÔ·Â) : ");
			while (1) {
				scanf("%s", student[*count].callnumber);

				if (isValidPhoneNumber(student[*count].callnumber)) {
					break;
				}
				else {
					printf("¿À·ù: ¿Ã¹Ù¸¥ ÀüÈ­¹øÈ£ Çü½ÄÀÌ ¾Æ´Õ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇÏ¼¼¿ä.\n");
					printf("ÀüÈ­¹øÈ£ : ");
				}
			}
			while (getchar() != '\n');
			while (1) {
				char buffer[100];  // ÃæºĞÇÑ Å©±âÀÇ ¹®ÀÚ¿­À» ÀúÀåÇÒ ¹öÆÛ
				printf("ÇĞ»ı ÁÖ¼Ò (ex: a, b, c, ...) : ");
				if (scanf("%99s", buffer) == 1) {
					int c;
					// ÀÔ·Â ¹öÆÛ¸¦ ºñ¿ì±â À§ÇØ °³Çà ¹®ÀÚ±îÁö ¸ğµÎ ÀĞ¾î¼­ Ã³¸®
					while ((c = getchar()) != '\n' && c != EOF);

					// ÀÔ·ÂµÈ °ªÀÌ ¾ËÆÄºªÀÌ°í, ¹®ÀÚ¿­ ±æÀÌ°¡ 1ÀÌ¸é Á¾·á
					if (isalpha(buffer[0]) && buffer[1] == '\0') {
						student[*count].adress = buffer[0];
						break;
					}
					else {
						printf("¿À·ù: ¾ËÆÄºª ÇÏ³ª¸¸ ÀÔ·ÂÇÏ¼¼¿ä.\n");
					}
				}
				else {
					int c;
					while ((c = getchar()) != '\n' && c != EOF); // ÀÔ·Â ¹öÆÛ ºñ¿ì±â
					printf("¿À·ù: ¾ËÆÄºª ÇÏ³ª¸¸ ÀÔ·ÂÇÏ¼¼¿ä.\n");
				}
			}
			printf("±¹¾î : ");
			student[*count].Kor = getValidScore();
			printf("¿µ¾î : ");
			student[*count].Eng = getValidScore();
			printf("¼öÇĞ : ");
			student[*count].Math = getValidScore();
			bongsa();
			int vmsChoice = inputInt(1, 3);
			switch (vmsChoice) {
			case 1:
				strcpy(student[*count].vms, "¾ç·Î¿ø");
				break;
			case 2:
				strcpy(student[*count].vms, "°í¾Æ¿ø");
				break;
			case 3:
				strcpy(student[*count].vms, "¹®È­ ¼¾ÅÍ");
				break;
			default:
				printf("¿À·ù: Àß¸øµÈ ¼±ÅÃÀÔ´Ï´Ù.\n");
				break;
			}
			dong();
			int dongChoice = inputInt(1, 3);
			switch (dongChoice) {
			case 1:
				strcpy(student[*count].dong, "µ¶¼­ºÎ");
				break;
			case 2:
				strcpy(student[*count].dong, "»çÁøºÎ");
				break;
			case 3:
				strcpy(student[*count].dong, "¿µÈ­ºÎ");
				break;
			default:
				printf("¿À·ù: Àß¸øµÈ ¼±ÅÃÀÔ´Ï´Ù.\n");
				break;
			}

			student[*count].Avg = (float)(student[*count].Kor + student[*count].Eng + student[*count].Math) / 3.0f;
			(*count)++; // ÇÑ¸í Ãß°¡ÇÒ¶§ ¸¶´Ù 1¾¿ Ãß°¡
			printf("µî·ÏÀÌ ¿Ï·áµÇ¾ú½À´Ï´Ù.\n");
			system("pause");
		}
	}
	else if (input == 2) {
		system("cls");
		printf("===== ÇĞ»ı Á¤º¸ Ãâ·ÂÇÏ±â =====\n");
		printf("1. ÀüÃ¼ Ãâ·ÂÇÏ±â \t 2. ¼±ÅÃ Ãâ·ÂÇÏ±â 3. Ãë¼Ò \n");
		printf("¿øÇÏ´Â ¸Ş´º¸¦ ÀÔ·ÂÇÏ¼¼¿ä : ");
		input = inputInt(1, 3);
		if (input == 1) {
			printAll(*count, student);
		}
		else if (input == 2) {
			printf("Ã£À» ÀÌ¸§À» ÀÔ·Â ÇÏ¼¼¿ä : ");
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
			return i; // ÇØ´ç ÇĞ¹øÀ» °¡Áø ÇĞ»ıÀÇ ÀÎµ¦½º ¹İÈ¯
		}
	}
	return -1; // ÇĞ¹øÀ» Ã£Áö ¸øÇÑ °æ¿ì -1 ¹İÈ¯
}
void modifyStudentInfo(int count, Student* student) {
	while (1) {
		char buffer[100];  // ÃæºĞÇÑ Å©±âÀÇ ¹®ÀÚ¿­À» ÀúÀåÇÒ ¹öÆÛ
		printf("¼öÁ¤ÇÒ ÁÖ¼Ò (ex: a, b, c, ...) : ");
		if (scanf("%99s", buffer) == 1) {
			int c;
			// ÀÔ·Â ¹öÆÛ¸¦ ºñ¿ì±â À§ÇØ °³Çà ¹®ÀÚ±îÁö ¸ğµÎ ÀĞ¾î¼­ Ã³¸®
			while ((c = getchar()) != '\n' && c != EOF);

			// ÀÔ·ÂµÈ °ªÀÌ ¾ËÆÄºªÀÌ°í, ¹®ÀÚ¿­ ±æÀÌ°¡ 1ÀÌ¸é Á¾·á
			if (isalpha(buffer[0]) && buffer[1] == '\0') {
				student->adress = buffer[0];
				break;
			}
			else {
				printf("¿À·ù: ¾ËÆÄºª ÇÏ³ª¸¸ ÀÔ·ÂÇÏ¼¼¿ä.\n");
			}
		}
		else {
			int c;
			while ((c = getchar()) != '\n' && c != EOF); // ÀÔ·Â ¹öÆÛ ºñ¿ì±â
			printf("¿À·ù: ¾ËÆÄºª ÇÏ³ª¸¸ ÀÔ·ÂÇÏ¼¼¿ä.\n");
		}
	}
	while (1) {
		printf("¼öÁ¤ÇÒ ÀüÈ­¹øÈ£ : (11ÀÚ¸® ÀüÃ¼ÀÔ·Â)");
		char number[15];
		scanf("%s", number);

		if (isValidPhoneNumber(number)) {
			strcpy(student->callnumber, number);
			break;
		}
		else {
			printf("¿À·ù: ¿Ã¹Ù¸¥ ÀüÈ­¹øÈ£ Çü½ÄÀÌ ¾Æ´Õ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇÏ¼¼¿ä.\n");
		}
	}
}
void modifyStudentBySnum(int count, Student* students) {
	printf("\n");
	printf("¼öÁ¤ÇÒ ÇĞ»ıÀÇ ÇĞ¹øÀ» ÀÔ·ÂÇÏ¼¼¿ä: ");

	int targetSnum = inputInt(1001, 3010);

	int studentIndex = findStudentIndexBySnum(count, students, targetSnum);

	if (studentIndex != -1) {
		// ÇĞ»ıÀ» Ã£¾ÒÀ» °æ¿ì ÇØ´ç ÇĞ»ı Á¤º¸ Ãâ·Â ¹× ¼öÁ¤
		printf("¼öÁ¤ Àü ÇĞ»ı Á¤º¸:\n");
		printStudentInfo(students[studentIndex]);

		// ÇĞ»ı Á¤º¸ ¼öÁ¤ ÇÔ¼ö È£Ãâ
		modifyStudentInfo(count, &students[studentIndex]);

		printf("¼öÁ¤ ÈÄ ÇĞ»ı Á¤º¸:\n");
		printStudentInfo(students[studentIndex]);
		system("pause");
	}
	else {
		printf("ÀÔ·ÂÇÑ ÇĞ¹ø°ú ÀÏÄ¡ÇÏ´Â ÇĞ»ıÀ» Ã£À» ¼ö ¾ø½À´Ï´Ù.\n");
		system("pause");
	}
}
void printAll(int count, Student* student)
{
	printf("===== ÇĞ»ı Á¤º¸ ÀüÃ¼ Ãâ·ÂÇÏ±â =====\n");
	for (int i = 0; i < count; i++)
	{
		printf("ÇĞ»ı [%d/100]\n", i + 1);
		printf("ÇĞ¹ø : %d ÀÌ¸§ : %ls »ı³â¿ùÀÏ : %d.%d.%d ÁÖ¼Ò : %c ÀüÈ­¹øÈ£ : %.3s-%.4s-%.4s \n\n",
			student[i].snum, student[i].sname, (student[i].birth / 10000), (student[i].birth % 10000) / 100, student[i].birth % 100, student[i].adress, student[i].callnumber,
			student[i].callnumber + 3, student[i].callnumber + 7);
	}
	if (count == 0)
	{
		printf("µî·ÏµÈ ÇĞ»ı Á¤º¸°¡ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.\n");
	}
}
void printName(int count, Student* student, wchar_t name[20])
{
	printf("===== ÇĞ»ı Á¤º¸ ¼±ÅÃ Ãâ·ÂÇÏ±â(%ls) =====\n", name);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(name, student[i].sname) == 0)
		{
			printf("ÇĞ¹ø : %d ÀÌ¸§ : %ls »ı³â¿ùÀÏ : %d.%d.%d ÁÖ¼Ò : %c ÀüÈ­¹øÈ£ : %.3s-%.4s-%.4s \t \n\n",
				student[i].snum, student[i].sname, (student[i].birth / 10000), (student[i].birth % 10000) / 100, student[i].birth % 100, student[i].adress, student[i].callnumber,
				student[i].callnumber + 3, student[i].callnumber + 7);
			return;
		}
	}
	printf("Ã£´Â ÇĞ»ıÀÌ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.\n");
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
	printf("\n»èÁ¦ÇÒ ÇĞ»ıÀÇ ÇĞ¹øÀ» ÀÔ·ÂÇÏ¼¼¿ä: ");
	int targetSnum = inputInt(0, 9999);

	int index = -1;



	// ÀÔ·Â¹ŞÀº ÇĞ¹ø°ú ÀÏÄ¡ÇÏ´Â ÇĞ»ıÀÇ ÀÎµ¦½º Ã£±â
	for (int i = 0; i < *count; i++) {
		if (students[i].snum == targetSnum) {
			index = i;
			break;
		}
	}

	// ÀÏÄ¡ÇÏ´Â ÇĞ¹øÀ» Ã£¾ÒÀ» °æ¿ì »èÁ¦ ÁøÇà
	if (index != -1) {
		// »èÁ¦µÈ ÇĞ»ı µÚ¿¡ ÀÖ´Â ÇĞ»ıµéÀ» ¾ÕÀ¸·Î ÀÌµ¿
		memmove(&students[index], &students[index + 1], (*count - index - 1) * sizeof(Student));
		(*count)--;
		printf("ÇĞ»ıÀÌ »èÁ¦µÇ¾ú½À´Ï´Ù.\n");
	}
	else {
		printf("ÀÔ·ÂÇÑ ÇĞ¹ø°ú ÀÏÄ¡ÇÏ´Â ÇĞ»ıÀ» Ã£À» ¼ö ¾ø½À´Ï´Ù.\n");
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
	printf("»èÁ¦ÇÒ ÇĞ»ıÀÇ ÀÌ¸§À» ÀÔ·ÂÇÏ¼¼¿ä: ");
	wchar_t targetSname[50] = { NULL };
	wscanf(L"%ls", targetSname);

	int index = -1;

	// ÀÔ·Â¹ŞÀº ÀÌ¸§°ú ÀÏÄ¡ÇÏ´Â ÇĞ»ıÀÇ ÀÎµ¦½º Ã£±â
	for (int i = 0; i < *count; i++) {
		if (strcmp(students[i].sname, targetSname) == 0) {
			index = i;
			break;
		}
	}

	// ÀÏÄ¡ÇÏ´Â ÀÌ¸§À» Ã£¾ÒÀ» °æ¿ì »èÁ¦ ÁøÇà
	if (index != -1) {
		// »èÁ¦µÈ ÇĞ»ı µÚ¿¡ ÀÖ´Â ÇĞ»ıµéÀ» ¾ÕÀ¸·Î ÀÌµ¿
		memmove(&students[index], &students[index + 1], (*count - index - 1) * sizeof(Student));
		(*count)--;
		printf("ÇĞ»ıÀÌ »èÁ¦µÇ¾ú½À´Ï´Ù.\n");
	}
	else {
		printf("ÀÔ·ÂÇÑ ÀÌ¸§°ú ÀÏÄ¡ÇÏ´Â ÇĞ»ıÀ» Ã£À» ¼ö ¾ø½À´Ï´Ù.\n");
	}
}
void deleteStudent(int* count, Student* students) {
	printf("===== ÇĞ»ı »èÁ¦ÇÏ±â =====\n");
	printf("1. ÇĞ¹øÀ¸·Î »èÁ¦ÇÏ±â\n");
	printf("2. ÀÌ¸§À¸·Î »èÁ¦ÇÏ±â\n");
	printf("3. Ãë¼Ò\n");

	int input = inputInt(1, 3);

	if (input == 1) {
		// ÇĞ¹øÀ¸·Î »èÁ¦ ÇÔ¼ö È£Ãâ
		deleteStudentBySnum(count, students);
	}
	else if (input == 2) {
		// ÀÌ¸§À¸·Î »èÁ¦ ÇÔ¼ö È£Ãâ
		deleteStudentBySname(count, students);
	}
	else if (input == 3) {
		printf("Ãë¼ÒµÇ¾ú½À´Ï´Ù.\n");
	}

	// ¹è¿­À» Á¤¸®ÇÏ´Â ·ÎÁ÷ Ãß°¡
}
void printscoremenu(int count, Student* student) {
	system("cls");
	printf("===== ¼ºÀû Á¤º¸ Ãâ·ÂÇÏ±â =====\n");
	printf("1. ÀüÃ¼ Ãâ·ÂÇÏ±â \t 2. ¼±ÅÃ Ãâ·ÂÇÏ±â \n");
	printf("¿øÇÏ´Â ¸Ş´º¸¦ ÀÔ·ÂÇÏ¼¼¿ä : ");
	int input = inputInt(1, 2);
	if (input == 1) {
		printscoreAll(count, student); // ¿À¸§Â÷¼ø ÇÊ¿ä
		system("pause");
	}
	else {
		printf("Ã£À» ÀÌ¸§À» ÀÔ·Â ÇÏ¼¼¿ä : ");
		wchar_t name[20];
		wscanf(L"%ls", name);
		printscore(count, student, name);
		system("pause");
	}
}
void printscoreAll(int count, Student* student)
{
	printf("===== ÇĞ»ı Á¤º¸ ÀüÃ¼ Ãâ·ÂÇÏ±â =====\n");
	for (int i = 0; i < count; i++)
	{
		printf("ÇĞ»ı [%d/30]\n", i + 1);
		printf("ÇĞ¹ø : %d ÀÌ¸§ : %ls ±¹¾î : %d \t ¿µ¾î : %d \t ¼öÇĞ : %d \t [Æò±Õ Á¡¼ö : %.1f] \n\n",
			student[i].snum, student[i].sname, student[i].Kor, student[i].Eng, student[i].Math, student[i].Avg);
	}
	if (count == 0)
	{
		printf("µî·ÏµÈ ÇĞ»ı Á¤º¸°¡ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.\n");
		system("pause");
	}
}
void printscore(int count, Student* student, wchar_t name[20])
{
	printf("===== ÇĞ»ı Á¤º¸ ¼±ÅÃ Ãâ·ÂÇÏ±â(%ls) =====\n", name);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(name, student[i].sname) == 0)
		{
			printf("ÇĞ¹ø : %d ÀÌ¸§ : %ls ±¹¾î : %d \t ¿µ¾î : %d \t ¼öÇĞ : %d \t [Æò±Õ Á¡¼ö : %.1f] \n\n",
				student[i].snum, student[i].sname, student[i].Kor, student[i].Eng, student[i].Math, student[i].Avg);
			return;
		}
	}
	printf("Ã£´Â ÇĞ»ıÀÌ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.\n");
	system("pause");
}
void printClubAndVolunteerMenu(int count, Student* student) {
	printf("===== ÇĞ»ı Á¤º¸ Ãâ·ÂÇÏ±â =====\n");
	printf("1. µ¿¾Æ¸® Ãâ·Â\n2. µ¿¾Æ¸® ¿¹»ê ÃÊ±âÈ­\n");
	printf("3. µ¿¾Æ¸® ¿¹»ê ºĞ¹è \n4. µ¿¾Æ¸® ¿¹»ê Ãâ·Â\n5. ¸ŞÀÎ¸Ş´º·Î µ¹¾Æ°¡±â\n");
	printf("¿øÇÏ´Â ¸Ş´º¸¦ ÀÔ·ÂÇÏ¼¼¿ä : ");
	int input = inputInt(1, 6);
	if (input == 1) {
		printf("1. µ¿¾Æ¸® ¸í´Ü ÀüÃ¼ Ãâ·Â\n");
		printf("2. µ¿¾Æ¸® ¸í´Ü ¼±ÅÃ Ãâ·Â\n");
		int input = inputInt(1, 2);
		if (input == 1) {
			printAllClubs(count, student);
		}
		else {
			char dong[20];
			printf("µ¿¾Æ¸®¸íÀ» ÀÔ·ÂÇÏ¼¼¿ä: \n 1 : µ¶¼­ºÎ, 2: ¿µÈ­ºÎ, 3 : »çÁøºÎ");
			input = inputInt(1, 3);
			switch (input) {
			case 1:
				strcpy(dong, "µ¶¼­ºÎ");
				break;
			case 2:
				strcpy(dong, "¿µÈ­ºÎ");
				break;
			case 3:
				strcpy(dong, "»çÁøºÎ");
				break;
			default:
				printf("Àß¸øµÈ ¼±ÅÃÀÔ´Ï´Ù.\n");
				return 1;
			}
			printClubMembers(count, student, dong);
		}
	}
	else if (input == 2) {
		initializeClubBudgets(student, count);
	}
	else if (input == 3) {
		// »ç¿ëÀÚ·ÎºÎÅÍ ¿¹»ê ÃÑ¾× ÀÔ·Â
		printf("µ¿¾Æ¸® ¿¹»êÀÇ ÃÑ¾×À» ÀÔ·ÂÇÏ¼¼¿ä: ");
		int totalBudget = inputInt(0, 1000000);

		// µ¿¾Æ¸® ¿¹»ê ºĞ¹è ÇÔ¼ö È£Ãâ
		distributeClubBudget(count, student, totalBudget, "µ¶¼­ºÎ");
		distributeClubBudget(count, student, totalBudget, "¿µÈ­ºÎ");
		distributeClubBudget(count, student, totalBudget, "»çÁøºÎ");
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
	printf("=== µ¿¾Æ¸® ÀüÃ¼ ¸í´Ü ===\n");

	for (int i = 0; i < count; ++i) {
		if (strcmp(student[i].dong, dong) == 0) {
			printf("ÇĞ¹ø: %d, ÀÌ¸§: %ls, µ¿¾Æ¸®: %s\n", student[i].snum, student[i].sname, student[i].dong);
		}
	}

	printf("=======================\n");
}
void printAllClubs(int count, Student* student) {
	printf("=== µ¿¾Æ¸® ÀüÃ¼ ¸í´Ü ===\n");

	// Áßº¹À» ÇÇÇÏ±â À§ÇÑ ¹è¿­
	char uniqueClubs[MAX_STUDENTS][20];
	int uniqueCount = 0;

	// µ¿¾Æ¸® ¸ñ·Ï ¼öÁı
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

	// °¢ µ¿¾Æ¸®º°·Î Ãâ·Â
	for (int i = 0; i < uniqueCount; ++i) {
		printf("=== µ¿¾Æ¸®¸í: %s ===\n", uniqueClubs[i]);
		for (int j = 0; j < count; ++j) {
			if (strcmp(student[j].dong, uniqueClubs[i]) == 0) {
				printf("ÇĞ¹ø: %d, ÀÌ¸§: %ls, µ¿¾Æ¸®: %s\n", student[j].snum, student[j].sname, student[j].dong);
			}
		}
		printf("=======================\n");
	}

	printf("=======================\n");
}
void initializeClubBudgets(Student* students, int count) {
	for (int i = 0; i < count; i++) {

		students[i].clubBudget = 0;    // µ¿¾Æ¸® ¿¹»ê ÃÊ±âÈ­
	}
}
int isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// °¢ ¿ùÀÇ ³¯Â¥ ¼ö ¹İ¿µ 
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
// ³¯Â¥ ÀÔ·Â ÇÔ¼ö
int inputDate(int* year, int* month, int* day) {
	printf("¸é´ã ½ÃÀÛ ³¯Â¥ ÀÔ·Â (¿¹: 2024. 01. 01.): ");
	int inputResult = scanf("%04d. %02d. %02d.", year, month, day);
	// ³¯Â¥ ÀÔ·ÂÀÌ Á¤¼ö°¡ ¾Æ´Ï°Å³ª, ³¯Â¥°¡ Àß¸ø ÀÔ·ÂµÈ °æ¿ì¿¡ ¿À·ù ¸Ş½ÃÁö Ãâ·Â
	if (inputResult != 3 || *year <= 0 || *month <= 0 || *day <= 0 || *month > 12 || *day > daysInMonth(*year, *month)) {
		printf("\"³¯Â¥ Á¤º¸ ÀÔ·Â ¿À·ù\"\n");
		// ½ÇÆĞÇÑ ÀÔ·Â°ª ¹«½Ã
		while (getchar() != '\n');
		printf("\n");
		return 0; // ³¯Â¥ ÀÔ·ÂÀ» ½ÇÆĞÇÏ¸é ´Ù½Ã ÀÔ·Â¹Ş´Â ¹®±¸·Î ¹İº¹
	}
	else {
		return 1;  // ¼º°ø
	}
}
// ¸é´ã ½ÃÀÛ ½Ã°£À» ÀÔ·Â¹Ş´Â ÇÔ¼ö
int inputMeetingHour(int* meetingHour) {
	printf("¸é´ã ½ÃÀÛ ½Ã°£ ÀÔ·Â (¿¹: 9 ~ 16): ");
	int inputResult = scanf("%d", meetingHour);

	// ÀÔ·Â°ªÀÌ Á¤¼ö°¡ ¾Æ´Ï°Å³ª, ½Ã°£ ¹üÀ§¸¦ ¹ş¾î³­ °æ¿ì¸¦ Ã³¸®
	if (inputResult != 1 || *meetingHour < 9 || *meetingHour > 16) {
		printf("\"½Ã°£ Á¤º¸ ÀÔ·Â ¿À·ù\"\n");
		// ½ÇÆĞÇÑ ÀÔ·Â°ª ¹«½Ã
		while (getchar() != '\n');
		printf("\n");
		return 0;

	}
	else {
		return 1;
	}
}
// ¿äÀÏ °è»ê ÇÔ¼ö (0: Åä¿äÀÏ, 1: ÀÏ¿äÀÏ, ..., 6: ±İ¿äÀÏ »êÃâ)
int day_of_week(int y, int m, int d) {
	static int t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
// ºÒ°¡´ÉÇÑ ¿äÀÏÀ» ÀÔ·Â¹Ş´Â ÇÔ¼ö
// ¿äÀÏ ¹®ÀÚ¿­À» ¼ıÀÚ·Î º¯È¯ÇÏ´Â ÇÔ¼ö
int weekdayStringToNumber(const char* weekdayStr) {
	int dayNumber = -1; // ±âº»ÀûÀ¸·Î -1·Î ÃÊ±âÈ­ÇÏ¿© Àß¸øµÈ ÀÔ·ÂÀ» Ã³¸®

	// ¿äÀÏ ¹®ÀÚ¿­À» ºñ±³ÇÏ¿© ÇØ´çÇÏ´Â ¿äÀÏÀÇ ¼ıÀÚ¸¦ ¹İÈ¯
	if (strcmp(weekdayStr, "ÀÏ") == 0) {
		dayNumber = 0;
	}
	else if (strcmp(weekdayStr, "¿ù") == 0) {
		dayNumber = 1;
	}
	else if (strcmp(weekdayStr, "È­") == 0) {
		dayNumber = 2;
	}
	else if (strcmp(weekdayStr, "¼ö") == 0) {
		dayNumber = 3;
	}
	else if (strcmp(weekdayStr, "¸ñ") == 0) {
		dayNumber = 4;
	}
	else if (strcmp(weekdayStr, "±İ") == 0) {
		dayNumber = 5;
	}
	else if (strcmp(weekdayStr, "Åä") == 0) {
		dayNumber = 6;
	}
	else if (strcmp(weekdayStr, "¾øÀ½") == 0) {
		dayNumber = 7;
	}

	return dayNumber; // º¯È¯µÈ ¿äÀÏ ¼ıÀÚ ¹İÈ¯
}
// ºÒ°¡´ÉÇÑ ¿äÀÏÀ» ÀÔ·Â¹Ş´Â ÇÔ¼ö
int inputExcludeWeekday(int* excludeWeekday, int* excludeWeekday1) {
	printf("¸é´ãÀÌ ºÒ°¡´ÉÇÑ ¿äÀÏ ÀÔ·Â (¿ù¿äÀÏ: ¿ù, ..., ±İ¿äÀÏ: ±İ, ¾øÀ¸¸é ¾øÀ½): ");
	char weekdayStr[20]; // ÃÖ´ë ¿äÀÏ ¹®ÀÚ¿­ ±æÀÌ´Â 3 (ex: ¿ù)
	int inputResult = scanf("%7s", weekdayStr);
	int con = 0;

	// ÀÔ·Â°ªÀÌ ¹®ÀÚ¿­ÀÌ ¾Æ´Ï°Å³ª, ¿äÀÏ ¹®ÀÚ¿­ÀÌ ¾Æ´Ñ °æ¿ì¸¦ Ã³¸®
	if (inputResult != 1 || getchar() != '\n' || weekdayStringToNumber(weekdayStr) == -1) {
		printf("\"¿äÀÏ Á¤º¸ ÀÔ·Â ¿À·ù\"\n");
		// ½ÇÆĞÇÑ ÀÔ·Â°ª ¹«½Ã
		while (getchar() != '\n');
		printf("\n");
		return 0;
	}
	else if (weekdayStringToNumber(weekdayStr) == 7) {
		*excludeWeekday = weekdayStringToNumber(weekdayStr);
		return 1;
	}
	else {
		*excludeWeekday = weekdayStringToNumber(weekdayStr); // ¿äÀÏ ¹®ÀÚ¿­À» ¼ıÀÚ·Î º¯È¯ÇÏ¿© ÀúÀå
		con += 1;
	}
	if (con = 1) {
		printf("¸é´ãÀÌ ºÒ°¡´ÉÇÑ ¿äÀÏ ÀÔ·Â (¿ù¿äÀÏ: ¿ù, ..., ±İ¿äÀÏ: ±İ): ");
		int inputResult = scanf("%7s", weekdayStr);
		if (inputResult != 1 || getchar() != '\n' || weekdayStringToNumber(weekdayStr) == -1) {
			printf("\"¿äÀÏ Á¤º¸ ÀÔ·Â ¿À·ù\"\n");
			// ½ÇÆĞÇÑ ÀÔ·Â°ª ¹«½Ã
			while (getchar() != '\n');
			printf("\n");
			return 0;
		}
		else if (weekdayStringToNumber(weekdayStr) == 7) {
			return 1;
		}
		else {
			*excludeWeekday1 = weekdayStringToNumber(weekdayStr); // ¿äÀÏ ¹®ÀÚ¿­À» ¼ıÀÚ·Î º¯È¯ÇÏ¿© ÀúÀå
			return 1;
		}
	}
}
// ºÒ°¡´ÉÇÑ ³¯Â¥¸¦ ÀÔ·Â¹Ş´Â ÇÔ¼ö
int inputExcludeDate(int* excludeYear, int* excludeMonth, int* excludeDay) {
	printf("¸é´ãÀÌ ºÒ°¡´ÉÇÑ ³¯Â¥ ÀÔ·Â (¿¹: 2024. 01. 01.): ");
	int inputResult = scanf("%d. %d. %d.", excludeYear, excludeMonth, excludeDay);

	// ÀÔ·Â°ªÀÌ Á¤¼ö°¡ ¾Æ´Ï°Å³ª, ³¯Â¥°¡ Àß¸ø ÀÔ·ÂµÈ °æ¿ì¿¡ ¿À·ù ¸Ş½ÃÁö Ãâ·Â
	if (inputResult != 3 || *excludeYear <= 0 || *excludeMonth <= 0 || *excludeDay <= 0 || *excludeMonth > 12 || *excludeDay > daysInMonth(*excludeYear, *excludeMonth)) {
		printf("\"³¯Â¥ Á¤º¸ ÀÔ·Â ¿À·ù\"\n");
		// ½ÇÆĞÇÑ ÀÔ·Â°ª ¹«½Ã
		while (getchar() != '\n');
		printf("\n");
		return 0; // ³¯Â¥ ÀÔ·ÂÀ» ½ÇÆĞÇÏ¸é ´Ù½Ã ÀÔ·Â¹Ş´Â ¹®±¸·Î ¹İº¹
	}
	else {
		return 1;  // ¼º°ø
	}
}
// ·£´ıÀ¸·Î ¹è¿­À» ¼¯´Â ÇÔ¼ö
void shuffleArray(int array[], int size) {
	srand(time(NULL));
	for (int i = size - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}
// ÀÏÁ¤ »ı¼º ÇÔ¼ö
void generateClassMeetingSchedule(int selectedClass, int classes[3][10], int startYear, int startMonth, int startDay, int meetingHour, int excludeWeekday, int excludeWeekday1, int excludeYear, int excludeMonth, int excludeDay, Student* student, int* count) {
	MeetingSchedule schedule[10];

	// ÇĞ»ı 10¸í ¹èÄ¡
	int studentOrder[10];
	for (int i = 0; i < 10; ++i) {
		studentOrder[i] = i;
	}
	shuffleArray(studentOrder, 10); // ÇĞ»ı ¹è¿­ ·£´ı

	int currentYear = startYear;
	int currentMonth = startMonth;
	int currentDay = startDay;
	int currentHour = meetingHour;

	for (int i = 0; i < 10; ++i) {
		int studentIndex = studentOrder[i];

		// ¸é´ã ºÒ°¡´ÉÇÑ ¿äÀÏ ¶Ç´Â ³¯Â¥ÀÎ °æ¿ì ´ÙÀ½ ³¯·Î Á¶Á¤
		while (day_of_week(currentYear, currentMonth, currentDay) == excludeWeekday || day_of_week(currentYear, currentMonth, currentDay) == excludeWeekday1 ||
			(currentYear == excludeYear && currentMonth == excludeMonth && currentDay == excludeDay) ||
			day_of_week(currentYear, currentMonth, currentDay) == 0 || // Åä¿äÀÏ
			day_of_week(currentYear, currentMonth, currentDay) == 6) { // ÀÏ¿äÀÏ

			currentDay += 1;
			// ÇØ´ç ¿ùÀÇ ÀÏ¼ö¸¦ ÃÊ°úÇÏ¸é ÇÑ ´Ş Ãß°¡ÇÏ°í 1ÀÏ·Î ÁöÁ¤
			if (currentDay > daysInMonth(currentYear, currentMonth)) {
				currentDay = 1;
				currentMonth += 1;
				// ¿ù ¼ö°¡ 12¿ùÀ» ÃÊ°úÇÏ¸é ÇÑ ¿¬µµ¸¦ Ãß°¡ÇÏ°í 1¿ù·Î ÁöÁ¤ 
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

		// ½Ã°£ ¹èÁ¤ ÈÄ ÇÏ·ç 2½Ã°£ ÃÊ°úÇÏ¸é ´ÙÀ½³¯·Î ÁöÁ¤
		if (currentHour >= meetingHour + 2) {
			currentHour = meetingHour;
			currentDay += 1;

			// ³¯Â¥ ¹èÁ¤ ÈÄ °¢ ¿ùÀÇ ¸¶Áö¸·³¯ ÃÊ°úÇÏ¸é ´ÙÀ½´Ş·Î ÁöÁ¤
			if (currentDay > daysInMonth(currentYear, currentMonth)) {
				currentDay = 1;
				currentMonth += 1;

				// 12¿ùÀ» ÃÊ°úÇÏ¸é ´ÙÀ½ ¿¬µµ·Î ÁöÁ¤
				if (currentMonth > 12) {
					currentMonth = 1;
					currentYear += 1;
				}
			}
		}
	}
	// ¸é´ãÀÏÁ¤ (°á°ú) Ãâ·Â
	printf("%d¹İ ¸é´ã ÀÏÁ¤\n", selectedClass);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < count; j++) {
			if (schedule[i].snum == student[j].snum) {
				printf("%04d. %02d. %02d. %s %02d½Ã %04d %ls ÇĞ»ı\n", schedule[i].year, schedule[i].month, schedule[i].day,day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 1 ? "¿ù" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 2 ? "È­" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 3 ? "¼ö" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 4 ? "¸ñ" : day_of_week(schedule[i].year, schedule[i].month, schedule[i].day) == 5 ? "±İ" : "Åä", schedule[i].hour, schedule[i].snum, student[j].sname);
			}
		}

	}
}
// ¹İ ÀÔ·Â ÇÔ¼ö
int inputClass(int* selectedClass) {
	printf("¸é´ã ÀÏÁ¤ Ãâ·Â (1¹İ: 1, 2¹İ: 2, 3¹İ: 3): ");
	int inputResult = scanf("%d", selectedClass);

	// ¹İ ÀÔ·ÂÀÌ Á¤¼ö°¡ ¾Æ´Ï°Å³ª, ¹İ ¹üÀ§°¡ Àß¸øµÈ °æ¿ì¿¡´Â ¿À·ù ¸Ş½ÃÁö Ãâ·Â
	if (inputResult != 1 || *selectedClass < 1 || *selectedClass > 3 || getchar() != '\n') {
		printf("\"¹İ Á¤º¸ ÀÔ·Â ¿À·ù\"\n");
		// ½ÇÆĞÇÑ ÀÔ·Â°ª ¹«½Ã
		while (getchar() != '\n');
		printf("\n");
		return 0;  // ½ÇÆĞ
	}
	else {
		return 1;  // ¼º°ø
	}
}
int checkBirth(const char* birth)//0~9¸¸ µé¾î°¡¾ß ÇÔ
{
	//19890430, 20020430
	if (birth[0] == '0') //00090430
	{
		return 0; //Á¤»ó ¾Æ´ÔÀ» ÀÇ¹ÌÇÔ
	}
	for (int i = 0; i < 9; i++)
	{
		if (birth[i] < '0' || birth[i] >'9') //0ºÎÅÍ 9°¡ ¾Æ´Ñ °æ¿ì
		{
			return 0;
		}
	}
	return 1; //Á¤»óÀÓÀ» ÀÇ¹ÌÇÔ

} // »ı³â¿ùÀÏ Ã¼Å©
int checkcall(const char* callnumber)
{
	if (callnumber[0] != '0' || callnumber[1] != 1)
	{
		return 0;
	}
	for (int i = 2; i < 11; i++)
	{
		if (callnumber[i] < '0' || callnumber[i] >'9') //0ºÎÅÍ 9°¡ ¾Æ´Ñ °æ¿ì
		{
			return 0;
		}
	}
	return 1; //Á¤»óÀÓÀ» ÀÇ¹ÌÇÔ
} // ÀüÈ­¹øÈ£ Ã¼Å©

