#include "header.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    setlocale(LC_NUMERIC, "C");                  // парсим и печатаем числа с точкой
    srand(time(NULL));

    Menu();

    return 0;
}