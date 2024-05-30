#include <iostream>
#include <chrono>
#include <thread>
#include "computer.hpp"

using namespace std;

class Game {
public:
    void play(); // здесь цикл до тех пор, пока геттер лис возвращает больше нуля
    void show();
};
