#include "computer.hpp"

Computer::Computer(unsigned int size) {
    field_size = size;

    used = new bool* [field_size + 2];
    near_foxes = new int* [field_size + 2];  
    
    for (unsigned int i = 0; i < size + 2; i++) {
        used[i] = new bool[field_size + 2];
        near_foxes[i] = new int[field_size + 2];
    }

    for (unsigned int i = 0; i < size + 2; i++) {
        for (unsigned int j = 0; j < size + 2; j++) {
            used[i][j] = false;
            near_foxes[i][j] = 0; // мы не знаем, есть ли рядом лисы - считаем, что их нет
        }
    }

    // отбортовка
    for (unsigned int i = 0; i < size + 2; i++) {
        used[i][0] = true;
        used[0][i] = true;
        used[i][size + 1] = true;
        used[size + 1][i] = true;
    }
}

Computer::~Computer() {
    for (unsigned int i = 0; i < field_size + 2; i++) {
        delete[] used[i];
        delete[] near_foxes[i];
    }
    delete[] used;
    delete[] near_foxes;
}

Result Computer::make_move(Foxes& foxes, Move& move) {
    Result result = foxes.step(move);
    used[move.x][move.y] = true;

    // если лисы пойманы
    if (result.type) {
        // для всех счётчков лис рядом, уменьшаем их на 1
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (near_foxes[move.x + i][move.y + j] > 0) {
                    near_foxes[move.x + i][move.y + j] -= result.foxes_count;
                }
            }
        }
    } else {
        // если получили новый счётчик лис, присваиваем его
        near_foxes[move.x][move.y] = result.foxes_count;
        // и если лис рядом нет - нет смысла ходить туда, где их нет
        if (result.foxes_count == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    used[move.x + i][move.y + j] = true;
                }
            }
        }
    }

    return result;
}

Move Computer::search() {
    queue <Move> priority_moves;
    // найти, если нам известна информация, что у какой-то ячейки есть рядом лисы
    for (int i = 1; i <= field_size; i++) {
        for (int j = 1; j <= field_size; j++) {
            if (near_foxes[i][j] > 0) {
                priority_moves.push(Move(i - 1, j - 1));
                priority_moves.push(Move(i    , j - 1));
                priority_moves.push(Move(i + 1, j - 1));
                priority_moves.push(Move(i - 1, j    ));
                priority_moves.push(Move(i + 1, j    ));
                priority_moves.push(Move(i - 1, j + 1));
                priority_moves.push(Move(i    , j + 1));
                priority_moves.push(Move(i + 1, j + 1));
                break;
            }
        }
    }

    while (!priority_moves.empty()) {
        Move mov = priority_moves.front();
        priority_moves.pop();
        if (used[mov.x][mov.y]) {
            continue;
        }
        return mov;
    }

    // нет ходов в приоритете, делаем случайный
    int moves = 0;
    for (int i = 1; i <= field_size; i++) {
        for (int j = 1; j <= field_size; j++) {
            if (!used[i][j]) {
                moves++;
            }
        }
    }

    // выбор случайного
    int rand_move = rand() % moves;
    for (int i = 1; i <= field_size; i++) {
        for (int j = 1; j <= field_size; j++) {
            if (used[i][j]) {
                continue;
            }
            if (rand_move == 0) {
                return Move(i, j);
            }
            rand_move--;
        }
    }
}
