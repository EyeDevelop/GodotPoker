//
// Created by eyedevelop on 03/02/2020.
//

#include <algorithm>
#include <iostream>
#include "manager.h"
#include "../get_combination.cpp"

/**
 * Adds a player to the manager.
 *
 * @param p The player to add.
 */
void Manager::add_player(Player * const p) noexcept {
    this->players.push_back(p);
}

/**
 * Removes a player from the manager.
 *
 * @param p The player to remove.
 */
void Manager::remove_player(Player * const p) noexcept {
    this->players.erase(std::find(this->players.begin(), this->players.end(), p));
}

/**
 * Does exactly one round of poker.
 *
 * @param folded_players The players who have folded before this round.
 * @return The pot delta after the round.
 */
double Manager::do_turn(std::vector<Player *> &folded_players) noexcept {
    double pot_delta = 0;
    for (Player *p: this->players) {
        bool folded = false;
        for (Player * foldedP : folded_players) {
            if (p->get_name() == foldedP->get_name())
                folded = true;
        }

        if (folded)
            continue;

        double ret = p->make_play(pot_delta);
        if (ret == FOLD)
            folded_players.push_back(p);
        else if (ret > 0)
            pot_delta += ret;
    }

    return pot_delta;
}

/**
 * Starts a whole game of Poker.
 * First enlists all players in the game, gives them cards,
 * then runs do_turn() until the game is over.
 *
 * After all this, the winner is calculated and gets the pot
 * added to their funds.
 */
void Manager::start_game() noexcept {
    // Sets the players in-game and gives them cards.
    for (Player * const p : players) {
        p->set_in_game();
        p->give_card(this->deck.next_card());
        p->give_card(this->deck.next_card());
    }

    int turnCount = 0;
    double pot = 0;

    std::vector<Card> board_cards;
    std::vector<Player*> folded_players;

    // Keeps running the game until it's over or
    // all players folded.
    while (turnCount < 4 && this->players.size() > 1) {
        std::cout << "\nCurrently in the pot: " << pot << std::endl;

        if (turnCount == 1) {
            for (int i = 0; i < 3; i++) {
                board_cards.push_back(deck.next_card());
            }
        } else if (turnCount > 1) {
            board_cards.push_back(deck.next_card());
        }

        if (!board_cards.empty()) {
            std::cout << "Cards currently on the table:\n" << std::endl;
            for (Card const &c : board_cards) {
                std::cout << c.to_string() << " ";
            }
            std::cout << std::endl;
        }

        pot = do_turn(folded_players);
        if (folded_players.size() == this->players.size() - 1)
            break;

        turnCount++;
    }

    std::vector<Player*> active_players;
    std::set_difference(this->players.begin(), this->players.end(), folded_players.begin(), folded_players.end(), std::back_inserter(active_players));

    // Calculate a winner and give them their prize money.
    // Or share it among a group of winners (same combo).
    if (folded_players.size() == this->players.size() - 1) {
        std::cout << "\nThe winner is: " << active_players[0]->get_name() << std::endl;
        active_players[0]->add_funds(pot);
    } else {
        std::vector<Player*> winners = check_win(active_players, board_cards);
        std::cout << "\nThe winners are: " << std::endl;
        for (Player * const p : winners) {
            std::cout << "- " << p->get_name() << std::endl;
            p->add_funds(pot / winners.size());
        }
    }

    // Reset the player's in-game status.
    for (Player * const p : players)
        p->reset_in_game();

    // Reset the deck.
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
std::vector<Player *> Manager::check_win(std::vector<Player*> const &active_players, std::vector<Card> const &board_cards) noexcept {
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

int main() {
    Manager m{};
    Player p{"Hans", 1200};
    Player p2{"John", 1200};
    Player p3{"Rutger", 1200};

    m.add_player(&p);
    m.add_player(&p2);
    m.add_player(&p3);

    m.start_game();

    return 0;
}
