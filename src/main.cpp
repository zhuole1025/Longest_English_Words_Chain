#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

using namespace std;

bool is_valid_char(char c) {
    // 判断一个字符是否是英文字符
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


int main(int argc, char* argv[]) {
    // 检查命令行参数是否正确
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // TODO 参数兼容异常处理

    string filename = argv[1];
    // filename = "test.txt";
    ifstream file(filename);
    // 检查文件是否成功打开
    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return 1;
    }

    // vector<const char*> wordList;
    vector<const char*> wordList;
    string line, word;

    while (getline(file, line)) {
        for (int i = 0; i < line.length(); ++i) {
            if (is_valid_char(line[i])) {
                word += (line[i] | 0x20); // 换成小写字母
            }
            else if (!word.empty()) {
                wordList.push_back(word.c_str());
                //cout << word.c_str() << " while wordList size: " << wordList.size() << endl;
                word = "";
            }
        }

        if (!word.empty()) {
            wordList.push_back(word.c_str());
        }
    }
    // finish preprocessing words, words are stored in wordList!
    


}
