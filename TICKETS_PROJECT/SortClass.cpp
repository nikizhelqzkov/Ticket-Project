#include "SortClass.h"
/**
 * @brief Метод сорт, който използва алгоритъма selection sort и самия метод е функция от по-висок ред
 * Целта му е да работи по подобен начин като std::sort  но с функция по наш избор (примерно сравнение на дати)
 * 
 * @param arr 
 * @param size 
 * @param func 
 */
void SortClass::sort(EventArr &arr, size_t size, comparatorFunction func)
{
    for (size_t i = 0; i < size - 1; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            if (func(arr[i], arr[j]))
            {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}