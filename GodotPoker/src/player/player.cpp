//
// Created by eyedevelop on 03/02/2020.
//

#include <random>
#include <iostream>
#include <utility>
#include "player.h"

// initializer list
// pass std::string_view / keep like this, either one
Player::Player(std::string name) noexcept {
    this->name = std::move(name);
    this->funds = 0;
}

// same thing
Player::Player(std::string name, double start_funds) noexcept {
    this->name = std::move(name);
    this->funds = start_funds;
}

double Player::get_funds() const noexcept {
    return this->funds;
}

std::string Player::get_name() const noexcept {
    return this->name;
}

double Player::add_funds(double to_add) noexcept {
    this->funds += to_add;
    return this->funds;
}

std::vector<Card> Player::get_cards() const noexcept {
    return this->cards;
}

void Player::give_card(Card c) noexcept {
    this->cards.emplace_back(c);
}

void Player::reset_in_game() noexcept {
    this->inGame = false;
}

void Player::set_in_game() noexcept {
    this->inGame = true;
}

double Player::make_play(double current_pot) noexcept {
    if (!this->inGame) {
        return -1;
    }

    std::cout << "Your funds: " << this->funds << std::endl;
    std::cout << "Your cards: ";
    for (const Card &c : this->cards) {
        std::cout << c.to_string() << " ";
    }
    std::cout << std::endl;

    std::string option;
    std::cout << "Do you wish to (F)old, (C)heck/call or (R)aise: ";
    std::cin >> option;

    // magic numbers
    double raiseAmount = 0;
    // .at() does bounds checking -> overhead
    // user operator[]
    switch(option.at(0)) {
        case 'f':
        case 'F':
            return -2;

        case 'c':
        case 'C':
            if (this->funds >= current_pot) {
                this->funds -= current_pot;
                return -3;
            } else if (this->funds == 0) {  // All-In
                return -3;
            } else {
                std::cerr << "You do not have enough funds." << std::endl;
                return make_play(current_pot);
            }

        case 'r':
        case 'R':
            std::cout << "Raise by how much: ";
            std::cin >> raiseAmount;
            if (raiseAmount > 0 && this->funds >= raiseAmount + current_pot) {
                this->funds -= raiseAmount + current_pot;
                return raiseAmount;
            } else {
                std::cerr << "You do not have enough funds." << std::endl;
                return make_play(current_pot);
            }

        default:
            std::cerr << "That's not a valid option." << std::endl;
            return make_play(current_pot);
    }
}

bool Player::operator==(Player const &p) const noexcept {
    return (*this) == p;
}
