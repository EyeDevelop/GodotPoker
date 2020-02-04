//
// Created by eyedevelop on 03/02/2020.
//

#include "deck.h"
#include <array>
#include <algorithm>

Deck::Deck() {
    this->reset();
}

void Deck::reset() {
    std::vector<Card> possible_combinations;
    for (int i = 0; i <= CLOVERS; i++) {
        for (int j = 0; j <= ACE; j++) {
            Suit s = static_cast<Suit>(i);
            Rank r = static_cast<Rank>(j);

            possible_combinations.emplace_back(s, r);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    while (!possible_combinations.empty()) {
        std::uniform_int_distribution<> combination_distribution(0, possible_combinations.size());
        int index = combination_distribution(gen);

        this->cards.emplace_back(possible_combinations[index]);
        possible_combinations.erase(possible_combinations.begin() + index);
    }
}

bool Deck::contains(Card const& a) const {
    return std::find(cards.begin(), cards.end(), a) != cards.end();
}

void Deck::remove(Card const& a) {
    cards.erase(std::find(cards.begin(), cards.end(), a));
}

Card Deck::next_card() {
    Card ret = this->cards.back();
    this->cards.pop_back();
    return ret;
}

std::vector<Card> Deck::get_cards() {
    return cards;
}
