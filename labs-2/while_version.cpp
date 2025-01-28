/***********************************************************************************
*                       Курс КОМПЬЮТЕРНЫЕ ТЕХНОЛОГИИ                               *
*----------------------------------------------------------------------------------*
* Project Type  : Win64 Console Application                                        *
* Project Name  : Labs2                                                            *
* File Name     : Labs2.exe                                                        *
* Language      : CPP, MSVS 2022                                                   *
* Programmers   : Тихонов Павел Сергеевич, Ефимов Ярослав Сергеевич, М3О-119БB-24  *
* Modifyed By   :                                                                  *
* Created       : 05.11.2024                                                       *
* Last Revision : 08.11.2024                                                       *
* Comment(s)    : Табулирование Функции                                            *
***********************************************************************************/

#include <iostream>
#include <iomanip>  // Для манипуляторов вывода
#include <cmath>    // Для функций sin и cos

using namespace std;

int main() {

    // получаем локаль для вывода табличных символов
    locale::global(locale("en_US.UTF-8"));
    wcout.imbue(locale("en_US.UTF-8"));


    // Вводим значения A, B и N
    long double A; // Исходное значение A = -π/4
    long double B; // Исходное значение B = π/2
    int N;         // Исходное значение N = 15
    long double h;
    long double x;
    long double F;
    long double G;

    cout<< "Введите A:";
    cin>> A;
    cout<< "Введите B:";
    cin>> B;

    // **echo print**
    cout <<setprecision(20) << "A:" << A << " B:" << B <<endl;

    // Проверка на положительное значение длины интервала
    if (A > B) {
        cout<< "Ошибка: A должно быть строго меньше B" << endl;
        return 1;
    }

    cout<< "Введите N:";
    cin>> N;
    //echo print
    cout << "N:"<<N<<endl;
    // Проверка на корректность N
    if (N <= 0) {
        cout << "Ошибка: N должно быть > 0" << endl;
        return 2;
    }


    // Вычисляем шаг h, если шаг h не вычисляем он приравнивется к нулю
    // Проверка на равенство A и B
    if(A != B) {
        h = (B - A) / N;
    }
    else {
    	N = 0;
        h = 0;
    }

     // Заголовок таблицы
    wcout << L"\u250C" << setw(6) << setfill(L'\u2500') << L"\u252C"
          << setw(15) << setfill(L'\u2500') << L"\u252C"
          << setw(25) << setfill(L'\u2500') << L"\u252C"
          << setw(27) << setfill(L'\u2500') << L"\u2510" << endl;

    wcout << L"\u2502" << L" " << left << setw(3) << setfill(L' ') << L"i" << L" " << L"\u2502"
          << setw(13) << L"x" << L" " << L"\u2502"
          << setw(23) << L"F(x) = sin(x) * cos(x)" << L" " << L"\u2502"
          << setw(25) << L"G(x) = 2 * sin(2 * x) + 1" << L" " << L"\u2502" << endl;

    wcout << L"\u251C" << setw(5) << setfill(L'\u2500') << L"\u2500"
          << setw(15) << setfill(L'\u2500') << L"\u253C"
          << setw(25) << setfill(L'\u2500') << L"\u253C"
          << setw(27) << setfill(L'\u2500') << L"\u253C" << L"\u2524"  << endl;

    // Цикл табулирования значения
    int i=1;
    x = A;
    while(x<=B+h/2){
        F = sin(x) * cos(x);
        G = 2 * sin(2 * x) + 1;
        std::cout << h << std::endl << x;

        // Выводим результат в табличном формате с рамкой
        wcout << L"\u2502" << L" " << left << setw(3) << setfill(L' ') << i << L" " << L"\u2502"
              << setw(13) << x << L" " << L"\u2502"
              << setw(23) << F << L" " << L"\u2502"
              << setw(25) << G << L" " << L"\u2502" << endl;

        // Добавляем горизонтальное разделение между строками
        if (x <= B) {
            wcout << L"\u251C" << setw(5) << setfill(L'\u2500') << L"\u2500"
                  << setw(15) << setfill(L'\u2500') << L"\u253C"
                  << setw(25) << setfill(L'\u2500') << L"\u253C"
                  << setw(27) << setfill(L'\u2500') << L"\u253C" << L"\u2524"  << endl;
        }
        i++;
        x = x + h;
        std::cout << x;
    }


    cout << setprecision(20) << "\u250C" << endl;

    // Нижняя граница таблицы
    wcout << L"\u2514" << setw(5) << setfill(L'\u2500') << L"\u2500"
          << setw(15) << setfill(L'\u2500') << L"\u2534"
          << setw(25) << setfill(L'\u2500') << L"\u2534"
          << setw(27) << setfill(L'\u2500') << L"\u2534" << L'\u2518' << endl;

    return 0;
}
