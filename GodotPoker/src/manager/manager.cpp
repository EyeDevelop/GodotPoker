//
// Created by eyedevelop on 03/02/2020.
//

#include <algorithm>
#include "manager.h"

void Manager::add_player(Player const &p) {
    this->players.emplace_back(p);
}

void Manager::remove_player(Player const &p) {
    this->players.erase(std::find(this->players.begin(), this->players.end(), p));
}

double Manager::do_turn(std::vector<Player> *active_players) {
    double potDelta = 0;
    for (Player p : *active_players) {
        double ret = p.make_play();
        if (ret == -2)
            active_players->erase(std::find(active_players->begin(), active_players->end(), p));
        else if (ret > 0)
            potDelta += ret;
    }

    return potDelta;
}

void Manager::start_game() {
    for (Player p : players) {
        p.set_in_game();
        p.give_card(this->deck.next_card());
        p.give_card(this->deck.next_card());
    }

    int turnCount = 0;
    double pot = 0;
    std::vector<Player> active_players = this->players;
    std::vector<Card> board_cards;

    while (turnCount < 4 && active_players.size() > 1) {
        if (turnCount == 1) {
            for (int i = 0; i < 3; i++) {
                board_cards.emplace_back(Card::generate_random());
            }
        } else {
            board_cards.emplace_back(Card::generate_random());
        }

        pot = do_turn(&active_players);
        turnCount++;
    }

    if (active_players.size() == 1) {
        active_players[0].add_funds(pot);
    }

    for (Player p : players)
        p.reset_in_game();
}

int main() {
    Manager m{};
    Player p{1200};
    Player p2{20};

    m.add_player(p);
    m.add_player(p2);

    m.start_game();
}
