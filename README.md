# PointsVisualization
### Dependencies
- Visual stusio / GCC
- VCPKG
- Cmake 
- SFML
---
### How build from source
1. Clone source 
    - `git clone ...`
2. Configure project
    - `mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=<path/to/vcpkg>/scripts`
3. Build project
    - `cmake --build . --config release --parallel`
5. Execute 
    - Run file 'Example'
---
### Description of the files
 - CMakeLists.txt -- Файл сборки
 - main.cpp -- Точка входа приложения Example
 - PointToSphere.h -- Заголовочный файл библиотеки визуализации точек 
 - PointToSphere.cpp -- Реализация библиотеки визуализации точек
 - test.cpp -- Тесты библиотеки
 - widget.h -- Реализация виджета для библиотеки