//
// Created by eyedevelop on 03/02/2020.
//

#ifndef GODOTPOKER_MANAGER_H
#define GODOTPOKER_MANAGER_H

#include <vector>
#include "../player/player.h"
#include "../card/deck.h"

class Manager {
    std::vector<Player *> players;
    std::vector<Player *> folded_players;

    std::vector<Card> table_cards;

    size_t current_player = 0;
    size_t round_end_at = 0;
    size_t round_num = 0;

    double raise_delta = 0;
    double biggest_raise = 0;
    double pot = 0;

    bool active = true;

    Deck deck;

public:
    void add_player(Player *p) noexcept;

    void remove_player(Player *p) noexcept;

    std::vector<Player *> get_players() noexcept;

    void next_play() noexcept;

    void next_round() noexcept;

    void start_game() noexcept;

    Player *get_current_player() noexcept;

    std::vector<Card> get_cards() noexcept;

    static std::vector<Player *>
    check_win(std::vector<Player *> const &active_players, std::vector<Card> const &board_cards) noexcept;
};


#endif //GODOTPOKER_MANAGER_H
