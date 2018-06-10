#ifndef OOP_HW4_RPSGAME_H
#define OOP_HW4_RPSGAME_H

#include <initializer_list>
#include <iostream>
#include <utility>
#include <memory>
#include <tuple>

using namespace std;


// Generic GameBoard class
template<int ROWS, int COLS, class GAME_PIECE, int NUM_PLAYERS = 2>
class GameBoard {

    using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

public:
    class rps_point {
        int num_player;
        GAME_PIECE game_piece;
    public:
        rps_point(int m_num_player, GAME_PIECE m_game_piece) : num_player(m_num_player), game_piece(m_game_piece) {}

        //set/get
        void setGamePlayer(int player) { this->num_player = player; };

        void setPieceOnBoard(GAME_PIECE piece) { this->game_piece = piece; };

        int getNumPlayer() { return this->num_player; }

        GAME_PIECE getPieceBoard() { return this->game_piece; }

    };

private:
    rps_point ***game_board;

public:
    // GameBoard Constructor
    GameBoard() {
        game_board = new rps_point **[ROWS];
        for (int i = 0; i < ROWS; ++i) {
            game_board[i] = new rps_point *[COLS];
            for (int j = 0; j < COLS; ++j) {
                game_board[i][j] = nullptr;
            }
        }
    }

    // delete
    ~ GameBoard() {
        delete[] game_board;
    }

    PieceInfo setPiece(int row, int col, GAME_PIECE piece, int player) {
        if (this->game_board[row][col] == nullptr) {
            this->game_board[row][col] = new rps_point(player, piece);
            return nullptr;
        }
        // if the location is not nullptr- returns the pieceinfo that was previously in this location
        int previous_player = this->game_board[row][col]->getNumPlayer();
        GAME_PIECE previous_piece = this->game_board[row][col]->getPieceBoard();
        this->game_board[row][col]->setGamePlayer(player);
        this->game_board[row][col]->setPieceOnBoard(piece);
        return make_unique<const pair<int, GAME_PIECE>>(previous_player, previous_piece);
    }

    PieceInfo getPiece(int row, int col) {
        return make_unique<const pair<int, GAME_PIECE>>(game_board[row][col]->getNumPlayer(),
                                                        game_board[row][col]->getPieceBoard());
    }

    class BaseIterator {
        GameBoard *m_game_board;
        int *m_num_player;
        GAME_PIECE *m_piece;
        int m_x, m_y;

    public:
        // first ctor - gameboard, player, gamepiece, x=-1, y=COLS-1
        BaseIterator(GameBoard *game_board, int *num_player, GAME_PIECE *piece) :
                m_game_board(game_board), m_num_player(num_player), m_piece(piece), m_x(-1), m_y(COLS - 1) {
            ++(*this);
        }

        // second ctor - gameboard, player, gamepiece, x, y
        BaseIterator(GameBoard *game_board, int *num_player, GAME_PIECE *piece, int x, int y) :
                m_game_board(game_board), m_num_player(num_player), m_piece(piece), m_x(x), m_y(y) {

        }

        // getters to x,y
        int get_x() { return this->m_x; }

        int get_y() { return this->m_y; }

        // operator *
        const tuple<int, int, GAME_PIECE, int> &operator*() const {
            return *(new tuple<int, int, GAME_PIECE, int>(m_x, m_y, m_game_board->game_board[m_x][m_y]->getPieceBoard(),
                                                          m_game_board->game_board[m_x][m_y]->getNumPlayer()));
        }
        //operator !=

        bool operator!=(const BaseIterator &other) {
            return (this->m_x != other.m_x || this->m_y != other.m_y);
        }

        // operator ++
        BaseIterator &operator++() {
            // if possible, iterate over y
            m_y = (m_y + 1) % COLS;
            if (m_y == 0)
                m_x++;
            if (m_x >= ROWS)
                return *this;
            if (m_game_board->game_board[m_x][m_y] != nullptr) {
                bool player_check = m_num_player != nullptr && m_game_board->game_board[m_x][m_y]->getNumPlayer() == *m_num_player;
                if ((player_check) || (m_num_player == nullptr)) {
                    bool piece_check = m_piece != nullptr && m_game_board->game_board[m_x][m_y]->getPieceBoard() == *m_piece;
                    if ((piece_check) || (m_piece == nullptr))
                        return *this;
                }
            }
            while (true) {
                m_y = (m_y + 1) % COLS;
                if (m_y == 0)
                    m_x++;
                if (m_x >= ROWS)
                    break;
                if (m_game_board->game_board[m_x][m_y] != nullptr) {
                    bool player_check = m_num_player != nullptr && m_game_board->game_board[m_x][m_y]->getNumPlayer() == *m_num_player;
                    if ((player_check) || (m_num_player == nullptr)) {
                        bool piece_check = m_piece != nullptr && m_game_board->game_board[m_x][m_y]->getPieceBoard() == *m_piece;
                        if ((piece_check) || (m_piece == nullptr))
                            return *this;
                    }
                }
            }
            return *this;
        }
    };

    class MyIterator {
        GameBoard *m_game_board;
        int *m_num_player;
        GAME_PIECE *m_piece;
    public:
        MyIterator(GameBoard *game_board, int *num_player, GAME_PIECE *piece) :
                m_game_board(game_board), m_num_player(num_player), m_piece(piece) {}

        BaseIterator begin() { return BaseIterator(m_game_board, m_num_player, m_piece); }

        BaseIterator end() { return BaseIterator(m_game_board, m_num_player, m_piece, ROWS, 0); }
    };


    // begin & end
    BaseIterator begin() { return BaseIterator(this, nullptr, nullptr); }

    BaseIterator end() { return BaseIterator(this, nullptr, nullptr, ROWS, 0); }

    MyIterator allPiecesOfPlayer(int num_player) { return MyIterator(this, new int(num_player), nullptr); }

    MyIterator allOccureneceOfPiece(GAME_PIECE piece) { return MyIterator(this, nullptr, new GAME_PIECE(piece)); }

    MyIterator allOccureneceOfPieceForPlayer(GAME_PIECE piece, int num_player) { return MyIterator(this, new int(num_player), new GAME_PIECE(piece)); }


};

#endif //OOP_HW4_RPSGAME_H
