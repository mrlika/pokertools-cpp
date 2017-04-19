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
    constexpr unsigned SuitsCount = 4;
    constexpr unsigned SuitSizeInBits = 16;
    constexpr unsigned RanksCount = 13;
    constexpr unsigned CardsCount = SuitsCount * RanksCount;

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
    private:
        uint64_t bits;
        uint16_t suits[4];

    public:
        Hand() noexcept = default;

        constexpr Hand(uint64_t value) noexcept : bits(value)
        {
            assert((bits & 0b1110000000000000111000000000000011100000000000001110000000000000) == 0);
        }

        constexpr Hand(Card card) noexcept : bits(static_cast<uint64_t>(card))
        {
            assert((bits & 0b1110000000000000111000000000000011100000000000001110000000000000) == 0);
        }

        inline constexpr operator uint64_t() const noexcept
        {
            return bits;
        }

        inline constexpr uint16_t suit(Suit suit) const noexcept
        {
            return suits[static_cast<unsigned>(suit)];
        }
    };

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

    template <typename T>
    inline constexpr Hand operator|(Card card, T value) noexcept
    {
        Hand result = static_cast<uint64_t>(card) | static_cast<uint64_t>(value);
        return result;
    }

    template <typename T>
    inline constexpr Hand operator|(Hand hand, T value) noexcept
    {
        Hand result = static_cast<uint64_t>(hand) | static_cast<uint64_t>(value);
        return result;
    }

    template <typename T>
    inline constexpr Hand& operator|=(Hand& hand, T value) noexcept
    {
        hand = hand | static_cast<uint64_t>(value);
        return hand;
    }

    template <typename T>
    inline constexpr bool operator==(Hand hand, T value) noexcept
    {
        return static_cast<uint64_t>(hand) == static_cast<uint64_t>(value);
    }

    template <typename T>
    inline constexpr bool operator==(Card card, T value) noexcept
    {
        return static_cast<uint64_t>(card) == static_cast<uint64_t>(value);
    }

    template <typename T>
    inline constexpr bool operator==(HandType handType, T value) noexcept {
        return handType == static_cast<unsigned>(value);
    }

    inline constexpr Card createCard(Rank rank, Suit suit) noexcept
    {
        assert(static_cast<unsigned>(suit) <= 3);
        assert(rank != Rank::None);
        return static_cast<Card>(static_cast<uint64_t>(rank) << SuitSizeInBits * static_cast<unsigned>(suit));
    }

    inline constexpr Card createCard(unsigned cardNumber) noexcept
    {
        assert(cardNumber < CardsCount);
        unsigned suite = cardNumber / RanksCount;
        uint64_t rank = cardNumber % RanksCount;
        return static_cast<Card>(uint64_t(1) << rank << SuitSizeInBits * suite);
    }

    inline constexpr Card operator"" _clubs(unsigned long long rank) noexcept
    {
        assert((rank >= 2) && (rank <= 14));
        return static_cast<Card>(uint64_t(1) << rank >> 2 << SuitSizeInBits * static_cast<unsigned>(Suit::Clubs));
    }

    inline constexpr Card operator"" _diamonds(unsigned long long rank) noexcept
    {
        assert((rank >= 2) && (rank <= 14));
        return static_cast<Card>(uint64_t(1) << rank >> 2 << SuitSizeInBits * static_cast<unsigned>(Suit::Diamonds));
    }

    inline constexpr Card operator"" _hearts(unsigned long long rank) noexcept
    {
        assert((rank >= 2) && (rank <= 14));
        return static_cast<Card>(uint64_t(1) << rank >> 2 << SuitSizeInBits * static_cast<unsigned>(Suit::Hearts));
    }

    inline constexpr Card operator"" _spades(unsigned long long rank) noexcept
    {
        assert((rank >= 2) && (rank <= 14));
        return static_cast<Card>(uint64_t(1) << rank >> 2 << SuitSizeInBits * static_cast<unsigned>(Suit::Spades));
    }

    constexpr Card ace_clubs = 14_clubs;
    constexpr Card king_clubs = 13_clubs;
    constexpr Card queen_clubs = 12_clubs;
    constexpr Card jack_clubs = 11_clubs;

    constexpr Card ace_diamonds = 14_diamonds;
    constexpr Card king_diamonds = 13_diamonds;
    constexpr Card queen_diamonds = 12_diamonds;
    constexpr Card jack_diamonds = 11_diamonds;

    constexpr Card ace_hearts = 14_hearts;
    constexpr Card king_hearts = 13_hearts;
    constexpr Card queen_hearts = 12_hearts;
    constexpr Card jack_hearts = 11_hearts;

    constexpr Card ace_spades = 14_spades;
    constexpr Card king_spades = 13_spades;
    constexpr Card queen_spades = 12_spades;
    constexpr Card jack_spades = 11_spades;

    static_assert(sizeof(Hand) == 8, "Hand should be exactly 64 bits");
    static_assert(sizeof(EvaluateResult) == 4, "EvaluateResult should be exactly 32 bits");
}
