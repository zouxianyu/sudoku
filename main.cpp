#include <iostream>
#include <regex>
#include "cxxopts.hpp"

int main(int argc, char *argv[]) {
    cxxopts::Options options("Sudoku", "Sudoku solver & generator");
    options.add_options()
            ("c,count", "��Ҫ����������������1-1000000��", cxxopts::value<int>())
            ("s,solve", "��Ҫ������������ļ�·��", cxxopts::value<std::string>())
            ("n,number", "��Ҫ����Ϸ������1-10000��", cxxopts::value<int>())
            ("m,mode", "���ɵ���Ϸ�Ѷȣ�1-3��", cxxopts::value<int>())
            ("r,range", "������Ϸ���ڿյ�������Χ��20~55��", cxxopts::value<std::string>())
            ("u,unique", "������Ϸ�Ľ�Ψһ", cxxopts::value<bool>()->default_value("false"))
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
                std::cout << "��Ҫ��������������Ӧ�� 1 ~ 1000000 ֮��" << std::endl;
                return 1;
            }

            std::cout << "��������" << std::endl;
            std::cout << "��Ҫ����������������" << count << std::endl;
            return 0;
        }

        // �ж��Ƿ�Ϊ�������
        if (result.count("solve")) {
            std::string filename = result["solve"].as<std::string>();

            std::cout << "�������" << std::endl;
            std::cout << "�����ļ���" << filename << std::endl;
            return 0;
        }

        // �ж��Ƿ�Ϊ������Ϸ
        if (result.count("number") && result.count("mode") && result.count("range")) {
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
            if (!std::regex_match(range_str, m, std::regex(R"(^(\d+)~(\d+)$)"))) {
                std::cout << "�ڿ�������Χ��ʽ����ӦΪ��20~55" << std::endl;
                return 1;
            }
            std::pair range = {std::stoi(m[1]), std::stoi(m[2])};
            if (!(range.first >= 20 && range.second <= 55 && range.first <= range.second)) {
                std::cout << "�ڿ�������ΧӦ�� 20 ~ 55 ֮��" << std::endl;
                return 1;
            }

            std::cout << "������Ϸ" << std::endl;
            std::cout << "��Ҫ����Ϸ������" << number << std::endl;
            std::cout << "��Ϸ�Ѷȣ�" << mode << std::endl;
            std::cout << "�ڿ�������Χ��" << range.first << " ~ " << range.second << std::endl;
            std::cout << "��Ψһ��" << (unique ? "��" : "��") << std::endl;
            return 0;
        }

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << "������ʽ����ȷ" << std::endl;
    return 1;

}
