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
    Deck();

    void reset();

    void remove(Card const &a);

    [[nodiscard]] bool contains(Card const &a) const;

    Card next_card();

    std::vector<Card> get_cards();
};

#endif //GODOTPOKER_DECK_H
