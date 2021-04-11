#include <iostream>
#include <string>
#include <list>
#include <utility>


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

        explicit Player(string name) : name{std::move(name)} {};

        void setName(string name) {
            this->name = name;
        }

        string getName() {
            return name;
        }

        friend bool operator==(const Player &p1, const Player &p2) {
            return p1.name == p2.name;
        }

        friend bool operator!=(const Player &p1, const Player &p2){
            return !(p1==p2);
        }
    };

    class Game {
        Player *players;
        int headcount;
        list<string> usedWords;
        string lastWord = "";
        int times = 0;
        list<string> wordlist;
    public:
        explicit Game(int headcount) : headcount{headcount} {
            players = new Player[headcount];
        };

        int getHeadcount() const { return headcount; }

        void setPlayer(int index, Player player) {
            players[index] = std::move(player);
        }

        Player getPlayer(int index) const { return players[index]; }

        void go(const Player &player, const string &word) {
            switch (check(player, word)) {
                case CheckResult::SAFE_WORD:
                    cout << "[" << word << "] " << "통과되었습니다." << endl;
                    usedWords.push_back(word);
                    lastWord = word;
                    times++;
                    break;
                case CheckResult::FIRST_WORD:
                    cout << "[" << word << "] " << "첫 단어를 발화하였습니다." << endl;
                    usedWords.push_back(word);
                    lastWord = word;
                    times++;
                    break;
                case CheckResult::INVALID_FIRST_CHARACTER:
                    cout << "[" << word << "] " << "입력하신 단어의 첫 글자가 마지막 단어의 마지막 글자와 다릅니다." << endl;
                    break;
                case CheckResult::USED_WORD:
                    cout << "[" << word << "] " << "이미 사용한 단어입니다." << endl;
                    break;
                case CheckResult::NOT_PLAYER_TURN:
                    cout << "아직 플레이어의 차례가 아닙니다." << endl;
                    break;
            }
        }

        int check(const Player &player, string word) {
            if (lastWord.empty()) {
                return CheckResult::FIRST_WORD;
            }
            if (player != players[times % headcount]) {
                return CheckResult::NOT_PLAYER_TURN;
            }
            if (!isAvailableWord(word)) {
                return CheckResult::UNAVAILABLE_WORD;
            }
            if (this->lastWord[(this->lastWord).length() - 1] != word[0]) {
                return CheckResult::INVALID_FIRST_CHARACTER;
            }
            if (isUsed(word)) {
                return CheckResult::USED_WORD;
            }
            return CheckResult::SAFE_WORD;
        }

    private:
        bool isAvailableWord(const string &word) {
            if (wordlist.empty()) {
                return true;
            }
            for (auto &availableWord : wordlist) {
                if (availableWord == word)
                    return true;
            }
            return false;
        }

        bool isUsed(const string &word) {
            for (auto &usedWord : usedWords) {
                if (usedWord == word)
                    return true;
            }
            return false;
        }
    };
}