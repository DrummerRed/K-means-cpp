#include "header.h"

struct centroid
{
    int centroid_number;            ////
    float* coordinates = nullptr;
    // указатель на список
};

centroid* centroids_array = nullptr;              // Глобальный указатель на массив центроидов

void centroid_initialization(float** array, int groups, int features, int points)              // Инициализация центроидов
{
    int random_index[groups];                                       // Массив индексов рандомных точек                             
    search_random_points(random_index, groups, points);             // Выбор k рандомных точек, как начальных центроидов

    centroids_array = new centroid[groups];                   // Инициализируем k центроидов

    for(int i=0; i<groups; i++)
    {
        centroids_array[i].centroid_number = i;
        centroids_array[i].coordinates = new float[features];
        
        int index = random_index[i];
        for(int j=0; j<features; j++)
        {
            centroids_array[i].coordinates[j] = array[index][j+1];
        }
    }
}

void array_print(float** array, int features, int points)                       // УДАЛИТЬ
{
    printw("\n\n===============================\n");
    for(int i=0; i<points; i++)
    {
        for(int j=0; j<features+1; j++)
        {
            printw("%f\t", array[i][j]);
        }
        printw("\n");
    }
}

void debug_print(int groups, int features)           // удалить
{
    printw("\n\n===============================\n");
    for(int i=0; i<groups; i++)
    {
        printw("Group number: %d\n", centroids_array[i].centroid_number);
        for (int j=0; j<features; j++)
        {
            printw("%f\t", centroids_array[i].coordinates[j]);
        }
        printw("\n\n");
    }
}

int rand_int(int a, int b)                          // Генерация случайного целого числа
{
    return a + rand() % (b - a + 1);            
}

void search_random_points(int* array, int groups, int points)  // Выбор рандомных неповторяющихся точек для инициализации центроидов
{
    for(int i=0; i<groups; )
    {
        bool repeat = false;
        int random_point = rand_int(0, points-1);
        for(int j=0; j<i; j++)
        {
            if (array[j] == random_point)
            {
                repeat = true;
                break;
            }
        }
        
        if (!repeat)
        {
            array[i] = random_point;
            i++;
        }
    } 
}