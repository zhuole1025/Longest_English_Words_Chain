#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "pch.h"
#include "CppUnitTest.h"
#include "../src/main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace maintest
{

    TEST_CLASS(maintest)
    {
    public:
        char* exe_file = "Longest_English_Words_Chain";

        TEST_METHOD(test_is_valid_char) {
            const char chars[] = { 'a', '-', ' ', 'Z', '\0', '_', '\t' };
            const bool expected_ans[] = { true, false, false, true, false, false, false };
            auto len = strlen(chars);
            cout << len << endl;
            for (int i = 0; i < len; ++i) {
                Assert::AreEqual(expected_ans[i], is_valid_char(chars[i]));
            }
        }

        void test_args(int argc, char* argv[], int expected_funcType, char expected_head, char expected_tail, char expected_skip, bool expected_loop, string expected_filename) {
            int func_type;
            char head, tail, skip;
            bool loop;
            string filename;
            deal_with_arg(argc, argv, func_type, head, tail, skip, loop, filename);
            Assert::AreEqual(expected_funcType, func_type);
            Assert::AreEqual(expected_head, head);
            Assert::AreEqual(expected_tail, tail);
            Assert::AreEqual(expected_skip, skip);
            Assert::AreEqual(expected_loop, loop);
            Assert::AreEqual(expected_filename, filename);
        }

        void test_arg_exception(int argc, char* argv[], const char * expected_info) {
            try
            {
                test_args(argc, argv, 0, 0, 0, 0, false, "");
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(0,strcmp(expected_info, e.what()));
            }
            Assert::Fail;
        }

        // correction test of deal_with_arg()
        TEST_METHOD(test1_deal_with_arg) {
            vector<char*> argv = { "Wordlist.exe", "-n", "test" };
            test_args(3, argv.data(), 1, 0, 0, 0, false, "test.txt");

            argv = { "Wordlist.exe","-W", "-h", "a", "test" };
            test_args(argv.size(), argv.data(), 2, 'a', 0, 0, false, "test.txt");
            argv = { "Wordlist.exe","-c", "-t", "B", "test" };
            test_args(argv.size(), argv.data(), 3, '\0', 'b', 0, false, "test.txt");
            argv = { "Wordlist.exe","-w", "-j", "c", "test" };
            test_args(argv.size(), argv.data(), 2, '\0', '\0', 'c', false, "test.txt");
            argv = { "Wordlist.exe","-c", "-r", "test" };
            test_args(argv.size(), argv.data(), 3, '\0', '\0', 0, true, "test.txt");
            argv = { "Wordlist.exe", "-W", "-R", "-h", "D", "test" };
            test_args(argv.size(), argv.data(), 2, 'd', '\0', 0, true, "test.txt");
            argv = { "Wordlist.exe", "-w", "-r", "-J", "e", "test" };
            test_args(argv.size(), argv.data(), 2, '\0', '\0', 'e', true, "test.txt");
            argv = { "Wordlist.exe", "-C", "-R", "-t", "F", "test" };
            test_args(argv.size(), argv.data(), 3, '\0', 'f', 0, true, "test.txt");
            argv = { "Wordlist.exe", "-W", "-H", "g", "-t", "h", "test" };
            test_args(argv.size(), argv.data(), 2, 'g', 'h', 0, false, "test.txt");
            argv = { "Wordlist.exe", "-w", "-r", "-j", "I","-t", "J", "test" };
            test_args(argv.size(), argv.data(), 2, '\0', 'j', 'i', true, "test.txt");
            argv = { "Wordlist.exe", "-C", "-r", "-h", "r", "-j", "k", "test" };
            test_args(argv.size(), argv.data(), 3, 'r', '\0', 'k', true, "test.txt");
            argv = { "Wordlist.exe", "-w", "-t", "a", "-h", "b", "-j", "c", "-r", "test" };
            test_args(argv.size(), argv.data(), 2, 'b', 'a', 'c', true, "test.txt");

            // unusual but considered legal:
            argv = { "Wordlist.exe", "-w", "-r", "-r", "test" };
            test_args(argv.size(), argv.data(), 2, 0, 0, 0, true, "test.txt");
            argv = { "Wordlist.exe", "-n", "-N", "test" };
            test_args(argv.size(), argv.data(), 1, 0, 0, 0, false, "test.txt");
            argv = { "Wordlist.exe", "-c", "-r", "test", "-t", "a" };
            test_args(argv.size(), argv.data(), 3, 0, 'a', 0, true, "test.txt");
        }

        TEST_METHOD(test_arg_exc1) {
            vector<char*> argv = { "Wordlist.exe" };

            string expected_info = "Usage: ";
            expected_info += "Wordlist.exe";
            expected_info += "[-option]+ <filename>";
            test_arg_exception(argv.size(), argv.data(), expected_info.c_str());
        }

        TEST_METHOD(test_arg_exc2) {
            vector<char*> argv = { "Wordlist.exe" , "-w", "-h", "test"};
            char* info = "Usage -h needs a letter following";
            test_arg_exception(4, argv.data(), info);

            argv = { "Wordlist.exe" , "-w","-t", "-r","test" };
            info = "Usage -t needs a letter following";
            test_arg_exception(5, argv.data(), info);

            argv = { "Wordlist.exe" , "-w", "-j", "test" };
            info = "Usage -j needs a letter following";
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc3) {
            vector<char*> argv = { "Wordlist.exe" , "-c", "-m", "test" };
            char* info = "arg not in the option";
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc4) {
            vector<char*> argv = { "Wordlist.exe" , "-w", "test", "-r","test"};
            char* info = "process one file at a time!";
            test_arg_exception(5, argv.data(), info);

            argv = { "Wordlist.exe", "-w", "tets", "test" };
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc5) {
            vector<char*> argv = { "Wordlist.exe" , "-n", "-r", "test" };
            char* info = "we don't support option -n used with other options.";
            test_arg_exception(4, argv.data(), info);

            argv = { "Wordlist.exe", "-n", "-w", "test"};
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc6) {
            vector<char*> argv = { "Wordlist.exe" , "-w", "-c", "test" };
            char* info = "option -w, -n, -c should not be used together";
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc7) {
            vector<char*> argv = { "Wordlist.exe" , "-r", "-j", "a", "test"};
            char* info = "you should use one of -w, -n, -c";
            test_arg_exception(5, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc8) {
            vector<char*> argv = { "Wordlist.exe" , "-w", "-J", "m", "-j", "m", "test"};
            char* info = "-h, -t, -j should be used no more than twice!";
            test_arg_exception(7, argv.data(), info);

            argv = { "Wordlist.exe" , "-w", "-h", "m", "-h", "m", "test" };
            test_arg_exception(7, argv.data(), info);
            argv = { "Wordlist.exe" , "-w", "-t", "m", "-t", "m", "test" };
            test_arg_exception(7, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc9) {
            vector<char*> argv = { "Wordlist.exe" , "-w", "-t", "t" };
            char* info = "no file given!";
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc10) {
            vector<char*> argv = { "Wordlist.exe" , "-w", "-", "test" };
            char* info = "'-', a specific option should be followed.";
            test_arg_exception(4, argv.data(), info);

            argv = { "Wordlist.exe" , "-w", "-jh", "test" };
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc11) {
            vector<char*> argv = { "Wordlist.exe" , "-w", "-h", "a", "-j", "a", "test"};
            char* info = "the letters of -h and -j shouldn't be the same.";
            test_arg_exception(7, argv.data(), info);
        }

        TEST_METHOD(test_openfile_exception) {
            try
            {
                open_file("tests.txt");
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(0, strcmp("File<tests.txt> does not exist!", e.what()));
                return;
            }
            Assert::Fail;
        }

        TEST_METHOD(test_openfile_exception2) {
            ofstream file_open("../test.txt");
            try
            {
                open_file("../test.txt");
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(0, strcmp("Fail to open file<../test.txt>", e.what()));
                return;
            }
            file_open.close();
            Assert::Fail;
        }

    };
}