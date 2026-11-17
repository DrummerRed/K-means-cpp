#include <iostream>
#include <cstdlib>          // system(), exit()
#include <ncurses.h>        
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

const int ESC = 27;
const int ENTER = 10;
const int DOWN = 258;
const int UP = 259;

void Menu();                                         // Главное меню программы
void interface(int choice);                          // Отрисовка интерфейса главного меню программы
void Help();                                         // Функция работы пункта меню "Помощь"
void Menu_start_work();
void message_of_error_load();                        // Вывод сообщения об ошибке загрузки файла
int set_groups_count(string file_name, int features, int samples);  // Вывод сообщения о данных файла и считывание количество групп для разделения
void clear_and_print();                              // Вывод подсказки пользователя на экран
string input_string(bool* flag_esc, string* arrows = nullptr);  // Ввод строки
int workaround(unsigned char first, unsigned char second);      // Проверка, что символ является кириллическим 
string input_file_name();                           // Ввод названия входгного файла
void print_message(int message);                    // Вывод диагностического сообщения

int file_checker(string file_name);                 // Функция проверки существования рабочего файла программы
int get_features_count(string file_name, int* samples);                         // Подсчет количества признаков и примеров в файле
int file_parser(string file_name, float** array, int features, int samples);    // Чтение признаков каждого примера и запись в массив
bool is_number(string str);                                                     // Проверка, что строка является числом

struct centroid;
void centroid_initialization(float** array, int groups, int features, int points);              // Инициализация центроидов
int rand_int(int a, int b);                          // Генерация случайного целого числа
void search_random_points(int* array, int groups, int points);  // Выбор рандомных неповторяюзихся точек для инициализации центроидов
void debug_print(int groups, int features);           // удалить
void array_print(float** array, int features, int points);                       // УДАЛИТЬ