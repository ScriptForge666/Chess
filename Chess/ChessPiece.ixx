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
using namespace Chess::Type;

namespace Chess::Piece {
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

	export
		template<Color C, Type T, bool isUnicode>
	class ChessPieceBase {
	public:
		ChessPieceBase() = default;
		ChessPieceBase(const Pos::ChessPos& pos) : m_pos{ pos } {}
		Color getColor() const { return m_color; }
		Type getType() const { return m_type; }
		Pos::ChessPos getPos() const { return m_pos; }
		bool getUnicode() const { return m_isUnicode; }
		virtual void setPos(const Pos::ChessPos& pos) { m_pos = pos; }
	protected:
		Color m_color = C;
		Type m_type = T;
		bool m_isUnicode = isUnicode;
		Pos::ChessPos m_pos;
	};
	
	export
		template<Color C,Type T,bool isUnicode>
	class ChessPiece : public ChessPieceBase<C, T, isUnicode> {
	public:
		ChessPiece() = default;
		ChessPiece(const Pos::ChessPos& pos) : ChessPieceBase<C, T, isUnicode>{ pos } {}
		friend std::ostream& operator<<(std::ostream& os, const ChessPiece<C, T, isUnicode>& piece) {
			int typeIndex = static_cast<int>(piece.getType());
			int colorIndex = static_cast<int>(piece.getColor());

			if (piece.getUnicode()) {
				auto& unicodeArray = std::get<1>(chessType);
				os << unicodeArray[colorIndex][typeIndex];
			}
			else {
				// 使用 ASCII 符号（tuple 的第一个元素）
				auto& asciiArray = std::get<0>(chessType);
				os << asciiArray[colorIndex][typeIndex];
			}

			return os;
		}
	};

	export
		template<bool isUnicode>
	class ChessPiece<Color::White, Type::Pawn, isUnicode> : public ChessPieceBase<Color::White, Type::Pawn, isUnicode> {
	public:
		ChessPiece() = default;
		ChessPiece(const Pos::ChessPos& pos) : ChessPieceBase<Color::White, Type::Pawn, isUnicode>{ pos } {}
		void setPos(const Pos::ChessPos& pos) override {
			if (pos.yInt() == 8 && !hasQueen) {
				hasQueen = true;
				this->m_type = Type::Queen;
			}
			else {
				this->m_pos = pos;
			}
		}
		friend
			std::ostream& operator<<(std::ostream& os, const ChessPiece<Color::White, Type::Pawn, isUnicode>& piece) {
			return operator<<(os, piece);
		}
	private:
		static bool hasQueen;
	};

	export 
		template<bool isUnicode>
	class ChessPiece<Color::Black, Type::Pawn, isUnicode> : public ChessPieceBase<Color::Black, Type::Pawn, isUnicode> {
	public:
		ChessPiece() = default;
		ChessPiece(const Pos::ChessPos& pos) : ChessPieceBase<Color::Black, Type::Pawn, isUnicode>{ pos } {}
		void setPos(const Pos::ChessPos& pos) override {
			if (pos.yInt() == 1 && !hasQueen) {
				hasQueen = true;
				this->m_type = Type::Queen;
			}
			else {
				this->m_pos = pos;
			}
		}
		friend
			std::ostream& operator<<(std::ostream& os, const ChessPiece<Color::White, Type::Pawn, isUnicode>& piece) {
			return operator<<(os, piece);
		}
	private:
		static bool hasQueen;
	};
}