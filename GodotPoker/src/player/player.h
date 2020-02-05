//
// Created by eyedevelop on 03/02/2020.
//

#ifndef GODOTPOKER_PLAYER_H
#define GODOTPOKER_PLAYER_H


#include <vector>
#include "../card/card.h"

class Player {
    double funds;
    std::vector<Card> cards;
    bool inGame = false;
    std::string name;

public:
    explicit Player(std::string name);

    Player(std::string name, double start_funds);

    bool operator==(Player const &p) const;

    double get_funds();

    std::string get_name();

    double add_funds(double to_add);

    std::vector<Card> get_cards();

    void give_card(Card c);

    void set_in_game();

    void reset_in_game();

    double make_play(double current_pot);
};


#endif //GODOTPOKER_PLAYER_H
