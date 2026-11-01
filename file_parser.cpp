#include "header.h"

int file_checker(string file_name)          // Функция проверки существования рабочего файла программы
{                                           // Возвращает 1, если файл с таким именем отсутствует
    ifstream file;                          // 2, если файл пуст
    file.open(file_name);                   // 0, если файл полностью корректен
    int result = 0;

    if (!file.is_open())                  
        result = 1;
    else                                    
    {
        int flag;       
        string str;
        getline(file, str);

        if (str == "")
            flag = 2;
        else
            flag = 0;

        file.close();
        result = flag;
    }
    return result;
}

int get_features(string file_name)              // Проверка записей файла на корректность и подсчет количества признаков в файле
{
    ifstream file;
    file.open(file_name);
    int features = 1;
    char separator = ',';

    if (file.is_open())
    {
        string str;
        getline(file, str);

        for (int i=0; i<str.length(); i++)
        {
            if (str[i] == separator)
                features ++;
        }
    }
    else
        features = 0;

    return features;
}