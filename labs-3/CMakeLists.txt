cmake_minimum_required(VERSION 3.29)
project(labs3)

set(CMAKE_CXX_STANDARD 23)

# Путь к папке __tests__
set(TEST_DIR ${PROJECT_SOURCE_DIR}/__tests__)

# Находим все текстовые файлы в папке __tests__
file(GLOB TEST_FILES "${TEST_DIR}/*.txt")
message("Found test files: ${TEST_FILES}")

# Добавляем исполняемый файл
add_executable(labs3 main.cpp)

# Копируем всю папку __tests__ в папку сборки, сохраняя вложенность
file(COPY ${TEST_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Добавляем директорию __tests__ в список директорий для поиска включаемых файлов
target_include_directories(labs3 PUBLIC ${TEST_DIR})