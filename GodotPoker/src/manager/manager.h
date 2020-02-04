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
    void add_player(Player const &p);

    void remove_player(Player const &p);

    static double do_turn(std::vector<Player> *active_players);

    void start_game();
};


#endif //GODOTPOKER_MANAGER_H
