#include <vector>
#include <string>
#include <algorithm>
#include "pch.h"
#include "CppUnitTest.h"
#include "../src/core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

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
            vector<char*> results(32768, 0);
            int expected_ans = 6;
            vector<string> expected_words = { "abc cde", "cde efg", "efg ghi", "abc cde efg", "cde efg ghi", "abc cde efg ghi" };
            int ans = gen_chains_all(words, len, results.data());
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
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
            vector<char*> results(32768, 0);
            int expected_ans = 5;
            vector<string> expected_words = { "head delay", "delay yale", "yale element", "head delay yale", "delay yale element", "head delay yale element", "key yale", "key yale element" };
            int ans = gen_chains_all(words, len, results.data());
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
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
            vector<char*> results(32768, 0);
            int expected_ans = 1;
            vector<string> expected_words = { "abcd defg" };
            int ans = gen_chains_all(words, len, results.data());
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
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
            const char* words[] = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", "ij", "jk", "kl", "lm", "ff", "bb", "uv"};
            int len = 15;
            vector<char*> results(32768, 0);
            
            // -w
            int expected_ans = 12;
            vector<string> expected_words = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", "ij", "jk", "kl", "lm"};
            int ans = gen_chain_word(words, len, results.data(), 0, 0, -1, false);
            Assert::AreEqual(ans, expected_ans);
            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], results[i]);
            }

            // -w -h e
            results.clear();
            int expected_ans = 8;
            vector<string> expected_words = {"ef", "fg", "gh", "hi", "ij", "jk", "kl", "lm"};
            int ans = gen_chain_word(words, len, results.data(), 'e' - 'a', 0, -1, false);
            Assert::AreEqual(ans, expected_ans);
            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], results[i]);
            }

            // -w -t k
            results.clear();
            int expected_ans = 10;
            vector<string> expected_words = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", "ij", "jk"};
            int ans = gen_chain_word(words, len, results.data(), 0, 'k' - 'a', -1, false);
            Assert::AreEqual(ans, expected_ans);
            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], results[i]);
            }

            // -w -h e -t k
            results.clear();
            int expected_ans = 6;
            vector<string> expected_words = {"ef", "fg", "gh", "hi", "ij", "jk"};
            int ans = gen_chain_word(words, len, results.data(), 0, 'k' - 'a', -1, false);
            Assert::AreEqual(ans, expected_ans);
            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], results[i]);
            }

            // -w -h b -t v
            results.clear();
            int expected_ans = 0;
            int ans = gen_chain_word(words, len, results.data(), 'b' - 'a', 'v' - 'a', -1, false);
            Assert::AreEqual(ans, expected_ans);
        }

        // unit test for gen_chain_word function in core.h case 2
        TEST_METHOD(gen_chain_word_test2)
        {
            const char* words[] = {"algebra", "apple", "zoo", "elephant", "under", "fox", "panz", "medium", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism"};
            int len = 13;
            vector<char*> results(32768, 0);
            
            // -w
            int expected_ans = 4;
            vector<string> expected_words = {"algebra", "apple", "elephant", "trick"};
            int ans = gen_chain_word(words, len, results.data(), 0, 0, -1, false);
            Assert::AreEqual(ans, expected_ans);
            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], results[i]);
            }

            // -w -h e
            results.clear();
            int expected_ans = 3;
            vector<string> expected_words = {"pseudopseudohypoparathyroidism", "medium", "moon"};
            int ans = gen_chain_word(words, len, results.data(), 'p' - 'a', 0, -1, false);
            Assert::AreEqual(ans, expected_ans);
            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], results[i]);
            }

            // -w -t m
            results.clear();
            int expected_ans = 2;
            vector<string> expected_words = {"pseudopseudohypoparathyroidism", "medium"};
            int ans = gen_chain_word(words, len, results.data(), 0, 'm' - 'a', -1, false);
            Assert::AreEqual(ans, expected_ans);
            for (int i = 0; i < len; i++) {
                Assert::AreEqual(pred_words[i], results[i]);
            }
        }
    };

}

