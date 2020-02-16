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
    double funds = 0;

    std::vector<Card> cards;
    std::vector<Card> *table_cards;

    bool in_game = false;
    bool networked = false;

    std::string name;

public:
    explicit Player(std::string_view name) noexcept;

    Player(std::string_view name, double start_funds) noexcept;

    Player(std::string_view name, double start_funds, bool networked) noexcept;

    bool operator==(Player const &p) const noexcept;

    [[nodiscard]] double get_funds() const noexcept;

    [[nodiscard]] std::string get_name() const noexcept;

    double add_funds(double to_add) noexcept;

    [[nodiscard]] std::vector<Card> get_cards() const noexcept;

    void give_card(Card c) noexcept;

    void set_in_game(std::vector<Card> *t_cards) noexcept;

    void reset_in_game() noexcept;

    double fold() noexcept;

    double check(double to_check) noexcept;

    double raise(double to_check, double raise_amount) noexcept;

    double make_play(double current_pot, double to_check) noexcept;

    double make_play_cli(double current_pot, double to_check) noexcept;

    double make_play_net(double to_check, Action a, double amount) noexcept;
};


#endif //GODOTPOKER_PLAYER_H
