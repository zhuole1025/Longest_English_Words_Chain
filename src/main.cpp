#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

using namespace std;

bool is_valid_char(char c) {
    // �ж�һ���ַ��Ƿ���Ӣ���ַ�
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


int main(int argc, char* argv[]) {
    // ��������в����Ƿ���ȷ
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // TODO ���������쳣����

    string filename = argv[1];
    // filename = "test.txt";
    ifstream file(filename);
    // ����ļ��Ƿ�ɹ���
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
                word += (line[i] | 0x20); // ����Сд��ĸ
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
