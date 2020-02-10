//
// Created by eyedevelop on 03/02/2020.
//

#ifndef GODOTPOKER_DECK_H
#define GODOTPOKER_DECK_H

#include <array>
#include <vector>
#include "card.h"

class Deck {
    std::vector<Card> cards;

public:
    Deck() noexcept;

    void reset() noexcept;

    void remove(Card const &a) noexcept;

    [[nodiscard]] bool contains(Card const &a) const noexcept;

    Card next_card() noexcept;

    std::vector<Card> const &get_cards() noexcept;
};

#endif //GODOTPOKER_DECK_H
