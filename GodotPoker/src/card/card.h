//
// Created by eyedevelop on 03/02/2020.
//

#ifndef GODOTPOKER_CARD_H
#define GODOTPOKER_CARD_H

#include <string>
#include <array>
#include <random>

enum Suit {
    HEARTS,
    DIAMONDS,
    SPADES,
    CLOVERS
};

enum Rank {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

class Card {
    Rank rank;
    Suit suit;

public:
    Card(Suit suit, Rank rank);

    Card();

    bool operator==(Card const &other) const;

    bool operator<(Card const &other) const;

    Suit get_suit();

    Rank get_rank();

    bool same_suit(Card *o);

    bool same_rank(Card *o);

    [[nodiscard]] std::string to_string() const;

    static Card generate_random();

    static bool same_suit(std::vector<Card> &cards);

    static bool same_rank(std::vector<Card> &cards);

    static int count_suit(std::vector<Card> &cards, Suit s);

    static int count_rank(std::vector<Card> &cards, Rank r);

    static int get_max_suit_count(std::vector<Card> &cards);

    static int get_max_rank_count(std::vector<Card> &cards);

    static std::vector<Rank> get_pairs(std::vector<Card> &cards);
};

#endif //GODOTPOKER_CARD_H