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

#pragma once

#include <cstdint>
#include <cassert>
#include <stdexcept>

namespace pokertools
{
    const unsigned SuitsCount = 4;
    const unsigned SuitSizeInBits = 16;
    const unsigned RanksCount = 13;
    const unsigned CardsCount = SuitsCount * RanksCount;

    enum class Suit : unsigned {
        Clubs,
        Diamonds,
        Hearts,
        Spades
    };

    enum class Rank : uint16_t {
        None  = 0,
        R2    = 1 << 0,
        R3    = 1 << 1,
        R4    = 1 << 2,
        R5    = 1 << 3,
        R6    = 1 << 4,
        R7    = 1 << 5,
        R8    = 1 << 6,
        R9    = 1 << 7,
        R10   = 1 << 8,
        Jack  = 1 << 9,
        Queen = 1 << 10,
        King  = 1 << 11,
        Ace   = 1 << 12
    };

    enum class Card : uint64_t {
        Clubs2 = (static_cast<uint64_t>(Rank::R2) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        Clubs3 = (static_cast<uint64_t>(Rank::R3) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        Clubs4 = (static_cast<uint64_t>(Rank::R4) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        Clubs5 = (static_cast<uint64_t>(Rank::R5) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        Clubs6 = (static_cast<uint64_t>(Rank::R6) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        Clubs7 = (static_cast<uint64_t>(Rank::R7) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        Clubs8 = (static_cast<uint64_t>(Rank::R8) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        Clubs9 = (static_cast<uint64_t>(Rank::R9) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        Clubs10 = (static_cast<uint64_t>(Rank::R10) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        ClubsJack = (static_cast<uint64_t>(Rank::Jack) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        ClubsQueen = (static_cast<uint64_t>(Rank::Queen) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        ClubsKing = (static_cast<uint64_t>(Rank::King) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),
        ClubsAceHearts = (static_cast<uint64_t>(Rank::Ace) << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs)),

        Diamonds2 = (static_cast<uint64_t>(Rank::R2) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        Diamonds3 = (static_cast<uint64_t>(Rank::R3) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        Diamonds4 = (static_cast<uint64_t>(Rank::R4) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        DiamondsCard5 = (static_cast<uint64_t>(Rank::R5) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        Diamonds6 = (static_cast<uint64_t>(Rank::R6) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        Diamonds7 = (static_cast<uint64_t>(Rank::R7) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        Diamonds8 = (static_cast<uint64_t>(Rank::R8) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        Diamonds9 = (static_cast<uint64_t>(Rank::R9) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        Diamonds10 = (static_cast<uint64_t>(Rank::R10) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        DiamondsJack = (static_cast<uint64_t>(Rank::Jack) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        DiamondsQueen = (static_cast<uint64_t>(Rank::Queen) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        DiamondsKing = (static_cast<uint64_t>(Rank::King) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),
        DiamondsAce = (static_cast<uint64_t>(Rank::Ace) << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds)),

        Hearts2 = (static_cast<uint64_t>(Rank::R2) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        Hearts3 = (static_cast<uint64_t>(Rank::R3) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        Hearts4 = (static_cast<uint64_t>(Rank::R4) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        Hearts5 = (static_cast<uint64_t>(Rank::R5) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        Hearts6 = (static_cast<uint64_t>(Rank::R6) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        Hearts7 = (static_cast<uint64_t>(Rank::R7) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        Hearts8 = (static_cast<uint64_t>(Rank::R8) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        Hearts9 = (static_cast<uint64_t>(Rank::R9) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        Hearts10 = (static_cast<uint64_t>(Rank::R10) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        HeartsJack = (static_cast<uint64_t>(Rank::Jack) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        HeartsQueen = (static_cast<uint64_t>(Rank::Queen) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        HeartsKing = (static_cast<uint64_t>(Rank::King) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),
        HeartsAce = (static_cast<uint64_t>(Rank::Ace) << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts)),

        Spades2 = (static_cast<uint64_t>(Rank::R2) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        Spades3 = (static_cast<uint64_t>(Rank::R3) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        Spades4 = (static_cast<uint64_t>(Rank::R4) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        Spades5 = (static_cast<uint64_t>(Rank::R5) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        Spades6 = (static_cast<uint64_t>(Rank::R6) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        Spades7 = (static_cast<uint64_t>(Rank::R7) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        Spades8 = (static_cast<uint64_t>(Rank::R8) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        Spades9 = (static_cast<uint64_t>(Rank::R9) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        Spades10 = (static_cast<uint64_t>(Rank::R10) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        SpadesJack = (static_cast<uint64_t>(Rank::Jack) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        SpadesQueen = (static_cast<uint64_t>(Rank::Queen) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        SpadesKing = (static_cast<uint64_t>(Rank::King) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades)),
        SpadesAce = (static_cast<uint64_t>(Rank::Ace) << SuitSizeInBits * static_cast<unsigned>(Suit::Spades))
    };

    union Hand {
        uint64_t bits;
        uint16_t suits[4];

        struct {
            uint16_t clubs;
            uint16_t diamonds;
            uint16_t hearts;
            uint16_t spades;
        } suit;

        bool operator==(Card card)
        {
            return bits == static_cast<uint64_t>(card);
        }
    };

    static_assert(sizeof(Hand) == 8, "Hand should be exactly 64 bits");

    constexpr Hand operator"" _hand(unsigned long long hand)
    {
        //assert((hand & 0b1110000000000000111000000000000011100000000000001110000000000000) == 0);
        return { hand };
    }

    constexpr Card operator"" _clubs(unsigned long long rank)
    {
        //assert((rank >= 2) && (rank <= 14));
        return static_cast<Card>(uint64_t(1) << rank >> 2 << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs));
    }

    constexpr Card operator"" _diamonds(unsigned long long rank)
    {
        //assert((rank >= 2) && (rank <= 14));
        return static_cast<Card>(uint64_t(1) << rank >> 2 << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds));
    }

    constexpr Card operator"" _hearts(unsigned long long rank)
    {
        //assert((rank >= 2) && (rank <= 14));
        return static_cast<Card>(uint64_t(1) << rank >> 2 << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts));
    }

    constexpr Card operator"" _spades(unsigned long long rank)
    {
        //assert((rank >= 2) && (rank <= 14));
        return static_cast<Card>(uint64_t(1) << rank >> 2 << SuitSizeInBits * static_cast<unsigned>(Suit::Spades));
    }

    const auto ace_clubs = 14_clubs;
    const auto king_clubs = 13_clubs;
    const auto queen_clubs = 12_clubs;
    const auto jack_clubs = 11_clubs;

    const auto ace_diamonds = 14_diamonds;
    const auto king_diamonds = 13_diamonds;
    const auto queen_diamonds = 12_diamonds;
    const auto jack_diamonds = 11_diamonds;

    const auto ace_hearts = 14_hearts;
    const auto king_hearts = 13_hearts;
    const auto queen_hearts = 12_hearts;
    const auto jack_hearts = 11_hearts;

    const auto ace_spades = 14_spades;
    const auto king_spades = 13_spades;
    const auto queen_spades = 12_spades;
    const auto jack_spades = 11_spades;

    inline Hand operator|(Card card1, Card card2) noexcept
    {
        return Hand { static_cast<uint64_t>(card1) | static_cast<uint64_t>(card2) };
    }

    inline Hand operator|(Hand hand, Card card) noexcept
    {
        return Hand { hand.bits | static_cast<uint64_t>(card) };
    }

    inline Hand operator|(Card card, Hand hand) noexcept
    {
        return Hand { hand.bits | static_cast<uint64_t>(card) };
    }

    inline Hand& operator|=(Hand& hand, Card card) noexcept
    {
        hand.bits |= static_cast<uint64_t>(card);
        return hand;
    }

    inline Hand operator|(Hand hand1, Hand hand2) noexcept
    {
        return Hand { hand1.bits | hand2.bits };
    }

    inline Hand& operator|=(Hand& hand1, Hand hand2) noexcept
    {
        hand1.bits |= hand2.bits;
        return hand1;
    }

    inline Card createCard(Rank rank, Suit suit) noexcept
    {
        return static_cast<Card>(static_cast<uint64_t>(rank) << SuitSizeInBits * static_cast<unsigned>(suit));
    }

    inline Card createCard(unsigned cardNumber) noexcept
    {
        assert(cardNumber < CardsCount);
        unsigned suite = cardNumber / RanksCount;
        uint64_t rank = cardNumber % RanksCount;
        return static_cast<Card>(uint64_t(1) << rank << SuitSizeInBits * suite);
    }

    enum class HandType : unsigned {
        HighCard,
        Pair,
        TwoPair,
        ThreeOfAKind,
        Straight,
        Flush,
        FullHouse,
        FourOfAKind,
        StraightFulsh
    };

    union EvaluateResult {
        uint32_t value;

        struct {
            unsigned lowRanks: 13;
            unsigned highRanks: 13;
            unsigned :2;
            unsigned handType: 4;
        } details;
    };

    static_assert(sizeof(EvaluateResult) == 4, "EvaluateResult should be exactly 32 bits");
}
