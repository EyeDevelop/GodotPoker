//
// Created by eyedevelop on 09/02/2020.
//

/**
 * Determines the current combination a player has
 * and calculates a score based on that.
 * 1000: Royal Flush
 * 900: Straight Flush
 * 800: 4 of a Kind
 * 700: Full House
 * 600: Flush
 * 500: Straight
 * 400: 3 of a Kind
 * 300: Two Pair
 * 200: One Pair
 *
 * This score gets added with the Rank value of the card.
 * This means two pairs, one with kings and the other with
 * two's, will not be the same.
 *
 * @param p The player to get best combination for.
 * @param board_cards The 5 cards on the table.
 * @return The score of his hand with the table.
 */
int get_combination_score(Player const *p, std::vector<Card> const &board_cards) {
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
        best = std::max(p->get_cards()[0].get_rank(), p->get_cards()[1].get_rank());
    }

    return best;
}
