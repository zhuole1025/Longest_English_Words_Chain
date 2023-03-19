#include "main.h"
#include "core.h"
constexpr auto DEBUG = 0;
constexpr auto INFO = 0;

using namespace std;

bool is_valid_char(char c) {
    
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int deal_with_arg(int argc, char* argv[], int& func_type, char& head, char& tail, char& jinz, bool& loop, string& filename) {
    head = 0;
    tail = 0;
    jinz = 0;
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
        str = "Usage: " + string{argv[0]};
        str += "[-option]+ <filename>";
        goto error;
    }


    while (i < argc) {
        if (strlen(argv[i]) == 2 && argv[i][0] == '-') {
            switch (argv[i][1] | 0x20)
            {
            case 'n':
                all_chains = 1;
                for (int j = i + 1; j < argc; ++j) {
                    if (strlen(argv[j]) == 2 && argv[j][0] == '-' && (argv[j][1] | 0x20) != 'n') {
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
                head = argv[i + 1][0] | 0x20;
                headc++;
                ++i;
                break;
            case 't':
                if (strlen(argv[i + 1]) != 1 || !is_valid_char(argv[i + 1][0])) {
                    str = "Usage -t needs a letter following";
                    goto error;
                }
                tail = argv[i + 1][0] | 0x20;
                ++tailc;
                ++i;
                break;
            case 'j':
                if (strlen(argv[i + 1]) != 1 || !is_valid_char(argv[i + 1][0])) {
                    str = "Usage -j needs a letter following";
                    goto error;
                }
                jinz = argv[i + 1][0] | 0x20;
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
        else if (strlen(argv[i]) != 2 && argv[i][0] == '-') {
            str = "'-', a specific option should be followed.";
            goto error;
        }
        else {
            if (!filename.empty()) {
                str = "process one file at a time!"; 
                goto error;
            }

            filename = argv[i];
            //filename += ".txt";
        }
        ++i;
    }
    if (filename.empty()) {
        str = "no file given!";
        goto error;
    }

    if (all_chains + max_word + max_char == 0) {
        str = "you should use one of -w, -n, -c"; goto error;
    }
    else if (all_chains + max_word + max_char >= 2) {
        str = "option -w, -n, -c should not be used together"; goto error;
    }
    else if (all_chains == 1 && headc + tailc + forbidden + loopc != 0) {
        str = "we don't support option -n used with other options."; goto error;
    }
    else if (headc > 1 || tailc > 1 || forbidden > 1) {
        str = "-h, -t, -j should be used no more than twice!"; goto error;
    }
    else if (headc == 1 && forbidden == 1 && head == jinz) {
        str = "the letters of -h and -j shouldn't be the same."; goto error;
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
        word.clear();
        for (int i = 0; i < line.length(); ++i) {
            if (is_valid_char(line[i])) {
                word += (line[i] | 0x20); 
            }
            else if (!word.empty()) {
                auto size = strlen(word.c_str()) + 1;
                char* tmp = new char[size];
                strcpy_s(tmp, size, word.c_str());
                wordList.push_back(tmp);
                //cout << word.c_str() << " while wordList size: " << wordList.size() << endl;
                word.clear();
            }
        }

        if (!word.empty()) {
            auto size = strlen(word.c_str()) + 1;
            char* tmp = new char[size];
            strcpy_s(tmp, size, word.c_str());
            wordList.push_back(tmp);
        }
    }
    if (wordList.empty()) {
        throw runtime_error("There is no word in your input!");
    }
    return wordList;
}

void free_memory(vector<char*> vecPtr) {
    vector<char*>::iterator it = vecPtr.begin();
    for (; it != vecPtr.end(); )
    {
        delete[] * it;
        it = vecPtr.erase(it);
    }
}

int main(int argc, char* argv[]) {
    
    int func_type;
    char head;
    char tail;
    char jinz;
    bool loop;
    string filename;

    if (INFO) cout << "processing args-------" << '\n';
    if (DEBUG) {
        func_type = 3;  // 1-n,2-w,3-c;
        head = 0;
        tail = 0;
        jinz = -1;
        loop = false;
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
    if (INFO) {
        cout << (func_type == 1 ? "gen all chains" : func_type == 2 ? "gen word chain" : "gen char chain") 
            << " , head=" << (char)head << ", tail=" << (char)tail << ", skip=" << (int)jinz << ", enable_loop=" << loop << '\n';
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
    if (INFO) cout << "-------- file opened.\t extract words----" << '\n';

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
    if (INFO) {
        for (int i = 0; i < wordList.size(); ++i) {
            cout << wordList[i] << ' ';
        }
        cout << "\n-------finish extracting words.\t gen chains----" << '\n';
    }

    vector<char*> results(32768, 0);

    int func_ret = 0;// TODO main func call
    try
    {
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
    }
    catch (const std::logic_error& e)
    {
        cerr << e.what() << std::endl;
        return -1;
    }

    if (func_ret == -1) {
        cerr << "Error: There is a circle in the graph." << '\n';
    }
    else if (func_ret > 20000) {
        cerr << "Error: Too many results." << '\n';
    }
    
    if (INFO) cout << "-------finish generating chains" << '\n';


    ofstream output;
    string outfile = "solution.txt";
    ostream& out = outfile.empty() ? cout : output; // use quote?

    if (INFO)   cout << "start to output" << "\nret_val = " << func_ret << ", outfile is empty ? " << outfile.empty() << '\n';

    // output
    if (outfile.empty()) {
        // -n
        out << func_ret << '\n';
    }
    else {
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
    free_memory(results);

    return 0;
}
