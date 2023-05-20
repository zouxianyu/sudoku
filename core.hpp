#ifndef SUDOKU_CORE_HPP
#define SUDOKU_CORE_HPP

#include <array>
#include <string>

using board_t = std::array<std::array<int, 9>, 9>;

board_t read_board(const std::string &filename);

void write_board(const std::string &filename, const board_t &board);

void print_board(const board_t &board);

board_t generate_final_board();

board_t solve_board(const board_t &board);

board_t generate_game_board(int mode, std::pair<int, int> range, bool unique);

#endif //SUDOKU_CORE_HPP
