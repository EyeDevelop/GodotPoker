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
    Deck deck;

public:
    void add_player(Player *p) noexcept;

    void remove_player(Player *p) noexcept;

    double do_turn(std::vector<Player *> &folded_players);

    double do_turn(std::vector<Player *> &folded_players, std::optional<std::string_view> raiser,
                   std::optional<double> raise_amount, std::optional<size_t> rotate_offset) noexcept;

    void start_game() noexcept;

    static std::vector<Player *>
    check_win(std::vector<Player *> const &active_players, std::vector<Card> const &board_cards) noexcept;
};


#endif //GODOTPOKER_MANAGER_H
