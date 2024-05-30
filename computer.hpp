#include <queue>
#include "foxes.hpp"

using namespace std;

class Computer {
private:
    bool **used;
    int **near_foxes;
    unsigned int field_size;
public:
    Computer(unsigned int size);
    ~Computer();
    Result make_move(Foxes &foxes, Move &move);
    Move search();
};
