#include <iostream>
#include <string>
#include <list>
#include <utility>

#include "shiritori.h"

using namespace std;


Shiritori::Player::Player(string name) : name{std::move(name)} {};

void Shiritori::Player::setName(string name) {
    this->name = name;
}

string Shiritori::Player::getName() {
    return name;
}

bool Shiritori::operator==(const Shiritori::Player &p1, const Shiritori::Player &p2) {
    return p1.name == p2.name;
}

bool Shiritori::operator!=(const Shiritori::Player &p1, const Shiritori::Player &p2) {
    return !(p1 == p2);
}

Shiritori::Game::Game(int headcount) : headcount{headcount} {
    players = new Player[headcount];
};

int Shiritori::Game::getHeadcount() const { return headcount; }

void Shiritori::Game::setPlayer(int index, Player player) {
    players[index] = std::move(player);
}

Shiritori::Player Shiritori::Game::getPlayer(int index) const { return players[index]; }

void Shiritori::Game::go(Player &player, const string &word) {
    switch (check(player, word)) {
        case CheckResult::SAFE_WORD:
            printf("[%s] \"%s\" is passed\n", word.c_str(), word.c_str());
            usedWords.push_back(word);
            lastWord = word;
            times++;
            break;
        case CheckResult::FIRST_WORD:
            cout << "[" << word << "] " << "Start word is set to \"" << word << "\"" <<
                 endl;
            usedWords.push_back(word);
            lastWord = word;
            times++;
            break;
        case CheckResult::INVALID_FIRST_CHARACTER:
            printf("[%s] First character of \"%s\" is not equal to '%c'",
                   word.c_str(), word.c_str(),
                   lastWord[lastWord.length() - 1]
            );
            break;
        case CheckResult::USED_WORD:
            printf("[%s] \"%s\" is a used word.\n", word.c_str(), word.c_str());
            break;
        case CheckResult::NOT_PLAYER_TURN:
            cout << "Your word is ignored because of not your turn." << endl;
            break;
    }
}

int Shiritori::Game::check(const Player &player, string word) {
    if (player != players[times % headcount]) {
        return CheckResult::NOT_PLAYER_TURN;
    }
    if (lastWord.empty()) {
        return CheckResult::FIRST_WORD;
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

bool Shiritori::Game::isAvailableWord(const string &word) {
    if (wordlist.empty()) {
        return true;
    }
    for (auto &availableWord : wordlist) {
        if (availableWord == word)
            return true;
    }
    return false;
}

bool Shiritori::Game::isUsed(const string &word) {
    for (auto &usedWord : usedWords) {
        if (usedWord == word)
            return true;
    }
    return false;
}
