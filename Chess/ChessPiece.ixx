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
import	std;
import Error;
import Scriptforge;

namespace sf = Scriptforge;

export namespace ChessPiece {
    enum class Ascii : char {
        Pawn = 'P',
        Rook = 'R',
        Knight = 'N',
        Bishop = 'B',
        Queen = 'Q',
        King = 'K'
    };
    enum class Unicode : char32_t {
        Pawn = U'♙',
        Rook = U'♖',
        Knight = U'♘',
        Bishop = U'♗',
        Queen = U'♕',
        King = U'♔'
    };
    class ChessType {
    public:
        ChessType() = delete;
        ChessType(bool isUnicode, const std::string& name) : m_isUnicode{ isUnicode } {
            if (name == "Pawn") {
                m_ascii = Ascii::Pawn;
                m_unicode = Unicode::Pawn;
            } else if (name == "Rook") {
                m_ascii = Ascii::Rook;
                m_unicode = Unicode::Rook;
            } else if (name == "Knight") {
                m_ascii = Ascii::Knight;
                m_unicode = Unicode::Knight;
            } else if (name == "Bishop") {
                m_ascii = Ascii::Bishop;
                m_unicode = Unicode::Bishop;
            } else if (name == "Queen") {
                m_ascii = Ascii::Queen;
                m_unicode = Unicode::Queen;
            } else if (name == "King") {
                m_ascii = Ascii::King;
                m_unicode = Unicode::King;
            } else {
                throw sf::Error(Error::to_string(Error::Code::InternalError), "Unknown chess piece.");
            }
        }

        auto operator()() const -> char32_t {
            return m_isUnicode ? static_cast<char32_t>(m_unicode) : static_cast<char32_t>(m_ascii);
        }
        auto operator()(bool isUnicode) const -> char32_t {
            return isUnicode ? static_cast<char32_t>(m_unicode) : static_cast<char32_t>(m_ascii);
        }
        void changeType(bool isUnicode) {
            m_isUnicode = isUnicode;
        }
    private:
        bool m_isUnicode;
        
        Ascii m_ascii;
        Unicode m_unicode;
    };
	template<typename Derived>
    class ChessCoordBase {
    public:
        ChessCoordBase() = delete;
        ChessCoordBase(int value) { write(value); }

        int toInt() const { return read(); }
        operator int() const { return toInt(); }

        virtual char toChar() const {
			return static_cast<char>('a' + read() - 1);
        }
        operator char() const { return toChar(); }

        Derived operator+(int other) const {
            islegal(read() + other);
            return Derived{ read() + other };
        }

        Derived operator-(int other) const {
            islegal(read() - other);
            return Derived{ read() - other };
        }

        Derived& operator++() {
            islegal(read() + 1);
            write(read() + 1);
            return *this;
        }

        Derived operator++(int) {
            Derived temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Derived& other) const {
            return read() == other.read();
        }

        bool operator!=(const Derived& other) const {
            return !(*this == other);
        }

       ~ChessCoordBase() = default;

    protected:
        uint8_t m_value;

        void islegal(int value) const {
            if (value < 1 || value > 8) {
                throw sf::Error(Error::to_string(Error::Code::InternalError), "ChessY value out of range.");
            }
        }
        void write(int value) {
            m_value = static_cast<uint8_t>(value);
        }
        int read() const {
            return static_cast<int>(m_value);
        }
    };

    class ChessX : public ChessCoordBase<ChessX> {
	public:
		ChessX(int value) : ChessCoordBase(value) {}
        char toChar() const override {
            return static_cast<char>('a' + read() - 1);
		}
    };

    class ChessY : public ChessCoordBase<ChessY>{
    public:
			ChessY(int value) : ChessCoordBase(value) {}
    };
    


    class ChessPiece {
    public:
        ChessPiece() = delete;
		ChessPiece(bool isUnicode,ChessType chessType) : m_isUnicode{ isUnicode },m_chessType{ chessType } {}
        auto getSymbol() const {
            return m_chessType(m_isUnicode);
        }
        void changeType(bool isUnicode) {
            m_isUnicode = isUnicode;
            m_chessType.changeType(isUnicode);
		}
        const ChessType& getType() const {
            return m_chessType;
		}
        bool getIsUnicode() const {
            return m_isUnicode;
        }
    private:
        bool m_isUnicode;
        ChessType m_chessType;
	};
}