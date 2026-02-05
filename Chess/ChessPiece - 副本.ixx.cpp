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
    class ChessCoordBase {
    public:
        ChessCoordBase() = delete;
        ChessCoordBase(int value) { write(value); }

        int toInt() const { return read(); }
        operator int() const { return toInt(); }

        // 算术运算符（不修改自身）
        ChessCoordBase operator+(int other) const {
            islegal(read() + other);
            return ChessCoordBase{ read() + other };
        }

        ChessCoordBase operator-(int other) const {
            islegal(read() - other);
            return ChessCoordBase{ read() - other };
        }

        // 自增自减（修改自身）
        ChessCoordBase& operator++() {
            islegal(read() + 1);
            write(read() + 1);
            return *this;
        }

        ChessCoordBase operator++(int) { // 后置++
            ChessCoordBase temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const ChessCoordBase& other) const {
            return read() == other.read();
        }

        bool operator!=(const ChessCoordBase& other) const {
            return !(*this == other);
        }

        virtual ~ChessCoordBase() = default;

    protected:
        uint8_t m_value; // 明确使用有符号8位整数

        virtual void islegal(int value) = 0;
        virtual void write(int value) = 0;
        virtual int read() const = 0;
    };

    class ChessY : public ChessCoordBase{
        public:
			ChessY(int value) : ChessCoordBase(value) {}
    private:
        void islegal(int value){
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

    class ChessPiece {
    public:
        Chess() = delete;
		Chess(bool isUnicode,ChessType chessType) : m_isUnicode{ isUnicode },m_chessType{ chessType } {}
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