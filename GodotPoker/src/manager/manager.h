//
// Created by eyedevelop on 03/02/2020.
//

#ifndef GODOTPOKER_MANAGER_H
#define GODOTPOKER_MANAGER_H


#include <vector>
#include "../player/player.h"
#include "../card/deck.h"

class Manager {
    std::vector<Player> players;
    Deck deck;

public:
    void add_player(Player const &p) noexcept;

    void remove_player(Player const &p) noexcept;

    static double do_turn(std::vector<Player> &active_players) noexcept;

    void start_game() noexcept;

    static std::vector<Player> check_win(std::vector<Player> &active_players, std::vector<Card> &board_cards) noexcept;
};


#endif //GODOTPOKER_MANAGER_H
