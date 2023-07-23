//
// Created by wilke on 23.07.2023.
//
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

bool is_solved(std::vector<std::vector<char>> &board) {

    for (const auto& line: board) {
        for(const auto& value: line) {
            if(value=='.') {
                return false;
            }
        }
    }
    return true;
}
std::vector<char> get_quadrant_values(std::vector<std::vector<char>> &board, unsigned char i, unsigned char n) {
    std::vector<char> quadrant_values;

    for(auto x = (i / 3) * 3; x < ((i / 3) * 3) + 3; x++)
    {
        for(auto y = (n / 3) * 3; y < ((n / 3) * 3) + 3; y++)
        {
            if(board[x][y] != '.')
            {
                quadrant_values.push_back(board[x][y]);
            }
        }
    }

    return quadrant_values;
}

std::vector<char> calculate_possibilities(std::vector<std::vector<char>> &board, unsigned char i, unsigned char n) {
    std::vector<char> possibilities({'1', '2', '3', '4', '5', '6', '7', '8', '9'});
    std::vector<char> row_possibilities;

    std::copy_if(possibilities.begin(), possibilities.end(), std::back_inserter(row_possibilities), [&board, &i](char c) -> bool
    {
        return std::find(board[i].begin(), board[i].end(), c) == board[i].end();
    });

    std::vector<char> column_values;

    std::for_each(board.begin(), board.end(), [&column_values, &n](auto v) -> char {
        column_values.push_back(v[n]);
    });

    std::vector<char> column_possibilities;
    std::copy_if(row_possibilities.begin(), row_possibilities.end(), std::back_inserter(column_possibilities), [&column_values] (char c) -> bool
    {
       return std::find(column_values.begin(), column_values.end(), c) == column_values.end();
    });

    auto quadrant_values = get_quadrant_values(board, i, n);
    std::vector<char> final_possibilities;
    std::copy_if(column_possibilities.begin(), column_possibilities.end(), std::back_inserter(final_possibilities), [&quadrant_values] (char c) -> bool
    {
       return std::find(quadrant_values.begin(), quadrant_values.end(), c) == quadrant_values.end();
    });

    return final_possibilities;
}

void solve_sudoku(std::vector<std::vector<char>> &board) {
    bool board_changed = false;
    while (!is_solved(board))
    {
        for(auto i = 0; i < board.size(); i++)
        {
            for(auto n = 0; n < board[i].size(); n++)
            {
                if(board[i][n] != '.'){
                    continue;
                }
                auto possibilities = calculate_possibilities(board, i, n);

                if(possibilities.size() == 1) {
                    board[i][n] = possibilities[0];
                    board_changed = true;
                }
            }
        }

        if(!board_changed){
            //TODO: Add handling of multiple possibilities
            throw std::exception();
        }
        board_changed = false;
    }
}

int main()
{
    std::vector<std::vector<char>> board({
        std::vector<char>({'5','3','.','.','7','.','.','.','.'}),
        std::vector<char>({'6','.','.','1','9','5','.','.','.'}),
        std::vector<char>({'.','9','8','.','.','.','.','6','.'}),
        std::vector<char>({'8','.','.','.','6','.','.','.','3'}),
        std::vector<char>({'4','.','.','8','.','3','.','.','1'}),
        std::vector<char>({'7','.','.','.','2','.','.','.','6'}),
        std::vector<char>({'.','6','.','.','.','.','2','8','.'}),
        std::vector<char>({'.','.','.','4','1','9','.','.','5'}),
        std::vector<char>({'.','.','.','.','8','.','.','7','9'})
    });

    solve_sudoku(board);

    for(const auto& line: board){
        for(auto value: line){
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }
}