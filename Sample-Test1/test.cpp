#include "pch.h"
#include "../src/core.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
  const char* words[] = { "abc", "cde", "efg", "ghi" };
  int len = 4;
  vector<char*> results(32768, 0);
  int expected_ans = 6;
  vector<char*> expected_words = { "abc cde", "cde efg", "efg ghi", "abc cde efg", "cde efg ghi", "abc cde efg ghi" };
  int ans = gen_chains_all(words, len, results.data());
  EXPECT_EQ(ans, expected_ans);
  vector<char*> pred_words;
  for (int i = 0; i < ans; i++) {
      pred_words.push_back(results[i]);
  }
  sort(pred_words.begin(), pred_words.end());
  sort(expected_words.begin(), expected_words.end());

  for (int i = 0; i < expected_ans; i++) {
      EXPECT_EQ(strcmp(pred_words[i], expected_words[i]), 0);
  }
}