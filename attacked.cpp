/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Dan Ravensloft <dan.ravensloft@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdbool.h>

#include "board.h"
#include "functions.h"

bool IsAttacked(struct Board * b, int side, int square)
{
    uint64_t pawns, knights, bishopsqueens, rooksqueens, kings;

    pawns = b->pieces[PAWN] & b->colors[side];
    if (PawnAttacks(!side, square) & pawns) return true;

    knights = b->pieces[KNIGHT] & b->colors[side];
    if (KnightAttacks(square) & knights) return true;

    kings = b->pieces[KING] & b->colors[side];
    if (KingAttacks(square) & kings) return true;

    bishopsqueens = (b->pieces[BISHOP] | b->pieces[QUEEN]) & b->colors[side];
    if (BishopAttacks(square, (b->colors[WHITE] | b->colors[BLACK])) & bishopsqueens) return true;

    rooksqueens = (b->pieces[ROOK] | b->pieces[QUEEN]) & b->colors[side];
    if (RookAttacks(square, (b->colors[WHITE] | b->colors[BLACK])) & rooksqueens) return true;

    return false;
}

bool IsIllegal(struct Board * b)
{
    return IsAttacked(b, b->side, lsb(b->pieces[KING] & b->colors[!b->side]));
}

bool IsInCheck(struct Board * b)
{
    return IsAttacked(b, !b->side, lsb(b->pieces[KING] & b->colors[b->side]));
}
