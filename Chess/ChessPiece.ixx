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
export module ChessPiece;
import std;
import ChessPos;
import ChessType;
using namespace Chess;

export namespace Chess::Piece {
	enum class Color {
		White,
		Black
	};
	enum class Type {
		Pawn,
		Rook,
		Knight,
		Bishop,
		Queen,
		King
	};

	template<Color C, Type T>
	class ChessPieceBase {
	public:
		ChessPieceBase() = default;
		ChessPieceBase(const Pos::ChessPos& pos) : m_pos{ pos }{}

	private:
		Color m_color = C;
		Type m_type = T;
		Pos::ChessPos m_pos;
	};
}