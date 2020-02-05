//
// Created by eyedevelop on 03/02/2020.
//

#include <iostream>
#include <random>
#include <algorithm>
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

bool Card::operator<(Card const &other) const {
    return (int) this->rank > (int) other.rank;
}

Card Card::generate_random() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> suit_distribution(0, CLOVERS);
    std::uniform_int_distribution<> rank_distribution(0, ACE);

    Suit s = static_cast<Suit>(suit_distribution(gen));
    Rank r = static_cast<Rank>(rank_distribution(gen));

    return Card{s, r};
}

bool Card::same_suit(std::vector<Card> &cards) {
    Suit s = cards[0].suit;
    bool same_suit = true;

    for (Card &c : cards) {
        same_suit &= (s == c.suit);
    }

    return same_suit;
}

bool Card::same_rank(std::vector<Card> &cards) {
    Rank r = cards[0].rank;
    bool same_rank = true;

    for (Card &c : cards) {
        same_rank = same_rank && (r == c.rank);
    }

    return same_rank;
}

int Card::count_suit(std::vector<Card> &cards, Suit s) {
    return std::count_if(cards.begin(), cards.end(), [s](Card const &c) {
        return s == c.suit;
    });
}

int Card::count_rank(std::vector<Card> &cards, Rank r) {
    return std::count_if(cards.begin(), cards.end(), [r](Card const &c) {
        return r == c.rank;
    });
}

int Card::get_max_suit_count(std::vector<Card> &cards) {
    int maxCount = 0;
    for (int i = HEARTS; i <= CLOVERS; i++) {
        Suit s = static_cast<Suit>(i);
        int suitCount = count_suit(cards, s);
        maxCount = std::max(suitCount, maxCount);
    }

    return maxCount;
}

int Card::get_max_rank_count(std::vector<Card> &cards) {
    int maxCount = 0;
    for (int i = TWO; i <= ACE; i++) {
        Rank r = static_cast<Rank>(i);
        int rankCount = count_rank(cards, r);
        maxCount = std::max(rankCount, maxCount);
    }

    return maxCount;
}

std::vector<Rank> Card::get_pairs(std::vector<Card> &cards) {
    std::vector<Rank> ret;

    for (int i = ACE; i >= TWO; i--) {
        Rank r = static_cast<Rank>(i);
        if (count_rank(cards, r) == 2)
            ret.emplace_back(r);
    }

    return ret;
}
