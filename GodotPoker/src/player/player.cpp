//
// Created by eyedevelop on 03/02/2020.
//

#include <random>
#include <iostream>
#include "player.h"

Player::Player() {
    this->funds = 0;
}

Player::Player(double start_funds) {
    this->funds = start_funds;
}

double Player::get_funds() {
    return this->funds;
}

double Player::add_funds(double to_add) {
    this->funds += to_add;
    return this->funds;
}

std::vector<Card> Player::get_cards() {
    return this->cards;
}

void Player::give_card(Card c) {
    this->cards.emplace_back(c);
}

void Player::reset_in_game() {
    this->inGame = false;
}

void Player::set_in_game() {
    this->inGame = true;
}

double Player::make_play() {
    if (!this->inGame) {
        return -1;
    }

    std::cout << "Your funds: " << this->funds << std::endl;
    std::cout << "Your cards: ";
    for (const Card &c : this->cards) {
        std::cout << c.to_string() << " ";
    }
    std::cout << std::endl;

    char option;
    std::cout << "Do you wish to (F)old, (C)heck or (R)aise: ";
    std::cin >> option;

    double raiseAmount = 0;
    switch(option) {
        case 'f':
        case 'F':
            return -2;

        case 'c':
        case 'C':
            return -3;

        case 'r':
        case 'R':
            std::cout << "Raise by how much: ";
            std::cin >> raiseAmount;
            if (raiseAmount > 0 && this->funds - raiseAmount > 0) {
                this->funds -= raiseAmount;
                return raiseAmount;
            } else {
                return make_play();
            }

        default:
            return -1;
    }
}

bool Player::operator==(Player const &p) const {
    return (*this) == p;
}
