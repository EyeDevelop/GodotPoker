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

/**
 * Gets the amount of funds this player has.
 *
 * @return Those funds.
 */
double Player::get_funds() const noexcept {
    return this->funds;
}

/**
 * Gets the name of this player.
 *
 * @return The name.
 */
std::string Player::get_name() const noexcept {
    return this->name;
}

/**
 * Adds funds to this player.
 *
 * @param to_add The funds to add.
 * @return The funds after adding.
 */
double Player::add_funds(double to_add) noexcept {
    this->funds += to_add;
    return this->funds;
}

/**
 * Gets the cards this player has.
 *
 * @return A vector of cards the player possesses.
 */
std::vector<Card> Player::get_cards() const noexcept {
    return this->cards;
}

/**
 * Gives a card to this player.
 *
 * @param c The card to give.
 */
void Player::give_card(Card c) noexcept {
    this->cards.emplace_back(c);
}

/**
 * Sets the player ready for a new game.
 * The player is not registered to be in-game after.
 */
void Player::reset_in_game() noexcept {
    this->cards.clear();
    this->inGame = false;
}

/**
 * Sets the player to be in-game.
 */
void Player::set_in_game() noexcept {
    this->cards.clear();
    this->inGame = true;
}

/**
 * Asks the player for a move.
 *
 * @param current_pot The amount of money currently on the table.
 * @return The move of the player.
 */
double Player::make_play(double current_pot) noexcept {
    if (!this->inGame) {
        return NOT_IN_GAME;
    }

    std::cout << "\nYour funds: " << this->funds << std::endl;
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
            return FOLD;

        case 'c':
        case 'C':
            if (this->funds >= current_pot) {
                this->funds -= current_pot;
            } else {
                this->funds = 0;
            }

            return CHECK;

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

/**
 * Checks if two players are the same.
 *
 * @param p The other player to compare two.
 * @return True if the names are the same.
 */
bool Player::operator==(Player const &p) const noexcept {
    return this->name == p.name;
}
