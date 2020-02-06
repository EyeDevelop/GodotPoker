//
// Created by eyedevelop on 03/02/2020.
//

#include <iostream>
#include <random>
#include <algorithm>
#include "card.h"

// These can be initialized in the initializer list
/*
Card::Card(const Suit suit, const Rank rank) noexcept
    : suit{ suit }, rank{ rank } {}
*/
Card::Card(Suit suit, Rank rank) noexcept {
    this->suit = suit;
    this->rank = rank;
}
// same here, why have a defalut ctor when this one is alrdy default?
// just = default;
Card::Card() noexcept {
    this->suit = HEARTS;
    this->rank = TWO;
}


Rank Card::get_rank() const noexcept {
    return this->rank;
}

Suit Card::get_suit() const noexcept {
    return this->suit;
}
// Card const& and const function
bool Card::same_rank(Card *o) noexcept {
    return this->rank == o->rank;
}
// Card const& and const function
bool Card::same_suit(Card *o) noexcept {
    return this->suit == o->suit;
}
// Constexpr arrays?
std::string Card::to_string() const noexcept {
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

bool Card::operator==(Card const &other) const noexcept {
    return this->suit == other.suit && this->rank == other.rank;
}

bool Card::operator<(Card const &other) const noexcept {
    return this->rank > other.rank;
}

Card Card::generate_random() noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> suit_distribution(0, CLOVERS);
    std::uniform_int_distribution<> rank_distribution(0, ACE);

    Suit s = static_cast<Suit>(suit_distribution(gen));
    Rank r = static_cast<Rank>(rank_distribution(gen));

    return Card{s, r};
}

bool Card::same_suit(std::vector<Card> const &cards) noexcept {
    Suit s = cards[0].get_suit();
    return std::all_of(cards.begin(), cards.end(), [s](Card const &c) { return c.suit == s; });
}

bool Card::same_rank(std::vector<Card> const &cards) noexcept {
    Rank r = cards[0].get_rank();
    return std::all_of(cards.begin(), cards.end(), [r](Card const &c) { return c.rank == r; });
}

int Card::count_suit(std::vector<Card> const &cards, Suit s) noexcept {
    return std::count_if(cards.begin(), cards.end(), [s](Card const &c) {
        return s == c.suit;
    });
}

int Card::count_rank(std::vector<Card> const &cards, Rank r) noexcept {
    return std::count_if(cards.begin(), cards.end(), [r](Card const &c) {
        return r == c.rank;
    });
}

int Card::get_max_suit_count(std::vector<Card> const &cards) noexcept {
    int maxCount = 0;
    for (int i = HEARTS; i <= CLOVERS; i++) {
        Suit s = static_cast<Suit>(i);
        int suitCount = count_suit(cards, s);
        maxCount = std::max(suitCount, maxCount);
    }

    return maxCount;
}

int Card::get_max_rank_count(std::vector<Card> const &cards) noexcept {
    int maxCount = 0;
    for (int i = TWO; i <= ACE; i++) {
        Rank r = static_cast<Rank>(i);
        int rankCount = count_rank(cards, r);
        maxCount = std::max(rankCount, maxCount);
    }

    return maxCount;
}

std::vector<Rank> Card::get_pairs(std::vector<Card> const &cards) noexcept {
    std::vector<Rank> ret;

    for (int i = ACE; i >= TWO; i--) {
        Rank r = static_cast<Rank>(i);
        if (count_rank(cards, r) == 2)
            ret.emplace_back(r);
    }

    return ret;
}
