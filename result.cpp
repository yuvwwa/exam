#include "result.hpp"
using namespace std;

Result::Result(bool _type, int _foxes_count) {
    //класс для хранения данных
    //bool type: если type = true, то foxes_count - сколько лис было найдено (убито); если type = false, то foxes_count - сколько лис находится рядом.
    type = _type;
    foxes_count = _foxes_count;
}
