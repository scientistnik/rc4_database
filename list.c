#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "rc4.h"

#define DATABASE_NAME "database.db"

FILE *fout;
Student_t *head = NULL;

void list_init(FILE* output)
{
  FILE* f;

  fout = output;

  fprintf(fout,"Try open database...\n");
  if ( (f = fopen(DATABASE_NAME,"rb")) == NULL)
  {
    f = fopen(DATABASE_NAME,"wb");
    fclose(f);
    f = fopen(DATABASE_NAME,"rb");
  }

  Student_t *buf = malloc(sizeof(Student_t));
	rc4_init();

	while (fgets(buf->fio,255,f) != NULL) {
		rc4_crypt(( char*)buf->fio,strlen(buf->fio));
		fgets(buf->direct,255,f);
		rc4_crypt(( char*)buf->direct,strlen(buf->direct));
		fgets(buf->group,255,f);
		rc4_crypt(( char*)buf->group,strlen(buf->group));
		fgets(&(buf->form),255,f);
		rc4_crypt(( char*)&(buf->group),1);
		fgets(&(buf->money),255,f);
		rc4_crypt(( char*)&(buf->money),1);
		fgets(&(buf->house),255,f);
		rc4_crypt(( char*)&(buf->house),1);

		add_to_list(buf);
  	buf = malloc(sizeof(Student_t));
	}
	free(buf);

  fclose(f);
}

void add_to_list(Student_t *new)
{
  if (head == NULL) {
    fprintf(fout,"Add first node...");
    head = new;
    head->next = head;
    head->prev = head;
  } else {
    fprintf(fout,"Add next node...");
    new->prev = head->prev;
    new->next = head;
    head->prev = new;
    new->prev->next = new;
  }
}

void save_list()
{
  FILE *f;
  Student_t *s = head;

  if (head == NULL)
    return;

  if ((f = fopen(DATABASE_NAME,"w")) == NULL) {
    fprintf(fout,"Error open database-file!\n");
    return;
  }
	rc4_reset();
	rc4_init();

  do {
		char ch = '\n';
		rc4_crypt((char *)s->fio,strlen(s->fio));
		fwrite(s->fio,sizeof(s->fio),1,f);
		fwrite(&ch,sizeof(ch),1,f);
		rc4_crypt((char *)s->direct,strlen(s->direct));
		fwrite(s->direct,sizeof(s->direct),1,f);
		fwrite(&ch,sizeof(ch),1,f);
		rc4_crypt((char *)s->group,strlen(s->group));
		fwrite(s->group,sizeof(s->group),1,f);
		fwrite(&ch,sizeof(ch),1,f);
		rc4_crypt((char *)&(s->form),1);
		fwrite(&(s->form),sizeof(s->form),1,f);
		fwrite(&ch,sizeof(ch),1,f);
		rc4_crypt((char *)&(s->money),1);
		fwrite(&(s->money),sizeof(s->money),1,f);
		fwrite(&ch,sizeof(ch),1,f);
		rc4_crypt((char *)&(s->house),1);
		fwrite(&(s->house),sizeof(s->house),1,f);
		fwrite(&ch,sizeof(ch),1,f);

    s = s->next;
  } while(s != head);
}

/*
Student* create_student(const char* first_name, const char* last_name, int grade, unsigned int gtid)
{
  Student *s = malloc(sizeof(Student));

  char *f = malloc((strlen(first_name)+1)*sizeof(char));
  char *l = malloc((strlen(last_name)+1)*sizeof(char));

  strncpy(f, first_name, strlen(first_name)+1);
  strncpy(l, last_name, strlen(last_name)+1);

  s->first_name = f;
  s->last_name = l;
  s->grade = grade;
  s->gtid = gtid;

  return s;
}

void print_student(void* data)
{
  Student *s = data;
  printf("Студент: %s %s\n", s->first_name, s->last_name);
  printf("Группа: %d\n", s->grade);
  printf("ИД: %d\n", s->gtid);
}

void free_student(void* data)
{
  Student *s = data;

  free(s->first_name);
  free(s->last_name);

  free(s);
}

int student_eq(const void* a, const void* b)
{
  const Student *s1 = a;
  const Student *s2 = b;

  if (!strncmp(s1->first_name, s2->first_name, strlen(s1->first_name)) &&
      !strncmp(s2->last_name,  s2->last_name,  strlen(s1->last_name)) &&
      s1->grade == s2->grade &&
      s1->gtid == s2->gtid) {
    return 1;
  } else {
    return 0;
  }
}

int student_failing(const void* a) {
  const Student *s = a;
  if (s->grade < 60) return 1;
  return 0;
}

typedef struct lnode
{
  struct lnode* prev;
  struct lnode* next;
  void* data;
} node;

static node* create_node(void* data);

list* create_list(void)
{
  list *l = malloc(sizeof(list));
  l->head = NULL;
  l->size = 0;
  return l;
}

static node* create_node(void* data)
{
  node *n = malloc(sizeof(node));
  n->data = data;
  n->prev = NULL;
  n->next = NULL;
  return n;
}

void push_front(list* llist, void* data)
{
  node *n = create_node(data);

  if (!llist->size) {
    n->next = n;
    n->prev = n;
  } else {
    node *head = llist->head;
    node *prev = head->prev;

    n->next = head;
    n->prev = head->prev;

    head->prev = n;
    prev->next = n;
  }

  llist->head = n;
  llist->size++;
}

void push_back(list* llist, void* data)
{
  node *n = create_node(data);

  if (!llist->size) {
    n->next = n;
    n->prev = n;
    llist->head = n;
  } else {
    node *head = llist->head;
    node *prev = head->prev;
    n->next = head;
    n->prev = head->prev;

    head->prev = n;
    prev->next = n;
  }
  llist->size++;
}

int remove_front(list* llist, list_op free_func)
{
  if (!llist->size) return -1;

  node *head = llist->head;

  if (llist->size == 1) {
    llist->head = NULL;
  } else {
    node *next = head->next;
    node *prev = head->prev;

    llist->head = next;

    next->prev = prev;
    prev->next = next;
  }

  free_func(head->data);
  free(head);

  llist->size--;

  return 0;
}

int remove_index(list* llist, int index, list_op free_func)
{
  if (!llist->size) return -1;

  node *current = llist->head;

  for (int i=0; i<index; i++) {
    current = current->next;
  }

  if (llist->size == 1) {
    llist->head = NULL;
  } else {
    node *next = current->next;
    node *prev = current->prev;

    prev->next = next;
    next->prev = prev;
  }

  free_func(current->data);
  free(current);

  llist->size--;

  return 0;
}

int remove_back(list* llist, list_op free_func)
{
  if (!llist->size) return -1;

  node *head = llist->head;
  node *tbr = head->prev;
  node *nb = tbr->prev;

  if (llist->size == 1) {
    llist->head = NULL;
  } else {
    head->prev = nb;
    nb->next = head;
  }

  free_func(tbr->data);
  free(tbr);

  llist->size--;

  return 0;
}

int remove_data(list* llist, const void* data, equal_op compare_func, list_op free_func)
{
  int removed = 0;

  if (!llist->size) return removed;

  node *current = llist->head;
  node *next = current->next;
  node *prev = current->prev;
  int is_head = 1;

  for (int i=0; i<llist->size; i++) {
    if (compare_func(data, current->data)) {
      if (is_head) llist->head = next;
      next->prev = prev;
      prev->next = next;
      free_func(current->data);
      free(current);
      current = next;

      removed++;
    } else {
      is_head = 0;
      current = current->next;
    }

    if (llist->size > 1) {
      next = current->next;
      prev = current->prev;
    }
  }

  llist->size-=removed;

  if (!llist->size) llist->head = NULL;

  return removed;
}

int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
  if (!llist->size) return 0;

  int removed = 0;
  node *current = llist->head;
  node *next = current->next;
  node *prev = current->prev;
  int is_head = 1;

  for (int i=0; i<llist->size; i++) {
    if (pred_func(current->data)) {
      if (is_head) llist->head = next;

      next->prev = prev;
      prev->next = next;

      free_func(current->data);
      free(current);

      current = next;

      removed++;
    } else {
      is_head = 0;

      current = current->next;
    }

    if (llist->size > 0) {
      next = current->next;
      prev = current->prev;
    }
  }

  llist->size-=removed;

  if (!llist->size) llist->head = NULL;

  return removed;
}

void* front(list* llist)
{
  if (llist->size) {
    return llist->head->data;
  } else {
    return NULL;
  }
}

void* get_index(list* llist, int index)
{
  if (!llist->size || index >= llist->size) {
    return NULL;
  }

  node *current = llist->head;
  for (int i=0; i<index; i++) {
    current = current->next;
  }

  return current->data;
}

void* back(list* llist)
{
  if (!llist->size) return NULL;

  node *end = llist->head->prev;
  return end->data;
}

int is_empty(list* llist)
{
  if (llist->size == 0 && llist->head == NULL) {
    return 1;
  } else {
    return 0;
  }
}

int size(list* llist)
{
  return llist->size;
}

int find_occurrence(list* llist, const void* search, equal_op compare_func)
{
  node *current = llist->head;
  for (int i=0; i<llist->size; i++) {
    if (compare_func(search, current->data)) return 1;
    current = current->next;
  }

  return 0;
}

void empty_list(list* llist, list_op free_func)
{
  if (!llist->size) return;

  node *current = llist->head;
  node *next = current->next;

  for (int i=0; i<llist->size; i++) {
    free_func(current->data);
    free(current);
    current = next;

    if (i < llist->size-1) next = current->next;
  }

  llist->head=NULL;
  llist->size=0;
}

void traverse(list* llist, list_op do_func)
{
  node *current = llist->head;
  for (int i=0; i<llist->size; i++) {
    do_func(current->data);
    current = current->next;
  }
}
*/
