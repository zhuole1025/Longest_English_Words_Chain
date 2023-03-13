#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <stdexcept>
#include "core.h"
constexpr auto DEBUG = 1;
constexpr auto INFO = 1;

using namespace std;

bool is_valid_char(char c) {
    
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int deal_with_arg(int argc, char* argv[], int& func_type, char& head, char& tail, char& jinz, bool& loop, string& filename) {
    head = 0;
    tail = 0;
    jinz = -1;
    filename = "";
    loop = false;

    string str = "";
    int ret = 0;
    int all_chains = 0;
    int max_word = 0;
    int max_char = 0;

    int headc = 0;
    int tailc = 0;
    int forbidden = 0;
    int loopc = 0;
    int i = 1;

    if (argc <= 2) {
        str = "Usage: " + *argv[0];
        str += "[-option]+ <filename>";
        goto error;
    }


    while (i < argc) {
        if (strlen(argv[i]) == 2 && argv[i][0] == '-') {
            switch (argv[i][1])
            {
            case 'n':
                all_chains = 1;
                for (int j = i + 1; j < argc; ++j) {
                    if (strlen(argv[i]) == 2 && argv[i][0] == '-' && argv[i][1] != 'n') {
                        str = "we don't support option -n used with other options.";
                        goto error;
                    }
                }
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
                    str = "Usage -h needs a letter following";
                    goto error;
                }
                head = argv[i + 1][0] | 0x20 - 'a';
                headc++;
                ++i;
                break;
            case 't':
                if (strlen(argv[i + 1]) != 1 || !is_valid_char(argv[i + 1][0])) {
                    str = "Usage -t needs a letter following";
                    goto error;
                }
                tail = argv[i + 1][0] | 0x20 - 'a';
                ++tailc;
                ++i;
                break;
            case 'j':
                if (strlen(argv[i + 1]) != 1 || !is_valid_char(argv[i + 1][0])) {
                    str = "Usage -j needs a letter following";
                    goto error;
                }
                jinz = argv[i + 1][0] | 0x20 - 'a';
                ++forbidden;
                ++i;
                break;
            case 'r':
                loopc++;
                loop = true;
                break;
            default:
                str = "arg not in the option";
                goto error;
                break;
            }
            
        }
        else {
            if (!filename.empty()) {
                str = "process one file at a time!"; 
                goto error;
            }

            filename = argv[i];
        }
        ++i;
    }
    if (filename.empty()) {
        str = "no file given!";
        goto error;
    }

    if (all_chains + max_word + max_char >= 2) {
        str = "option -w, -n, -c should not be used together"; goto error;
    }
    else if (all_chains + max_word + max_char == 0) {
        str = "you should use one of -w, -n, -c"; goto error;
    }
    else if (headc > 1 || tailc > 1 || forbidden > 1) {
        str = "-h, -t, -j should be used no more than twice!"; goto error;
    }
    else if (all_chains == 1 && headc + tailc + forbidden != 0) {

    }
    
    func_type = all_chains ? 1 : max_word ? 2 : 3;
    goto end;

error:
    throw invalid_argument(str);
end:
    return ret;
}

ifstream open_file(const string& filename) {
    ifstream file(filename, ios::in);
    if (!file) {
        throw logic_error("File<" + filename + "> does not exist!");
    }else if (!file.is_open()) {
        throw logic_error("Fail to open file<" + filename + ">");
    }
    return file;
}

vector<const char*> extract_words(ifstream& file) {
    vector<const char*> wordList;
    string line, word;

    while (getline(file, line)) {
        for (int i = 0; i < line.length(); ++i) {
            if (is_valid_char(line[i])) {
                word += (line[i] | 0x20); 
            }
            else if (!word.empty()) {
                char* tmp = new char[strlen(word.c_str()) + 1];
                strcpy(tmp, word.c_str());
                wordList.push_back(tmp);
                //cout << word.c_str() << " while wordList size: " << wordList.size() << endl;
                word.clear();
            }
        }

        if (!word.empty()) {
            char* tmp = new char[strlen(word.c_str()) + 1];
            strcpy(tmp, word.c_str());
            wordList.push_back(tmp);
        }
    }
    if (wordList.empty()) {
        throw runtime_error("There is no word in your input!");
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

    if (DEBUG) {
        func_type = 3;  // 1-n,2-w,3-c;
        head = 0;
        tail = 0;
        jinz = -1;
        loop = true;
        filename = "../test.txt";
    }
    else {
        try
        {
            deal_with_arg(argc, argv, func_type, head, tail, jinz, loop, filename);
        }
        catch (const invalid_argument& e)
        {
            cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }


    ifstream file;
    try
    {
        file = open_file(filename);
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }

    // extract legal words into wordList
    vector<const char*> wordList;
    try
    {
        wordList = extract_words(file);
        file.close();
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        file.close();
        return -1;
    }

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
        // static_assert("func_ret set wrong?!");
        break;
    }


    ofstream output;
    string outfile = func_type == 1 ? "" : "solution.txt";
    ostream& out = outfile.empty() ? cout : output; // use quote?

    // output
    if (outfile.empty()) {
        // -n
        out << func_ret << '\n';
    }
    else {
        ofstream output;
        output.open(outfile, ios::trunc | ios::out);
        if (!output.is_open()) {
            cerr << "Error: " + outfile + " cannot open!" << endl;
            return -1;
        }

    }

    // TODO output results
    for (int i = 0; i < func_ret; ++i) {
        out << results[i] << " " << '\n';
    }

    if (!outfile.empty()) {
        output.close();
    }

    return 0;
}
