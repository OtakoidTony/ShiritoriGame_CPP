#include <iostream>
#include "shiritori.cpp"

using namespace std;

class Game : public Shiritori::Game {

public:
    Game(int headcount) : Shiritori::Game(headcount) {};

};

int main(int argc, char *argv[]) {
    auto *game = new Game(3);

    auto *player1 = new Shiritori::Player("OtakoidTony");
    auto *player2 = new Shiritori::Player("Rojiku");
    auto *player3 = new Shiritori::Player("Logic");

    game->setPlayer(0, *player1);
    game->setPlayer(1, *player2);
    game->setPlayer(2, *player3);

    cout << 1 << endl;
    game->go(*player1, "banana");
    cout << 2 << endl;
    game->go(*player2, "apple");
    cout << 3 << endl;
    game->go(*player2, "engine");
    cout << 4 << endl;
    game->go(*player3, "engine");
    cout << 5 << endl;
    game->go(*player1, "engine");

    return 0;
}