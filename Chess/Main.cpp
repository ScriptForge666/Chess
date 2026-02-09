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
#include "json.hpp"
import std;
import ChessPos;
import ChessPiece;
import Local;
import Scriptforge.Err;
namespace sf = Scriptforge;
using namespace Chess;

int main() {
        try {
            Local::Lang chineseLang(std::locale("zh-CN"));
            std::cout << "中文语言: " << chineseLang.getLanguageName() << std::endl;
            Pos::ChessPos pos1{ 'a',1,chineseLang };

            Local::Lang englishLang(std::locale("en-US"));
            std::cout << "英文语言: " << englishLang.getLanguageName() << std::endl;
            Pos::ChessPos pos2{ 'a',1,englishLang };
            Piece::ChessPiece WKnight{ Type::Color::White, Type::Type::Knight, pos1, true};
            std::cout << "白色骑士: " << WKnight << std::endl;
        }
        catch (const sf::Error& e) {
            std::cerr << "错误: " << e.what() << std::endl;
        }
        return 0;
}
