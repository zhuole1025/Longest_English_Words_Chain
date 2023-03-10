#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "core.h"

using namespace std;

bool is_valid_char(char c) {
    // 判断一个字符是否是英文字符
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int deal_with_arg(int argc, char* argv[], int& func_type, char& head, char& tail, char& jinz, bool& loop, string& filename) {
    // 检查命令行参数是否正确
    if (argc <= 2) {
        cout << "Usage: " << argv[0] << "[-option]+ <filename>" << std::endl;
        return 1;
    }
    int ret = 0;

    int all_chains = 0;
    int max_word = 0;
    int max_char = 0;

    int headc = 0;
    int tailc = 0;
    int forbidden = 0;
    int loopc = 0;

    head = 0;
    tail = 0;
    jinz = 0;
    filename = "";
    loop = false;
    int i = 1;
    while (i < argc) {
        if (strlen(argv[i]) == 2 && argv[i][0] == '-') {
            switch (argv[i][1])
            {
            case 'n':
                all_chains = 1;
                break;
            case 'w':
                max_word = 1;
                break;
            case 'c':
                max_char = 1;
                break;
            // head && tail : allow upper letter. not allow muti-arg 
            case 'h':
                if (strlen(argv[i + 1]) != 1 || !is_valid_char(argv[i + 1][0])) {
                    cerr << "Usage -h needs a letter following" << endl;
                    ret = -1;
                }
                head = argv[i + 1][0] | 0x20;
                headc++;
                ++i;
                break;
            case 't':
                if (strlen(argv[i + 1]) != 1 || !is_valid_char(argv[i + 1][0])) {
                    cerr << "Usage -t needs a letter following" << endl;
                    ret = -1;
                }
                tail = argv[i + 1][0] | 0x20;
                ++i;
                break;
            case 'j':
                if (strlen(argv[i + 1]) != 1 || !is_valid_char(argv[i + 1][0])) {
                    cerr << "Usage -j needs a letter following" << endl;
                    ret = -1;
                }
                jinz = argv[i + 1][0] | 0x20;
                ++forbidden;
                break;
            case 'r':
                loopc++;
                loop = true;
                break;
            default:
                cerr << "arg not in the option" << endl;
                ret = -1;
                break;
            }
            
        }
        else {
            if (!filename.empty()) {
                cerr << "process one file at a time!" << endl;
                ret = -1;
            }
            else {
                filename = argv[i];
            }
        }
        ++i;
    }
    if (ret != -1) {
        // 功能型参数互相冲突
        if (all_chains + max_word + max_char >= 2) {
            cerr << "-w, -n, -c should not be used together" << endl;
            ret = -1;
        }
        else if (all_chains + max_word + max_char == 0) {
            cerr << "you should use one of -w, -n, -c" << endl;
        }
        // 附加型参数除了 -r 以外不允许出现多次
        else if (headc > 1 || tailc > 1 || forbidden > 1) {
            cerr << "-h, -t, -j should be used no more than twice!" << endl;
            ret = -1;
        }
    }
    func_type = all_chains ? 1 : max_word ? 2 : 3;

    return ret;
}

vector<const char*> extract_words(ifstream& file) {
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
    return wordList;
}

int main(int argc, char* argv[]) {
    
    int func_type;
    char head;
    char tail;
    char jinz;
    bool loop;
    string filename;

    // 参数兼容异常处理
    int ret = deal_with_arg(argc, argv, func_type, head, tail, jinz, loop, filename);
    if (ret == -1) {
        return ret;
    }

    string outfile = func_type == 1 ? "": "solution.txt";
    // filename = "test.txt";
    ifstream file(filename);
    // 检查文件是否成功打开
    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return -1;
    }

    // extract legal words into wordList
    vector<const char*> wordList = extract_words(file);

    vector<char*> results(32768, 0);

    int func_ret = 0;// TODO main func call
    switch (func_type)
    {
    case 1:
        func_ret = gen_chains_all(wordList.data(), (int)wordList.size(), results.data());
        break;
    case 2:
        func_ret = gen_chain_word(wordList.data(), (int)wordList.size(), results.data(), head, tail, jinz, loop);
        break;
    case 3:
        func_ret = gen_chain_char(wordList.data(), (int)wordList.size(), results.data(), head, tail, jinz, loop);
        break;
    default:
        static_assert("func_ret set wrong?!");
        break;
    }

    if (results.size() > 20000) {
        cerr << "results.size() > 20000!" << '\n';
        return -1;
    }

    ofstream output;
    ostream& out = outfile.empty() ? cout : output; // use quote?

    // output
    if (outfile.empty()) {
        // -n
        out << ret << '\n';
    }
    else {
        ofstream output;
        output.open(outfile, ios::trunc | ios::out);
        if (!output.is_open()) {
            cerr << outfile + " cannot open!" << endl;
            return -1;
        }

    }

    // TODO output results
    for (int i{ 0 }; i < func_ret; ++i) {
        out << results[i] << '\n';
    }

    if (!outfile.empty()) {
        output.close();
    }

    return 0;
}
