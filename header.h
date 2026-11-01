#include <iostream>
#include <cstdlib>          // system(), exit()
#include <ncurses.h>        
#include <string>
#include <fstream>

using namespace std;

const int ESC = 27;
const int ENTER = 10;
const int DOWN = 258;
const int UP = 259;

void Menu();                                         // Главное меню программы
void interface(int choice);                          // Отрисовка интерфейса главного меню программы
void Help();                                         // Функция работы пункта меню "Помощь"
void Menu_start_work();
void clear_and_print();                              // Вывод подсказки пользователя на экран
string input_string(bool* flag_esc, string* arrows = nullptr);  // Ввод строки
int workaround(unsigned char first, unsigned char second);      // Проверка, что символ является кириллическим 
string input_file_name();                           // Ввод названия входгного файла
void print_message(int message);                    // Вывод диагностического сообщения

int file_checker(string file_name);          // Функция проверки существования рабочего файла программы
int get_features(string file_name);              // Проверка записей файла на корректность и подсчет количества признаков в файле