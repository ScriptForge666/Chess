// Copyright 2026 Scriptforge
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
export module ChessType;
import std;

export namespace Chess::Type {
    const auto chessType = std::make_tuple(
        std::array<std::array<char, 6>, 2>{{
            {{'P', 'R', 'N', 'B', 'Q', 'K'}},
            { {'p', 'r', 'n', 'b', 'q', 'k'} }
            }},
        std::array<std::array<std::string, 6>, 2>{{
            {{"♙", "♖", "♘", "♗", "♕", "♔"}},
            { {"♟", "♜", "♞", "♝", "♛", "♚"} }
            }},
        std::array<std::string, 6>{{
                "Pawn", "Rook", "Knight", "Bishop", "Queen", "King"
            }}
    );

    export enum class Color {
        White,
        Black
    };
    export enum class Type {
        Pawn,
        Rook,
        Knight,
        Bishop,
        Queen,
        King
    };
}