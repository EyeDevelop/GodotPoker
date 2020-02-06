//
// Created by eyedevelop on 03/02/2020.
//

#include <random>
#include <iostream>
#include "player.h"

Player::Player(std::string_view name) noexcept
        : name{name}, funds{0} {}

Player::Player(std::string_view name, double start_funds) noexcept
        : name{name}, funds{start_funds} {}

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
        return static_cast<double>(Action::NOT_IN_GAME);
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

    if (option.length() == 0) {
        std::cerr << "Please enter your move." << std::endl;
        return make_play(current_pot);
    }

    double raiseAmount = 0;
    switch (option[0]) {
        case 'f':
        case 'F':
            return static_cast<double>(Action::FOLD);

        case 'c':
        case 'C':
            if (this->funds >= current_pot) {
                this->funds -= current_pot;
                return static_cast<double>(Action::CHECK);
            } else {
                this->funds = 0;
                return static_cast<double>(Action::CHECK);
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
    return this->name == p.name;
}
