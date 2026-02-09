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
import Local;
using namespace Chess::Type;

namespace Chess::Piece {
	export class ChessPieceBase {
	public:
		ChessPieceBase() = delete;
		ChessPieceBase(Chess::Type::Color color, Chess::Type::Type type, bool isUnicode = false) :
			m_color{ color }, m_type{ type }, m_pos{ Chess::Pos::ChessPos{1,1, Local::Lang{}} } {
		}
		ChessPieceBase(Chess::Type::Color color, Chess::Type::Type type, Chess::Pos::ChessPos pos, bool isUnicode = false) :
			m_color{ color }, m_type{ type }, m_pos{ pos }, m_isUnicode{ isUnicode } {
		}
		Chess::Type::Color getColor() const { return m_color; }
		Chess::Type::Type getType() const { return m_type; }
		Chess::Pos::ChessPos getPos() const { return m_pos; }
		bool getUnicode() const { return m_isUnicode; }
		void setPos(const Pos::ChessPos& pos) {
			if (pos.yInt() == 8 && m_color == Chess::Type::Color::White && m_type == Chess::Type::Type::Pawn) {
					this->WhitePawnHasQueen = true;
					this->m_type = Chess::Type::Type::Queen;
			}
			else if(pos.yInt() == 1 && m_color == Chess::Type::Color::Black && m_type == Chess::Type::Type::Pawn) {
				this->BlackPawnHasQueen = true;
				this->m_type = Chess::Type::Type::Queen;
			}
				this->m_pos = pos;
		}
	protected:
		Chess::Type::Color m_color;
		Chess::Type::Type m_type;
		Chess::Pos::ChessPos m_pos;
		bool m_isUnicode;
		bool m_iscaptured{ false };
		inline static bool WhitePawnHasQueen{ false };
		inline static bool BlackPawnHasQueen{ true };
	};
	
	export
	class ChessPiece : public ChessPieceBase {
	public:
		ChessPiece() = default;
		ChessPiece(Chess::Type::Color color, Chess::Type::Type type, Chess::Pos::ChessPos pos, bool isUnicode = false) : ChessPieceBase(color, type, pos, isUnicode) {}
		friend std::ostream& operator<<(std::ostream& os, const ChessPiece& piece) {
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
}