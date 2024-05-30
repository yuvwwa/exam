#include "game.hpp"

using namespace std;

const int SIZE = 10;
const int FOXES = 8;

void Game::play() {
    //цикл, благодаря которому будет играть пользователь
    Foxes foxes(SIZE, FOXES);
    
    cout << "Field size = " << foxes.getFieldSize() << "x" << foxes.getFieldSize() << endl;
    cout << "Foxes left = " << foxes.getFoxesLeft() << endl;

    while (foxes.getFoxesLeft() > 0) {
        int x, y;
        cout << "Enter (x, y): ";
        cin >> x >> y;

        if (x < 1 || x > foxes.getFieldSize() + 1 || y < 1 || y > foxes.getFieldSize() + 1) {
            cout << "Invalid coordinates. Try again." << endl;
            continue;
        }

        Move move(x, y);
        Result res = foxes.step(move);
        
        // если это счётчик пойманных лис
        if (res.type) {
            cout << "You've found " << res.foxes_count << " foxes." << endl;
            cout << "Foxes left: " << foxes.getFoxesLeft() << endl;
        } else {
            cout << "Foxes near: " << res.foxes_count << endl;
        }
    }
}

void Game::show() {
    //цикл, благодаря которому будет играть компьютер
    Computer comp(SIZE);
    Foxes foxes(SIZE, FOXES);

    cout << "Field size = " << foxes.getFieldSize() << "x" << foxes.getFieldSize() << endl;
    cout << "Foxes left = " << foxes.getFoxesLeft() << endl;

    while (foxes.getFoxesLeft() > 0) {
        Move move = comp.search();
        cout << "Computer played = (" << move.x << ", " << move.y << ")" << endl;
        Result res = comp.make_move(foxes, move);

        if (res.type) {
            cout << "Have found " << res.foxes_count << " foxes." << endl;
            cout << "Foxes left: " << foxes.getFoxesLeft() << endl;
        } else {
            cout << "Foxes near: " << res.foxes_count << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}
