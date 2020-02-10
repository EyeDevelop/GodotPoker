//
// Created by eyedevelop on 10/02/2020.
//

#ifndef GODOTPOKER_MODEL_H
#define GODOTPOKER_MODEL_H

#include "manager/manager.h"

class Model {
    std::vector<Player *> *players;
    std::optional<Manager> m;

public:
    Model();

    void set_manager(Manager &model);

    void add_player(Player *p);

    void remove_player(Player *p);
};


#endif //GODOTPOKER_MODEL_H
