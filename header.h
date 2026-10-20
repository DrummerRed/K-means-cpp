#include <iostream>
#include <cstdlib>          // system(), exit()
#include <ncurses.h>        
#include <string>

using namespace std;

const int ESC = 27;
const int ENTER = 10;
const int DOWN = 258;
const int UP = 259;

void Menu();                                         // Главное меню программы
void interface(int choice);                          // Отрисовка интерфейса главного меню программы
void Help();                                         // Функция работы пункта меню "Помощь"
void clear_and_print();                              // Вывод подсказки пользователя на экран