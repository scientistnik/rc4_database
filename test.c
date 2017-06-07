void test()
{
    	list* llist = create_list();

  	printf("TEST CASE 1\nПустая БД не должна ничего напечатать:\n");
  	traverse(llist, print_student);
	printf("\n");

 	push_front(llist, create_student("Nick", "Polive", 56, 239402128));
 	printf("TEST CASE 2\nБД с одним студентом должна напечатать одного студента:\n");
 	traverse(llist, print_student);
 	printf("\n");

 	remove_front(llist, free_student);
 	printf("TEST CASE 3\nЕще однна созданная пустая БД не должна напечатать ничего:\n");
 	traverse(llist, print_student);
 	printf("\n");

 	push_front(llist, create_student("Иван", "Иванович", 92, 123456789));
 	push_front(llist, create_student("Григорий", "Михайлович", 65, 902313373));
 	printf("TEST CASE 4\nA БД с двумя студентами должна напечатать двоих студентов:\n");
 	traverse(llist, print_student);
 	printf("\n");

	Student* p = create_student("Семен", "Веселый", 3, 131313137);
	printf("TEST CASE 5\nПоиск несущесвтующего студента в БД должен вернуть ошибку: \n");
	printf("%d\n", find_occurrence(llist, p, student_eq));

	free_student(p);

  	empty_list(llist, free_student);
 	printf("TEST CASE 6\nПосле освобождения памяти БД, она должна быть пустой:\n");
 	traverse(llist, print_student);
 	printf("\n");

        push_front(llist, create_student("Петр", "Суровый", 92, 123456789));
        push_front(llist, create_student("Джон", "Добрый", 13, 666));
        push_front(llist, create_student("Владимир", "Уничтожитель", 200, 54545454));
        push_back(llist, create_student("Анна", "Прекрасная", 0, 222222222));
        printf("TEST CASE 7\nВставить в конец БД. ЗАпись должна быть: Петр, Джон, Владимир, Анна:\n");
        traverse(llist, print_student);
        printf("\n");

        remove_front(llist, free_student);
        printf("TEST CASE 8\nУдаление спереди. Петр покидает БД:\n");
        traverse(llist, print_student);
        printf("\n");

        remove_back(llist, free_student);
        printf("TEST CASE 9\nУдаление сзади. Анна также покидает БД:\n");
        traverse(llist, print_student);
        printf("\n");

        remove_index(llist, 1, free_student);
        printf("TEST CASE 10\nУдаление по индексу. Удаление студента из БД под индексом 1:\n");
        traverse(llist, print_student);
        printf("\n");

  	empty_list(llist, free_student);
        push_front(llist, create_student("Петр", "Суровый", 92, 123456789));
        push_front(llist, create_student("Джон", "Добрый", 13, 666));
        push_front(llist, create_student("Валдимир", "Уничтожитель", 200, 54545454));
        push_back(llist, create_student("Анна", "Милая", 0, 222222222));
        push_back(llist, create_student("Анна", "Милая", 0, 222222222));

        p = create_student("Анна", "Милая", 0, 222222222);
        int removed = remove_data(llist, p, student_eq, free_student);
        printf("TEST CASE 11\nУдалить данные. Был создан новый список и Анну случайно два раза добавил. Анны не должно быть в списке дважды:\n");
        traverse(llist, print_student);
        printf("Повторения удалены: %d\n", removed);
        printf("\n");
        free_student(p);

        p = create_student("Анна", "Милая", 0, 222222222);
        removed = remove_data(llist, p, student_eq, free_student);
        printf("TEST CASE 12\nУдаление данных. Повторное удаление Анны не приведет к удалению:\n");
        traverse(llist, print_student);
        printf("Повторения удалены: %d\n", removed);
        printf("\n");
        free_student(p);

        printf("TEST CASE 13\nНачало списка. Получение начального элемента списка. Должен быть Владимир:\n");
        print_student(front(llist));
        printf("\n");

        printf("TEST CASE 14\nПолучение элмента по иднексу. Получаем элемент под индексом 1:\n");
        print_student(get_index(llist, 1));
        printf("\n");

        printf("TEST CASE 15\nПолучение элменте списка с конца:\n");
        print_student(back(llist));
        printf("\n");

        printf("TEST CASE 16\nПроверка списка на пустоту? (ответ должен быть - нет)\n");
        printf(is_empty(llist) ? "Да\n" : "Нет\n");
        printf("\n");

        printf("TEST CASE 17\nРазмер. Какой размер БД? (должен быть 3)\n");
        printf("%d\n", size(llist));
        printf("\n");

        p = create_student("Петр", "Суровый", 92, 123456789);
        printf("TEST CASE 18\nОшибка опоиска. Существует ли этот Петр в БД?\n");
        printf(find_occurrence(llist, p, student_eq) ? "Да\n" : "Нет\n");
        printf("\n");
        free_student(p);

        empty_list(llist, free_student);

        push_back(llist, create_student("Петр", "Суровый", 92, 123456789));
        printf("TEST CASE 19\nВставить в конец пустого списка:\n");
        traverse(llist, print_student);
        printf("\n");
        empty_list(llist, free_student);

        printf("TEST CASE 20\nУдалить с начала списка, список пуст: (должно быть -1)\n");
        printf("%d\n", remove_front(llist, free_student));
        printf("\n");

        printf("TEST CASE 21\nУдаление по индексу, список пуст: (должно быть -1)\n");
        printf("%d\n", remove_index(llist, 0, free_student));
        printf("\n");

        printf("TEST CASE 22\nУдаление с конца списка, список пуст: (должно быть -1)\n");
        printf("%d\n", remove_back(llist, free_student));
        printf("\n");

        p = create_student("Петр", "Суровый", 92, 123456789);
        printf("TEST CASE 23\nУдаление данных из пустого списка: (ничего не произойдет, вернется 0)\n");
        printf("%d\n", remove_data(llist, p, student_eq, free_student));
        printf("\n");
        free_student(p);

        printf("TEST CASE 24\nС начала пустого списка:\n");
        printf("%d\n", (int)front(llist));
        printf("\n");

        printf("TEST CASE 25\nС конца пустого списка:\n");
        printf("%d\n", (int)back(llist));
        printf("\n");

        printf("TEST CASE 26\nПолучить индекс пустого списка:\n");
        printf("%d\n", (int)get_index(llist, 0));
        printf("\n");

        printf("TEST CASE 27\nПроверка списка на пустоту\n");
        printf("%d\n", is_empty(llist));
        printf("\n");

        p = create_student("Петр", "Суровый", 92, 123456789);
        printf("TEST CASE 28\nПоиск вхождения в пустом списке:\n");
        printf("%d\n", find_occurrence(llist, p, student_eq));
        printf("\n");
        free_student(p);

        empty_list(llist, free_student);

        push_front(llist, create_student("Петр", "Суровый", 92, 123456789));

        push_back(llist, create_student("Анна", "Милая", 13, 666));
        printf("TEST CASE 29\nВставить в конец списка длиной в 1. Должен быть Петр, потом Анна:\n");
        traverse(llist, print_student);
        printf("\n");
        empty_list(llist, free_student);

        push_front(llist, create_student("Петр", "Суровый", 92, 123456789));
        printf("TEST CASE 30\nУдаление с конца, список размера 1:\n");
        remove_back(llist, free_student);
        printf("\n");

        push_front(llist, create_student("Петр", "Суровый", 92, 123456789));
        printf("TEST CASE 31\nУдаление по индексу, размер списка 1:\n");
        remove_index(llist, 0, free_student);
        traverse(llist, print_student);
        printf("\n");

        push_front(llist, create_student("Петр", "Суровый", 92, 123456789));
        p = create_student("Петр", "Суровый", 92, 123456789);
        printf("TEST CASE 32\nУдалить данные из списка размером 1: (вернет 1)\n");
        printf("%d\n", remove_data(llist, p, student_eq, free_student));
        printf("\n");
        free_student(p);

        push_front(llist, create_student("Петр", "Суровый", 92, 123456789));
        printf("TEST CASE 33\nНачало списка размером в 1: (должен быть Петр)\n");
        print_student(front(llist));
        printf("\n");

        printf("TEST CASE 34\nКонец списка размером в 1: (должен быть Петр)\n");
        print_student(back(llist));
        printf("\n");

        printf("TEST CASE 35\nПолучение эллмента по индеусу 1: (должен быть Петр)\n");
        print_student(get_index(llist, 0));
        printf("\n");

        empty_list(llist, free_student);

        push_front(llist, create_student("Петр", "Суровый", 92, 123456789));
        push_front(llist, create_student("Анна", "Милая", 13, 666));
        push_front(llist, create_student("Владимир", "Разрушитель", 200, 54545454));
        push_back(llist, create_student("Тина", "Петрова", 0, 222222222));
        push_back(llist, create_student("Тина", "Петрова", 0, 222222222));
        push_front(llist, create_student("Петр", "Суровый", 2, 123456789));
        printf("TEST CASE 36\nУдалить студентов, с рейтингом ниже 60:\n");
        remove_if(llist, student_failing, free_student);
        traverse(llist, print_student);
        printf("\n");

        empty_list(llist, free_student);

 	free(llist);
}
