#include <vector>
#include <algorithm>
#include "pch.h"
#include "CppUnitTest.h"
#include "../src/core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest
{
    TEST_CLASS(unittest)
    {
    public:


        // unit test for get_all function in graph.h case 1
        TEST_METHOD(gen_chains_all_test1)
        {
            const char* words[] = { "abc", "cde", "efg", "ghi" };
            int len = 4;
            std::vector<char*> results(32768, 0);
            int expected_ans = 6;
            std::vector<std::string> expected_words = { "abc cde", "cde efg", "efg ghi", "abc cde efg", "cde efg ghi", "abc cde efg ghi" };
            int ans = gen_chains_all(words, len, results.data());
            Assert::AreEqual(ans, expected_ans);
            std::vector<std::string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            sort(pred_words.begin(), pred_words.end());
            sort(expected_words.begin(), expected_words.end());

            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chains_all function in core.h case 2
        TEST_METHOD(gen_chains_all_test2)
        {
            const char* words[] = { "head", "delay", "element", "yale", "key" };
            int len = 8;
            std::vector<char*> results(32768, 0);
            int expected_ans = 5;
            std::vector<std::string> expected_words = { "head delay", "delay yale", "yale element", "head delay yale", "delay yale element", "head delay yale element", "key yale", "key yale element" };
            int ans = gen_chains_all(words, len, results.data());
            Assert::AreEqual(ans, expected_ans);
            std::vector<std::string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            sort(pred_words.begin(), pred_words.end());
            sort(expected_words.begin(), expected_words.end());

            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for get_all function in graph.h case 3
        TEST_METHOD(gen_chains_all_test3)
        {
            const char* words[] = { "ab", "abc", "abcd", "abcde", "defg" };
            int len = 5;
            std::vector<char*> results(32768, 0);
            int expected_ans = 1;
            std::vector<std::string> expected_words = { "abcd defg" };
            int ans = gen_chains_all(words, len, results.data());
            Assert::AreEqual(ans, expected_ans);
            std::vector<std::string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            sort(pred_words.begin(), pred_words.end());
            sort(expected_words.begin(), expected_words.end());

            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_word function in core.h case 1
        TEST_METHOD(gen_chain_word_test1)
        {
            const char* words[] = { "abc", "cde", "efg", "ghi" };
            int len = 4;
            std::vector<char*> results(32768, 0);
            int expected_ans = 3;
            std::vector<std::string> expected_words = { "abc cde efg" };
            int ans = gen_chain_word(words, len, results.data(), 'a', 'g', 'd', false);
            Assert::AreEqual(ans, expected_ans);
            std::vector<std::string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }

            sort(pred_words.begin(), pred_words.end());
            sort(expected_words.begin(), expected_words.end());

            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }
    };

}

