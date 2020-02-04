//
// Created by eyedevelop on 03/02/2020.
//

#include <iostream>
#include <random>
#include "card.h"

Card::Card(Suit suit, Rank rank) {
    this->suit = suit;
    this->rank = rank;
}

Card::Card() {
    this->suit = HEARTS;
    this->rank = TWO;
}


Rank Card::get_rank() {
    return this->rank;
}

Suit Card::get_suit() {
    return this->suit;
}

bool Card::same_rank(Card *o) {
    return this->rank == o->rank;
}

bool Card::same_suit(Card *o) {
    return this->suit == o->suit;
}

std::string Card::to_string() const {
    std::array<std::string, CLOVERS + 1> card_names = {
            "♥",
            "♦",
            "♠",
            "♣"
    };

    std::array<std::string, ACE + 1> rank_names = {
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "J",
            "Q",
             "K",
            "A",
    };

    return card_names[this->suit] + rank_names[this->rank];
}

bool Card::operator==(Card const &other) const {
    return this->suit == other.suit && this->rank == other.rank;
}
