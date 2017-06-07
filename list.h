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
//void create_student();
/*
struct lnode;

typedef struct llist
{
  struct lnode* head;
  unsigned int size;
} list;

typedef void (*list_op)(void*);
typedef int (*list_pred)(const void*);
typedef int (*equal_op)(const void*, const void*);
list* create_list(void);
void push_front(list* llist, void* data);
void push_back(list* llist, void* data);
int remove_front(list* llist, list_op free_func);
int remove_index(list* llist, int index, list_op free_func);
int remove_back(list* llist, list_op free_func);
int remove_data(list* llist, const void* data, equal_op compare_func, list_op free_func);
int remove_if(list* llist, list_pred pred_func, list_op free_func);
void* front(list* llist);
void* back(list* llist);
void* get_index(list* llist, int index);
int is_empty(list* llist);
int size(list* llist);
int find_occurrence(list* llist, const void* search, equal_op compare_func);
void empty_list(list* llist, list_op free_func);
void traverse(list* llist, list_op do_func);
*/
#endif
