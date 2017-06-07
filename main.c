#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef enum Actions {
	EXIT,
	TEST,
	VIEW,
	ADD,
	DELETE,
	MENU
} Actions_t;

void view_all();

void menu()
{
	printf("\n%d. Тестирование базы",TEST);
	printf("\n%d. Просмотр содержимого базы",VIEW);
	printf("\n%d. Добавить в базу",ADD);
	printf("\n%d. Удалить из базы",DELETE);
	printf("\n%d. Выход",EXIT);
	printf("\nВаш выбор: ");
}

void help()
{
	printf("USE: --fout <FILE_NAME> for save output in file FILE_NAME");
}

void create_student()
{
	Student_t *student = malloc(sizeof(Student_t));
	int i = 0;
	char ch;
	//while(getchar() == '\n');

	printf("FIO: ");
	for (; (ch = getchar()) != '\n'; i++)
		student->fio[i] = ch;
	student->fio[i] = '\0';
	printf("Direct study: ");
	scanf("%s",student->direct);
	printf("Group: ");
	scanf("%s", student->group); getchar();
	printf("Form: ");
	student->form = (char) getchar(); getchar();
	printf("Money: ");
	student->money = (char) getchar(); getchar();
	printf("House: ");
	student->house = (char) getchar(); getchar();

	student->next = student;
	student->prev = student;

	add_to_list(student);
	view_all();
}

void view_all()
{
	Student_t *h = head;
	printf("\n");
	printf(",================================,============,=======,======,=======,=======,\n");
	printf("|               FIO              |   Direct   | Group | Form | Money | House |\n");
	printf("|================================|============|=======|======|=======|=======|\n");
	if (h!= NULL) {
		printf("| %30.30s | %10.10s | %5.5s | %4c | %5c | %5c |\n",h->fio,h->direct,h->group,h->form,h->money,h->house);
		for (Student_t *s = h->next; s != h; s = s->next) {
			printf("|--------------------------------|------------|-------|------|-------|-------|\n");
			printf("| %30.30s | %10.10s | %5.5s | %4c | %5c | %5c |\n",s->fio,s->direct,s->group,s->form,s->money,s->house);
		}
	}
	printf("`================================`============`=======`======`=======`=======`\n");
}

int main(int argc, char **argv)
{
		Actions_t choice = MENU;
		FILE *fout = stdout;

		for (int i = 1; i < argc; i++) {
			if ((strcmp(argv[i],"-h") == 0) ||
					(strcmp(argv[i],"--help") == 0) ||
					(strcmp(argv[i],"-?") == 0)) {
				help();
				return 0;
			} else if (( (strcmp(argv[i],"--fout")) == 0) && argc >= i+1) {
				if ((fout = fopen(argv[i+1],"a+")) == NULL) {
					printf("Don't open file %s",argv[i+1]);
					return 1;
				}
			}
		}

		list_init(fout);

    while(choice != EXIT)
    {
				char ch[2] = {'\0'};
				menu();
        //scanf("%d",&choice);
				*ch = getchar(); getchar();
				choice = (Actions_t) atoi(ch);
        switch(choice)
        {
        case TEST:
            //test();
            break;
				case VIEW: view_all(); break;
				case ADD:	create_student();	break;
        default: break;
        }
    }
		save_list();

  	return 0;
}
