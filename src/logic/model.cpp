//
// Created by eyedevelop on 10/02/2020.
//

#include <algorithm>
#include "model.h"

Model::Model() : players{nullptr}, m{std::nullopt} {}

void Model::set_manager(Manager &model) {
    this->m = std::optional<Manager>(model);
    this->players = &model.get_players();
}

void Model::add_player(Player *p) {
    this->players->push_back(p);
}

void Model::remove_player(Player *p) {
    std::vector<Player *> to_remove;
    for (Player *const my_p : *this->players) {
        if (p->get_name() == my_p->get_name()) {
            to_remove.push_back(my_p);
        }
    }

    for (Player *const rem : to_remove) {
        this->players->erase(std::find(this->players->begin(), this->players->end(), rem));
    }
}
