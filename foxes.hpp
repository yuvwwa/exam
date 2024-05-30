#include <cstdlib>
#include <ctime>
#include "move.hpp"
#include "result.hpp"

using namespace std;

class Foxes {
private:
    unsigned int **field;
    unsigned int field_size;
    unsigned int foxes_left;
public:
    Foxes(unsigned int size, unsigned int foxes);
    ~Foxes();
    Result step(Move &move);
    unsigned int getFieldSize();
    unsigned int getFoxesLeft();
};
