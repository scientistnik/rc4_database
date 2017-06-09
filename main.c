#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef enum Actions {
	EXIT,
	TEST,
	VIEW,
	VIEW_ONE,
	FOUND,
	ADD,
	DELETE,
	MENU
} Actions_t;

void view_all(void);
void menu(void);
Actions_t input_choice(void);
void help(void);
void create_student(void);
void view_one(void);
void found(void);

FILE *fout;

void menu()
{
	printf("\n%d. Тестирование базы",TEST);
	printf("\n%d. Просмотр содержимого базы",VIEW);
	printf("\n%d. Постраничный просморт",VIEW_ONE);
	printf("\n%d. Найти",FOUND);
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

void view_one()
{
	Actions_t choice = MENU;
	Student_t *c = head;

	while(choice != EXIT) {
		printf("\nFIO: \t\t%s\n",c->fio);
		printf("Direct: \t\t%s\n",c->direct);
		printf("Group: \t\t%s\n",c->group);
		printf("Form: \t\t%c\n",c->form);
		printf("Money: \t\t%c\n",c->money);
		printf("House: \t\t%c\n",c->house);
		
		printf("\n1. Следующий\n");
		printf("2. Предыдущий\n");
		printf("3. Удалить\n");
		printf("%d. Выход в Меню\n",MENU);
		printf("Your choice: ");
		choice = input_choice();

		switch(choice) {
			case 1: c = c->next; break;
			case 2: c = c->prev; break;
			case 3: 
				c = c->next; 
				delete_from_list(c->prev); 
				break;
			default: break;
		}
	}
}

void found()
{
	int choice = 1;
	char buf[STRING_FIELD_SIZE] = {'\0'};
	Student_t *std = NULL;

	while(choice != 0) {
		printf("\nПо какому критерию искать?\n");
		printf("1. FIO\n");
		printf("2. Direct\n");
		printf("3. Group\n");
		printf("4. Form\n");
		printf("5. Money\n");
		printf("6. House\n");
		printf("0. EXIT\n");
		printf("Ваш выбор: ");

		choice = input_choice();

		if (choice != 0) {
			printf("Что искать? ");
			scanf("%s",buf);
		}
		switch(choice) {
			case 1: std = find_by_fio(buf,NULL);
			case 2: std = find_by_direct(buf,NULL);
			case 3: std = find_by_group(buf,NULL);
			case 4: std = find_by_form(buf[0],NULL);
			case 5: std = find_by_money(buf[0],NULL);
			case 6: std = find_by_house(buf[0],NULL);
			default: break;
		}

		if (std != NULL) {
			fprintf(fout,"\nFIO: \t\t%s\n",std->fio);
			fprintf(fout,"Direct: \t\t%s\n",std->direct);
			fprintf(fout,"Group: \t\t%s\n",std->group);
			fprintf(fout,"Form: \t\t%c\n",std->form);
			fprintf(fout,"Money: \t\t%c\n",std->money);
			fprintf(fout,"House: \t\t%c\n",std->house);
			std = NULL;
		}
	}
}

Actions_t input_choice()
{
	char ch[2] = {'\0'};
	*ch = getchar(); getchar();
	return (Actions_t) atoi(ch);
}

int main(int argc, char **argv)
{
		Actions_t choice = MENU;
		FILE *fout1 = stdout;

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
				menu();
				choice = input_choice();
        switch(choice)
        {
        case TEST:
            //test();
            break;
				case VIEW: view_all(); break;
				case VIEW_ONE: view_one(); break;
				case FOUND: found(); break;
				case ADD:	create_student();	break;
        default: break;
        }
    }
		save_list();

  	return 0;
}
