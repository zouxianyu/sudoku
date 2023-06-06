#include <iostream>
#include <regex>
#include "cxxopts.hpp"
#include "core.hpp"

int main(int argc, char *argv[]) {
    cxxopts::Options options("Sudoku", "Sudoku solver & generator");
    options.add_options()
            ("c,count", "��Ҫ����������������1-1000000��", cxxopts::value<int>())
            ("s,solve", "��Ҫ������������ļ�·��",
             cxxopts::value<std::string>())
            ("n,number", "��Ҫ����Ϸ������1-10000��", cxxopts::value<int>())
            ("m,mode", "���ɵ���Ϸ�Ѷȣ�1-3��",
             cxxopts::value<int>()->default_value("1"))
            ("r,range", "������Ϸ���ڿյ�������Χ��20~55��",
             cxxopts::value<std::string>()->default_value("20~55"))
            ("u,unique", "������Ϸ�Ľ�Ψһ",
             cxxopts::value<bool>()->default_value("false"))
            ("h,help", "��ʾ������Ϣ");
    try {

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        // �ж��Ƿ�Ϊ��������
        if (result.count("count")) {

            // ������ȡ & У��
            int count = result["count"].as<int>();
            if (!(count >= 1 && count <= 1000000)) {
                std::cout << "��Ҫ��������������Ӧ�� 1 ~ 1000000 ֮��"
                          << std::endl;
                return 1;
            }

            std::cout << "��������" << std::endl;
            std::cout << "��Ҫ����������������" << count << std::endl;

            std::vector<board_t> boards = generate_final_boards(count);
            size_t i = 1;
            for (const board_t &board: boards) {
                // ��ӡ�վ�
                std::cout << "���ɵ� " << i++ << " ���������̣�" << std::endl;
                print_board(board);
            }
            write_boards("final.txt", boards);
            return 0;
        }

        // �ж��Ƿ�Ϊ�������
        if (result.count("solve")) {
            std::string filename = result["solve"].as<std::string>();

            std::cout << "�������" << std::endl;
            std::cout << "�����ļ���" << filename << std::endl;

            std::vector<board_t> boards = read_boards(filename);
            for (board_t &board: boards) {
                board = solve_board(board);
                std::cout << "�������" << std::endl;
                print_board(board);
            }
            write_boards("sudoku.txt", boards);
            return 0;
        }

        // �ж��Ƿ�Ϊ������Ϸ
        if (result.count("number")) {
            int number = result["number"].as<int>();
            int mode = result["mode"].as<int>();
            std::string range_str = result["range"].as<std::string>();
            bool unique = result["unique"].as<bool>();

            if (!(number >= 1 && number <= 10000)) {
                std::cout << "��Ҫ����Ϸ����Ӧ�� 1 ~ 10000 ֮��" << std::endl;
                return 1;
            }
            if (!(mode >= 1 && mode <= 3)) {
                std::cout << "��Ϸ�Ѷ�Ӧ�� 1 ~ 3 ֮��" << std::endl;
                return 1;
            }
            std::smatch m;
            if (!std::regex_match(range_str, m,
                                  std::regex(R"(^(\d+)~(\d+)$)"))) {
                std::cout << "�ڿ�������Χ��ʽ����ӦΪ��20~55" << std::endl;
                return 1;
            }
            std::pair range = {std::stoi(m[1]), std::stoi(m[2])};
            if (!(range.first >= 20 && range.second <= 55 &&
                  range.first <= range.second)) {
                std::cout << "�ڿ�������ΧӦ�� 20 ~ 55 ֮��" << std::endl;
                return 1;
            }

            std::cout << "������Ϸ" << std::endl;
            std::cout << "��Ҫ����Ϸ������" << number << std::endl;
            std::cout << "��Ϸ�Ѷȣ�" << mode << std::endl;
            std::cout << "�ڿ�������Χ��" << range.first << " ~ " << range.second
                      << std::endl;
            std::cout << "��Ψһ��" << (unique ? "��" : "��") << std::endl;

            std::vector<board_t> boards =
                    generate_game_boards(number, mode, range, unique);
            size_t i = 1;
            for (const board_t &board: boards) {
                // ��ӡ��Ϸ
                std::cout << "���ɵ� " << i++ << " ����Ϸ��" << std::endl;
                print_board(board);
            }
            write_boards("game.txt", boards);
            return 0;
        }

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << "������ʽ����ȷ" << std::endl;
    return 1;

}
