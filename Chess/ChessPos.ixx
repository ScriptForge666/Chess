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
export module ChessPos;
import std;
import Error;
import Local;
import Scriptforge;
namespace sf = Scriptforge;

export namespace Chess::Pos {

    template<typename Derived>
    class ChessCoordBase {
    public:
        ChessCoordBase() = delete;
        ChessCoordBase(int value, Local::Lang lang):
            m_lang{lang} {
			isLegal(value);
            write(value);
        }

        int toInt() const { return read(); }
        operator int() const { return toInt(); }

        virtual char toChar() const {
            return static_cast<char>(read() + '0');
        }
        operator char() const { return toChar(); }

        Derived operator+(int other) const {
            isLegal(read() + other);
            return Derived{ read() + other, m_lang };
        }

        Derived operator-(int other) const {
            isLegal(read() - other);
            return Derived{ read() - other, m_lang };
        }

        Derived& operator++() {
            isLegal(read() + 1);
            write(read() + 1);
            return *this;
        }

        Derived operator++(int) {
            Derived temp = *this;
            ++(*this);
            return temp;
        }

        Derived& operator--() {
            isLegal(read() - 1);
            write(read() - 1);
            return *this;
        }

        Derived operator--(int) {
            Derived temp = *this;
            --(*this);
            return temp;
        }
        bool operator==(const Derived& other) const {
            return read() == other.read();
        }

        bool operator!=(const Derived& other) const {
            return !(*this == other);
        }

        Derived& operator=(int other) {
            isLegal(other);
            write(other);
            return static_cast<Derived&>(*this);
        }

        ~ChessCoordBase() = default;

    protected:
        std::byte m_value;
		Local::Lang m_lang;

        void isLegal(int value) const {
            if (value < 1 || value > 8) {
                throw sf::Error(Error::to_string(Error::Code::InternalError), m_lang.get("ChessCoordBase_value_out_of_range"));
            }
        }
        void write(int value) {
            m_value = static_cast<std::byte>(value);
        }
        int read() const {
            return static_cast<int>(m_value);
        }
    };

    class ChessX : public ChessCoordBase<ChessX> {
    public:
        ChessX(int value, Local::Lang lang) : ChessCoordBase(value, lang) {}
        using ChessCoordBase<ChessX>::operator=;
        char toChar() const override {
            return static_cast<char>('a' + read() - 1);
        }
    };

    class ChessY : public ChessCoordBase<ChessY> {
    public:
        ChessY(int value, Local::Lang lang) : ChessCoordBase(value, lang) {}
        using ChessCoordBase<ChessY>::operator=;
    };

    class ChessPos {
    public:
        ChessPos() = delete;
        ChessPos(int x, int y, Local::Lang lang) : m_x{ x, lang }, m_y{ y, lang } {}
        ChessPos(char x, int y, Local::Lang lang) : m_x{ x - 'a' + 1, lang }, m_y{ y, lang } {}

        // 明确区分不同的获取方式
        ChessX xObject() const { return m_x; }
        ChessY yObject() const { return m_y; }

        int xInt() const { return m_x.toInt(); }
        int yInt() const { return m_y.toInt(); }

        char xChar() const { return m_x.toChar(); }
        char yChar() const { return m_y.toChar(); }

        std::string toString() const {
            return std::string{ xChar() } + std::to_string(yInt());
        }

        void setX(int x) { m_x = x; }
        void setY(int y) { m_y = y; }
        void set(int x, int y) {
            setX(x);
            setY(y);
        }

        void moveX(int delta) { m_x = m_x + delta; }
        void moveY(int delta) { m_y = m_y + delta; }
        void move(int deltaX, int deltaY) {
            moveX(deltaX);
            moveY(deltaY);
        }

        bool isValid() const {
            return m_x.toInt() >= 1 && m_x.toInt() <= 8 &&
                m_y.toInt() >= 1 && m_y.toInt() <= 8;
        }

        // 重载比较运算符
        bool operator==(const ChessPos& other) const {
            return m_x == other.m_x && m_y == other.m_y;
        }

        bool operator!=(const ChessPos& other) const {
            return !(*this == other);
        }

    private:
        ChessX m_x;
        ChessY m_y;
    };
}