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
 * Tests correctness of hand evaluators by comparing results of different
 * implementations.
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

static Hand getRandomHand(unsigned cardsCount, Hand filter = 0) noexcept
{
    Hand hand = 0;

    while (cardsCount) {
        Card card;

        do {
            card = getRandomCard();
        } while (((hand | card) == hand) | ((filter | card) == filter));

        hand |= card;
        cardsCount--;
    }

    return hand;
}

void testCorrectness() noexcept
{
    for (unsigned i = 0; i < 9999999; i++) {
        Hand hand = getRandomHand(7);

        if (evaluateHoldem7CardsHand(hand) != evaluateHoldemHand(hand, 7)) {
            std::cout << "ERROR evaluating hand " << std::bitset<64>(hand) << std::endl;
        }

        hand = getRandomHand(5);

        if (evaluateHoldem5CardsHand(hand) != evaluateHoldemHand(hand, 5)) {
            std::cout << "ERROR evaluating hand " << std::bitset<64>(hand) << std::endl;
        }
    }
}

int main()
{
    pokertools::initializeEvaluator();
    testCorrectness();
    std::cout << "Test END" << std::endl;
}
