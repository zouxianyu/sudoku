#ifndef SUDOKU_CORE_HPP
#define SUDOKU_CORE_HPP

#include <array>
#include <string>

using board_t = std::array<std::array<int, 9>, 9>;

std::vector<board_t> read_boards(const std::string &filename);

void
write_boards(const std::string &filename, const std::vector<board_t> &boards);

void print_board(const board_t &board);

std::vector<board_t> generate_final_boards(int count);

board_t solve_board(const board_t &board);

std::vector<board_t>
generate_game_boards(int count, int mode, std::pair<int, int> range,
                     bool unique);

#endif //SUDOKU_CORE_HPP
