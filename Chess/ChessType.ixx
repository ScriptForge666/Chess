export module ChessType;
import std;

export namespace Chess::Type {
	std::map<std::tuple<char, char, char32_t, char32_t>, std::string> chessType{
        // 基础棋子类型
        {{'P', 'p', U'♙', U'♟'}, "Pawn"},       // 兵
        {{'R', 'r', U'♖', U'♜'}, "Rook"},       // 车
        {{'N', 'n', U'♘', U'♞'}, "Knight"},     // 马
        {{'B', 'b', U'♗', U'♝'}, "Bishop"},     // 象
        {{'Q', 'q', U'♕', U'♛'}, "Queen"},      // 后
        {{'K', 'k', U'♔', U'♚'}, "King"},       // 王
	};
}