#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <locale>

class TableDrawer
{
public:
    TableDrawer(const std::vector<std::string> &headers, const std::vector<std::vector<std::string>> &rows)
        : headers(headers), rows(rows)
    {
        widths = calculateColumnWidths();
    }

    void drawTable()
    {
        drawTableBorder("top");
        drawTableRow(headers);
        drawTableBorder("middle");
        for (const auto &row : rows)
        {
            drawTableRow(row);
        }
        drawTableBorder("bottom");
    }

private:
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> rows;
    std::vector<int> widths;

    std::vector<int> calculateColumnWidths()
    {
        std::vector<int> widths(headers.size(), 0);
        for (size_t i = 0; i < headers.size(); ++i)
        {
            widths[i] = headers[i].size();
            for (const auto &row : rows)
            {
                widths[i] = std::max(widths[i], static_cast<int>(row[i].size()));
            }
        }
        return widths;
    }

    void drawTableRow(const std::vector<std::string> &row)
    {
        wchar_t verticalBar = L'│';
        std::wcout << verticalBar;
        for (size_t i = 0; i < row.size(); ++i)
        {
            std::wcout << " " << std::left << std::setw(widths[i]) << std::setfill(L' ') << std::wstring(row[i].begin(), row[i].end()) << " " << verticalBar;
        }
        std::wcout << std::endl;
    }

    void drawTableBorder(const std::string &borderType)
    {
        wchar_t left, middle, right;
        if (borderType == "top")
        {
            left = L'┌';
            middle = L'┬';
            right = L'┐';
        }
        else if (borderType == "middle")
        {
            left = L'├';
            middle = L'┼';
            right = L'┤';
        }
        else if (borderType == "bottom")
        {
            left = L'└';
            middle = L'┴';
            right = L'┘';
        }

        std::wcout << left;
        for (size_t i = 0; i < widths.size(); ++i)
        {
            std::wcout << std::setw(widths[i] + 2) << std::setfill(L'─') << L"";
            if (i < widths.size() - 1)
            {
                std::wcout << middle;
            }
        }
        std::wcout << right << std::endl;
    }
};

int main()
{
    // Устанавливаем локаль для корректного отображения символов Unicode
    std::locale::global(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));

    // Вводим значения A, B и N
    long double A = -(M_PI_4); // Исходное значение A = -π/4
    long double B = M_PI_2;    // Исходное значение B = π/2
    int N = 15;                // Исходное значение N = 15

    std::wcout << L"Введите A:";
    std::cin >> A;
    std::wcout << L"Введите B:";
    std::cin >> B;
    std::wcout << L"Введите N:";
    std::cin >> N;

    // **echo print**
    std::cout << "A:" << A << " B:" << B << " N:" << N << std::endl;

    // Проверка на корректность N
    if (N <= 0)
    {
        std::cout << "Ошибка: N должно быть > 0" << std::endl;
        return 1;
    }

    // Проверка на положительное значение длины интервала
    if (A > B)
    {
        std::swap(A, B);
    }

    // Вычисляем шаг h
    long double h = (B - A) / N;
    std::cout << "Шаг h = " << h << std::endl;

    // Наименования столбцов таблицы
    std::vector<std::string> headers = {"i", "x", "F(x) = sin(x) * cos(x)", "G(x) = 2 * sin(2 * x) + 1"};

    // Сбор данных для таблицы
    double x;
    double F;
    double G;
    std::vector<std::vector<std::string>> rows;
    for (int i = 0; i <= N; ++i)
    {
        x = A + i * h;
        F = sin(x) * cos(x);
        G = 2 * sin(2 * x) + 1;

        rows.push_back({std::to_string(i), std::to_string(x), std::to_string(F), std::to_string(G)});
    }

    // Создание экземпляра TableDrawer и отрисовка таблицы
    TableDrawer tableDrawer(headers, rows);
    tableDrawer.drawTable();

    return 0;
}