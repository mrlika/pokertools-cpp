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

#include <pokertools-cpp/evaluators.hpp>

#include <bitset>
#include <iostream>

namespace pokertools
{
    static uint8_t* numberOfBits;
    static uint16_t* rankOfStraights;
    static uint16_t* highUpTo5Bits;
    static uint16_t* highBit;
    static uint16_t* highUpTo3Bits;
    static std::unique_ptr<uint8_t, std::function<void(uint8_t*)>> buffer;

    const unsigned HandTypeInValueShift = 28;

    static inline uint32_t calculateStraightFlushValue(uint16_t highCardRank) noexcept
    {
        return (static_cast<uint32_t>(HandType::StraightFulsh) << HandTypeInValueShift) | highCardRank;
    }

    static inline uint32_t calculateFourOfAKindValue(uint16_t quadsRank, uint16_t kickerRank) noexcept
    {
        return (static_cast<uint32_t>(HandType::FourOfAKind) << HandTypeInValueShift) | (static_cast<uint32_t>(quadsRank) << RanksCount) | kickerRank;
    }

    static inline uint32_t calculateFullHouseValue(uint16_t tripsRank, uint16_t pairRank) noexcept
    {
        return (static_cast<uint32_t>(HandType::FullHouse) << HandTypeInValueShift) | (static_cast<uint32_t>(tripsRank) << RanksCount) | pairRank;
    }

    static inline uint32_t calculateFlushValue(uint16_t fiveCardsRanks) noexcept
    {
        return (static_cast<uint32_t>(HandType::Flush) << HandTypeInValueShift) | fiveCardsRanks;
    }

    static inline uint32_t calculateStraightValue(uint16_t highCardRank) noexcept
    {
        return (static_cast<uint32_t>(HandType::Straight) << HandTypeInValueShift) | highCardRank;
    }

    static inline uint32_t calculateThreeOfAKindValue(uint16_t tripsRank, uint16_t twoKickersRanks) noexcept
    {
        return (static_cast<uint32_t>(HandType::ThreeOfAKind) << HandTypeInValueShift) | (static_cast<uint32_t>(tripsRank) << RanksCount) | twoKickersRanks;
    }

    static inline uint32_t calculateTwoPairValue(uint16_t pairsRanks, uint16_t kickerRank) noexcept
    {
        return (static_cast<uint32_t>(HandType::TwoPair) << HandTypeInValueShift) | (static_cast<uint32_t>(pairsRanks) << RanksCount) | kickerRank;
    }

    static inline uint32_t calculatePairValue(uint16_t pairRank, uint16_t threeKickersRanks) noexcept
    {
        return (static_cast<uint32_t>(HandType::Pair) << HandTypeInValueShift) | (static_cast<uint32_t>(pairRank) << RanksCount) | threeKickersRanks;
    }

    static inline uint32_t calculateHighCardValue(uint16_t fiveCardsRanks) noexcept
    {
        return (static_cast<uint32_t>(HandType::HighCard) << HandTypeInValueShift) | fiveCardsRanks;
    }

    uint32_t evaluateHoldem7CardsHand(Hand hand) noexcept
    {
        assert(std::bitset<64>(hand.bits).count() == 7);

        uint16_t clubs = hand.suit.clubs;
        uint16_t diamonds = hand.suit.diamonds;
        uint16_t hearts = hand.suit.hearts;
        uint16_t spades = hand.suit.spades;

        uint16_t ranks = clubs | diamonds | hearts | spades;
        uint8_t ranksCount = numberOfBits[ranks];

        if (ranksCount >= 5) { // Straight, Fulsh or Straight Flush is possible
            if (numberOfBits[clubs] >= 5) {
                uint16_t straightRank = rankOfStraights[clubs];
                if (straightRank == 0) { // Flush
                    return calculateFlushValue(highUpTo5Bits[clubs]);
                } else { // Straight Flush
                    return calculateStraightFlushValue(straightRank);
                }
            } else if (numberOfBits[diamonds] >= 5) {
                uint16_t straightRank = rankOfStraights[diamonds];
                if (straightRank == 0) { // Flush
                    return calculateFlushValue(highUpTo5Bits[diamonds]);
                } else { // Straight Flush
                    return calculateStraightFlushValue(straightRank);
                }
            } else if (numberOfBits[hearts] >= 5) {
                uint16_t straightRank = rankOfStraights[hearts];
                if (straightRank == 0) { // Flush
                    return calculateFlushValue(highUpTo5Bits[hearts]);
                } else { // Straight Flush
                    return calculateStraightFlushValue(straightRank);
                }
            } else if (numberOfBits[spades] >= 5) {
                uint16_t straightRank = rankOfStraights[spades];
                if (straightRank == 0) { // Flush
                    return calculateFlushValue(highUpTo5Bits[spades]);
                } else { // Straight Flush
                    return calculateStraightFlushValue(straightRank);
                }
            } else {
                uint16_t straightRank = rankOfStraights[ranks];
                if (straightRank != 0) { // Straight
                    return calculateStraightValue(straightRank);
                }
            }
        }

        switch (ranksCount) {
        case 2: { // 2 ranks = [4, 3]
            uint16_t quadsRank = clubs & diamonds & hearts & spades;
            uint16_t tripsRank = ranks ^ quadsRank;

            return calculateFourOfAKindValue(quadsRank, tripsRank);
        }

        case 3: { // 3 ranks = [3, 3, 1] or [3, 2, 2] or [4, 2, 1]
            uint16_t singletonAndTripsRanks = clubs ^ diamonds ^ hearts ^ spades;

            if (numberOfBits[singletonAndTripsRanks] == 1) { // [4, 2, 1] or [3, 2, 2]
                uint16_t quadsRank = clubs & diamonds & hearts & spades;
                if (quadsRank == 0) { // Full House = [3, 2, 2]
                    uint16_t pairsRanks = ranks ^ singletonAndTripsRanks;
                    uint16_t highPairRank = highBit[pairsRanks];

                    return calculateFullHouseValue(singletonAndTripsRanks, highPairRank);
                } else { // Four of a Kind = [4, 2, 1]
                    uint16_t otherRanks = ranks ^ quadsRank;
                    uint16_t kickerRank = highBit[otherRanks];

                    return calculateFourOfAKindValue(quadsRank, kickerRank);
                }
            } else { // Full House = [3, 3, 1]
                uint16_t tripsRanks = ((clubs & diamonds) | (hearts & spades));
                uint16_t highTripsRank = highBit[tripsRanks];
                uint16_t lowTripsRank = tripsRanks ^ highTripsRank;

                return calculateFullHouseValue(highTripsRank, lowTripsRank);
            }
        }

        case 4: { // 4 ranks = [2, 2, 2, 1] or [3, 2, 1, 1] or [4, 1, 1, 1]
            uint16_t singletonsAndTripsRanks = clubs ^ diamonds ^ hearts ^ spades;

            if (numberOfBits[singletonsAndTripsRanks] == 1) { // Two Pair = [2, 2, 2, 1]
                uint64_t threePairsRanks = ranks ^ singletonsAndTripsRanks;
                uint64_t highPairRank = highBit[threePairsRanks];
                uint64_t secondPairRank = highBit[threePairsRanks ^ highPairRank];
                uint64_t kickerRank = highBit[ranks ^ highPairRank ^ secondPairRank];

                return calculateTwoPairValue(highPairRank | secondPairRank, kickerRank);
            } else {
                uint16_t quadsRank = clubs & diamonds & hearts & spades;
                if (quadsRank == 0) { // Full House = [3, 2, 1, 1]
                    uint16_t pairRank = ranks ^ singletonsAndTripsRanks;
                    uint16_t tripsRank = ((clubs & diamonds) | (hearts & spades)) & (~pairRank);

                    return calculateFullHouseValue(tripsRank, pairRank);
                } else { // Four of a Kind = [4, 1, 1, 1]
                    uint16_t kickerRank = highBit[singletonsAndTripsRanks];

                    return calculateFourOfAKindValue(quadsRank, kickerRank);
                }
            }
        }

        case 5: { // 5 ranks = [3, 1, 1, 1, 1] or [2, 2, 1, 1, 1]
            uint16_t singletonsAndTripsRanks = clubs ^ diamonds ^ hearts ^ spades;
            uint16_t pairsRanks = ranks ^ singletonsAndTripsRanks;

            if (pairsRanks != 0) { // Two Pairs = [2, 2, 1, 1, 1]
                uint16_t kickerRank = highBit[singletonsAndTripsRanks];

                return calculateTwoPairValue(pairsRanks, kickerRank);
            } else { // Three of a Kind = [3, 1, 1, 1, 1]
                uint16_t tripsRank = (clubs & diamonds) | (hearts & spades);
                uint16_t kickersRanks = ranks ^ tripsRank;
                uint16_t firstKickerRank = highBit[kickersRanks];
                uint16_t secondKickerRank = highBit[kickersRanks ^ firstKickerRank];

                return calculateThreeOfAKindValue(tripsRank, firstKickerRank | secondKickerRank);
            }
        }

        case 6: { // 6 ranks = [2, 1, 1, 1, 1, 1] = Pair
            uint16_t singletonsRanks = clubs ^ diamonds ^ hearts ^ spades;
            uint16_t pairRank = ranks ^ singletonsRanks;

            return calculatePairValue(pairRank, highUpTo3Bits[singletonsRanks]);
        }

        case 7: // 7 ranks = [1, 1, 1, 1, 1, 1, 1] = High Card
            return calculateHighCardValue(highUpTo5Bits[ranks]);

        default:
            assert(0); // Impossible if hand is valid
            return 0;
        }
    }

    uint32_t evaluateHoldem5CardsHand(Hand hand) noexcept
    {
        assert(std::bitset<64>(hand.bits).count() == 5);

        uint16_t clubs = hand.suit.clubs;
        uint16_t diamonds = hand.suit.diamonds;
        uint16_t hearts = hand.suit.hearts;
        uint16_t spades = hand.suit.spades;

        uint16_t ranks = clubs | diamonds | hearts | spades;
        uint8_t ranksCount = numberOfBits[ranks];

        switch (ranksCount) {
            case 5: { // Straight, Fulsh, Straight Flush or High Card
                if (numberOfBits[clubs] == 5) {
                    uint16_t straightRank = rankOfStraights[clubs];
                    if (straightRank == 0) { // Flush
                        return calculateFlushValue(clubs);
                    } else { // Straight Flush
                        return calculateStraightFlushValue(straightRank);
                    }
                } else if (numberOfBits[diamonds] == 5) {
                    uint16_t straightRank = rankOfStraights[diamonds];
                    if (straightRank == 0) { // Flush
                        return calculateFlushValue(diamonds);
                    } else { // Straight Flush
                        return calculateStraightFlushValue(straightRank);
                    }
                } else if (numberOfBits[hearts] == 5) {
                    uint16_t straightRank = rankOfStraights[hearts];
                    if (straightRank == 0) { // Flush
                        return calculateFlushValue(hearts);
                    } else { // Straight Flush
                        return calculateStraightFlushValue(straightRank);
                    }
                } else if (numberOfBits[spades] == 5) {
                    uint16_t straightRank = rankOfStraights[spades];
                    if (straightRank == 0) { // Flush
                        return calculateFlushValue(spades);
                    } else { // Straight Flush
                        return calculateStraightFlushValue(straightRank);
                    }
                } else {
                    uint16_t straightRank = rankOfStraights[ranks];
                    if (straightRank == 0) { // High Card
                        return calculateHighCardValue(ranks);
                    } else { // Straight
                        return calculateStraightValue(straightRank);
                    }
                }
            }

            case 4: { // Pair
                uint16_t singletonsRanks = clubs ^ diamonds ^ hearts ^ spades;
                uint16_t pairRank = ranks ^ singletonsRanks;

                return calculatePairValue(pairRank, singletonsRanks);
            }

            case 3 : { // Two Pair or Three of a Kind
                uint16_t singletonsAndTripsRanks = clubs ^ diamonds ^ hearts ^ spades;
                uint16_t pairsRanks = ranks ^ singletonsAndTripsRanks;

                if (pairsRanks != 0) {
                    return calculateTwoPairValue(pairsRanks, singletonsAndTripsRanks);
                } else {
                    uint16_t tripsRank = (clubs & diamonds) | (hearts & spades);
                    uint16_t singletonsRanks = ranks ^ tripsRank;

                    return calculateThreeOfAKindValue(tripsRank, singletonsRanks);
                }
            }

            case 2: { // Four of a Kind or Full House
                uint16_t quadsRank = clubs & diamonds & hearts & spades;
                if (quadsRank == 0) {
                    uint16_t tripsRank = clubs ^ diamonds ^ hearts ^ spades;
                    uint16_t pairRank = ranks ^ tripsRank;

                    return calculateFullHouseValue(tripsRank, pairRank);
                } else {
                    uint16_t kickerRank = ranks ^ quadsRank;

                    return calculateFourOfAKindValue(quadsRank, kickerRank);
                }
            }

            default:
                assert(0); // Impossible if hand is valid
                return 0;
        }
    }

    uint32_t evaluateHoldemHand(Hand hand, unsigned cardsCount) noexcept
    {
        assert((cardsCount >= 5) && (cardsCount <= 7));
        assert(std::bitset<64>(hand.bits).count() == cardsCount);

        uint16_t clubs = hand.suit.clubs;
        uint16_t diamonds = hand.suit.diamonds;
        uint16_t hearts = hand.suit.hearts;
        uint16_t spades = hand.suit.spades;

        uint16_t ranks = clubs | diamonds | hearts | spades;
        uint8_t ranksCount = numberOfBits[ranks];
        unsigned duplicatesCount = cardsCount - ranksCount;
        uint32_t flushOrStraightValue = 0;

        if (ranksCount >= 5) { // Straight, Fulsh or Straight Flush is possible
            if (numberOfBits[clubs] >= 5) {
                uint16_t straightRank = rankOfStraights[clubs];
                if (straightRank == 0) {
                    flushOrStraightValue = calculateFlushValue(highUpTo5Bits[clubs]);
                } else {
                    return calculateStraightFlushValue(straightRank);
                }
            } else if (numberOfBits[diamonds] >= 5) {
                uint16_t straightRank = rankOfStraights[diamonds];
                if (straightRank == 0) {
                    flushOrStraightValue = calculateFlushValue(highUpTo5Bits[diamonds]);
                } else {
                    return calculateStraightFlushValue(straightRank);
                }
            } else if (numberOfBits[hearts] >= 5) {
                uint16_t straightRank = rankOfStraights[hearts];
                if (straightRank == 0) {
                    flushOrStraightValue = calculateFlushValue(highUpTo5Bits[hearts]);
                } else {
                    return calculateStraightFlushValue(straightRank);
                }
            } else if (numberOfBits[spades] >= 5) {
                uint16_t straightRank = rankOfStraights[spades];
                if (straightRank == 0) {
                    flushOrStraightValue = calculateFlushValue(highUpTo5Bits[spades]);
                } else {
                    return calculateStraightFlushValue(straightRank);
                }
            } else {
                uint16_t straightRank = rankOfStraights[ranks];
                if (straightRank) {
                    flushOrStraightValue = calculateStraightValue(straightRank);
                }
            }

            if ((flushOrStraightValue != 0) && (duplicatesCount < 3)) {
                return flushOrStraightValue;
            }
        }

        switch (duplicatesCount) {
            case 0: // High Card
                return calculateHighCardValue(highUpTo5Bits[ranks]);

            case 1: { // Pair
                uint16_t singletonsRanks = clubs ^ diamonds ^ hearts ^ spades;
                uint16_t pairRank = ranks ^ singletonsRanks;

                return calculatePairValue(pairRank, highUpTo3Bits[singletonsRanks]);
            }

            case 2: { // Two Pair or Three of a Kind
                uint16_t singletonsAndTripsRanks = clubs ^ diamonds ^ hearts ^ spades;
                uint16_t pairsRanks = ranks ^ singletonsAndTripsRanks;

                if (pairsRanks != 0) { // Two Pairs
                    uint16_t kickerRank = highBit[singletonsAndTripsRanks];

                    return calculateTwoPairValue(pairsRanks, kickerRank);
                } else { // Three of a Kind
                    uint16_t tripsRank = (clubs & diamonds) | (hearts & spades);
                    uint16_t kickersRanks = ranks ^ tripsRank;
                    uint16_t firstKickerRank = highBit[kickersRanks];
                    uint16_t secondKickerRank = highBit[kickersRanks ^ firstKickerRank];

                    return calculateThreeOfAKindValue(tripsRank, firstKickerRank | secondKickerRank);
                }
            }

            default: { // Four of a Kind, Full Houe, Straight, Flush, Two Pair
                uint16_t singletonsAndTripsRanks = clubs ^ diamonds ^ hearts ^ spades;
                uint16_t pairsRanks = ranks ^ singletonsAndTripsRanks;

                if (numberOfBits[pairsRanks] != duplicatesCount) {
                    uint16_t quadsRank = clubs & diamonds & hearts & spades;
                    if (quadsRank == 0) {
                        // Must be some trips then, which really means there is a full house since duplicatesCount >= 3

                        uint16_t tripsRanks = (((clubs & diamonds) | (hearts & spades)) & ((clubs & hearts) | (diamonds & spades)));
                        uint16_t highTripsRank = highBit[tripsRanks];
                        uint16_t pairRank = highBit[(tripsRanks | pairsRanks) ^ highTripsRank];

                        return calculateFullHouseValue(highTripsRank, pairRank);
                    } else {
                        uint16_t otherRanks = ranks ^ quadsRank;

                        return calculateFourOfAKindValue(quadsRank, highBit[otherRanks]);
                    }
                } else {
                    if (flushOrStraightValue == 0) { // Two Pair
                        uint64_t highPairRank = highBit[pairsRanks];
                        uint64_t secondPairRank = highBit[pairsRanks ^ highPairRank];
                        uint64_t kickerRank = highBit[ranks ^ highPairRank ^ secondPairRank];

                        return calculateTwoPairValue(highPairRank | secondPairRank, kickerRank);
                    } else { // Flush or Straight
                        return flushOrStraightValue;
                    }
                }
            }
        }
    }

    static uint16_t getRankOfStraight(uint16_t ranks) noexcept
    {
        uint16_t straightMask = 0b1111100000000;

        for (int i = 8; i >= 0; i--) {
            if ((ranks & straightMask) == straightMask) {
                return 1 << (i + 4);
            }
            straightMask >>= 1;
        }

        const uint16_t fiveHighStraightMask = 0b1000000001111;

        return ((ranks & fiveHighStraightMask) == fiveHighStraightMask) ? (1 << 3) : 0;
    }

    void initializeEvaluator(std::unique_ptr<uint8_t, std::function<void(uint8_t*)>> internalTablesBuffer) noexcept
    {
        buffer          = std::move(internalTablesBuffer);
        numberOfBits    = buffer.get();
        rankOfStraights = reinterpret_cast<uint16_t*>(buffer.get() + sizeof(uint8_t) * BitsArraySize);
        highUpTo5Bits   = reinterpret_cast<uint16_t*>(buffer.get() + 3 * sizeof(uint8_t) * BitsArraySize);
        highBit         = reinterpret_cast<uint16_t*>(buffer.get() + 5 * sizeof(uint8_t) * BitsArraySize);
        highUpTo3Bits   = reinterpret_cast<uint16_t*>(buffer.get() + 7 * sizeof(uint8_t) * BitsArraySize);

        numberOfBits[0] = 0;
        rankOfStraights[0] = 0;
        highUpTo5Bits[0] = 0;
        highBit[0] = 0;
        highUpTo3Bits[0] = 0;

        for (uint16_t i = 1; i < BitsArraySize; i++) {
            std::bitset<16> bitset(i);

            numberOfBits[i] = bitset.count();

            for (int bit = 15; ; bit--) {
                if (bitset.test(bit)) {
                    highBit[i] = (1 << bit);
                    break;
                }
            }

            rankOfStraights[i] = getRankOfStraight(i);

            int bitsCounter = 0;
            highUpTo5Bits[i] = 0;
            if (i < HigUpTo3BitsArraySize) {
                highUpTo3Bits[i] = 0;
            }

            for (int bit = 15; bit >= 0; bit--) {
                if (bitset.test(bit)) {
                    highUpTo5Bits[i] |= (1 << bit);
                    bitsCounter++;

                    if ((bitsCounter <= 3) && (i < HigUpTo3BitsArraySize)) {
                        highUpTo3Bits[i] |= (1 << bit);
                    } else if (bitsCounter == 5) {
                        break;
                    }
                }
            }
        }
    }

    void deinitializeEvaluator()
    {
        buffer.reset();
    }
}
