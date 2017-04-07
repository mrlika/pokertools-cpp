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
 * Test performance of different hand evaluator implementations.
 */

#include <pokertools-cpp/evaluators.hpp>

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <bitset>
#include <algorithm>
#include <fstream>

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

void testPerformance() noexcept
{
    std::cout << "Testing performance" << std::endl;

    std::vector<std::chrono::steady_clock::duration> testDurations;
    std::vector<std::string> testNames;

    const unsigned iterationsCount = 99999999;
    const unsigned handsCount = 9999;
    Hand hands[handsCount];
    Hand hands5[handsCount];
    unsigned result = 0;

    for (unsigned i = 0; i < handsCount; i++) {
        hands[i] = getRandomHand(7);
        hands5[i] = getRandomHand(5);
    }

    std::chrono::steady_clock::time_point begin, end;

    for (unsigned i = 0; i < iterationsCount; i++) {
        result += evaluateHoldem7CardsHand(hands[i % handsCount]);
    }

    testNames.emplace_back("evaluateHoldemHand 5");
    begin = std::chrono::steady_clock::now();

    for (unsigned i = 0; i < iterationsCount; i++) {
        result += evaluateHoldemHand(hands5[i % handsCount], 5);
    }

    end = std::chrono::steady_clock::now();
    testDurations.push_back(end - begin);

    testNames.emplace_back("evaluateHoldemHand 7");
    begin = std::chrono::steady_clock::now();

    for (unsigned i = 0; i < iterationsCount; i++) {
        result += evaluateHoldemHand(hands[i % handsCount], 7);
    }

    end = std::chrono::steady_clock::now();
    testDurations.push_back(end - begin);

    testNames.emplace_back("evaluateHoldem5CardsHand");
    begin = std::chrono::steady_clock::now();

    for (unsigned i = 0; i < iterationsCount; i++) {
        result += evaluateHoldem5CardsHand(hands5[i % handsCount]);
    }

    end = std::chrono::steady_clock::now();
    testDurations.push_back(end - begin);

    testNames.emplace_back("evaluateHoldem7CardsHand");
    begin = std::chrono::steady_clock::now();

    for (unsigned i = 0; i < iterationsCount; i++) {
        result += evaluateHoldem7CardsHand(hands[i % handsCount]);
    }

    end = std::chrono::steady_clock::now();
    testDurations.push_back(end - begin);

    std::cout << result << std::endl;;
    for (unsigned i = 0; i < testDurations.size(); i++) {
        std::cout << "Performance " << testNames[i] << " is " << (std::chrono::duration_cast<std::chrono::nanoseconds>(testDurations[i]).count() / iterationsCount) << " ns per hand. It is " <<
                 iterationsCount * std::chrono::seconds(1) / testDurations[i] << " hands per second" << std::endl;
    }
}

int main()
{
    pokertools::initializeEvaluator();
    testPerformance();
}
