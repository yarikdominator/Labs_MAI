/***********************************************************************************
*                       Курс КОМПЬЮТЕРНЫЕ ТЕХНОЛОГИИ                               *
*----------------------------------------------------------------------------------*
* Project Type  : Win64 Console Application                                        *
* Project Name  : Labs3                                                            *
* File Name     : Labs3.exe                                                        *
* Language      : CPP, MSVS 2022                                                   *
* Programmers   : Тихонов Павел Сергеевич, Ефимов Ярослав Сергеевич, М3О-119БB-24  *
* Modifyed By   :                                                                  *
* Created       : 19.11.2024                                                       *
* Last Revision : 21.11.2024                                                       *
* Comment(s)    : Одномерные массивы                                               *
***********************************************************************************/
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sstream>

struct Filenames {
    std::string correct_1;
    std::string correct_2;
    std::string correct_3;
    std::string error_empty;
    std::string error_invalid_format;
    std::string error_negative_params;
    std::string uncorrected_M1M2_1;
    std::string uncorrected_M1M2_2;
    std::string uncorrected_M1M2_3;
    std::string uncorrected_VEC;
    std::string uncorrected_VEC1;
    std::string uncorrected_VEC2;
};

// Имена файлов для различных тестов
Filenames filenames = {
    "test_correct_01.txt",
    "test_correct_02.txt",
    "test_correct_03.txt",
    "test_error_empty.txt",
    "test_error_invalid_format.txt",
    "test_error_negative_params.txt",
    "test_uncorrected_M1M2_1.txt",
    "test_uncorrected_M1M2_2.txt",
    "test_uncorrected_M1M2_3.txt",
    "test_uncorrected_VEC.txt",
    "test_uncorrected_VEC1.txt",
    "test_uncorrected_VEC2.txt"
};

// Имя файла для текущего теста
auto FNAME = "__tests__/" + filenames.correct_3;

// Максимальные размеры массивов
const int VECT1MAX = 8;
const int VECT2MAX = 10;

// Коды ошибок
constexpr int NOT_FOUND = 1;
constexpr int INVALID_DATA = 2;
constexpr int ACCESS_PERMISSION = 3;

int main() {
    // Получение текущего рабочего каталога
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Текущий рабочий каталог: " << cwd << std::endl;
    } else {
        std::cerr << "Ошибка при получении текущего рабочего каталога" << std::endl;
        return ACCESS_PERMISSION;
    }

    // ------------------------
	//  ЧТЕНИЕ ДАННЫХ ИЗ ФАЙЛА
	// ------------------------

    // Установка локали
    std::locale::global(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));

    const std::string CWDFN = std::string(cwd) + "/" + FNAME; // Путь к файлу
    int M1, M2;

    // Векторы для хранения данных
    std::vector<double> VECT1(VECT1MAX);
    std::vector<double> VECT2(VECT2MAX);
    std::vector<double> NEWVEC(floor(VECT2MAX / 2) + ceil(VECT1MAX / 2));

    // Итератор для нового вектора
    size_t newVectorIterator = 0;
    // Сумма элементов нового вектора
    double sumOfNewVec = 0;

    // Накопленные суммы для M1 и M2
    double accumulatedSumM1 = 0;
    double accumulatedSumM2 = 0;

    // Индекс и значение максимального отрицательного числа
    int maxNegativeIndex = -1;
    double maxNegativeValue = 0;

    std::cout << "Чтение данных из файла: " << CWDFN << std::endl;

    // Открытие файла для чтения std::ios::in указывает режим открытия файла(только чтение)
    std::fstream fin(FNAME, std::ios::in);

    if (!fin.is_open())
    {
        // Файл не найден
        std::cerr << "Файл \"" <<  CWDFN << "\"" << " не найден" << std::endl;

        fin.close(); // закрыть файл
        return NOT_FOUND;
    }

    if (fin.peek() == EOF) // файл пуст
    {
        std::cerr << "Файл \"" << CWDFN << "\" пустой\n";
        fin.close(); // закрыть файл
        return INVALID_DATA; // выход по ошибке
    }

    if(!(fin >> M1 >> M2)) {
        std::cerr << "Ошибка: не удалось заполнить параметры M1 и M2" << std::endl;
        return INVALID_DATA;
    }

    /**
     * Проверки необходимы для выполнения условий, указанных в пункте 5, где сказано, что M1 и M2
     * будут использоваться как индексы массивов. Следовательно, все положительные значения M1 и M2
     * допустимы, а отрицательные - нет.
     *
     * Согласно пункту 5, где говорится: "только в диапазоне индексов от M1 до M2", M1 должно быть
     * меньше M2. В противном случае длина диапазона будет отрицательной, что делает условие
     * нерелевантным.
     *
     * Также необходимо проверить, что M1 и M2 не превышают размер наибольшего массива (или индекс
     * последнего элемента массива). В противном случае индексы M1 и M2 могут выйти за пределы массива,
     * что приведет к критической ошибке.
     **/
    if(M1 < 0 || M2 < 0) {
        std::cerr << "Ошибка: M1 и M2 должны быть положительными числами" << std::endl;
        return INVALID_DATA;
    }

    if(M1 > M2) {
        std::cerr << "Ошибка: M1 должно быть меньше чем M2" << std::endl;
        return INVALID_DATA;
    }

    /**
     * VECT2MAX по услоивю задачи всегда больше чем VECT1MAX, поэтому учитывать только VECT2MAX.
    **/
    if (M2 > VECT2MAX) {
        std::cerr << "Ошибка: значение M2 превышает допустимый предел VECT2MAX" << std::endl;
        return INVALID_DATA;
    }

    /**
     * Сумма четных и нечетный индексов масивов VECT1 и VECT2 равна.
     * Целой части от деления ( VECT2MAX / 2) + результат деления (VECT1MAX / 2), округлённый в большую сторону.
     * Из этого следует, что M1 и M2 не должны превышать размер массива NEWVEC.
     **/
    if(M2 > NEWVEC.size()) {
        std::cerr << "Ошибка: M1 и M2 должны быть меньше чем размер массива NEWVEC" << std::endl;
        return INVALID_DATA;
    }


    // Заполнение массивов VECT1 и VECT2 из файла CWDFN
   for (auto& value : VECT1) {
        if (!(fin >> value)) {
            std::cerr << "Ошибка: не удалось заполнить VECT1" << std::endl;
            fin.close();
            return INVALID_DATA;
        }
    }

    for (auto& value : VECT2) {
        if (!(fin >> value)) {
            std::cerr << "Ошибка: не удалось заполнить VECT2" << std::endl;
            fin.close();
            return INVALID_DATA;
        }
    }

    // Проверка, что после считывания значений в fin что-то еще осталось
    if (fin.peek() != EOF) {
        std::cerr << "Ошибка: после считывания значений остались данные в файле: " << fin.peek() << std::endl;
        fin.close();
        return INVALID_DATA;
    }

    fin.close();

    // -----------------------------
	//  ОСНОВНОЙ АЛГОРИТМ ПРОГРАММЫ
	// -----------------------------

    // Формирование нового массива NEWVEC
   for (size_t i = 0; i < VECT2.size(); ++i) {
        // Оставляем только нечетные элементы
        if(i % 2 != 0) {
            /** Добавляем элемент в новый массив NEWVEC
             * и считаем сумму элементов **/
            NEWVEC[newVectorIterator] = VECT2[i];
            sumOfNewVec += VECT2[i];
            newVectorIterator++;
        }
    }

    for (size_t i = VECT1.size(); i-- > 0;) {
        // Оставляем только четные элементы
        if(i % 2 == 0) {
            double element = VECT1[i] * (-1);
            /** Добавляем элемент в новый массив NEWVEC
             * и считаем сумму элементов **/
            NEWVEC[newVectorIterator] = element;
            // По условию задачи берем противоположный знак
            sumOfNewVec += element;
            newVectorIterator++;
        }
    }


    // начиная с 0 индекса считаем сумму M1 элементов(инными словами сумму элементов от 0 до M1)
    for(size_t i = 0; i < M1; ++i) {
        accumulatedSumM1 += NEWVEC[i];
    }

    // начиная с последнего индекса считаем сумму M2 элементов(инными словами сумму элементов от последнего индекса до M2)
    for (size_t i = NEWVEC.size(); i-- > NEWVEC.size() - M2;) {
        accumulatedSumM2 += NEWVEC[i];
    }

    std::cout << "Сумма всех элементов массива [NEWVEC]: " << sumOfNewVec << "\n"
            << "Сумма первых " << M1 << " элементов: " << accumulatedSumM1 << "\n"
            << "Сумма последних " << M2 << " элементов: " << accumulatedSumM2 << std::endl;

    // Поиск максимального отрицательного числа на промежутке индексов [M1, M2]
    for (size_t i = static_cast<size_t>(M1); i < M2; ++i) {
        if(NEWVEC[i]  < maxNegativeValue) {
            maxNegativeValue = NEWVEC[i];
            maxNegativeIndex = i;
        }
    }

    std::cout << "Максимальное отрицательное число на промежутке индексов [" <<
         M1  << " , " << M2 << "]: " <<
         maxNegativeValue << "\n" << "Индекс максимального отрицательного числа в массиве [NEWVECT]: " <<
         maxNegativeIndex << std::endl;

    return 0;
}
