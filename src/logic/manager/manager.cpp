//
// Created by eyedevelop on 03/02/2020.
//

#include "manager.h"
#include <algorithm>
#include <iostream>
#include "../get_combination.cpp"

/**
 * Adds a player to the manager.
 *
 * @param p The player to add.
 */
void Manager::add_player(Player *const p) noexcept {
    this->players.push_back(p);
}

/**
 * Removes a player from the manager.
 *
 * @param p The player to remove.
 */
void Manager::remove_player(Player *const p) noexcept {
    this->players.erase(std::find(this->players.begin(), this->players.end(), p));
}

/**
 * Gets the current player and calls the player's
 * make_play function to determine the action to
 * be taken for that player.
 */
void Manager::next_play() noexcept {
    Player *p_current_player = get_current_player();

    // Check if a round has been concluded.
    if (current_player == round_end_at) {
        this->next_round();
    }

    // Game has to be active to make moves.
    if (!this->active) {
        return;
    }

    // Check if the player has folded before.
    bool folded = false;
    for (Player *const p : this->folded_players) {
        if (p->get_name() == p_current_player->get_name()) {
            folded = true;
        }
    }

    // Increment current player.
    if (folded) {
        this->current_player = (this->current_player + 1) % this->players.size();
        return;
    }

    // Let the player make their move.
    double action = p_current_player->make_play(this->pot, this->raise_delta);
    if (action == FOLD) {
        this->folded_players.push_back(p_current_player);

    } else if (action == CHECK) {
        this->pot += this->biggest_raise;

    } else if (action > 0) {
        this->pot += action;

        if (action > this->biggest_raise) {
            this->raise_delta = action - this->biggest_raise;
            this->biggest_raise = action;
            this->round_end_at = this->current_player;
        }
    }

    // Increment player.
    this->current_player = (this->current_player + 1) % this->players.size();
}

/**
 * Increments the round counter and places
 * a card (or multiple) depending on the
 * current round.
 *
 * Round 1: Betting on the just-given hand.
 * Round 2: Three cards appear on the table.
 * Round 3: Extra card gets placed.
 * Round 4: Another extra card is placed. These are the final bets.
 */
void Manager::next_round() noexcept {
    if (++this->round_num > 4) {
        this->active = false;
        return;
    }

    if (this->round_num == 2) {
        for (int i = 0; i < 3; i++) {
            this->table_cards.push_back(this->deck.next_card());
        }
    } else if (this->round_num > 2) {
        this->table_cards.push_back(this->deck.next_card());
    }

    this->biggest_raise = 0;
    this->round_end_at = 0;
}

/**
 * Starts a whole game of Poker.
 * First enlists all players in the game, gives them cards,
 * then runs next_play() until the game is over.
 *
 * After all this, the winner is calculated and gets the pot
 * added to their funds.
 */
void Manager::start_game() noexcept {
    // Cannot start a game with only one player.
    if (this->players.size() < 2)
        return;

    // Sets the players in-game and gives them cards.
    for (Player *const p : players) {
        p->set_in_game(&this->table_cards);
        p->give_card(this->deck.next_card());
        p->give_card(this->deck.next_card());
    }

    // Make moves.
    while (active)
        this->next_play();

    // Get the players still active in the game.
    std::vector<Player *> active_players;
    std::set_difference(this->players.begin(), this->players.end(), folded_players.begin(), folded_players.end(),
                        std::back_inserter(active_players));

    // Calculate a winner and give them their prize money.
    // Or share it among a group of winners (same combo).
    if (folded_players.size() == this->players.size() - 1) {
        std::cout << "\nThe winner is: " << active_players[0]->get_name() << std::endl;
        active_players[0]->add_funds(pot);
    } else {
        std::vector<Player *> winners = check_win(active_players, table_cards);
        std::cout << "\nThe winners are: " << std::endl;
        for (Player *const p : winners) {
            std::cout << "- " << p->get_name() << std::endl;
            p->add_funds(pot / winners.size());
        }
    }

    // Reset the player's in-game status.
    for (Player *const p : players)
        p->reset_in_game();

    // Reset the manager.
    this->current_player = 0;
    this->round_end_at = 0;
    this->biggest_raise = 0;
    this->pot = 0;
    this->deck.reset();
}

/**
 * Calculates which player won based on their
 * hand/table score.
 *
 * @param active_players The players still in the game after all rounds.
 * @param board_cards The cards on the table.
 * @return A vector of winners.
 */
std::vector<Player *>
Manager::check_win(std::vector<Player *> const &active_players, std::vector<Card> const &board_cards) noexcept {
    std::vector<Player *> winners;
    int highestScore = 0;

    for (Player *p : active_players) {
        int score = get_combination_score(p, board_cards);
        if (score == highestScore)
            winners.push_back(p);

        else if (score > highestScore) {
            highestScore = score;
            winners.clear();
            winners.push_back(p);
        }
    }

    return winners;
}

/**
 * Gets all the players in this manager.
 *
 * @return Those players.
 */
std::vector<Player *> Manager::get_players() noexcept {
    return players;
}

/**
 * Gets the current player as Player*.
 *
 * @return The player (as pointer) currently at turn.
 */
Player *Manager::get_current_player() noexcept {
    return this->players[current_player];
}

/**
 * Gets the cards currently on the table.
 *
 * @return The cards on the table.
 */
std::vector<Card> Manager::get_cards() noexcept {
    return this->table_cards;
}

int main() {
    Manager m{};
    Player p{"Hans", 1200};
    Player p2{"John", 1201};
//    Player p3{"Rutger", 1200};

    m.add_player(&p);
    m.add_player(&p2);
//    m.add_player(&p3);

    m.start_game();

    return 0;
}
