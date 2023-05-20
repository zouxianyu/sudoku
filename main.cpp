#include <iostream>
#include <regex>
#include "cxxopts.hpp"

int main(int argc, char *argv[]) {
    // -c 需要的数独终盘数量
    // -s 求解的文件
    // -n 需要的游戏数量
    // -m 生成游戏的难度
    // -r 生成游戏中挖空的数量范围
    // -u 生成游戏的解唯一
    cxxopts::Options options("Sudoku", "Sudoku solver & generator");
    options.add_options()
            ("c,count", "Number of sudoku to solve", cxxopts::value<int>())
            ("s,solve", "Sudoku file to solve", cxxopts::value<std::string>())
            ("n,number", "Number of sudoku to generate", cxxopts::value<int>())
            ("m,mode", "Difficulty of sudoku to generate", cxxopts::value<int>())
            ("r,range", "Range of number to dig", cxxopts::value<std::string>())
            ("u,unique", "Unique solution", cxxopts::value<bool>()->default_value("false"))
            ("h,help", "Print usage");
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
                std::cout << "需要的数独终盘数量应在 1 ~ 1000000 之间" << std::endl;
                return 1;
            }

            std::cout << "生成终盘" << std::endl;
            std::cout << "需要的数独终盘数量：" << count << std::endl;
            return 0;
        }

        // 判断是否为求解数独
        if (result.count("solve")) {
            std::string filename = result["solve"].as<std::string>();

            std::cout << "求解数独" << std::endl;
            std::cout << "数独文件：" << filename << std::endl;
            return 0;
        }

        // 判断是否为生成游戏
        if (result.count("number") && result.count("mode") && result.count("range")) {
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
            if (!std::regex_match(range_str, m, std::regex(R"(^(\d+)~(\d+)$)"))) {
                std::cout << "挖空数量范围格式错误，应为：20~55" << std::endl;
                return 1;
            }
            std::pair range = {std::stoi(m[1]), std::stoi(m[2])};
            if (!(range.first >= 20 && range.second <= 55 && range.first <= range.second)) {
                std::cout << "挖空数量范围应在 20 ~ 55 之间" << std::endl;
                return 1;
            }

            std::cout << "生成游戏" << std::endl;
            std::cout << "需要的游戏数量：" << number << std::endl;
            std::cout << "游戏难度：" << mode << std::endl;
            std::cout << "挖空数量范围：" << range.first << " ~ " << range.second << std::endl;
            std::cout << "解唯一：" << (unique ? "是" : "否") << std::endl;
            return 0;
        }

    } catch (std::exception &e) {
        std::cout << "参数格式不正确" << std::endl;
        return 1;
    }

    std::cout << "参数格式不正确" << std::endl;
    return 1;

}
