//
// Created by eyedevelop on 03/02/2020.
//

#include "deck.h"
#include <array>
#include <algorithm>
#include <chrono>

Deck::Deck() noexcept {
    this->reset();
}

void Deck::reset() noexcept {
    for (int i = 0; i <= CLOVERS; i++) {
        for (int j = 0; j <= ACE; j++) {
            Suit s = static_cast<Suit>(i);
            Rank r = static_cast<Rank>(j);

            this->cards.emplace_back(s, r);
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->cards.begin(), this->cards.end(), std::default_random_engine(seed));
}

bool Deck::contains(Card const& a) const noexcept {
    return std::find(cards.begin(), cards.end(), a) != cards.end();
}

void Deck::remove(Card const& a) noexcept {
    cards.erase(std::find(cards.begin(), cards.end(), a));
}

Card Deck::next_card() noexcept {
    Card ret = this->cards.back();
    this->cards.pop_back();
    return ret;
}

std::vector<Card> const& Deck::get_cards() noexcept {
    return cards;
}
