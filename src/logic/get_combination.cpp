//
// Created by eyedevelop on 09/02/2020.
//

/**
 * Determines the current combination a player has
 * and calculates a score based on that.
 * 10000: Royal Flush
 * 9000: Straight Flush
 * 8000: 4 of a Kind
 * 7000: Full House
 * 6000: Flush
 * 5000: Straight
 * 4000: 3 of a Kind
 * 3000: Two Pair
 * 2000: One Pair
 *
 * This score gets added with the Rank value of the card multiplied by 10.
 * Then, the rank of the highest player card is added.
 * This means two pairs, one with kings and the other with
 * 2's, will not have the same score.
 *
 * @param p The player to get best combination for.
 * @param board_cards The 5 cards on the table.
 * @return The score of his hand with the table.
 */
int get_combination_score(Player const *p, std::vector<Card> const &board_cards) noexcept {
    std::vector<Card> combinationCards = board_cards;
    combinationCards.emplace_back(p->get_cards()[0]);
    combinationCards.emplace_back(p->get_cards()[1]);
    std::sort(combinationCards.begin(), combinationCards.end());

    int best = 0;

    // Check for any flush or straight.
    for (int i = 0; i < 2; i++) {
        Card &c = combinationCards[i];
        std::vector<Card> sub{combinationCards.begin() + i, combinationCards.begin() + i + 5};

        bool straight = true;
        int lastRank = sub[0].get_rank();
        for (int j = 1; j < sub.size(); j++) {
            straight &= sub[i].get_rank() < lastRank;
            lastRank = sub[i].get_rank();
        }

        bool flush = Card::same_suit(sub);
        bool royal = c.get_rank() == ACE;

        if (royal && straight && flush) {
            if (1000 > best)
                best = 1000;
        } else if (straight && flush) {
            if (900 + 10 * sub[0].get_rank() > best)
                best = 900 + 10 * sub[0].get_rank();
        } else if (flush || Card::get_max_suit_count(combinationCards) >= 5) {
            if (600 > best)
                best = 600;
        } else if (straight) {
            if (500 + 10 * sub[0].get_rank() > best)
                best = 500 + 10 * sub[0].get_rank();
        }
    }

    // Check for 3 of a kind, 4 of a kind.
    Rank the_rank;
    int rank_count = Card::get_max_rank_count(combinationCards, the_rank);
    if (rank_count == 4) {
        if (800 + 10 * the_rank > best)
            best = 800 + 10 * the_rank;
    } else if (rank_count == 3 && !Card::get_pairs(combinationCards).empty()) {
        if (700 + 10 * the_rank > best)
            best = 700 + 10 * the_rank;
    } else if (rank_count == 3) {
        if (400 + 10 * the_rank > best)
            best = 400 + 10 * the_rank;
    }

    // Check the highest pair.
    std::vector<Rank> pairs = Card::get_pairs(combinationCards);
    std::sort(pairs.begin(), pairs.end());
    if (pairs.size() >= 2) {
        if (300 + 10 * pairs[0] > best)
            best = 300 + 10 * pairs[0];
    } else if (!Card::get_pairs(combinationCards).empty()) {
        if (200 + 10 * pairs[0] > best)
            best = 200 + 10 * pairs[0];
    }

    // Add the highest card of the player to the score.
    best += std::max(p->get_cards()[0].get_rank(), p->get_cards()[1].get_rank());

    return best;
}
