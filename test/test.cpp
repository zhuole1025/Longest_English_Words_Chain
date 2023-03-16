#include "pch.h"
#include "CppUnitTest.h"
#include "../src/core.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
bool cmp(const char* a, const char* b) {
    return strcmp(a, b) < 0;
}
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
            vector<char*> results(500, 0);
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

            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chains_all function in core.h case 2
        TEST_METHOD(gen_chains_all_test2)
        {
            const char* words[] = { "head", "delay", "element", "yale", "key" };
            int len = 5;
            vector<char*> results(500, 0);
            int expected_ans = 8;
            vector<string> expected_words = { "head delay", "delay yale", "yale element", "head delay yale", "delay yale element", "head delay yale element", "key yale", "key yale element" };
            int ans = gen_chains_all(words, len, results.data());
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            sort(pred_words.begin(), pred_words.end());
            sort(expected_words.begin(), expected_words.end());

            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for get_all function in graph.h case 3
        TEST_METHOD(gen_chains_all_test3)
        {
            const char* words[] = { "ab", "abc", "abcd", "abcde", "defg" };
            int len = 5;
            vector<char*> results(500, 0);
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

            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for get_all function in graph.h case 4 for error
        TEST_METHOD(gen_chains_all_test4)
        {
            const char* words[] = { "ab", "bc", "cd", "dea", "defg" };
            int len = 5;
            vector<char*> results(500, 0);
            try {
                int ans = gen_chains_all(words, len, results.data());
            }
            catch (exception& e) {
                Assert::AreEqual(e.what(), "There is a circle in the graph.");
            }
        }

        // unit test for gen_chain_word function in core.h case 1
        TEST_METHOD(gen_chain_word_test1)
        {
            const char* words[] = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", "ij", "jk", "kl", "lm", "ff", "bb", "uv"};
            int len = 15;
            vector<char*> results(500, 0);
            
            // -w
            int expected_ans = 14;
            vector<string> expected_words = {"ab", "bb", "bc", "cd", "de", "ef", "ff", "fg", "gh", "hi", "ij", "jk", "kl", "lm"};
            int ans = gen_chain_word(words, len, results.data(), 0, 0, 0, false);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -h e
            results.clear();
            expected_ans = 9;
            expected_words = {"ef", "ff", "fg", "gh", "hi", "ij", "jk", "kl", "lm"};
            ans = gen_chain_word(words, len, results.data(), 'e', 0, 0, false);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -t k
            results.clear();
            expected_ans = 12;
            expected_words = {"ab", "bb", "bc", "cd", "de", "ef", "ff", "fg", "gh", "hi", "ij", "jk"};
            ans = gen_chain_word(words, len, results.data(), 0, 'k', 0, false);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -h e -t k
            results.clear();
            expected_ans = 7;
            expected_words = {"ef", "ff", "fg", "gh", "hi", "ij", "jk"};
            ans = gen_chain_word(words, len, results.data(), 0, 'k', 0, false);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -h b -t v
            results.clear();
            expected_ans = 0;
            ans = gen_chain_word(words, len, results.data(), 'b', 'v', 0, false);
            Assert::AreEqual(ans, expected_ans);
        }

        // unit test for gen_chain_word function in core.h case 2
        TEST_METHOD(gen_chain_word_test2)
        {
            const char* words[] = {"algebra", "apple", "zoo", "elephant", "under", "fox", "panz", "medium", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism"};
            int len = 13;
            vector<char*> results(500, 0);
            
            // -w
            int expected_ans = 4;
            vector<string> expected_words = {"algebra", "apple", "elephant", "trick"};
            int ans = gen_chain_word(words, len, results.data(), 0, 0, 0, false);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -h p
            results.clear();
            expected_ans = 3;
            expected_words = {"pseudopseudohypoparathyroidism", "medium", "moon"};
            ans = gen_chain_word(words, len, results.data(), 'p', 0, 0, false);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -t m
            results.clear();
            expected_ans = 2;
            expected_words = {"pseudopseudohypoparathyroidism", "medium"};
            ans = gen_chain_word(words, len, results.data(), 0, 'm', 0, false);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_word function in core.h case 3
        TEST_METHOD(gen_chain_word_test3)
        {
            const char* words[] = {"algebra", "apple", "zoo", "elephant", "under", "fox", "panz", "medium", "dog", "moon", "egg", "trick", "knee"};
            int len = 13;
            vector<char*> results(500, 0);
            
            // -w -r
            int expected_ans = 6;
            vector<string> expected_words = {"algebra", "apple", "elephant", "trick", "knee", "egg"};
            int ans = gen_chain_word(words, len, results.data(), 0, 0, 0, true);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -h e -r
            results.clear();
            expected_ans = 4;
            expected_words = {"elephant", "trick", "knee", "egg"};
            ans = gen_chain_word(words, len, results.data(), 'e', 0, 0, true);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -t e -r
            results.clear();
            expected_ans = 5;
            expected_words = {"algebra", "apple", "elephant", "trick", "knee"};
            ans = gen_chain_word(words, len, results.data(), 0, 'e', 0, true);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            Assert::AreEqual(ans, expected_ans);
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_word function in core.h case 4
        TEST_METHOD(gen_chain_word_test4)
        {
            const char* words[] = {"algebra", "apple", "zoo", "elephant", "under", "fox", "panz", "medium", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism"};
            int len = 13;
            vector<char*> results(500, 0);
            
            // -w -j a
            int expected_ans = 3;
            vector<string> expected_words = {"pseudopseudohypoparathyroidism", "medium", "moon"};
            int ans = gen_chain_word(words, len, results.data(), 0, 0, 'a', false);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -t n -j p 
            results.clear();
            expected_ans = 2;
            expected_words = {"medium", "moon"};
            ans = gen_chain_word(words, len, results.data(), 0, 'm', 0, false);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_word function in core.h case 5 for error
        TEST_METHOD(gen_chain_word_test5)
        {
            const char* words[] = {"algebra", "apple", "zoo", "elephant", "under", "fox", "panz", "medium", "dog", "moon", "leaf", "trick", "knod"};
            int len = 13;
            vector<char*> results(500, 0);
            int ans;
            // -w
            try {
                ans = gen_chain_word(words, len, results.data(), 0, 0, 0, false);
            }
            catch (exception& e) {
                Assert::AreEqual(e.what(), "There is a circle in the graph.");
            }

            // -w -h e
            try {
                ans = gen_chain_word(words, len, results.data(), 'e', 0, 0, false);
            }
            catch (exception& e) {
                Assert::AreEqual(e.what(), "There is a circle in the graph.");
            }

            // -w -t d
            try {
                ans = gen_chain_word(words, len, results.data(), 0, 'd', 0, false);
            }
            catch (exception& e) {
                Assert::AreEqual(e.what(), "There is a circle in the graph.");
            }
        }

        // unit test for gen_chain_char function in core.h case 1
        TEST_METHOD(gen_chain_char_test1)
        {
            const char* words[] = {"algebra", "apple", "zoo", "elephant", "under", "fox", "panz", "medium", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism"};
            int len = 13;
            vector<char*> results(500, 0);
            
            // -c
            int expected_ans = 3;
            vector<string> expected_words = {"pseudopseudohypoparathyroidism", "medium", "moon"};
            int ans = gen_chain_char(words, len, results.data(), 0, 0, 0, false);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -h e
            results.clear();
            expected_ans = 3;
            expected_words = {"pseudopseudohypoparathyroidism", "medium", "moon"};
            ans = gen_chain_char(words, len, results.data(), 'p', 0, 0, false);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -t m
            results.clear();
            expected_ans = 2;
            expected_words = {"pseudopseudohypoparathyroidism", "medium"};
            ans = gen_chain_char(words, len, results.data(), 0, 'm', 0, false);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_char function in core.h case 2
        TEST_METHOD(gen_chain_char_test2)
        {
            const char* words[] = {"aaaaaaaaaaaaaaab", "cd", "de", "ef"};
            int len = 4;
            vector<char*> results(500, 0);
            
            int expected_ans = 3;
            vector<string> expected_words = {"cd", "de", "ef"};
            int ans = gen_chain_char(words, len, results.data(), 0, 0, 0, false);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_char function in core.h case 3
        TEST_METHOD(gen_chain_char_test3) {
            const char* words[] = {"abc", "cba", "aaaaaaaaa"};
            int len = 3;
            vector<char*> results(500, 0);
            
            int expected_ans = 3;
            vector<string> expected_words = {"abc", "cba", "aaaaaaaaa"};
            int ans = gen_chain_char(words, len, results.data(), 0, 0, 0, true);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            sort(pred_words.begin(), pred_words.end());
            sort(expected_words.begin(), expected_words.end());

            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_char function in core.h case 4
        TEST_METHOD(gen_chain_char_test4) {
            const char* words[] = {"ab", "bc", "aaaaaaaa"};
            int len = 3;
            vector<char*> results(500, 0);
            
            int expected_ans = 3;
            vector<string> expected_words = {"aaaaaaaa", "ab", "bc"};
            int ans = gen_chain_char(words, len, results.data(), 0, 0, 0, false);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_char function in core.h case 5
        TEST_METHOD(gen_chain_char_test5) {
            const char* words[] = {"zzzzzz", "yz", "xy"};
            int len = 3;
            vector<char*> results(500, 0);
            
            int expected_ans = 3;
            vector<string> expected_words = {"xy", "yz", "zzzzzz"};
            int ans = gen_chain_char(words, len, results.data(), 0, 0, 0, false);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_char function in core.h case 6
        TEST_METHOD(gen_chain_char_test6)
        {
            const char* words[] = {"algebra", "apple", "zoo", "elephant", "under", "fox", "panz", "medium", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism"};
            int len = 13;
            vector<char*> results(500, 0);
            
            // -c -j p
            int expected_ans = 3;
            vector<string> expected_words = {"algebra", "apple", "elephant", "trick"};
            int ans = gen_chain_char(words, len, results.data(), 0, 0, 'p', false);
            Assert::AreEqual(ans, expected_ans);
            vector<string> pred_words;
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }

            // -w -t t -j p
            results.clear();
            expected_ans = 2;
            expected_words = {"algebra", "apple", "elephant"};
            ans = gen_chain_char(words, len, results.data(), 0, 't', 'p', false);
            Assert::AreEqual(ans, expected_ans);
            pred_words.clear();
            for (int i = 0; i < ans; i++) {
                pred_words.push_back(results[i]);
            }
            for (int i = 0; i < expected_ans; i++) {
                Assert::AreEqual(pred_words[i], expected_words[i]);
            }
        }

        // unit test for gen_chain_char function in core.h case 7 for error
        TEST_METHOD(gen_chain_char_test7) {
            const char* words[] = {"abc", "cba", "aaaaaaaaa"};
            int len = 3;
            vector<char*> results(500, 0);
            
            try {
                int ans = gen_chain_char(words, len, results.data(), 0, 0, 0, true);
            }
            catch (exception e) {
                Assert::AreEqual(e.what(), "There is a circle in the graph.");
            }
        }
    };

}

