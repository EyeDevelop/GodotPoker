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
    Card(Suit suit, Rank rank) noexcept;

    Card() noexcept;

    bool operator==(Card const &other) const noexcept;

    bool operator<(Card const &other) const noexcept;

    [[nodiscard]] Suit get_suit() const noexcept;

    [[nodiscard]] Rank get_rank() const noexcept;

    bool same_suit(Card *o) noexcept;

    bool same_rank(Card *o) noexcept;

    [[nodiscard]] std::string to_string() const noexcept;

    static Card generate_random() noexcept;

    static bool same_suit(std::vector<Card> const &cards) noexcept;

    static bool same_rank(std::vector<Card> const &cards) noexcept;

    static int count_suit(std::vector<Card> const &cards, Suit s) noexcept;

    static int count_rank(std::vector<Card> const &cards, Rank r) noexcept;

    static int get_max_suit_count(std::vector<Card> const &cards) noexcept;

    static int get_max_rank_count(std::vector<Card> const &cards) noexcept;

    static std::vector<Rank> get_pairs(std::vector<Card> const &cards) noexcept;
};

#endif //GODOTPOKER_CARD_H