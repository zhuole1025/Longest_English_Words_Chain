#include "pch.h"
#include "CppUnitTest.h"
#include "../src/core.h"


namespace unittest
{
    TEST_CLASS(unittest)
    {
        public:
            
            TEST(TestCaseName, TestName) {
                EXPECT_EQ(1, 1);
                EXPECT_TRUE(true);
            }

            // unit test for get_all function in graph.h case 1
            TEST_METHOD(gen_chains_all_test1)
            {
                const char* words[] = {"abc", "cde", "efg", "ghi"};
                int len = 4;
                vector<char*> results(32768, 0);
                int expected_ans = 6;
                vector<string> expected_words = {"abc cde", "cde efg", "efg ghi", "abc cde efg", "cde efg ghi", "abc cde efg ghi"};
                int ans = get_chains_all(words, len, results.data());
                Assert::AreEqual(ans, expected_ans);
                vector<string> pred_words = results;
                for (int i = 0; i < ans; i++) {
                    pred_words.push_back(results[i]);
                }
                sort(pred_words.begin(), pred_words.end());
		        sort(expected_words.begin(), expected_words.end());

                for (int i = 0; i < len; i++) {
                    Assert::AreEqual(result[i], expected_words[i]);
                }
            }

            // unit test for gen_chains_all function in core.h case 2
            TEST_METHOD(gen_chains_all_test2)
            {
                const char* words[] = {"head", "delay", "element", "yale", "key"};
                int len = 8;
                vector<char*> results(32768, 0);
                int expected_ans = 5;
                vector<string> expected_words = {"head delay", "delay yale", "yale element", "head delay yale", "delay yale element", "head delay yale element", "key yale", "key yale element"};
                int ans = get_chains_all(words, len, results.data());
                Assert::AreEqual(ans, expected_ans);
                vector<string> pred_words = results;
                for (int i = 0; i < ans; i++) {
                    pred_words.push_back(results[i]);
                }
                sort(pred_words.begin(), pred_words.end());
            }

            // unit test for get_all function in graph.h case 3
            TEST_METHOD(gen_chains_all_test3)
            {
                const char* words[] = {"ab", "abc", "abcd", "abcde", "defg"};
                int len = 5;
                vector<char*> results(32768, 0);
                int expected_ans = 1;
                vector<string> expected_words = {"abcd defg"};
                int ans = get_chains_all(words, len, results.data());
                Assert::AreEqual(ans, expected_ans);
                vector<string> pred_words = results;
                for (int i = 0; i < ans; i++) {
                    pred_words.push_back(results[i]);
                }
                sort(pred_words.begin(), pred_words.end());
		        sort(expected_words.begin(), expected_words.end());

                for (int i = 0; i < len; i++) {
                    Assert::AreEqual(result[i], expected_words[i]);
                }
            }

            // unit test for gen_chain_word function in core.h case 1
            TEST_METHOD(gen_chain_word_test1)
            {
                const char* words[] = {"abc", "cde", "efg", "ghi"};
                int len = 4;
                vector<char*> results(32768, 0);
                int expected_ans = 3;
                vector<string> expected_words = {"abc cde efg"};
                int ans = get_chain_word(words, len, results.data(), 'a', 'g', 'd', false);
                Assert::AreEqual(ans, expected_ans);
                vector<string> pred_words = results;
                for (int i = 0; i < ans; i++) {
                    pred_words.push_back(results[i]);
                }
                sort(pred_words.begin(), pred_words.end());
                sort(expected_words.begin(), expected_words.end());

                for (int i = 0; i < len; i++) {
                    Assert::AreEqual(result[i], expected_words[i]);
                }
            }
    }

}

