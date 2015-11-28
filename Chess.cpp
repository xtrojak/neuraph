#include "types.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>




// Loads and handles a database of chess moves.
class Chess
{
public:
    struct Move
    {
        std::vector<f64> board, boardAfter;
        std::tuple<f64, f64> from, to;
        bool white;
    };


    Chess(const std::string& filename)
    {
        std::ifstream input;
        input.open(filename);

        while (!input.eof())
        {
            try
            {
                Move m;
        
                std::string line;
                std::getline(input, line);
                m.board = parseBoard(line);
                std::getline(input, line);
                m.boardAfter = parseBoard(line);

                std::string player;
                input >> player;
                m.white = (player == "w");

                m.from = parseTuple(input);
                m.to = parseTuple(input);

                Moves.push_back(m);

                std::getline(input, player);
                std::getline(input, player);
            }
            catch (const std::string &ex ) {
                std::cerr << ex << std::endl;
            }
        }
    }

    const u32 getMoveCount() const
    {
        return Moves.size();
    }

    const Move &getMove(const u32 i) const
    {
        return Moves.at(i);
    }

    
    static void printBoard(std::vector<f64> &board)
    {
        std::string WHITE = "prnbqk";
        std::string BLACK = "PRNBQK";
        for (u32 i = 0; i < 64; i++)
        {
            if ( i % 8 == 0 )
            {
                std::cout << "\n";
            }
            if ( board[i] > 0 )
            {
                std::cout << WHITE.at(board[i]) << " ";
            }
            else if ( board[i] < 0 )
                {
                    std::cout << BLACK.at( (-1) * board[i] ) << " ";
                }
            else 
                {
                    std::cout << ". ";
                }
        }
    }

    static const std::vector<f64> parseBoard(const std::string &line)
    {
        std::vector<f64> board;

        std::stringstream ss(line);
        std::string item;

        while (std::getline(ss, item, ' '))
        {
            board.push_back(std::stoi(item));
        }

        if (board.size() != 64)
            throw "Chess::parseBoard invalid board input: " + line;

        return board;
    }

private:
    std::vector<Move> Moves;

    const std::tuple<f64, f64> parseTuple(std::ifstream &file) const
    {
        std::string s1, s2;
        file >> s1 >> s2;
        return std::tuple<f64, f64>(std::stoi(s1), std::stoi(s2));
    }
            
};

