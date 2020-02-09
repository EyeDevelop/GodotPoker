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
    CLUBS
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

    Card() = default;

    bool operator==(Card const &other) const noexcept;

    bool operator<(Card const &other) const noexcept;

    [[nodiscard]] Suit get_suit() const noexcept;

    [[nodiscard]] Rank get_rank() const noexcept;

    [[nodiscard]] bool same_suit(Card const &o) const noexcept;

    [[nodiscard]] bool same_rank(Card const &o) const noexcept;

    [[nodiscard]] std::string to_string() const noexcept;

    static Card from_string(std::string str) noexcept;

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