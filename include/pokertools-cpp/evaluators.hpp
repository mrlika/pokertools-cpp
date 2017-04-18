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

#include "poker.hpp"

#include <memory>
#include <functional>

namespace pokertools
{
    static constexpr unsigned BitsArraySize = 0b1111111000000 + 1;
    static constexpr unsigned HigUpTo3BitsArraySize = 0b1111100000000 + 1;
    static constexpr unsigned InternalTablesBufferSize = sizeof(uint8_t) * BitsArraySize + sizeof(uint16_t) * (HigUpTo3BitsArraySize + 3 * BitsArraySize);

    extern void initializeEvaluator(std::unique_ptr<uint8_t, std::function<void(uint8_t*)>> internalTablesBuffer) noexcept;

    template<typename Allocator = std::allocator<uint8_t>>
    extern void initializeEvaluator(const Allocator& allocatorForInternalTables = Allocator())
    {
        Allocator allocator(allocatorForInternalTables);

        initializeEvaluator(std::unique_ptr<uint8_t, std::function<void(uint8_t*)>>(
            allocator.allocate(InternalTablesBufferSize),
            [allocator] (uint8_t* pointer) mutable {
                allocator.deallocate(pointer, InternalTablesBufferSize);
            }));
    }

    extern void deinitializeEvaluator();

    extern uint32_t evaluateHoldem7CardsHand(Hand hand) noexcept;
    extern uint32_t evaluateHoldem5CardsHand(Hand hand) noexcept;
    extern uint32_t evaluateHoldemHand(Hand hand, unsigned cardsCount) noexcept;
}
