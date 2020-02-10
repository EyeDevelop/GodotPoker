//
// Created by eyedevelop on 03/02/2020.
//

#include <random>
#include <iostream>
#include <thread>
#include <chrono>
#include "player.h"
#include "../../net/client/client.h"

Player::Player(std::string_view name) noexcept
        : name{name}, funds{0} {}

Player::Player(std::string_view name, double start_funds) noexcept
        : name{name}, funds{start_funds} {}

Player::Player(std::string_view name, double start_funds, bool networked) noexcept
        : name{name}, funds{start_funds}, networked{networked} {}

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
    this->in_game = false;
}

/**
 * Sets the player to be in-game.
 */
void Player::set_in_game() noexcept {
    this->cards.clear();
    this->in_game = true;
}

double Player::fold() noexcept {
    if (!this->in_game)
        return NOT_IN_GAME;

    return FOLD;
}

double Player::check(double current_pot) noexcept {
    if (!this->in_game)
        return NOT_IN_GAME;

    // Check if we go all-in or no.
    if (this->funds >= current_pot) {
        this->funds -= current_pot;
    } else {
        this->funds = 0;
        return ALL_IN;
    }

    return CHECK;
}

double Player::raise(double current_pot, double raise_amount) noexcept {
    if (!this->in_game)
        return NOT_IN_GAME;

    // Perform the raise after checking if there are enough funds, otherwise go all-in.
    if (raise_amount > 0) {
        if (this->funds <= current_pot + raise_amount)
            return ALL_IN;

        this->funds -= raise_amount + current_pot;
        return raise_amount;
    }

    return 0;
}

double Player::make_play(double current_pot) noexcept {
//    if (networked)
//        return make_play_net(current_pot);

    return make_play_cli(current_pot);
}

/**
 * Asks the player for a move.
 *
 * @param current_pot The amount of money currently on the table.
 * @return The move of the player.
 */
double Player::make_play_cli(double current_pot) noexcept {
    if (!this->in_game) {
        return NOT_IN_GAME;
    }

    std::cout << "\nYour funds: " << this->funds << std::endl;
    std::cout << "Your cards: ";
    std::string card_str;
    for (const Card &c : this->cards) {
        card_str += c.to_string() + " ";
    }
    std::string hidden = std::string(6, '\b') +
                         std::string(4, '*');

    // Show for two seconds, then remove.
    std::cout << card_str;
    std::cout.flush();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << hidden << std::endl;

    std::string option;
    std::cout << "Do you wish to (F)old, (C)heck/call or (R)aise: ";
    std::cin >> option;

    if (option.length() == 0) {
        std::cerr << "Please enter your move." << std::endl;
        return make_play(current_pot);
    }

    switch (option[0]) {
        case 'f':
        case 'F':
            return fold();

        case 'c':
        case 'C':
            return check(current_pot);

        case 'r':
        case 'R': {
            double raise_amount = 0;
            std::cout << "Raise by how much: ";
            std::cin >> raise_amount;

            if (raise_amount == 0) {
                std::cerr << "That's not a valid amount." << std::endl;
                return make_play(current_pot);
            }

            return raise(current_pot, raise_amount);
        }

        default: {
            std::cerr << "That's not a valid choice." << std::endl;
            return make_play(current_pot);
        }
    }
}

double Player::make_play_net(double current_pot, Action a, double amount) noexcept {
    if (!this->in_game)
        return NOT_IN_GAME;

    switch (a) {
        case FOLD:
            return fold();

        case CHECK:
            return check(current_pot);

        default:
            return raise(current_pot, amount);
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
