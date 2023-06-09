/*
# Copyright (c) 2023 Yuanyi Xu. All rights reserved.
*/

#include <iostream>
#include <regex>
#include "./cxxopts.hpp"
#include "./core.hpp"

int main(int argc, char *argv[]) {
    cxxopts::Options options("Sudoku", "Sudoku solver & generator");
    options.add_options()
            ("c,count", "需要的数独终盘数量（1-1000000）", cxxopts::value<int>())
            ("s,solve", "需要解的数独棋盘文件路径",
             cxxopts::value<std::string>())
            ("n,number", "需要的游戏数量（1-10000）", cxxopts::value<int>())
            ("m,mode", "生成的游戏难度（1-3）",
             cxxopts::value<int>()->default_value("1"))
            ("r,range", "生成游戏中挖空的数量范围（20~55）",
             cxxopts::value<std::string>()->default_value("20~55"))
            ("u,unique", "生成游戏的解唯一",
             cxxopts::value<bool>()->default_value("false"))
            ("h,help", "显示帮助信息");
    try {
        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        // 判断是否为生成终盘
        if (result.count("count")) {
            // 参数获取 & 校验
            int count = result["count"].as<int>();
            if (!(count >= 1 && count <= 1000000)) {
                std::cout << "需要的数独终盘数量应在 1 ~ 1000000 之间"
                          << std::endl;
                return 1;
            }

            std::cout << "生成终盘" << std::endl;
            std::cout << "需要的数独终盘数量：" << count << std::endl;

            std::vector<board_t> boards = generate_final_boards(count);
            size_t i = 1;
            for (const board_t &board : boards) {
                // 打印终局
                std::cout << "生成第 " << i++ << " 个数独终盘：" << std::endl;
                print_board(board);
            }
            write_boards("final.txt", boards);
            return 0;
        }
        // 判断是否为求解数独
        if (result.count("solve")) {
            std::string filename = result["solve"].as<std::string>();

            std::cout << "求解数独" << std::endl;
            std::cout << "数独文件：" << filename << std::endl;

            std::vector<board_t> boards = read_boards(filename);
            for (board_t &board : boards) {
                board = solve_board(board);
                std::cout << "求解结果：" << std::endl;
                print_board(board);
            }
            write_boards("sudoku.txt", boards);
            return 0;
        }

        // 判断是否为生成游戏
        if (result.count("number")) {
            int number = result["number"].as<int>();
            int mode = result["mode"].as<int>();
            std::string range_str = result["range"].as<std::string>();
            bool unique = result["unique"].as<bool>();

            if (!(number >= 1 && number <= 10000)) {
                std::cout << "需要的游戏数量应在 1 ~ 10000 之间" << std::endl;
                return 1;
            }
            if (!(mode >= 1 && mode <= 3)) {
                std::cout << "游戏难度应在 1 ~ 3 之间" << std::endl;
                return 1;
            }
            std::smatch m;
            if (!std::regex_match(range_str, m,
                                  std::regex(R"(^(\d+)~(\d+)$)"))) {
                std::cout << "挖空数量范围格式错误，应为：20~55" << std::endl;
                return 1;
            }
            std::pair range = {std::stoi(m[1]), std::stoi(m[2])};
            if (!(range.first >= 20 && range.second <= 55 &&
                  range.first <= range.second)) {
                std::cout << "挖空数量范围应在 20 ~ 55 之间" << std::endl;
                return 1;
            }

            std::cout << "生成游戏" << std::endl;
            std::cout << "需要的游戏数量：" << number << std::endl;
            std::cout << "游戏难度：" << mode << std::endl;
            std::cout << "挖空数量范围：" << range.first << " ~ " << range.second
                      << std::endl;
            std::cout << "解唯一：" << (unique ? "是" : "否") << std::endl;

            std::vector<board_t> boards =
                    generate_game_boards(number, mode, range, unique);
            size_t i = 1;
            for (const board_t &board : boards) {
                // 打印游戏
                std::cout << "生成第 " << i++ << " 个游戏：" << std::endl;
                print_board(board);
            }
            write_boards("game.txt", boards);
            return 0;
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    std::cout << "参数格式不正确" << std::endl;
    return 1;
}
