#ifndef __LIST_H__
#define __LIST_H__

#define STRING_FIELD_SIZE 50

typedef struct Student {
	char fio[STRING_FIELD_SIZE];
	char direct[STRING_FIELD_SIZE];
	char group[STRING_FIELD_SIZE];
	char form;
	char money;
	char house;
	struct Student *next;
	struct Student *prev;
} Student_t;

extern Student_t *head;

void list_init(FILE*);
void add_to_list(Student_t *new);
void save_list();
void delete_from_list(Student_t *del);
int student_eq(const Student_t *a, const Student_t *b);
Student_t* find_by_fio(char *fio, Student_t *h);
Student_t* find_by_direct(char *direct, Student_t *h);
Student_t* find_by_group(char *group, Student_t *h);
Student_t* find_by_form(char form, Student_t *h);
Student_t* find_by_money(char money, Student_t *h);
Student_t* find_by_house(char house, Student_t *h);

#endif
