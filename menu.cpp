#include "header.h"

const string HELP = "help.txt";                 // Название файла для вкладки "Помощь"

void Menu()                                     // Главное меню программы
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);                // выключение курсора

    int switcher = 1;
    bool flag_esc = false;
    while(!flag_esc)
    {    
        clear();
        interface(switcher);
        refresh();
        int ch = getch();
        if (ch == DOWN)
        {
            if (switcher != 3)
                switcher += 1;
            else
                switcher = 1;
        }
        if (ch == UP)
        {
            if (switcher != 1)
                switcher -= 1;
            else
                switcher = 3;
        }
        if (ch == ENTER)
        {
            if (switcher == 1)
                Help();

            // if (switcher == 2)
                // Menu_start_work();
            
            if (switcher == 3)
                flag_esc = true;
        }
    }
    endwin();
    system("clear");
}


void interface(int choice)                          // Отрисовка интерфейса главного меню программы
{
    switch(choice)
    {
        case 1:
        printw("  << Помощь >>\n  Начать работу\n  Выход");            // либо начать запись
        break;
        case 2:
        printw("  Помощь\n  << Начать работу >>\n  Выход");
        break;
        case 3:
        printw("  Помощь\n  Начать работу\n  << Выход >>");
        break;
    }
}

void Help()             // Функция работы пункта меню "Помощь"
{
    int ch = 0;
    while (ch != ESC)
    {
        clear();

        char str;
        string duplicate_str = "";
        FILE * file = fopen(HELP.c_str(), "r");

        if (file == NULL)
        {
            clear_and_print();
            printw("Ошибка! Не удалось считать файл инструкций!\n");
            printw("Проверьте наличие файла help.txt в рабочей директории программы!");
        }
        else
        {
            int symb;
            while ((symb = fgetc(file)) != EOF) 
            {
                str = (char)symb;
                duplicate_str += str;
            }
            fclose(file);
            printw("%s", duplicate_str.c_str());
        }

        ch = getch();
        refresh();
    }
}

void clear_and_print()                      // Вывод подсказки пользователя на экран
{
    clear();
    printw("Для возвращения нажмите Esc\n");
    printw("---------------------------\n\n");
}