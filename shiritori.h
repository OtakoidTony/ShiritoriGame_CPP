#ifndef SHIRITORIGAME_SHIRITORI_H
#define SHIRITORIGAME_SHIRITORI_H

#include <string>
#include <list>

using namespace std;

namespace Shiritori {
    enum CheckResult {
        SAFE_WORD,
        FIRST_WORD,
        INVALID_FIRST_CHARACTER,
        USED_WORD,
        NOT_PLAYER_TURN,
        UNAVAILABLE_WORD
    };

    class Player {
        string name;
    public:
        Player() = default;

        explicit Player(string name);

        void setName(string name);

        string getName();

        friend bool operator==(const Player &p1, const Player &p2);

        friend bool operator!=(const Player &p1, const Player &p2);
    };

    class Game {
        Player *players;
        int headcount;
        list<string> usedWords;
        string lastWord = "";
        int times = 0;
        list<string> wordlist;
    public:
        explicit Game(int headcount);

        int getHeadcount() const;

        void setPlayer(int index, Player player);

        Player getPlayer(int index) const;

        void go(Player &player, const string &word);

        int check(const Player &player, string word);

    private:
        bool isAvailableWord(const string &word);

        bool isUsed(const string &word);
    };
}
#endif //SHIRITORIGAME_SHIRITORI_H
