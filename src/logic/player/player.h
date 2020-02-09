//
// Created by eyedevelop on 03/02/2020.
//

#ifndef GODOTPOKER_PLAYER_H
#define GODOTPOKER_PLAYER_H


#include <vector>
#include "../card/card.h"


enum Action {
    ALL_IN = -4,
    CHECK = -3,
    FOLD = -2,
    NOT_IN_GAME = -1
};

class Player {
    double funds;
    std::vector<Card> cards;
    bool inGame = false;
    std::string name;

public:
    explicit Player(std::string_view name) noexcept;

    Player(std::string_view name, double start_funds) noexcept;

    bool operator==(Player const &p) const noexcept;

    [[nodiscard]] double get_funds() const noexcept;

    [[nodiscard]] std::string get_name() const noexcept;

    double add_funds(double to_add) noexcept;

    [[nodiscard]] std::vector<Card> get_cards() const noexcept;

    void give_card(Card c) noexcept;

    void set_in_game() noexcept;

    void reset_in_game() noexcept;

    double fold() noexcept;

    double check(double current_pot) noexcept;

    double raise(double current_pot, double raise_amount) noexcept;

    double make_play(double current_pot) noexcept;
};


#endif //GODOTPOKER_PLAYER_H
