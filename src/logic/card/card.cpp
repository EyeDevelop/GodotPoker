//
// Created by eyedevelop on 03/02/2020.
//

#include <iostream>
#include <random>
#include <algorithm>
#include "card.h"

Card::Card(const Suit suit, const Rank rank) noexcept
        : suit{suit}, rank{rank} {}

/**
 * Gets the rank of a card.
 *
 * @return The rank.
 */
Rank Card::get_rank() const noexcept {
    return this->rank;
}

/**
 * Gets the suit of a card.
 *
 * @return The suit.
 */
Suit Card::get_suit() const noexcept {
    return this->suit;
}

/**
 * Compares this card to another to check
 * if they have the same rank.
 *
 * @param o The other card.
 * @return True if they have the same rank.
 */
bool Card::same_rank(Card const &o) const noexcept {
    return this->rank == o.rank;
}

/**
 * Compares this card to another to check
 * if they have the same suit.
 *
 * @param o The other card.
 * @return True if they have the same suit.
 */
bool Card::same_suit(Card const &o) const noexcept {
    return this->suit == o.suit;
}

/**
 * Turns the card to a string.
 * Uses unicode symbols for the suits.
 *
 * @return The string representation of a card.
 */
std::string Card::to_string() const noexcept {
    static std::array<std::string, CLUBS + 1> card_names = {
            "♥",
            "♦",
            "♠",
            "♣"
    };

    static std::array<std::string, ACE + 1> rank_names = {
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

std::optional<Card> Card::from_string(std::string str) noexcept {
    static std::unordered_map<std::string, Suit> suit_str = {
            {"♥", HEARTS},
            {"H", HEARTS},

            {"♦", DIAMONDS},
            {"D", DIAMONDS},

            {"♠", SPADES},
            {"S", SPADES},

            {"♣", CLUBS},
            {"C", CLUBS}
    };

    static std::unordered_map<std::string, Rank> rank_str = {
            {"2",  TWO},
            {"3",  THREE},
            {"4",  FOUR},
            {"5",  FIVE},
            {"6",  SIX},
            {"7",  SEVEN},
            {"8",  EIGHT},
            {"9",  NINE},
            {"10", TEN},
            {"J",  JACK},
            {"Q",  QUEEN},
            {"K",  KING},
            {"A",  ACE}
    };

    std::string s = std::string(1, str[0]);
    std::string r = str.substr(1, str.length());

    if (suit_str.find(s) == suit_str.end() || rank_str.find(r) == rank_str.end())
        return std::nullopt;

    return {suit_str[s], rank_str[r]}
}

/**
 * Checks if two cards are the same.
 * Same rank and same suit.
 *
 * @param other The other card.
 * @return True if they are the same.
 */
bool Card::operator==(Card const &other) const noexcept {
    return this->suit == other.suit && this->rank == other.rank;
}

/**
 * Checks if a card is less than another.
 * This is based on the rank of the card.
 *
 * @param other The other card.
 * @return True if this rank < other rank.
 */
bool Card::operator<(Card const &other) const noexcept {
    return this->rank > other.rank;
}

/**
 * Generates a completely random card.
 *
 * @return The random card.
 */
Card Card::generate_random() noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> suit_distribution(0, CLUBS);
    std::uniform_int_distribution<> rank_distribution(0, ACE);

    Suit s = static_cast<Suit>(suit_distribution(gen));
    Rank r = static_cast<Rank>(rank_distribution(gen));

    return Card{s, r};
}

/**
 * Compares a vector of cards
 * to check if they have the same suit.
 *
 * @param cards The vector of cards.
 * @return True if they all have the same suit.
 */
bool Card::same_suit(std::vector<Card> const &cards) noexcept {
    Suit s = cards[0].get_suit();
    return std::all_of(cards.begin(), cards.end(), [s](Card const &c) { return c.suit == s; });
}

/**
 * Compares a vector of cards
 * to check if they have the same rank.
 *
 * @param cards The vector of cards.
 * @return True if they all have the same rank.
 */
bool Card::same_rank(std::vector<Card> const &cards) noexcept {
    Rank r = cards[0].get_rank();
    return std::all_of(cards.begin(), cards.end(), [r](Card const &c) { return c.rank == r; });
}

/**
 * Counts the occurrence of a given suit in a vector
 * of cards.
 *
 * @param cards The vector of cards.
 * @param s The suit to count.
 * @return How often _s_ occurs in cards.
 */
int Card::count_suit(std::vector<Card> const &cards, Suit s) noexcept {
    return std::count_if(cards.begin(), cards.end(), [s](Card const &c) {
        return s == c.suit;
    });
}

/**
 * Counts the occurence of a given rank in a vector
 * of cards.
 *
 * @param cards The vector of cards.
 * @param r The rank to count.
 * @return How often _r_ occurs in cards.
 */
int Card::count_rank(std::vector<Card> const &cards, Rank r) noexcept {
    return std::count_if(cards.begin(), cards.end(), [r](Card const &c) {
        return r == c.rank;
    });
}

/**
 * Checks each suit to see how often they occur
 * in a given card vector.
 *
 * @param cards The vector of cards.
 * @return The frequency of the most occurring suit in cards.
 */
int Card::get_max_suit_count(std::vector<Card> const &cards) noexcept {
    int maxCount = 0;
    for (int i = HEARTS; i <= CLUBS; i++) {
        Suit s = static_cast<Suit>(i);
        int suitCount = count_suit(cards, s);
        maxCount = std::max(suitCount, maxCount);
    }

    return maxCount;
}

/**
 * Checks each rank to see how often they occur
 * in a given card vector.
 *
 * Used for retrieving pairs, 3 of a kinds and 4 of a kinds.
 *
 * @param cards The vector of cards.
 * @return The frequency of the most occurring rank in cards.
 */
int Card::get_max_rank_count(std::vector<Card> const &cards) noexcept {
    int maxCount = 0;
    for (int i = TWO; i <= ACE; i++) {
        Rank r = static_cast<Rank>(i);
        int rankCount = count_rank(cards, r);
        maxCount = std::max(rankCount, maxCount);
    }

    return maxCount;
}

/**
 * Gets all the pairs in a card vector.
 *
 * @param cards The card vector.
 * @return A vector of ranks which form a pair in cards.
 */
std::vector<Rank> Card::get_pairs(std::vector<Card> const &cards) noexcept {
    std::vector<Rank> ret;

    for (int i = ACE; i >= TWO; i--) {
        Rank r = static_cast<Rank>(i);
        if (count_rank(cards, r) == 2)
            ret.emplace_back(r);
    }

    return ret;
}
