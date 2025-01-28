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
* Comment(s)    : Вычисление суммы бесконечного числового ряда                     *
***********************************************************************************/

#include <iostream>
#include <iomanip>  // Для манипуляторов вывода
#include <cmath>    // Для функций sin и cos

using namespace std;
//TODO: Исправить таблицу

int main() {

    // получаем локаль для вывода табличных символов
    locale::global(locale("en_US.UTF-8"));
    wcout.imbue(locale("en_US.UTF-8"));


    // Вводим значения A, B и N
    long double A = -(M_PI_4); // Исходное значение A = -π/4
    long double B = M_PI_2;    // Исходное значение B = π/2
    int N = 15;                // Исходное значение N = 15

    cout<< "Введите A:";
    cin>> A;
    cout<< "Введите B:";
    cin>> B;
    cout<< "Введите N:";
    cin>> N;

    // **echo print**
    cout<<"A:"<<A<<" B:"<<B<<" N:"<<N<<endl;

    // Проверка на корректность N
    if (N <= 0) {
        cout << "Ошибка: N должно быть > 0" << endl;
        return 0;
    }

    // Проверка на равенство A и B
    if (A == B) {
        cout << "Ошибка: A не должно быть равно B" << endl;
        return 0;
    }

    // Проверка на положительное значение длины интервала
    if (A > B) {
        // double C = A;
        // A=B;
        // B=C;
        // Что в действительности эквивалентно
        swap(A,B);
    }

    // Вычисляем шаг h
    double h = (B - A) / N;

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

    // Цикл табулирования значений
    for (int i = 0; i <= N; ++i) {
        double x = A + i * h;
        double F = sin(x) * cos(x);
        double G = 2 * sin(2 * x) + 1;

        // Выводим результат в табличном формате с рамкой
        wcout << L"\u2502" << L" " << left << setw(3) << setfill(L' ') << i << L" " << L"\u2502"
              << setw(13) << fixed << setprecision(6) << x << L" " << L"\u2502"
              << setw(23) << fixed << setprecision(6) << F << L" " << L"\u2502"
              << setw(25) << fixed << setprecision(6) << G << L" " << L"\u2502" << endl;
    }

    // Нижняя граница таблицы
    wcout << L"\u2514" << setw(5) << setfill(L'\u2500') << L"\u2500"
          << setw(15) << setfill(L'\u2500') << L"\u2534"
          << setw(25) << setfill(L'\u2500') << L"\u2534"
          << setw(27) << setfill(L'\u2500') << L"\u2534" << L'\u2518' << endl;

    return 0;
}
