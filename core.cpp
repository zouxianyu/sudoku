#include <fstream>
#include <iostream>
#include <algorithm>
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

void generate_final_board(const int count) {
    int n = count;
    int first_line[9] = {5,1,2,3,4,6,7,8,9};
    int shift[9] = {0,3,6,1,4,7,2,5,8};
    
    int pos1[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,5,3 },{ 4,3,5 },{ 5,4,3 },{ 5,3,4 } };
    int pos2[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,6,7 },{ 8,7,6 } };

    board_t board;
    
    do{
        // �����վ�����
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                board[i][j] = first_line[(j + shift[i]) % 9];
            }
        }

        // ��ӡ�����վ�
        print_board(board);

        // �ɻ����վ��ܹ��ݻ���36���վ�
        // ǰ3�б��ֲ���
        board_t new_board;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 9; j++){
                new_board[i][j] = board[i][j];
            }
        }

        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 6; j++){
                // 4~6�б任, 7~9�б任
                for(int k = 0; k < 3; k++){
                    for(int p = 0; p < 9; p++){
                        new_board[k+3][p] = board[pos1[i][k]][p];
                        new_board[k+6][p] = board[pos2[j][k]][p];
                    }
                }

                // �洢���ļ�
                write_board("final_board.txt", new_board);
                n--;
                if(!n)return;
            }
        }
    }while(std::next_permutation(first_line+1, first_line+9));
}

board_t solve_board(const board_t &board) {
    // TODO: �������
    return {};
}

board_t generate_game_board(int mode, std::pair<int, int> range, bool unique) {
    // TODO: ������Ϸ
    return {};
}
