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
                Assert::AreEqual(expected_info, e.what());
            }
            Assert::Fail;
        }

        // correction test of deal_with_arg()
        TEST_METHOD(test1_deal_with_arg) {
            vector<char*> argv = { exe_file, "-n", "test" };
            test_args(2, argv.data(), 1, 0, 0, 0, false, "test.txt");

            argv = { exe_file,"-W", "-h", "a", "test" };
            test_args(4, argv.data(), 2, 'a', 0, 0, false, "test.txt");
            argv = { exe_file,"-c", "-t", "B", "test" };
            test_args(4, argv.data(), 3, '\0', 'b', 0, false, "test.txt");
            argv = { exe_file,"-w", "-j", "c", "test" };
            test_args(4, argv.data(), 2, '\0', '\0', 'c', false, "test.txt");
            argv = { "-c", "-r", "test" };
            test_args(3, argv.data(), 3, '\0', '\0', 0, true, "test.txt");
            argv = { exe_file, "-W", "-R", "-h", "D", "test" };
            test_args(5, argv.data(), 2, 'd', '\0', 0, true, "test.txt");
            argv = { exe_file, "-w", "-r", "-J", "e", "test" };
            test_args(5, argv.data(), 2, '\0', '\0', 'e', true, "test.txt");
            argv = { exe_file, "-C", "-R", "-t", "F", "test" };
            test_args(5, argv.data(), 3, '\0', 'f', 0, true, "test.txt");
            argv = { exe_file, "-W", "-H", "g", "-t", "h", "test" };
            test_args(6, argv.data(), 2, 'g', 'h', 0, false, "test.txt");
            argv = { exe_file, "-w", "-r", "-j", "I","-t", "J", "test" };
            test_args(7, argv.data(), 2, '\0', 'j', 'i', false, "test.txt");
            argv = { exe_file, "-C", "-r", "-h", "r", "-j", "k", "test" };
            test_args(7, argv.data(), 3, 'r', 'k', 0, true, "test.txt");
            argv = { exe_file, "-w", "-t", "a", "-h", "b", "-j", "b", "-r", "test" };
            test_args(9, argv.data(), 2, 'b', 'a', 'b', true, "test.txt");

            // unusual but considered legal:
            argv = { exe_file, "-w", "-r", "-r", "test" };
            test_args(4, argv.data(), 2, 0, 0, 0, true, "test.txt");
            argv = { exe_file, "-n", "-N", "test" };
            test_args(3, argv.data(), 1, 0, 0, 0, false, "test.txt");
            argv = { exe_file, "-c", "-r", "test", "-t", "a" };
            test_args(5, argv.data(), 3, 0, 'a', 0, true, "test.txt");
        }

        TEST_METHOD(test_arg_exc1) {
            vector<char*> argv = { exe_file };

            string expected_info = "Usage: ";
            expected_info += exe_file;
            expected_info += "[-option]+ <filename>";
            test_arg_exception(1, argv.data(), expected_info.c_str());
        }

        TEST_METHOD(test_arg_exc2) {
            vector<char*> argv = { exe_file , "-w", "-h", "test"};
            char* info = "Usage -h needs a letter following";
            test_arg_exception(4, argv.data(), info);

            argv = { exe_file , "-w","-t", "-r","test" };
            info = "Usage -t needs a letter following";
            test_arg_exception(5, argv.data(), info);

            argv = { exe_file , "-w", "-j", "test" };
            info = "Usage -j needs a letter following";
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc3) {
            vector<char*> argv = { exe_file , "-c", "-m", "test" };
            char* info = "arg not in the option";
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc4) {
            vector<char*> argv = { exe_file , "-w", "test", "-r","test"};
            char* info = "process one file at a time";
            test_arg_exception(5, argv.data(), info);

            argv = { exe_file, "-w", "tets", "test" };
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc5) {
            vector<char*> argv = { exe_file , "-n", "-r", "test" };
            char* info = "we don't support option -n used with other options.";
            test_arg_exception(4, argv.data(), info);

            argv = { exe_file, "-n", "-w", "test"};
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc6) {
            vector<char*> argv = { exe_file , "-w", "-c", "test" };
            char* info = "option -w, -n, -c should not be used together";
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc7) {
            vector<char*> argv = { exe_file , "-r", "-j", "a", "test"};
            char* info = "you should use one of -w, -n, -c";
            test_arg_exception(5, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc8) {
            vector<char*> argv = { exe_file , "-w", "-J", "m", "-j", "m", "test"};
            char* info = "-h, -t, -j should be used no more than twice!";
            test_arg_exception(7, argv.data(), info);

            argv = { exe_file , "-w", "-h", "m", "-h", "m", "test" };
            test_arg_exception(7, argv.data(), info);
            argv = { exe_file , "-w", "-t", "m", "-t", "m", "test" };
            test_arg_exception(7, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc9) {
            vector<char*> argv = { exe_file , "-w", "-t", "t" };
            char* info = "no file given!";
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_arg_exc10) {
            vector<char*> argv = { exe_file , "-w", "-", "test" };
            char* info = "'-', a specific option should be followed.";
            test_arg_exception(4, argv.data(), info);

            argv = { exe_file , "-w", "-jh", "test" };
            test_arg_exception(4, argv.data(), info);
        }

        TEST_METHOD(test_openfile_exception) {
            try
            {
                open_file("tests.txt");
            }
            catch (const std::exception& e)
            {
                Assert::AreEqual(0, strcmp("File<tests.txt> does not exists!", e.what()));
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