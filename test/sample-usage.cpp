/* pokertools - tools for poker related coding
 * Copyright (C) 2016 Andriy Lysnevych
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 */

/**
 * Evaluates hand and finds strenght of your cards against random opponent
 * hand using sampling (Monte Carlo method).
 */

#include <pokertools-cpp/evaluators.hpp>

#include <iostream>
#include <random>
#include <bitset>

using namespace pokertools;

static std::mt19937 randomEngine(std::random_device{}());

static Card getRandomCard() noexcept
{
    static std::uniform_int_distribution<unsigned> cardsUniformDistribution(0, CardsCount - 1);
    return createCard(cardsUniformDistribution(randomEngine));
}

static Hand getRandomHand(unsigned cardsCount, Hand filter = 0_hand) noexcept
{
    Hand hand = 0_hand;

    while (cardsCount) {
        Card card;

        do {
            card = getRandomCard();
        } while (((hand | card).bits == hand.bits) | ((filter | card).bits == filter.bits));

        hand |= card;
        cardsCount--;
    }

    return hand;
}

int main()
{
    pokertools::initializeEvaluator();

    // Hand communityCards =  0b0001110000000000000000000000000000000000000000000000000011000000_hand;
    Hand communityCards = ace_spades | 8_clubs | 9_clubs | king_spades | queen_spades;
    Hand myHoleCards = 10_spades | 8_diamonds;
    Hand myHand = communityCards | myHoleCards;

    uint32_t myHandValue = evaluateHoldem7CardsHand(myHand);

    unsigned winCount = 0;
    unsigned splitCount = 0;
    unsigned totalCount = 10000;

    for (unsigned i = 0; i < totalCount; i++) {
        Hand opponentHoleCards = getRandomHand(2, myHand);
        uint32_t opponentHoleCardsValue = evaluateHoldem7CardsHand(communityCards | opponentHoleCards);

        if (opponentHoleCardsValue < myHandValue) {
            winCount++;
        } else if (opponentHoleCardsValue == myHandValue) {
            splitCount++;
        }
    }

    const char* handTypes[] = { "High Card", "Pair", "Two Pair", "Three Of A Kind", "Straight", "Flush", "FullHouse", "Four Of A Kind", "Straight Fulsh" };
    EvaluateResult myHandEvaluateResult{ myHandValue };

    std::cout << "hand: " << std::bitset<64>(myHand.bits) << std::endl
              << "value: " << myHandValue << " (0b" << std::bitset<32>(myHandValue) << ")" << std::endl
              << handTypes[myHandEvaluateResult.details.handType]
              << " High Ranks " << std::bitset<RanksCount>(myHandEvaluateResult.details.highRanks)
              << " Low Ranks " << std::bitset<RanksCount>(myHandEvaluateResult.details.lowRanks)
              << std::endl;
    std::cout << "win   " << (double) winCount / totalCount << "%" << std::endl;
    std::cout << "split " << (double) splitCount / totalCount << "%" << std::endl;
    std::cout << "loose " << 1 - (double) winCount / totalCount << "%" << std::endl;
}
