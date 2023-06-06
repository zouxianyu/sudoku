#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "core.hpp"

int flag = 0;

std::vector<board_t> read_boards(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin) {
        throw std::runtime_error("数独文件不存在");
    }

    std::vector<board_t> boards;

    std::string line;
    while (std::getline(fin, line) && !line.empty()) {
        std::stringstream linein(line);

        board_t board;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char v{};
                linein >> v;
                if (!(v >= '1' && v <= '9' || v == '$')) {
                    throw std::runtime_error("数独文件格式错误");
                }
                if (v == '$') {
                    v = '0';
                }
                board[i][j] = v - '0';
            }
        }
        boards.emplace_back(board);
    }

    return boards;
}

void write_boards(const std::string &filename, const std::vector<board_t> &boards) {
    std::ofstream fout(filename);
    for (const board_t &board: boards) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char v = board[i][j] == 0 ? '$' : board[i][j] + '0';
                fout << v;
            }
        }
        fout << std::endl;
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

std::vector<board_t> generate_final_boards(int count) {
    std::vector<board_t> result;
    int n = count;
    int first_line[9] = {5,1,2,3,4,6,7,8,9};
    int shift[9] = {0,3,6,1,4,7,2,5,8};
    
    int pos1[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,5,3 },{ 4,3,5 },{ 5,4,3 },{ 5,3,4 } };
    int pos2[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,6,7 },{ 8,7,6 } };

    board_t board;
    
    do{
        // 基础终局生成
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                board[i][j] = first_line[(j + shift[i]) % 9];
            }
        }

        // 由基础终局总共演化出36个终局
        // 前3行保持不变
        board_t new_board;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 9; j++){
                new_board[i][j] = board[i][j];
            }
        }

        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 6; j++){
                // 4~6行变换, 7~9行变换
                for(int k = 0; k < 3; k++){
                    for(int p = 0; p < 9; p++){
                        new_board[k+3][p] = board[pos1[i][k]][p];
                        new_board[k+6][p] = board[pos2[j][k]][p];
                    }
                }

                result.emplace_back(new_board);
                n--;
                if(!n)return result;
            }
        }
    }while(std::next_permutation(first_line+1, first_line+9));
    return result;
}

void prune(int i, int j, bool num[10], board_t &res){
    // 排除本行已有的数字
    for(int k = 0; k < 9; k++){
        if(k == j || res[i][k] == 0)continue;
        num[res[i][k]] = 1;
    }

    // 排除本列已有的数字
    for(int k = 0; k < 9; k++){
        if(k == i || res[k][j] == 0)continue;
        num[res[k][j]] = 1;
    }

    // 排除九宫格内已有的数字
    int n, m;
    if(i / 3 == 0)n = 0;
    else if(i / 6 == 0)n = 3;
    else n = 6;

    if(j / 3 == 0)m = 0;
    else if(j / 6 == 0)m = 3;
    else m = 6;

    for(int p = n; p < n + 3; p++){
        for(int q = m; q < m + 3; q++){
            if((p == i && q == j) || res[p][q] == 0)continue;
            num[res[p][q]] = 1;
        }
    }

}

void solve(int i, int j, board_t &res, int solve_num){
    if(j == 9){
        i++;
        j = 0;
    }
    if(i == 9){
        flag++;
        return;
    }

    // 填数
    if(res[i][j] == 0) {
        // 剪枝，判断某个数字是否能填入
        bool num[10] = {false};
        prune(i, j, num, res);

        // 轮流尝试填入1~9，并递归
        for (int k = 1; k < 10; k++) {
            if (num[k])continue;
            res[i][j] = k;
            solve(i, j + 1, res, solve_num);
            if (flag == solve_num) return;
            res[i][j] = 0;
        }
    }
    else{
        solve(i, j + 1, res, solve_num);
    }
}

board_t solve_board(const board_t &board) {
    flag = 0;
    board_t res;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            res[i][j] = board[i][j];
        }
    }
    solve(0, 0, res, 1);
    return res;
}

// 挖空数独终局生成数独
board_t dig(board_t final_board, int req_num){
    // 先在每个3*3中挖2个空
    int st_i = 0, st_j = 0;
    while(st_i != 9){
        int hole[2];
        hole[0] = rand() % 9;
        hole[1] = rand() % 9;
        // 防止重复
        while(hole[0] == hole[1]){
            hole[1] = rand() % 9;
        }
        for(int k = 0; k < 2; k++){
            int i = hole[k] / 3;
            int j = hole[k] % 3;
            final_board[st_i + i][st_j + j] = 0;
        }
        st_j += 3;
        if (st_j == 9){
            st_j = 0;
            st_i += 3;
        }
    }

    // 挖剩下的空
    req_num -= 18;
    while (req_num--)
    {
        int i = rand() % 9;
        int j = rand() % 9;

        if (final_board[i][j] != 0)final_board[i][j] = 0;
        else req_num++;
    }

    return final_board;
}

board_t generate_game_board_impl(const board_t &final_board, int mode, std::pair<int, int> range, bool unique) {
    // 根据难度进一步确认挖空范围
    int req_num = 0;
    if((range.second - range.first + 1) % 3 == 0){
        int gap = (range.second - range.first + 1) / 3;
        req_num = range.first + (mode - 1) * gap;
        req_num += rand() % gap;
    }
    else if((range.second - range.first + 1) % 3 == 1){
        int gap[3] = {(range.second - range.first + 1) / 3,
                      (range.second - range.first + 1) / 3,
                      (range.second - range.first + 1) / 3 + 1};
        req_num = range.first + (mode - 1) * gap[0];
        req_num += rand() % gap[mode - 1];
    }
    else {
        int gap[3] = {(range.second - range.first + 1) / 3 + 1,
                      (range.second - range.first + 1) / 3 + 1,
                      (range.second - range.first + 1) / 3};
        req_num = range.first + (mode - 1) * gap[0];
        req_num += rand() % gap[mode - 1];
    }

    // 根据要求生成唯一解/多解的游戏
    board_t game_board = dig(final_board, req_num);
    if (!unique) return game_board;
    else{
        board_t res;

        // 如果当前游戏的解数大于1，重新生成
        while(1){
            flag = 0;
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    res[i][j] = game_board[i][j];
                }
            }
            solve(0, 0, res, 2);

            // 唯一解，退出
            if(flag == 1)return game_board;

            //非唯一解，重新生成
            game_board = dig(final_board, req_num);
        }
    }
}

std::vector<board_t> generate_game_boards(int count, int mode, std::pair<int, int> range, bool unique) {
    std::vector<board_t> result;
    std::vector<board_t> final_boards = generate_final_boards(count);
    result.reserve(count);
    for (int i = 0; i < count; i++) {
        result.emplace_back(generate_game_board_impl(final_boards[i], mode, range, unique));
    }
    return result;
}
