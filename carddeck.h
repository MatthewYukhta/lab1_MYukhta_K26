#pragma once
#include <stack>
#include <string>
#include <compare>

struct Card
{
    friend class Carddeck;

    private:
        int value;
        std::string suit;
        Card(int val, std::string suit);

    public:
        std::strong_ordering operator<=>(const Card& other) const { return this->value <=> other.value; };
};

class Carddeck
{
    private:
        std::stack<Card> deck;
        int suit_capacity;
        void new_deck();

    public:
        Carddeck(int cap);
        Card operator()();
};