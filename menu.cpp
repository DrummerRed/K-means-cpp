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

            if (switcher == 2)
                // input_file_name();
                Menu_start_work();
            
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

void Menu_start_work()                                  // Раздел меню "Начать работу" 
{
    string file_name = input_file_name();

    if (file_name != "")
    {
        clear_and_print();
        int samples = 0;
        int features = get_features_count(file_name, &samples);
        if ((features > 0) && (samples > 1))                                               // все содержимое if перенести в отдельную функцию???
        {
            float** array_points = new float*[samples];
            int code = file_parser(file_name, array_points, features, samples);

            if (code == -1)
                printw("Ошибка чтения! Файл содержит некорректные данные. Значения признаков должны быть записаны в виде числа!");
                /////нужно прописать здесь выход из функции по ESC
            else
            {
                printw("Файл \"%s\" успешно считан.\n\n", file_name.c_str());
                printw("Количество входных признаков: %d\n", features);
                printw("Количество примеров: %d\n", samples);
                // Количество примеров: ...
                // Введите количество групп для разбиения данных... групп <= примеров
                // или (для разбиения примеров на группы введите кол-во групп...)
            }
            getch();                    ///////
            getch();

            delete[] array_points;
        }
    }
}

string input_file_name()                    // Ввод названия входгного файла
{                                           // Возвращает имя входного файла, если оно корректно
    bool flag_esc = false;                  // Иначе возвращает пустую строку
    string file_name;                       // При нажатии Esc также возвращает пустую строку
    int diagnostic_message = 0;
    
    while(!flag_esc)
    {
        clear_and_print();
        if (diagnostic_message != 0)
            print_message(diagnostic_message);

        printw("Введите название файла: ");
        file_name = input_string(&flag_esc);

        if (file_name != "")
        {
            int checker = file_checker(file_name);
            diagnostic_message = checker;

            if (checker == 0)
                flag_esc = true;
        }
    }

    if (diagnostic_message != 0)
        file_name = "";

    return file_name;
}

void print_message(int message)                           // Вывод диагностического сообщения
{
    if (message == 1)
        printw("Данный файл не обнаружен!\n");
    else if (message == 2)
        printw("Данный файл пуст! Выберите другой файл.\n");
}

void clear_and_print()                      // Вывод подсказки пользователя на экран
{
    clear();
    printw("Для возвращения нажмите Esc\n");
    printw("---------------------------\n\n");
}

string input_string(bool* flag_esc, string* arrows)    // Ввод строки
{                                                     // Возвращает введенную строку при корректном вводе
    string str = "";                                  // При выходе по Esc возвращает пустую строку
    int x, y;
    noecho();
    curs_set(1);
    while(true)
    {
        refresh();          /////////
        int ch = getch();
        if (ch == KEY_BACKSPACE)                // Удаление символа
        {
            if (str != "")
            {
                int len = str.length();
                if (len > 1)
                {
                    unsigned char first = str[len - 2];
                    unsigned char second = str[len - 1];

                    if (workaround(first, second) == 1)       
                    {
                        str.erase(str.length()-2, 2);
                        getyx(stdscr, y, x);                // координаты курсора на экране
                        move(y, x-1);                       // сдвиг курсора 
                        delch();                            // удаление символа
                    }
                    else                                   
                    {
                        str.erase(str.length()-1, 1);
                        getyx(stdscr, y, x);                // координаты курсора на экране
                        move(y, x-1);
                        delch();
                    }
                }
                else
                {
                    str.erase(str.length()-1, 1);
                    getyx(stdscr, y, x);
                    move(y, x-1);
                    delch();
                }  
            }
        }
        else if (ch == ESC)              // Выход по ESC
        {
            *flag_esc = true;
            break;
        }
        else if (ch == ENTER)              // Выход при нажатии Enter
            break;

        else if (((ch == KEY_RIGHT) || (ch == KEY_LEFT)) && (arrows != nullptr))         // нажатие стрелок 
        {
            if (ch == KEY_RIGHT)
            {
                *arrows = "right";
                break;
            }
            else if (ch == KEY_LEFT)
            {
                *arrows = "left";
                break;
            }
        }  
        else if ((ch == UP) || (ch == DOWN) || (ch == KEY_RIGHT) || (ch == KEY_LEFT))
            continue;
        else
        {
            str += ch;
            addch(ch);                              // вывод символа на экран
            if (ch >= 0xC0 && ch <= 0xDF)
            {                                       // если двухбайтовый символ
                int next_ch = getch();              // считываем находящийся в буфере второй байт символа
                str += next_ch;
                addch(next_ch);
            }
        }
    }
    noecho();
    curs_set(0);
    echo();
    return str;
}

int workaround(unsigned char first, unsigned char second)              // возвращает 1, если это символ кириллицы (2 байтовый)
{                                                    // иначе 0
    if (first == 0xD0 && second >= 0x90 && second <= 0xAF)              // А-Я
        return 1;

    if (first == 0xD0 && second >= 0xB0 && second <= 0xBF)              // а-п
        return 1;
    
    if (first == 0xD1 && second >= 0x80 && second <= 0x8F)              // р-я
        return 1;

    if (first == 0xD0 && second == 0x81)                                // Ё
        return 1; 

    if (first == 0xD1 && second == 0x91)                                // ё
        return 1;
        
    return 0;
}