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

    int lowest_i = -1;
    int lowest_n = -1;
    std::vector<char> lowest_possibilities;

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

                if(possibilities.empty()) {
                    throw std::runtime_error("Possibility Array is empty");
                }
                if(possibilities.size() == 1) {
                    board[i][n] = possibilities[0];
                    board_changed = true;
                }
                else if(lowest_possibilities.empty() || lowest_possibilities.size() > possibilities.size()) {
                    lowest_possibilities = possibilities;
                    lowest_i = i;
                    lowest_n = n;
                }
            }
        }

        if(!board_changed){
            for (auto possibility: lowest_possibilities) {
                try {
                    auto board_copy = board;
                    board_copy[lowest_i][lowest_n] = possibility;
                    solve_sudoku(board_copy);
                    if(is_solved(board_copy)) {
                        board.swap(board_copy);
                    }
                    break;
                }
                catch (std::runtime_error &exc) {
                    std::cout << exc.what() << " " << lowest_i << " " << lowest_n << " " << possibility << std::endl;
                }
            }

            if(!is_solved(board)) {
                throw std::runtime_error("Multiple possibilities exhausted, backtracking...");
            }
        }
        board_changed = false;
        lowest_i = -1;
        lowest_n = -1;
        lowest_possibilities.clear();
    }
}

int main()
{
    std::vector<std::vector<char>> board({
        std::vector<char>({'.','.','9','7','4','8','.','.','.'}),
        std::vector<char>({'7','.','.','.','.','.','.','.','.'}),
        std::vector<char>({'.','2','.','1','.','9','.','.','.'}),
        std::vector<char>({'.','.','7','.','.','.','2','4','.'}),
        std::vector<char>({'.','6','4','.','1','.','5','9','.'}),
        std::vector<char>({'.','9','8','.','.','.','3','.','.'}),
        std::vector<char>({'.','.','.','8','.','3','.','2','.'}),
        std::vector<char>({'.','.','.','.','.','.','.','.','6'}),
        std::vector<char>({'.','.','.','2','7','5','9','.','.'})
    });

    solve_sudoku(board);

    for(const auto& line: board){
        for(auto value: line){
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }
}