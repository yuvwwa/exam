#include "foxes.hpp"

using namespace std;

Foxes::Foxes(unsigned int size, unsigned int foxes) {
    srand(time(nullptr));
    
    foxes_left = foxes;
    field_size = size;
    
    //Добавление строк и столбцов по краям для оптимизации игры компьютера.
    field = new unsigned int* [size + 2];
    for (unsigned int i = 0; i < field_size + 2; i++) {
        field[i] = new unsigned int[field_size + 2];
    }

    //Всем координатам поля присваивается 0.
        for (unsigned int i = 0; i < field_size + 2; i++) {
        for (unsigned int j = 0; j < field_size + 2; j++) {
            field[i][j] = 0;
        }
    }
    //рандомно заполняем поле лисами.
    for (unsigned int i = 0; i < foxes_left; i++) {
        unsigned int x = rand() % field_size;
        unsigned int y = rand() % field_size;
        field[x + 1][y + 1]++;
    }
}

Foxes::~Foxes() {
    //деструктор динамического массива
    for (unsigned int i = 0; i < field_size + 2; i++) {
        delete[] field[i];
    }
    delete[] field;
}

Result Foxes::step(Move &move) {
    //сохранить количество лис в координату, куда пошёл игрок
    unsigned int foxes_count = field[move.x][move.y];
    //если лис больше 0, заменить ячейку на 0
    if (foxes_count > 0) {
        foxes_left -= foxes_count;
        field[move.x][move.y] = 0;
        return Result(1, foxes_count);
    }
    //если лис нет, посчитать лис рядом
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int x = move.x + i;
            int y = move.y + j;
            foxes_count += field[x][y];
        }
    }
    //вернуть Result(type = 0, count = лисы рядом)
    return Result(0, foxes_count);
}

//функции, которые мы будем использовать в game.hpp
unsigned int Foxes::getFieldSize() {
    return field_size;
}

unsigned int Foxes::getFoxesLeft() {
    return foxes_left;
}
