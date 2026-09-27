#include "carddeck.h"
#include <vector>
#include <deque>
#include <cstdlib>
#include <random>
#include <compare>

Carddeck::Carddeck(int cap)
{
    if (cap <= 0) throw std::invalid_argument("Not positive suit capacity - can't build a deck");

    this->suit_capacity = cap;
    new_deck();
}

Card::Card(int value, std::string suit)
{
    this->value = value;
    this->suit = std::move(suit);
}

void Carddeck::new_deck()
{
    std::deque<std::string> suits = {"clubs", "spades", "diamonds", "hearts"};
    std::vector<Card> fut_deck;
    
    while (!suits.empty())
    {
        for (int i = 1; i <= suit_capacity; ++i)
            {
                fut_deck.push_back(Card(i, suits.front()));
            }
            suits.pop_front();
        }

        auto shuffle = [&]()
        {
            std::random_device shuffler;
            std::mt19937 rng(shuffler());
            std::shuffle(fut_deck.begin(), fut_deck.end(), rng);
        };

        shuffle();

        for (const auto& card : fut_deck)
        {
            deck.push(card);
        }
}

Card Carddeck::operator()()
{
    Card card = deck.top();
    deck.pop();
    if (deck.empty()) new_deck();
    return card;
}