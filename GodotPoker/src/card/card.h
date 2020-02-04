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

    Suit get_suit();

    Rank get_rank();

    bool same_suit(Card *o);

    bool same_rank(Card *o);

    [[nodiscard]] std::string to_string() const;

    static Card generate_random() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> suit_distribution(0, CLOVERS);
        std::uniform_int_distribution<> rank_distribution(0, ACE);

        Suit s = static_cast<Suit>(suit_distribution(gen));
        Rank r = static_cast<Rank>(rank_distribution(gen));

        return Card{s, r};
    }
};

#endif //GODOTPOKER_CARD_H