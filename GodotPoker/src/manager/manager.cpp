//
// Created by eyedevelop on 03/02/2020.
//

#include <algorithm>
#include <iostream>
#include "manager.h"

void Manager::add_player(Player const &p) noexcept {
    this->players.emplace_back(p);
}

void Manager::remove_player(Player const &p) noexcept {
    this->players.erase(std::find(this->players.begin(), this->players.end(), p));
}

double Manager::do_turn(std::vector<Player> &active_players) noexcept {
    double pot_delta = 0;
    for (Player &p : active_players) {
        double ret = p.make_play(pot_delta);
        if (ret == -2)
            active_players.erase(std::find(active_players.begin(), active_players.end(), p));
        else if (ret > 0)
            pot_delta += ret;
    }

    return pot_delta;
}

void Manager::start_game() noexcept {
    for (Player &p : players) {
        p.set_in_game();
        p.give_card(this->deck.next_card());
        p.give_card(this->deck.next_card());
    }

    int turnCount = 0;
    double pot = 0;
    std::vector<Player> active_players;
    for (Player const &p : this->players) {
        active_players.emplace_back(p);
    }

    std::vector<Card> board_cards;

    while (turnCount < 4 && active_players.size() > 1) {
        std::cout << "Currently in the pot: " << pot << std::endl;

        if (turnCount == 1) {
            for (int i = 0; i < 3; i++) {
                board_cards.emplace_back(deck.next_card());
            }
        } else if (turnCount > 1) {
            board_cards.emplace_back(deck.next_card());
        }

        if (!board_cards.empty()) {
            std::cout << "Cards currently on the table:" << std::endl;
            for (Card &c : board_cards) {
                std::cout << c.to_string() << " ";
            }
            std::cout << std::endl;
        }

        if (active_players.size() == 1)
            break;

        pot = do_turn(active_players);
        turnCount++;
    }

    if (active_players.size() == 1) {
        std::cout << "The winner is: " << active_players[0].get_name() << std::endl;
        // .front(), doesn't rlly matter
        active_players[0].add_funds(pot);
    } else {
        std::vector<Player> winners = check_win(active_players, board_cards);
        std::cout << "The winners are: " << std::endl;
        for (Player &p : winners) {
            std::cout << "- " << p.get_name() << std::endl;
            p.add_funds(pot / winners.size());
        }
    }

    for (Player &p : players)
        p.reset_in_game();
}

int getCombination(Player const &p, std::vector<Card> &board_cards) {
    std::vector<Card> combinationCards = board_cards;
    combinationCards.emplace_back(p.get_cards()[0]);
    combinationCards.emplace_back(p.get_cards()[1]);
    std::sort(combinationCards.begin(), combinationCards.end());

    int best = 0;

    // Check for any flush or straight.
    for (int i = 0; i < 2; i++) {
        Card &c = combinationCards[i];
        std::vector<Card> sub{combinationCards.begin() + i, combinationCards.begin() + i + 5};

        bool straight = std::is_sorted(sub.begin(), sub.end());
        bool flush = Card::same_suit(sub);
        bool royal = c.get_rank() == ACE;

        if (royal && straight && flush) {
            if (1000 > best)
                best = 1000;
        } else if (straight && flush) {
            if (900 + (sub[0].get_rank() + 1) > best)
                best = 900 + (sub[0].get_rank() + 1);
        } else if (flush || Card::get_max_suit_count(combinationCards) >= 5) {
            if (600 > best)
                best = 600;
        } else if (straight) {
            if (500 + (sub[0].get_rank() + 1) > best)
                best = 500 + (sub[0].get_rank() + 1);
        }
    }

    // Check for 3 of a kind, 4 of a kind.
    int rank_count = Card::get_max_rank_count(combinationCards);
    if (rank_count == 4) {
        if (800 > best)
            best = 800;
    } else if (rank_count == 3 && !Card::get_pairs(combinationCards).empty()) {
        if (700 > best)
            best = 700;
    } else if (rank_count == 3) {
        if (400 > best)
            best = 400;
    }

    // Check the highest pair.
    std::vector<Rank> pairs = Card::get_pairs(combinationCards);
    std::sort(pairs.begin(), pairs.end());
    if (pairs.size() >= 2) {
        if (300 + pairs[0] > best)
            best = 300 + pairs[0];
    } else if (!Card::get_pairs(combinationCards).empty()) {
        if (200 + pairs[0] > best)
            best = 200 + pairs[0];
    } else {
        best = std::max(p.get_cards()[0].get_rank(), p.get_cards()[1].get_rank());
    }

    return best;
}

std::vector<Player> Manager::check_win(std::vector<Player> &active_players, std::vector<Card> &board_cards) noexcept {
    std::vector<Player> winners;
    int highestScore = 0;

    for (Player const &p : active_players) {
        int score = getCombination(p, board_cards);
        if (score == highestScore)
            winners.emplace_back(p);

        else if (score > highestScore) {
            highestScore = score;
            winners.clear();
            winners.emplace_back(p);
        }
    }

    return winners;
}

int main() {
    Manager m{};
    Player p{"Hans", 1200};
    Player p2{"John", 1220};

    m.add_player(p);
    m.add_player(p2);

    m.start_game();

    return 0;
}
