#include <fstream>
#include <iostream>
#include "core.hpp"

board_t read_board(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin) {
        throw std::runtime_error("�����ļ�������");
    }

    board_t board;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!fin) {
                throw std::runtime_error("�����ļ���ʽ����");
            }
            char v;
            fin >> v;
            if (!(v >= '1' && v <= '9' || v == '$')) {
                throw std::runtime_error("�����ļ���ʽ����");
            }
            if (v == '$') {
                v = '0';
            }
            board[i][j] = v - '0';
        }
    }
    return board;
}

void write_board(const std::string &filename, const board_t &board) {
    std::ofstream fout(filename);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char v = board[i][j] == 0 ? '$' : board[i][j] + '0';
            fout << v;
        }
    }
}

void print_board(const board_t &board) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            std::cout << "+-------+-------+-------+" << std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                std::cout << "| ";
            }
            std::cout << (char) (board[i][j] == 0 ? ' ' : board[i][j] + '0') << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+-------+-------+-------+" << std::endl;
}

board_t generate_final_board() {
    // TODO: ������������
    return {};
}

board_t solve_board(const board_t &board) {
    // TODO: �������
    return {};
}

board_t generate_game_board(int mode, std::pair<int, int> range, bool unique) {
    // TODO: ������Ϸ
    return {};
}
