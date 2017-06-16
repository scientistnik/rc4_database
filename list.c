#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "rc4.h"

#define DATABASE_NAME "database.db"

FILE *fout;
Student_t *head = NULL;

void list_init(FILE* output,char *name)
{
  FILE* f;

  fout = output;

	if (name == NULL) {
		name = malloc(sizeof(char)*50);
		strcpy(name, DATABASE_NAME);
	}

  fprintf(fout,"Try open database...\n");
  if ( (f = fopen(name,"rb")) == NULL)
  {
		fprintf(fout,"Database not found!!!\n Create new database...\n");
    f = fopen(name,"wb");
    fclose(f);
    f = fopen(name,"rb");
  }

  Student_t *buf = malloc(sizeof(Student_t));
	rc4_init();

	fprintf(fout,"Read data from file database.db\n");
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
    fprintf(fout,"Add first node...\n");
    head = new;
    head->next = head;
    head->prev = head;
  } else {
    fprintf(fout,"Add next node...\n");
    new->prev = head->prev;
    new->next = head;
    head->prev = new;
    new->prev->next = new;
  }
}

void delete_from_list(Student_t *del)
{
	Student_t *std = head;

	if (head == NULL || del == NULL)
		return;

	while (std != del){
		std = std->next;
		if (std == head)
			return;
	}

	fprintf(fout,"Delete element from database....\n");
	if (std->next == std->prev) {
		fprintf(fout,"Database empty....\n");
		free(head);
		head = NULL;
	} else {
		std->next->prev = std->prev;
		std->prev->next = std->next;
		free(std);
	}
}

void save_list(char *name)
{
  FILE *f;
  Student_t *s = head;

	if (name == NULL) {
		name = malloc(sizeof(char)*50);
		strcpy(name,DATABASE_NAME);
	}

  if ((f = fopen(name,"w")) == NULL) {
    fprintf(fout,"Error open database-file!\n");
    return;
  }

  if (head == NULL)
    return;

	rc4_reset();
	rc4_init();

	fprintf(fout,"Save list to database.db file....\n");
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

int student_eq(const Student_t *a, const Student_t *b)
{
	if (strlen(a->fio) != strlen(b->fio) ||
			strlen(a->direct) != strlen(b->direct) ||
			strlen(a->group) != strlen(b->group))
			return 0;

	if 	(!strcmp(a->fio,b->fio) && !strcmp(a->direct,b->direct) && !strcmp(a->group,b->group) &&
				a->form == b->form && a->money == b->money && a->house == b->house) {
    return 1;
  } else {
    return 0;
  }
}

Student_t* find_by_fio(char *fio, Student_t *h)
{
	Student_t *cur;
	
	if (h == NULL)
		cur = head;
	
	fprintf(fout,"Find by fio...\n");
	while (strstr(cur->fio, fio) == NULL) {
		cur = cur->next;
		if (cur == head)
			return NULL;
	}

	return cur;
}

Student_t* find_by_group(char *group, Student_t *h)
{
	Student_t *cur;

	if (h == NULL)
		cur = head;

	fprintf(fout,"Find by Group...\n");
	while (strstr(cur->group, group) == NULL) {
		cur = cur->next;
		if (cur == head)
			return NULL;
	}

	return cur;
}

Student_t* find_by_direct(char *direct, Student_t *h)
{
	Student_t *cur;

	if (h == NULL)
		cur = head;

	fprintf(fout,"Find by Direct...\n");
	while (strstr(cur->direct, direct) == NULL) {
		cur = cur->next;
		if (cur == head)
			return NULL;
	}

	return cur;
}

Student_t* find_by_form(char form, Student_t *h)
{
	Student_t *cur;

	if (h == NULL)
		cur = head;

	fprintf(fout,"Find by Form...\n");
	while (cur->form == form) {
		cur = cur->next;
		if (cur == head)
			return NULL;
	}

	return cur;
}

Student_t* find_by_money(char money, Student_t *h)
{
	Student_t *cur;

	if (h == NULL)
		cur = head;

	fprintf(fout,"Find by Money...\n");
	while (cur->money == money) {
		cur = cur->next;
		if (cur == head)
			return NULL;
	}

	return cur;
}

Student_t* find_by_house(char house, Student_t *h)
{
	Student_t *cur;

	if (h == NULL)
		cur = head;

	fprintf(fout,"Find by House...\n");
	while (cur->house == house) {
		cur = cur->next;
		if (cur == head)
			return NULL;
	}

	return cur;
}
