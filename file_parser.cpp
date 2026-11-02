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

int get_features_count(string file_name, int* samples)              // Подсчет количества признаков и примеров в файле
{                                                                   // Возвращает количество признаков входного файла
    ifstream file;                                                  // Если файл не удалось открыть, возвращает -1
    file.open(file_name);
    int features = 1;
    *samples = 0;
    char separator = ',';

    if (file.is_open())
    {
        string str;
        getline(file, str);

        for (int i=0; i<str.length(); i++)              // Считывание признаков
        {
            if (str[i] == separator)
                features++;
        }

        while (getline(file, str))
            *samples += 1;

        file.close();
    }
    else
        features = -1;

    return features;
}

int file_parser(string file_name, float** array, int features, int samples)                 // Чтение признаков каждого примера и запись в массив
{                                                                                           // Возвращает 0 при удачном чтении файла    
    int code = 0;                                                                           // При ошибке возвращает -1
    ifstream file;
    file.open(file_name);
    char separator = ',';
    int columns = features + 1;                  // Добавим колонку с номером точки

    if (file.is_open())
    {
        string str;
        getline(file, str);

        for (int i=0; i<samples; i++)
        {
            getline(file, str);
            array[i] = new float[columns];
            
            if (code == -1)
                break;

            for (int j=0; j<columns; j++)
            {
                if (j == 0)
                    array[i][j] = i + 1;                    // Номер точки
                else
                {
                    string temp = str;
                    int index = temp.find(separator);
                    if (index != -1)
                    {
                        temp.erase(index, (str.length() - index));
                        str.erase(0, index + 1);
                        if (is_number(temp))
                            array[i][j] = stof(temp);
                        else
                        {
                            code = -1;
                            break;
                        }
                        printw("%s\t", temp.c_str());
                    }
                    else
                    {
                        if (is_number(str))
                            array[i][j] = stof(str);
                        else
                        {
                            code = -1;
                            break;
                        }
                        printw("%s\n\n", str.c_str());          ////
                    }
                }
            }
        }
        file.close();    
    }
    return code;
}                           // Сократить!!

bool is_number(string str)                              // Проверка, что строка является числом
{                                                       // Возвращает true, если строка является числом
    bool result = true;                                 // Иначе возвращает false
    try
    {
        stof(str);
    }
    catch(...)
    {
        result = false;
    }
    return result;
}


// Проверить корректность записи в массив!