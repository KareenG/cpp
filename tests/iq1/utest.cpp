#include <string>
#include <string_view>
#include <algorithm>
#include <iostream>

#include "mu_test.h"

namespace iq1 {

int count(std::string_view s1, std::string_view s2);
std::string_view palindrome(std::string_view s);
void redact(std::string& s1, std::string_view s2);
void redact(char* s1, std::string_view s2);

} // namespace iq1


BEGIN_TEST(palindrome_basic)
    std::string input = "ABC1771CDTW";
    std::string_view result = iq1::palindrome(input);
    ASSERT_EQUAL(result, "C1771C");
END_TEST

BEGIN_TEST(palindrome_single_char)
    ASSERT_EQUAL(iq1::palindrome("a"), "a");
END_TEST

BEGIN_TEST(palindrome_empty_string)
    ASSERT_EQUAL(iq1::palindrome(""), "");
END_TEST

BEGIN_TEST(palindrome_entire_string)
    ASSERT_EQUAL(iq1::palindrome("racecar"), "racecar");
END_TEST

BEGIN_TEST(palindrome_multiple_valid_outputs)
    std::string_view result = iq1::palindrome("abdbabcbdabcba");
    ASSERT_THAT(result == "abcba" || result == "abdba");
END_TEST

BEGIN_TEST(palindrome_no_palindrome_longer_than_one)
    ASSERT_EQUAL(iq1::palindrome("abcdefg"), "");
END_TEST

/*-----------------------------------------------------------------------------------------------*/

BEGIN_TEST(count_basic)
    ASSERT_EQUAL(iq1::count("abracadabra", "bax"), 7);
END_TEST

BEGIN_TEST(count_all_matches)
    ASSERT_EQUAL(iq1::count("aaaaaa", "a"), 6);
END_TEST

BEGIN_TEST(count_no_matches)
    ASSERT_EQUAL(iq1::count("hello", "xyz"), 0);
END_TEST

BEGIN_TEST(count_empty_source)
    ASSERT_EQUAL(iq1::count("", "abc"), 0);
END_TEST

BEGIN_TEST(count_empty_chars)
    ASSERT_EQUAL(iq1::count("hello", ""), 0);
END_TEST

BEGIN_TEST(count_both_empty)
    ASSERT_EQUAL(iq1::count("", ""), 0);
END_TEST

/*-----------------------------------------------------------------------------------------------*/

// ---------------------- REDACT STRING TESTS ----------------------

BEGIN_TEST(redact_string_basic)
    std::string s = "hello world";
    iq1::redact(s, "eod");
    ASSERT_EQUAL(s, "h*ll* w*rl*");
END_TEST

BEGIN_TEST(redact_string_no_redaction)
    std::string s = "hello";
    iq1::redact(s, "xyz");
    ASSERT_EQUAL(s, "hello");
END_TEST

BEGIN_TEST(redact_string_all_redacted)
    std::string s = "abcdef";
    iq1::redact(s, "abcdef");
    ASSERT_EQUAL(s, "******");
END_TEST

BEGIN_TEST(redact_string_empty_input)
    std::string s = "";
    iq1::redact(s, "a");
    ASSERT_EQUAL(s, "");
END_TEST

BEGIN_TEST(redact_string_empty_pattern)
    std::string s = "unchanged";
    iq1::redact(s, "");
    ASSERT_EQUAL(s, "unchanged");
END_TEST

// ---------------------- REDACT C-STRING TESTS ----------------------

BEGIN_TEST(redact_cstring_basic)
    char s[] = "hello world";
    iq1::redact(s, "eod");
    ASSERT_EQUAL(std::string(s), "h*ll* w*rl*");
END_TEST

BEGIN_TEST(redact_cstring_no_redaction)
    char s[] = "test";
    iq1::redact(s, "xyz");
    ASSERT_EQUAL(std::string(s), "test");
END_TEST

BEGIN_TEST(redact_cstring_all_redacted)
    char s[] = "abc";
    iq1::redact(s, "abc");
    ASSERT_EQUAL(std::string(s), "***");
END_TEST

BEGIN_TEST(redact_cstring_empty_input)
    char s[] = "";
    iq1::redact(s, "abc");
    ASSERT_EQUAL(std::string(s), "");
END_TEST

BEGIN_TEST(redact_cstring_empty_pattern)
    char s[] = "unchanged";
    iq1::redact(s, "");
    ASSERT_EQUAL(std::string(s), "unchanged");
END_TEST


BEGIN_SUITE(full_iq1_test_suite)
    // palindrome
    TEST(palindrome_basic)
    TEST(palindrome_single_char)
    TEST(palindrome_empty_string)
    TEST(palindrome_entire_string)
    TEST(palindrome_multiple_valid_outputs)
    TEST(palindrome_no_palindrome_longer_than_one)

    // count
    TEST(count_basic)
    TEST(count_all_matches)
    TEST(count_no_matches)
    TEST(count_empty_source)
    TEST(count_empty_chars)
    TEST(count_both_empty)

    // redact string
    TEST(redact_string_basic)
    TEST(redact_string_no_redaction)
    TEST(redact_string_all_redacted)
    TEST(redact_string_empty_input)
    TEST(redact_string_empty_pattern)

    // redact c-string
    TEST(redact_cstring_basic)
    TEST(redact_cstring_no_redaction)
    TEST(redact_cstring_all_redacted)
    TEST(redact_cstring_empty_input)
    TEST(redact_cstring_empty_pattern)
END_SUITE



namespace iq1 {

constexpr int CharSetSize = 256;

/**
 * @brief  Q1: function that counts the occurrences in the first argument of any of the characters in the second argument.
 */
int count(std::string_view s1, std::string_view s2)
{
    bool all_ch[CharSetSize] = {false};
    int count_ch{};

    std::for_each(s2.begin(), s2.end(), [&all_ch](char c) {
                                                              all_ch[static_cast<unsigned char>(c)] = true;
                                                          });
    

    std::for_each(s1.begin(), s1.end(), [&all_ch, &count_ch](char c) {
                                                                         count_ch += (all_ch[static_cast<unsigned char>(c)]) ? 1 : 0;
                                                                     });
    return count_ch;
}

/**
 * @brief  Q2: function that finds the longest palindromic substring in a string.
 */
static int expand_around_center(std::string_view s, int left, int right)
{
    if(s.empty() || left > right) {
        return 0;
    }
    while(left >= 0 && right < static_cast<int>(s.length()) && s[left] == s[right]) {
        --left;
        ++right;
    }
    return right - left - 1;
}

std::string_view palindrome(std::string_view s)
{
    if(s.empty() || s.length() <= 1) {
        return s;
    }
    int start = 0;
    int end = 0;

    for(int i = 0; i < static_cast<int>(s.length()); ++i) {
        int palnd_around_one_c  = expand_around_center(s, i, i);
        int palnd_around_two_c  = expand_around_center(s, i, i + 1);
        int max_len = std::max(palnd_around_one_c , palnd_around_two_c );

        if(max_len > end - start) {
            // Found a longer palindrome centered at index i
            start = i - (max_len - 1) / 2;
            end = i + max_len / 2;
        }
    }

    if (end - start + 1 == 1) {
        return {};  // Treat single-character result as no valid palindrome
    }

    return s.substr(start, end - start + 1);
}

/**
 * @brief  Q3: function that will replace each occurrence of a char from the second string that appears in the first string with *.
 */
void redact(std::string& s1, std::string_view s2)
{
    bool all_ch[CharSetSize] = {false};

    std::for_each(s2.begin(), s2.end(), [&all_ch](char c) {
                                                              all_ch[static_cast<unsigned char>(c)] = true;
                                                          });
    
    // std::for_each gives copies of elements, so modifying c doesn't change the string. -> traditional loop
    for(char& c : s1) {
        if(all_ch[static_cast<unsigned char>(c)]) {
            c = '*';
        }
    }
}

void redact(char* s1, std::string_view s2)
{
    bool all_ch[CharSetSize] = {false};

    std::for_each(s2.begin(), s2.end(), [&all_ch](char c) {
                                                              all_ch[static_cast<unsigned char>(c)] = true;
                                                          });
    
    for(char *p = s1; *p != '\0'; ++p) {
        if(all_ch[static_cast<unsigned char>(*p)]) {
            *p = '*';
        }
    }
}

} // namespace iq1