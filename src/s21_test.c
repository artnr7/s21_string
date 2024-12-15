#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"
#define SIZE 100

START_TEST(test_memchr) {
  char s1[10] = "adddasf";

  char *dest1 = memchr(s1, 'a', 3);
  char *dest2 = s21_memchr(s1, 'a', 3);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memchr_null_terminator) {
  char s1[10] = "add\0casf";

  char *dest1 = memchr(s1, 'c', 5);
  char *dest2 = s21_memchr(s1, 'c', 5);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memchr_not_found_in_n) {
  char s1[10] = "addcasf";

  char *dest1 = memchr(s1, 'f', 5);
  char *dest2 = s21_memchr(s1, 'f', 5);

  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memchr_n_less_str) {
  char s1[10] = "add";

  char *dest1 = memchr(s1, 'a', 5);
  char *dest2 = s21_memchr(s1, 'a', 5);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memchr_empty_str) {
  char s1[10] = "";

  char *dest1 = memchr(s1, 'a', 5);
  char *dest2 = s21_memchr(s1, 'a', 5);

  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcmp_n_less_str) {
  char s1[10] = "add";
  char s2[10] = "add";

  int result1 = memcmp(s1, s2, 5);
  int result2 = s21_memcmp(s1, s2, 5);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp) {
  char s1[10] = "addb";
  char s2[10] = "addd";

  int result1 = memcmp(s1, s2, 2);
  int result2 = s21_memcmp(s1, s2, 2);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp_first_less_second) {
  char s1[10] = "addbbbb";
  char s2[10] = "adddddd";

  int result1 = memcmp(s1, s2, 3);
  int result2 = s21_memcmp(s1, s2, 3);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp_first_more_second) {
  char s1[10] = "addddddd";
  char s2[10] = "addbbbbb";

  int result1 = memcmp(s1, s2, 7);
  int result2 = s21_memcmp(s1, s2, 7);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp_eq_n) {
  char s1[10] = "abcd";
  char s2[10] = "abcd";

  int result1 = memcmp(s1, s2, 4);
  int result2 = s21_memcmp(s1, s2, 4);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp_n_large) {
  char s1[10] = "abcd";
  char s2[10] = "abcd";

  int result1 = memcmp(s1, s2, 5);
  int result2 = s21_memcmp(s1, s2, 5);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcpy_second_less) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";

  char s3[] = "\0";
  char *dest1 = memcpy(s1, s3, 1);
  char *dest2 = s21_memcpy(s2, s3, 1);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_second_more) {
  char s1[] = "123456";
  char s2[] = "123456";

  char s3[] = "00000000";
  char *dest1 = memcpy(s1, s3, 3);
  char *dest2 = s21_memcpy(s2, s3, 3);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_eq_str) {
  char s1[100] = "world!";
  char s2[100] = "world!";
  char str[10] = "fffff";
  int n = 3;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_big_n) {
  char s1[100] = "Hello, world!";
  char s2[100] = "Hello, world!";
  char str[10] = "aboba";
  int n = 7;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_second_str_null_term) {
  char s1[100] = "dsf";
  char s2[100] = "dsf";
  char str[10] = "\0";
  int n = 1;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_second_str_zero_n) {
  char s1[100] = "dsfd";
  char s2[100] = "dsfd";
  char str[10] = "f";
  int n = 0;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_second_str_term_null) {
  char s1[100] = "dsdf\02fd";
  char s2[100] = "dsdf\02fd";
  char str[10] = "cum";
  int n = 3;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_second_str_term_null_num) {
  char s1[100] = "2343\032423";
  char s2[100] = "2343\032423";
  char str[10] = "fsd\0123";
  int n = 7;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memset_null_terminator) {
  char s1[10] = {'\0'};
  char s2[10] = {'\0'};

  char *dest1 = memset(s1, 64, 3);
  char *dest2 = s21_memset(s2, 64, 3);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memset_str_eq) {
  char s1[10] = "111111111\0";
  char s2[10] = "111111111\0";

  char *dest1 = memset(s1, 12, 3);
  char *dest2 = s21_memset(s2, 12, 3);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat) {
  char s1[20] = "addddddd";
  char s2[10] = "addbbbbb";

  char *result1 = strncat(s1, s2, 7);
  char *result2 = s21_strncat(s1, s2, 7);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strncat_first_empty_str) {
  char s1[20] = "";
  char s2[10] = "add";

  char *result1 = strncat(s1, s2, 4);
  char *result2 = s21_strncat(s1, s2, 4);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strncat_two_empty_str) {
  char s1[20] = "";
  char s2[10] = "";

  char *result1 = strncat(s1, s2, 4);
  char *result2 = s21_strncat(s1, s2, 4);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strchr) {
  char s1[10] = "adddasf";

  char *dest1 = strchr(s1, 'a');
  char *dest2 = s21_strchr(s1, 'a');

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_null_terminator) {
  char s1[10] = "add\0casf";

  char *dest1 = strchr(s1, 'c');
  char *dest2 = s21_strchr(s1, 'c');

  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_find_null_terminator) {
  char s1[10] = "addcasf";

  char *dest1 = strchr(s1, '\0');
  char *dest2 = s21_strchr(s1, '\0');

  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_not_found) {
  char s1[10] = "addcasf";

  char *dest1 = strchr(s1, 'g');
  char *dest2 = s21_strchr(s1, 'g');

  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_found_end) {
  char s1[10] = "addf";

  char *dest1 = strchr(s1, 'f');
  char *dest2 = s21_strchr(s1, 'f');

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_empty_str) {
  char s1[20] = "";

  char *result1 = strchr(s1, 'a');
  char *result2 = s21_strchr(s1, 'a');

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_null_terminator) {
  char s1[20] = "abca\0a";
  char s2[20] = "abca\0a";

  int result1 = strncmp(s1, s2, 6);
  int result2 = s21_strncmp(s1, s2, 6);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_str_eq) {
  char s1[20] = "abbbddd";
  char s2[20] = "abbbddd";

  int result1 = strncmp(s1, s2, 6);
  int result2 = s21_strncmp(s1, s2, 6);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_first_str_big) {
  char s1[20] = "abbbbbbb";
  char s2[20] = "afff";

  int result1 = strncmp(s1, s2, 6);
  int result2 = s21_strncmp(s1, s2, 6);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_second_str_big) {
  char s2[20] = "abbbbbbb";
  char s1[20] = "afff";

  int result1 = strncmp(s1, s2, 6);
  int result2 = s21_strncmp(s1, s2, 6);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncpy_src_less_n) {
  char s1[20] = "abbbbbbb";
  char s2[20] = "abbbbbbb";
  char s3[5] = "afff";

  char *result1 = strncpy(s1, s3, 6);
  char *result2 = s21_strncpy(s2, s3, 6);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strncpy_overwrite_null_terminator) {
  char s1[20] = "abb\0bbbbb";
  char s2[20] = "abb\0bbbbb";
  char s3[20] = "afff";

  char *result1 = strncpy(s1, s3, 6);
  char *result2 = s21_strncpy(s2, s3, 6);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strncpy) {
  char s1[20] = "abbbbbbb";
  char s2[20] = "abbbbbbb";
  char s3[5] = "afff";

  char *result1 = strncpy(s1, s3, 3);
  char *result2 = s21_strncpy(s2, s3, 3);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strcspn_zero) {
  char *s1 = "aaaafd";
  char *s2 = "aab";

  int result1 = strcspn(s1, s2);
  int result2 = s21_strcspn(s1, s2);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strcspn_one_symbol) {
  char *s1 = "acaaabbbfd";
  char *s2 = "b";

  int result1 = strcspn(s1, s2);
  int result2 = s21_strcspn(s1, s2);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strcspn_two_symbol) {
  char *s1 = "acaaabbbfd";
  char *s2 = "ab";

  int result1 = strcspn(s1, s2);
  int result2 = s21_strcspn(s1, s2);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strerror_negative) {
  char *s1 = s21_strerror(-10);
  char *s2 = strerror(-10);

  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strerror_zero) {
  char *s1 = s21_strerror(0);
  char *s2 = strerror(0);

  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strerror_positive) {
  char *s1 = s21_strerror(20);
  char *s2 = strerror(20);

  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strerror_offside) {
  char *s1 = s21_strerror(200);
  char *s2 = strerror(200);

  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strlen_empty_str) {
  char *s1 = "";

  int result1 = strlen(s1);
  int result2 = s21_strlen(s1);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strlen) {
  char *s1 = "12344567890";

  int result1 = strlen(s1);
  int result2 = s21_strlen(s1);

  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strpbrk_two_empty_str) {
  char *s1 = "";
  char *s2 = "";

  char *result1 = strpbrk(s1, s2);
  char *result2 = s21_strpbrk(s1, s2);

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strpbrk_first_empty_str) {
  char *s1 = "";
  char *s2 = "ad";

  char *result1 = strpbrk(s1, s2);
  char *result2 = s21_strpbrk(s1, s2);

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strpbrk) {
  char *s1 = "aabbcc";
  char *s2 = "cb";

  char *result1 = strpbrk(s1, s2);
  char *result2 = s21_strpbrk(s1, s2);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strpbrk_not_found) {
  char *s1 = "aabbcc";
  char *s2 = "cba";

  char *result1 = strpbrk(s1, s2);
  char *result2 = s21_strpbrk(s1, s2);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_str_A) {
  char s1[20] = "123a567";

  char *result1 = strrchr(s1, 'A');
  char *result2 = s21_strrchr(s1, 'A');

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_empty_str) {
  char s1[20] = "";

  char *result1 = strrchr(s1, 'a');
  char *result2 = s21_strrchr(s1, 'a');

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_str_a) {
  char s1[20] = "123a567a";

  char *result1 = strrchr(s1, 'a');
  char *result2 = s21_strrchr(s1, 'a');

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_null_terminator) {
  char s1[20] = "abca\0a";

  char *result1 = strrchr(s1, 'a');
  char *result2 = s21_strrchr(s1, 'a');

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_null_terminator_one) {
  char s1[20] = "Hello, world!";

  char *result1 = strrchr(s1, 'h');
  char *result2 = s21_strrchr(s1, 'h');

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_null_terminator_two) {
  char s1[20] = "";

  char *result1 = strrchr(s1, 'H');
  char *result2 = s21_strrchr(s1, 'H');

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_null_terminator_three) {
  char s1[20] = "\0";

  char *result1 = strrchr(s1, '\0');
  char *result2 = s21_strrchr(s1, '\0');

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_null_terminator_four) {
  char s1[20] = "\0";

  char *result1 = strrchr(s1, '\0');
  char *result2 = s21_strrchr(s1, '\0');

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_null_terminator_five) {
  char s1[20] = "Hello, world!";

  char *result1 = strrchr(s1, '0');
  char *result2 = s21_strrchr(s1, '0');

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_null_terminator_six) {
  char s1[20] = "Hello, world!";

  char *result1 = strrchr(s1, 'm');
  char *result2 = s21_strrchr(s1, 'm');

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_full) {
  char *s1 = "Hello, world!";
  char *s2 = "Hello, world!";

  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_one_word) {
  char *s1 = "Hello, world!";
  char *s2 = "world";

  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_specify) {
  char *s1 = "Hello, world!";
  char *s2 = "!";

  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_testing_word) {
  char *s1 = "This is a test string";
  char *s2 = "test";

  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_susping_work) {
  char *s1 = "sus";
  char *s2 = "suspi";

  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);

  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_insert_second_null) {
  char *result = s21_insert("wtf", S21_NULL, 0);
  ck_assert_ptr_eq(result, S21_NULL);
  free(result);
}
END_TEST

START_TEST(test_insert_two_null) {
  char *result = s21_insert(S21_NULL, S21_NULL, 0);
  ck_assert_ptr_eq(result, S21_NULL);
  free(result);
}
END_TEST

START_TEST(test_insert_zero) {
  char *result = s21_insert("non-empty", "insert", 20);
  ck_assert_ptr_eq(result, S21_NULL);
  free(result);
}
END_TEST

START_TEST(test_strstr_second_empty_str) {
  char *s1 = "adbc";
  char *s2 = "";

  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr) {
  char *s1 = "aabbcc";
  char *s2 = "bb";

  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_not_found) {
  char *s1 = "aabbcc";
  char *s2 = "cba";

  char *result1 = strpbrk(s1, s2);
  char *result2 = s21_strpbrk(s1, s2);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok) {
  char s1[30] = "as, as; as| as. as/ as; as";
  char *delim = ";";

  char *result1 = strtok(s1, delim);
  char *result2 = s21_strtok(s1, delim);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok_null) {
  char s1[30] = "as, as; as| as. as/ as; as";
  char s2[30] = "as, as; as| as. as/ as; as";

  char *delim = ";";

  char *result1 = strtok(s1, delim);
  char *result2 = s21_strtok(s2, delim);

  result1 = strtok(NULL, delim);
  result2 = s21_strtok(S21_NULL, delim);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok_not_found_delim) {
  char s1[30] = "as, as; as| as. as/ as; as";
  char s2[30] = "as, as; as| as. as/ as; as";

  char *delim = "-";

  char *result1 = strtok(s1, delim);
  char *result2 = s21_strtok(s2, delim);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok_empty_delim) {
  char s1[30] = "as, as; as| as. as/ as; as";
  char s2[30] = "as, as; as| as. as/ as; as";

  char *delim = "";

  char *result1 = strtok(s1, delim);
  char *result2 = s21_strtok(s2, delim);

  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_to_upper) {
  char str[16] = "Hello World";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);
}
END_TEST
START_TEST(test_to_upper_empty_str) {
  char str[16] = "";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST
START_TEST(test_to_upper_not_char_str) {
  char str[16] = "3/";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "3/");
  free(result);
}
END_TEST

START_TEST(test_to_lower) {
  char *result = s21_to_lower("Hello World");
  ck_assert_str_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_to_lower_empty_str) {
  char *result = s21_to_lower("");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_lower_not_char_str) {
  char *result = s21_to_lower("3/");
  ck_assert_str_eq(result, "3/");
  free(result);
}
END_TEST

START_TEST(test_insert) {
  char *result = s21_insert("hello frend", "my good ", 6);
  ck_assert_str_eq(result, "hello my good frend");
  free(result);
}
END_TEST
START_TEST(test_insert_in_start) {
  char *result = s21_insert("hello frend", "my good ", 0);
  ck_assert_str_eq(result, "my good hello frend");
  free(result);
}
END_TEST

START_TEST(test_insert_return_null) {
  char *result = s21_insert("", "my good ", 0);
  ck_assert_str_eq(result, "my good ");
  free(result);
}
END_TEST

START_TEST(test_insert_substring_empty) {
  char *result = s21_insert("he", "", 1);
  ck_assert_str_eq(result, "he");
  free(result);
}
END_TEST

START_TEST(test_insert_empty_str) {
  char *result = s21_insert("", "", 1);
  ck_assert_ptr_eq(result, S21_NULL);
  free(result);
}
END_TEST

START_TEST(test_trim) {
  char *result = s21_trim("  aaacdgr eet  ", "acd");
  ck_assert_str_eq(result, "gr eet");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_str) {
  char *result = s21_trim("", "wer");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_all_delete) {
  char *result = s21_trim("adsdd", "ads");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_all_str) {
  char *result = s21_trim("", "");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_null_str) {
  char *result = s21_trim(S21_NULL, "");
  ck_assert_ptr_eq(result, S21_NULL);
  free(result);
}
END_TEST

START_TEST(test_trim_empty_str_secnod_empty) {
  char *result = s21_trim(" wtf ", "");
  ck_assert_str_eq(result, " wtf ");
  free(result);
}
END_TEST

START_TEST(test_specifier_c) {
  char c = 'd';
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%csd";
  int len1 = sprintf(result1, format, c, 1);
  int len2 = s21_sprintf(result2, format, c, 1);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_d) {
  int d = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%dsd";
  int len1 = sprintf(result1, format, d);
  int len2 = s21_sprintf(result2, format, d);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_d_zero) {
  int d = 0;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%dsd";
  int len1 = sprintf(result1, format, d);
  int len2 = s21_sprintf(result2, format, d);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_i) {
  int d = -120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%isd";
  int len1 = sprintf(result1, format, d);
  int len2 = s21_sprintf(result2, format, d);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_e) {
  double e = 10.9023499e-10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%.18easd";
  int len1 = sprintf(result1, format, e);
  int len2 = s21_sprintf(result2, format, e);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_E) {
  float e = -10.9090099;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%Easd";
  int len1 = sprintf(result1, format, e);
  int len2 = s21_sprintf(result2, format, e);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_f) {
  float f = 10.999;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%fsd";
  int len1 = sprintf(result1, format, f);
  int len2 = s21_sprintf(result2, format, f);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_g) {
  float g = -10.999;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%012gsd";
  int len1 = sprintf(result1, format, g);
  int len2 = s21_sprintf(result2, format, g);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_G) {
  float g = 100.00e-13;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%Gsd";
  int len1 = sprintf(result1, format, g);
  int len2 = s21_sprintf(result2, format, g);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_o) {
  int o = 10123;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%o";
  int len1 = sprintf(result1, format, o);
  int len2 = s21_sprintf(result2, format, o);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_s) {
  char s[20] = "corrre12!";
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%s";
  int len1 = sprintf(result1, format, s);
  int len2 = s21_sprintf(result2, format, s);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_u) {
  unsigned int u = 102;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%u";
  int len1 = sprintf(result1, format, u);
  int len2 = s21_sprintf(result2, format, u);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_x) {
  int x = 0xFF;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%x";
  int len1 = sprintf(result1, format, x);
  int len2 = s21_sprintf(result2, format, x);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_X) {
  int x = 0xFF;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%X";
  int len1 = sprintf(result1, format, x);
  int len2 = s21_sprintf(result2, format, x);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_p) {
  int a = 123;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%p";
  int len1 = sprintf(result1, format, &a);
  int len2 = s21_sprintf(result2, format, &a);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_n) {
  int n1 = 0;
  int n2 = 0;
  int n3 = 0;
  int n4 = 0;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%nas%n";
  int len1 = sprintf(result1, format, &n1, &n3);
  int len2 = s21_sprintf(result2, format, &n2, &n4);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_minus_d) {
  int number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%-das";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_plus_f) {
  float number = 99.9999;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%+fas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_plus_d) {
  int number = 99.9999;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%+das";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_space_g) {
  float number = 99.9999;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:% gas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_space_minus_g) {
  float number = 99.9999;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:% -gas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_sharp_o) {
  int number = 99;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%#oas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_sharp_x) {
  float number = 99.9999;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%#xas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_sharp_e) {
  float number = 102.23e-20;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%#eas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_sharp_f) {
  float number = 99;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%#fas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_sharp_g) {
  float number = 99;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%#gas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_zero_with_width_g) {
  float number = 1123.89;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%020gas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_width_eq_zero_x) {
  int number = 9;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%0xas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_width_g) {
  float number = 99.9999;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%100gas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_width_variable_E) {
  float number = 99.9999;
  int width = 100;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%*Eas";
  int len1 = sprintf(result1, format, width, number);
  int len2 = s21_sprintf(result2, format, width, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_accuracy_d) {
  int number = 12;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%.100das";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_accuracy_u) {
  unsigned int number = 12;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%.10uas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_accuracy_o) {
  int number = 12;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%.100oas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_accuracy_f) {
  float number = 12.23f;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%.12fas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_accuracy_g) {
  double number = 12.234556;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%.21gas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_accuracy_s) {
  char str[10] = "asdf\0";
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%.3sas";
  int len1 = sprintf(result1, format, str);
  int len2 = s21_sprintf(result2, format, str);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_accuracy_with_variable_X) {
  int number = 1216;
  int accuracy = 12;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%.*Xas";
  int len1 = sprintf(result1, format, accuracy, number);
  int len2 = s21_sprintf(result2, format, accuracy, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_h_i) {
  short number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%hias";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_h_d) {
  short number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%hdas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_h_o) {
  short number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%hoas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_h_u) {
  short number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%huas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_h_x) {
  short number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%hxas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_h_X) {
  short number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%hXas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_i) {
  long number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lias";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_d) {
  long number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%ldas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_ll_d) {
  long long number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lldas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_ll_o) {
  long long unsigned number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lloas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_ll_u) {
  long long unsigned number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lluas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_ll_x) {
  long long unsigned number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%llxas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_ll_X) {
  long long unsigned number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%llXas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_o) {
  long number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%loas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_u) {
  long number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%luas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_x) {
  long number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lxas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_X) {
  long number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lXas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_c) {
  int number = L'a';
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lcas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_s) {
  int number[10] = L"abcdefd";
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lsas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_L_e) {
  long double number = 1123123220.1782912339123;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%Leas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_L_E) {
  long double number = -999999.9999999;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%LEas\n";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_L_f) {
  long double number = 9876.54321;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%Lfas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_L_g) {
  long double number = 120.00000011123;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%Lgas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_L_G) {
  long double number = 120.00000011123;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%LGas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_f_negative_inf) {
  double number = -5.0 / 0.0;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lfas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_f_positive_inf) {
  double number = 5.0 / 0.0;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%lfas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_flags_width_accuracy_length_f) {
  double number = -5.0 / 0.0;
  int width = 10;
  int accuracy = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:% +*.*lfas";
  int len1 = sprintf(result1, format, width, accuracy, number);
  int len2 = s21_sprintf(result2, format, width, accuracy, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_flags_width_length_f) {
  double number = -5.0 / 0.0;
  int width = 10;
  int accuracy = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:% +*lfas";
  int len1 = sprintf(result1, format, width, accuracy, number);
  int len2 = s21_sprintf(result2, format, width, accuracy, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_flags_accuracy_length_f) {
  double number = -5.0 / 0.0;
  int accuracy = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:% +.*lfas";
  int len1 = sprintf(result1, format, accuracy, number);
  int len2 = s21_sprintf(result2, format, accuracy, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_flags_length_f) {
  double number = -5.0 / 0.0;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:% +lfas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_length_character) {
  int width = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%l))";
  int len1 = sprintf(result1, format, width);
  int len2 = s21_sprintf(result2, format, width);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_character) {
  int width = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%))";
  int len1 = sprintf(result1, format, width);
  int len2 = s21_sprintf(result2, format, width);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_flags_character) {
  int width = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%-&10))";
  int len1 = sprintf(result1, format, width);
  int len2 = s21_sprintf(result2, format, width);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_width_character) {
  int width = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%10))";
  int len1 = sprintf(result1, format, width);
  int len2 = s21_sprintf(result2, format, width);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_width_acccuracy_character) {
  int width = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%10.20))";
  int len1 = sprintf(result1, format, width);
  int len2 = s21_sprintf(result2, format, width);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_combo_width_acccuracy_length_character) {
  int width = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";

  char *format = "Test1:%10.20))";
  int len1 = sprintf(result1, format, width);
  int len2 = s21_sprintf(result2, format, width);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_all_specifiers) {
  char c = 'd';
  int d = 102020;
  int i = -999999012;
  float e = -99.999e-12;
  float E = -99.999e+12;
  float f = -99.999;
  float g = 10.000;
  float G = -123.000;
  unsigned int o = 123;
  char str[12] = "adfgf";
  unsigned int u = 123;
  unsigned int x = 123;
  unsigned int X = 123;
  void *p = &c;
  int count_vstr1 = 0;
  int count1 = 0;

  int count_vstr2 = 0;
  int count2 = 0;

  char result1[400] = "\0";
  char result2[300] = "\0";

  char *format =
      "Test%c1:%ddsjf%i; %ell%nkd%Edfg%ffg%g fd %Gdf%o fd%s%u%xjkl %X, %pdf%n";
  int len1 = sprintf(result1, format, c, d, i, e, &count_vstr1, E, f, g, G, o,
                     str, u, x, X, p, &count_vstr2);
  int len2 = s21_sprintf(result2, format, c, d, i, e, &count1, E, f, g, G, o,
                         str, u, x, X, p, &count2);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
  ck_assert_int_eq(count_vstr1, count1);
  ck_assert_int_eq(count_vstr2, count2);
}
END_TEST

START_TEST(test_all_specifiers_with_flags) {
  char c = 'd';
  int d = 102020;
  int i = -999999012;
  float e = -99.999e-12;
  float E = -99.999e+12;
  float f = -99.999;
  float g = 10.000;
  float G = -123.000;
  unsigned int o = 123;
  char str[12] = "adfgf";
  unsigned int u = 123;
  unsigned int x = 123;
  unsigned int X = 123;
  void *p = &c;
  int count_vstr1 = 0;
  int count1 = 0;

  int count_vstr2 = 0;
  int count2 = 0;

  char result1[400] = "\0";
  char result2[400] = "\0";

  char *format =
      "Test%c1:%0ddsjf%#i; %-ell%nkd%+Eiu%010fkHK% "
      "2gNED%#GBL%-oSs%sdf%-uKD%#xS,k%#Xdd%#ps%n";
  int len1 = sprintf(result1, format, c, d, i, e, &count_vstr1, E, f, g, G, o,
                     str, u, x, X, p, &count_vstr2);
  int len2 = s21_sprintf(result2, format, c, d, i, e, &count1, E, f, g, G, o,
                         str, u, x, X, p, &count2);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
  ck_assert_int_eq(count_vstr1, count1);
  ck_assert_int_eq(count_vstr2, count2);
}
END_TEST

START_TEST(test_all_specifiers_with_width) {
  char c = 'd';
  int d = 102020;
  int i = -999999012;
  float e = -99.999e-12;
  float E = -99.999e+12;
  float f = -99.999;
  float g = 10.000;
  float G = -123.000;
  unsigned int o = 123;
  char str[12] = "adfgf";
  unsigned int u = 123;
  unsigned int x = 123;
  unsigned int X = 123;
  void *p = &c;
  int count_vstr1 = 0;
  int count1 = 0;

  int count_vstr2 = 0;
  int count2 = 0;

  char result1[1000] = "\0";
  char result2[1000] = "\0";

  char *format =
      "Test%12c1:%02ddsjf%#32i; %-22ell%nkd%33Eiu%10fkHK%12gNED%012GBL% "
      "12oSs%12sdf%-90uKD%#23xS,k%+213Xdd%#23ps%n";
  int len1 = sprintf(result1, format, c, d, i, e, &count_vstr1, E, f, g, G, o,
                     str, u, x, X, p, &count_vstr2);
  int len2 = s21_sprintf(result2, format, c, d, i, e, &count1, E, f, g, G, o,
                         str, u, x, X, p, &count2);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
  ck_assert_int_eq(count_vstr1, count1);
  ck_assert_int_eq(count_vstr2, count2);
}
END_TEST

START_TEST(test_all_specifiers_with_accuracy) {
  char c = 'd';
  int d = 102020;
  int i = -999999012;
  double e = -99.999e-5;
  double E = -99.999e+5;
  float f = -99.999;
  float g = 10.000;
  float G = -123.000;
  unsigned int o = 123;
  char str[12] = "adfgf";
  unsigned int u = 123;
  unsigned int x = 123;
  unsigned int X = 123;
  void *p = &c;
  int count_vstr1 = 0;
  int count1 = 0;

  int count_vstr2 = 0;
  int count2 = 0;

  char result1[1000] = "\0";
  char result2[1000] = "\0";

  char *format =
      "Test%c1:%.2ddsjf%#.32i; %-.16ell%nkd%.16Eiu%.10fkHK%.12gNED%0.12GBL% "
      ".12oSs%.12sdf%-.90uKD%#.23xS,k%+.213Xdd%#.23ps%n";
  int len2 = s21_sprintf(result2, format, c, d, i, e, &count1, E, f, g, G, o,
                         str, u, x, X, p, &count2);
  int len1 = sprintf(result1, format, c, d, i, e, &count_vstr1, E, f, g, G, o,
                     str, u, x, X, p, &count_vstr2);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
  ck_assert_int_eq(count_vstr1, count1);
  ck_assert_int_eq(count_vstr2, count2);
}
END_TEST

START_TEST(test_all_specifiers_with_length) {
  unsigned int lc = L'd';

  short int hd = 1020;
  long int ld = 102020;

  short int hi = -9012;
  long int li = -999999012;

  long double Le = -99.999e-5;
  long double LE = -99.999e+5;
  long double Lf = -99.999;
  long double Lg = 102342.000434;
  long double LG = -123432.0042340;

  long unsigned int lo = 123;
  short unsigned int ho = 987;

  const char *str = "adfgf";
  unsigned int lstr[12] = {0};

  for (int i = 0; i < 5; i++) {
    lstr[i] = (unsigned int)str[i];
  }

  long unsigned int lu = 12334;
  short unsigned int hu = 123;

  long unsigned int lx = 12332423;
  short unsigned int hx = 123;

  long unsigned int lX = 1232323;
  short unsigned int hX = 123;

  void *p = &lc;
  int count_vstr1 = 0;
  int count1 = 0;

  int count_vstr2 = 0;
  int count2 = 0;

  char result1[1000] = "\0";
  char result2[1000] = "\0";

  char *format =
      "Test%lc1:%.2hd %.2hi %.2hods%.2hu%.2hxjf%.2hX%-.16Lel%LE, %Lf, "
      "(%Lg)(%LG)hk%lds%lid%loj%lufk%lxjs%lXdfs%lsd;aa%pa0%n-=";
  int len1 = sprintf(result2, format, lc, hd, hi, ho, hu, hx, hX, Le, LE, Lf,
                     Lg, LG, ld, li, lo, lu, lx, lX, lstr, p, &count_vstr1);
  int len2 = s21_sprintf(result1, format, lc, hd, hi, ho, hu, hx, hX, Le, LE,
                         Lf, Lg, LG, ld, li, lo, lu, lx, lX, lstr, p, &count1);

  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
  ck_assert_int_eq(count_vstr1, count1);
  ck_assert_int_eq(count_vstr2, count2);
}
END_TEST

START_TEST(test_sscanf_char) {
  char result = '\0', result_orig = '\0';
  const char *str = "A";
  const char *format = "%c";
  sscanf(str, format, &result_orig);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result_orig);
}
END_TEST

START_TEST(test_sscanf_char_star) {
  char result = '\0', result_orig = '\0';
  const char *str = "A";
  const char *format = "%*c";
  sscanf(str, format, &result_orig);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result_orig);
}
END_TEST

START_TEST(test_sscanf_decimal) {
  int result = 0, result2 = 0;
  const char *str = " +1234";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_d_count) {
  int result = 0;
  const char *str = "123 333";
  const char *format = "%d %d";
  result = s21_sscanf(str, format, &result, &result);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(test_sscanf_d_count_2) {
  int result = 0;
  const char *str = "123xyz333";
  const char *format = "%dxyz%d";
  result = s21_sscanf(str, format, &result, &result);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(test_sscanf_d_negative) {
  int result = 0, result2 = 0;
  const char *str = "       -1344";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_d_zero) {
  int result = 0, result2 = 0;
  const char *str = "00000";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_d_zero_in_start) {
  int result = 0, result2 = 0;
  const char *str = "002133";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_d_invalid_number) {
  int result = 0, result2 = 0;
  const char *str = "gtr123";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_d_dash_in_number) {
  int result = 0, result2 = 0;
  const char *str = "22-55";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_d_spaces_before_and_after_number) {
  int result = 0, result2 = 0;
  const char *str = "  1234  ";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_d_number_in_single_quotes) {
  int result = 0, result2 = 0;
  const char *str = "'43'";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_d_in_double_quotes) {
  int result1 = 0, result2 = 0, result3 = 0, result4 = 0;
  const char *str = "\"11\" \"34\"";
  const char *format = "%d %d";
  sscanf(str, format, &result3, &result4);
  s21_sscanf(str, format, &result1, &result2);
  ck_assert_int_eq(result1, result3);
  ck_assert_int_eq(result2, result4);
}
END_TEST

START_TEST(test_sscanf_d_in_single_quotes) {
  int result1 = 0, result2 = 0, result3 = 0, result4 = 0;
  const char *str = "'1234' '5678'";
  const char *format = "%d %d";
  sscanf(str, format, &result3, &result4);
  s21_sscanf(str, format, &result1, &result2);
  ck_assert_int_eq(result1, result3);
  ck_assert_int_eq(result2, result4);
}
END_TEST
START_TEST(test_sscanf_number_in_brackets) {
  int result = 0;
  int result2 = 0;
  const char *str = "[4343]";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_d_with_comma) {
  int result = 0;
  int result1 = 0;
  const char *str = "1,234";
  const char *format = "%d";
  sscanf(str, format, &result1);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result1);
}
END_TEST

START_TEST(test_sscanf_d_with_dot_and_negative) {
  int result = 0, result2 = 0;
  const char *str = "-1.234";
  const char *format = "%d";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_i_negative) {
  int result = 0, result2 = 0;
  const char *str = "-1239";
  const char *format = "%i";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}

START_TEST(test_sscanf_i_negative_star) {
  int result = 0, result2 = 0;
  const char *str = "-1239";
  const char *format = "%*i";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}

START_TEST(test_sscanf_i_positive) {
  int result = 0, result2 = 0;
  const char *str = "+1239";
  const char *format = "%i";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_i_hexadecimal) {
  int result = 0, result2 = 0;
  const char *str = "0x2CDEf";
  const char *format = "%i";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_i_octal) {
  int result = 0, result2 = 0;
  const char *str = "0227";
  const char *format = "%i";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
}
END_TEST

START_TEST(test_sscanf_i_hex) {
  int result = 0, result2 = 0;
  const char *str = "0x1A2B";
  const char *format = "%i";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
}
END_TEST
START_TEST(test_sscanf_i_not_exist) {
  int result = 0, result2 = 0;
  const char *str = "1GLK";
  const char *format = "%i";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
}
END_TEST

START_TEST(test_sscanf_e) {
  int result = 0, result2 = 0;
  const char *str = "1.663e-4";
  const char *format = "%e";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_e_star) {
  int result = 0, result2 = 0;
  const char *str = "1.663e-4";
  const char *format = "%*e";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_E) {
  int result = 0, result2 = 0;
  const char *str = "1.663e-4";
  const char *format = "%E";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_E_positive) {
  int result = 0, result2 = 0;
  const char *str = "+1.663e+4";
  const char *format = "%E";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_f_with_exp_comma_and_space) {
  float result = 0.0, result2 = 0.0;
  const char *str = " 1.23e4 , 123 ";
  const char *format = "%f";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_float_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_float_negative) {
  float result = 0.0, result2 = 0.0;
  const char *str = " -123.123";
  const char *format = "%f";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_float_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_f_exponential) {
  float result = 0.0, result2 = 0.0;
  const char *str = "1.23e-3";
  const char *format = "%f";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_float_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_f_positive) {
  float result = 0.0;
  float result1 = 0.0;
  const char *str = "123.123";
  const char *format = "%f";
  sscanf(str, format, &result1);
  s21_sscanf(str, format, &result);
  ck_assert_float_eq(result, result1);
}
END_TEST

START_TEST(test_sscanf_f_space_in_start) {
  float result = 0.0;
  float result1 = 0.0;
  const char *str = " 123.123";
  const char *format = "%f";
  sscanf(str, format, &result1);
  s21_sscanf(str, format, &result);
  ck_assert_float_eq(result, result1);
}
END_TEST

START_TEST(test_sscanf_f_zero_exponential) {
  float result = 0.0, result2 = 0.0;
  const char *str = "0.0e0";
  const char *format = "%f";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_float_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_f_spaces_around_comma) {
  float result1 = 0, result2 = 0, result3 = 0, result4 = 0;
  const char *str = " 444 , 123 ";
  const char *format = "%f %f";
  sscanf(str, format, &result1, &result2);
  s21_sscanf(str, format, &result3, &result4);
  ck_assert_float_eq(result1, result3);
  ck_assert_float_eq(result2, result4);
}
END_TEST
START_TEST(test_sscanf_f_space_around_percent) {
  float result = 0.0, result2 = 0.0;
  const char *str = " 123 % ";
  const char *format = "%f %";
  sscanf(str, format, &result2, &result2);
  s21_sscanf(str, format, &result, &result);
  ck_assert_float_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_f_percent) {
  float result = 0.0, result2 = 0.0;
  const char *str = "50%";
  const char *format = "%f%%";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_float_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_g_negative) {
  int result = 0, result2 = 0;
  const char *str = "-1.663e-4";
  const char *format = "%g";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_g_positive) {
  int result = 0, result2 = 0;
  const char *str = "3e4";
  const char *format = "%g";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_G_positive) {
  int result = 0, result2 = 0;
  const char *str = "3e4";
  const char *format = "%G";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_G) {
  int result = 0, result2 = 0;
  const char *str = "31.6643";
  const char *format = "%G";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_o_decimal) {
  unsigned int result = 0, result2 = 0;
  const char *str = "+1234";
  const char *format = "%o";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_o_decimal_star) {
  unsigned int result = 0, result2 = 0;
  const char *str = "+1234";
  const char *format = "%*o";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_o_octal) {
  unsigned int result = 0, result2 = 0;
  const char *str = "0754";
  const char *format = "%o";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_o_zero) {
  unsigned int result = 0, result2 = 0;
  const char *str = "0";
  const char *format = "%o";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_o_negative_octal) {
  unsigned int result = 0;
  unsigned int result2 = 0;

  const char *str = "-07595";
  const char *format = "%o";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_s_empty_string) {
  char result[SIZE] = "\0", result2[SIZE] = "\0";
  const char *str = "   ";
  const char *format = "%s";
  sscanf(str, format, result2);
  s21_sscanf(str, format, result);
  ck_assert_str_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_string) {
  char result[SIZE] = "\0", result2[SIZE] = "\0";
  const char *str = "Hello, World!";
  const char *format = "%s";
  sscanf(str, format, result2);
  s21_sscanf(str, format, result);
  ck_assert_str_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_string_star) {
  char result[SIZE] = "\0", result2[SIZE] = "\0";
  const char *str = "Hello, World!";
  const char *format = "%*s";
  sscanf(str, format, result2);
  s21_sscanf(str, format, result);
  ck_assert_str_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_s_newline_string) {
  char result[SIZE] = "\0", result2[SIZE] = "\0";
  const char *str = "Hello\nWorld";
  const char *format = "%s";
  sscanf(str, format, result2);
  s21_sscanf(str, format, result);
  ck_assert_str_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_s_with_spaces) {
  char result[SIZE] = "\0", result2[SIZE] = "\0";
  const char *str = "   Hello";
  const char *format = "%s";
  sscanf(str, format, result2);
  s21_sscanf(str, format, result);
  ck_assert_str_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_s_multiple_spaces) {
  char result1[SIZE] = "\0", result2[SIZE] = "\0", result3[SIZE] = "\0",
       result4[SIZE] = "\0";
  const char *str = "Hello   World";
  const char *format = "%s %s";
  sscanf(str, format, result1, result2);
  s21_sscanf(str, format, result3, result4);
  ck_assert_str_eq(result1, result3);
  ck_assert_str_eq(result2, result4);
}
END_TEST
START_TEST(test_sscanf_s_invalid_characters) {
  char result[SIZE] = "\0", result2[SIZE] = "\0";
  const char *str = "Hello!@#1 ";
  const char *format = "%s";
  sscanf(str, format, result2);
  s21_sscanf(str, format, result);
  ck_assert_str_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_u) {
  int result = 0, result2 = 0;
  const char *str = "+31";
  const char *format = "%u";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_u_star) {
  int result = 0, result2 = 0;
  const char *str = "+31";
  const char *format = "%*u";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_u_negative) {
  int result = 0, result2 = 0;
  const char *str = "-31";
  const char *format = "%u";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_x_hexadecimal) {
  unsigned int result = 0, result2 = 0;
  const char *str = "0x1a2B";
  const char *format = "%x";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_x_hexadecimal_star) {
  unsigned int result = 0, result2 = 0;
  const char *str = "0x1a2B";
  const char *format = "%*x";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_x_hexadecimal_with_prefix) {
  unsigned int result = 0, result2 = 0;
  const char *str = "0x1A2B";
  const char *format = "%x";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_x_hexadecimal_positive) {
  unsigned int result = 0, result2 = 0;
  const char *str = "+0x1A2B";
  const char *format = "%x";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_x_invalid_hexadecimal) {
  unsigned int result = 0, result2 = 0;
  const char *str = "G1A2B";
  const char *format = "%x";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_x_negative_hex_number) {
  unsigned int result = 0;
  unsigned int result2 = 0;

  const char *str = "-0x1A2B";
  const char *format = "%x";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_x_zero_hex_number) {
  unsigned int result = 0, result2 = 0;
  const char *str = "0x0";
  const char *format = "%x";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_x_hex_with_space_after_comma) {
  unsigned int result = 0, result2 = 0;
  const char *str = " 0x1A2B , 567 ";
  const char *format = "%x";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_X_hex) {
  unsigned int result = 0, result2 = 0;
  const char *str = " 0x1A2B";
  const char *format = "%X";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_X_hex_negative) {
  unsigned int result = 0, result2 = 0;
  const char *str = "-1E4DC";
  const char *format = "%X";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_int_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_p_pointer) {
  void *result = 0, *result2 = 0;
  const char *str = "0x7ffeFf708";
  const char *format = "%p";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_ptr_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_p_pointer_star) {
  void *result = 0, *result2 = 0;
  const char *str = "0x7ffeFf708";
  const char *format = "%*p";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_ptr_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_p_pointer_2) {
  void *result = 0, *result2 = 0;
  const char *str = "0X7ABCDF708";
  const char *format = "%p";
  sscanf(str, format, &result2);
  s21_sscanf(str, format, &result);
  ck_assert_ptr_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_n) {
  int number = 0, char_read = 0, number2 = 0, char_read2 = 0;
  const char *str = "2313";
  const char *format = "%d%*n";
  sscanf(str, format, &number, &char_read);
  s21_sscanf(str, format, &number2, &char_read2);
  ck_assert_int_eq(number, number2);
  ck_assert_int_eq(char_read, char_read2);
}
END_TEST

START_TEST(test_sscanf_n_star) {
  int number = 0, char_read = 0, number2 = 0, char_read2 = 0;
  const char *str = "2313";
  const char *format = "%d%*n";
  sscanf(str, format, &number, &char_read);
  s21_sscanf(str, format, &number2, &char_read2);
  ck_assert_int_eq(number, number2);
  ck_assert_int_eq(char_read, char_read2);
}
END_TEST

START_TEST(test_sscanf_n_and_s) {
  int number = 0, char_read = 0, number2 = 0, char_read2 = 0;
  char text[SIZE] = "\0", text2[SIZE] = "\0";
  const char *str = "Hello 999";
  const char *format = "%s %d%n";
  sscanf(str, format, text, &number, &char_read);
  s21_sscanf(str, format, text2, &number2, &char_read2);
  ck_assert_int_eq(number, number2);
  ck_assert_int_eq(char_read, char_read2);
}
END_TEST

START_TEST(test_sscanf_empty_format) {
  char result[SIZE] = "\0";
  char result2[SIZE] = "\0";
  const char *str = "Hello, World!";
  const char *format = "";
  sscanf(str, format, result2);
  s21_sscanf(str, format, result);
  ck_assert_str_eq(result, result2);
}
END_TEST

START_TEST(test_sscanf_multiple_formats) {
  int int_result = 0, int_result2 = 0;
  float float_result = 0.0, float_result2 = 0.0;
  const char *str = "123 -123.456";
  const char *format = "%d %f";
  sscanf(str, format, &int_result2, &float_result2);
  s21_sscanf(str, format, &int_result, &float_result);
  ck_assert_int_eq(int_result, int_result2);
  ck_assert_float_eq(float_result, float_result2);
}
END_TEST

START_TEST(test_sscanf_min_len) {
  int int_result = 0, int_result2 = 0;
  const char *str = "123";
  const char *format = "%15d";
  sscanf(str, format, &int_result2);
  s21_sscanf(str, format, &int_result);
  ck_assert_int_eq(int_result, int_result2);
}
END_TEST
START_TEST(test_sscanf_ignor) {
  int result1 = 0, result2 = 0;
  const char *str = "24 30";
  sscanf(str, "%d %*d", &result1);
  s21_sscanf(str, "%d %*d", &result2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_sscanf_short_int) {
  short int result1 = 0, result2 = 0;
  const char *str = "123";
  sscanf(str, "%hd", &result1);
  s21_sscanf(str, "%hd", &result2);
  ck_assert_int_eq(result1, result2);
}
END_TEST
START_TEST(test_sscanf_long_int) {
  long int result = 0, result2 = 0;
  const char *str = "1234567890";
  sscanf(str, "%ld", &result);
  s21_sscanf(str, "%ld", &result2);
  ck_assert_int_eq(result, result2);
}
END_TEST
START_TEST(test_sscanf_long_str) {
  int result1[SIZE] = L"\0", result2[SIZE] = L"\0";
  char *str = "Hello!";
  int count1 = 0, count2 = 0;
  sscanf(str, "%ls", result1);
  s21_sscanf(str, "%ls", result2);
  for (int i = 0; result1[i] != '\0'; i++) {
    count1++;
  }
  for (int i = 0; result2[i] != '\0'; i++) {
    count2++;
  }
  ck_assert_int_eq(count1, count2);
}
END_TEST
START_TEST(test_sscanf_long_char) {
  unsigned int result1 = 0, result2 = 0;
  char *str = "H";
  sscanf(str, "%lc", &result1);
  s21_sscanf(str, "%lc", &result2);
  ck_assert_uint_eq(result1, result2);
}
END_TEST
START_TEST(test_sscanf_long_char_clear) {
  unsigned int result1 = 0, result2 = 0;
  char *str = "        ";
  sscanf(str, "%lc", &result1);
  s21_sscanf(str, "%lc", &result2);
  ck_assert_uint_eq(result1, result2);
}
END_TEST
START_TEST(test_sscanf_long_double) {
  long double result1 = 0, result2 = 0;
  const char *str = "123.45678901266";
  sscanf(str, "%Lf", &result1);
  s21_sscanf(str, "%Lf", &result2);
  ck_assert_double_eq(result1, result2);
}
END_TEST
START_TEST(test_sscanf_unsigned_long) {
  unsigned long int result1 = 0, result2 = 0;
  const char *str = "1234567890";
  sscanf(str, "%lu", &result1);
  s21_sscanf(str, "%lu", &result2);
  ck_assert_uint_eq(result1, result2);
}
END_TEST
START_TEST(test_sscanf_unsigned_short) {
  unsigned short int result1 = 0, result2 = 0;
  const char *str = "12";
  sscanf(str, "%hu", &result1);
  s21_sscanf(str, "%hu", &result2);
  ck_assert_uint_eq(result1, result2);
}
END_TEST

Suite *create_test_suite() {
  Suite *suite = suite_create("String+ tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memchr);
  tcase_add_test(tc_core, test_memchr_empty_str);
  tcase_add_test(tc_core, test_memchr_n_less_str);
  tcase_add_test(tc_core, test_memchr_not_found_in_n);
  tcase_add_test(tc_core, test_memchr_null_terminator);

  tcase_add_test(tc_core, test_memcpy_second_less);
  tcase_add_test(tc_core, test_memcpy_second_more);
  tcase_add_test(tc_core, test_memcpy_eq_str);
  tcase_add_test(tc_core, test_memcpy_big_n);
  tcase_add_test(tc_core, test_memcpy_second_str_null_term);
  tcase_add_test(tc_core, test_memcpy_second_str_zero_n);
  tcase_add_test(tc_core, test_memcpy_second_str_term_null);
  tcase_add_test(tc_core, test_memcpy_second_str_term_null_num);

  tcase_add_test(tc_core, test_memset_null_terminator);
  tcase_add_test(tc_core, test_memset_str_eq);

  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcmp_first_less_second);
  tcase_add_test(tc_core, test_memcmp_first_more_second);
  tcase_add_test(tc_core, test_memcmp_eq_n);
  tcase_add_test(tc_core, test_memcmp_n_large);
  tcase_add_test(tc_core, test_memcmp_n_less_str);

  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strncat_first_empty_str);
  tcase_add_test(tc_core, test_strncat_two_empty_str);

  tcase_add_test(tc_core, test_strchr_empty_str);
  tcase_add_test(tc_core, test_strchr_found_end);
  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strchr_not_found);
  tcase_add_test(tc_core, test_strchr_null_terminator);
  tcase_add_test(tc_core, test_strchr_find_null_terminator);

  tcase_add_test(tc_core, test_strrchr_empty_str);
  tcase_add_test(tc_core, test_strrchr_str_A);
  tcase_add_test(tc_core, test_strrchr_str_a);
  tcase_add_test(tc_core, test_strrchr_null_terminator);
  tcase_add_test(tc_core, test_strrchr_null_terminator_one);
  tcase_add_test(tc_core, test_strrchr_null_terminator_two);
  tcase_add_test(tc_core, test_strrchr_null_terminator_three);
  tcase_add_test(tc_core, test_strrchr_null_terminator_four);
  tcase_add_test(tc_core, test_strrchr_null_terminator_five);
  tcase_add_test(tc_core, test_strrchr_null_terminator_six);

  tcase_add_test(tc_core, test_strncmp_first_str_big);
  tcase_add_test(tc_core, test_strncmp_second_str_big);
  tcase_add_test(tc_core, test_strncmp_null_terminator);
  tcase_add_test(tc_core, test_strncmp_str_eq);

  tcase_add_test(tc_core, test_strncpy_overwrite_null_terminator);
  tcase_add_test(tc_core, test_strncpy_src_less_n);
  tcase_add_test(tc_core, test_strncpy);

  tcase_add_test(tc_core, test_strcspn_one_symbol);
  tcase_add_test(tc_core, test_strcspn_two_symbol);
  tcase_add_test(tc_core, test_strcspn_zero);

  tcase_add_test(tc_core, test_strerror_negative);
  tcase_add_test(tc_core, test_strerror_positive);
  tcase_add_test(tc_core, test_strerror_zero);
  tcase_add_test(tc_core, test_strerror_offside);

  tcase_add_test(tc_core, test_strlen);
  tcase_add_test(tc_core, test_strlen_empty_str);

  tcase_add_test(tc_core, test_strpbrk_first_empty_str);
  tcase_add_test(tc_core, test_strpbrk_two_empty_str);
  tcase_add_test(tc_core, test_strpbrk);
  tcase_add_test(tc_core, test_strpbrk_not_found);

  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strstr_not_found);
  tcase_add_test(tc_core, test_strstr_second_empty_str);

  tcase_add_test(tc_core, test_strstr_two_empty_str_full);
  tcase_add_test(tc_core, test_strstr_two_empty_str_one_word);
  tcase_add_test(tc_core, test_strstr_two_empty_str_specify);
  tcase_add_test(tc_core, test_strstr_two_empty_str_testing_word);
  tcase_add_test(tc_core, test_strstr_two_empty_str_susping_work);

  tcase_add_test(tc_core, test_strtok_empty_delim);
  tcase_add_test(tc_core, test_strtok_not_found_delim);
  tcase_add_test(tc_core, test_strtok_null);
  tcase_add_test(tc_core, test_strtok);

  tcase_add_test(tc_core, test_to_upper);
  tcase_add_test(tc_core, test_to_upper_empty_str);
  tcase_add_test(tc_core, test_to_upper_not_char_str);

  tcase_add_test(tc_core, test_to_lower);
  tcase_add_test(tc_core, test_to_lower_empty_str);
  tcase_add_test(tc_core, test_to_lower_not_char_str);

  tcase_add_test(tc_core, test_insert);
  tcase_add_test(tc_core, test_insert_zero);
  tcase_add_test(tc_core, test_insert_two_null);
  tcase_add_test(tc_core, test_insert_second_null);
  tcase_add_test(tc_core, test_insert_empty_str);
  tcase_add_test(tc_core, test_insert_in_start);
  tcase_add_test(tc_core, test_insert_return_null);
  tcase_add_test(tc_core, test_insert_substring_empty);

  tcase_add_test(tc_core, test_trim);
  tcase_add_test(tc_core, test_trim_empty_str);
  tcase_add_test(tc_core, test_trim_all_delete);
  tcase_add_test(tc_core, test_trim_empty_all_str);
  tcase_add_test(tc_core, test_trim_empty_null_str);
  tcase_add_test(tc_core, test_trim_empty_str_secnod_empty);

  tcase_add_test(tc_core, test_specifier_c);
  tcase_add_test(tc_core, test_specifier_d);
  tcase_add_test(tc_core, test_specifier_d_zero);
  tcase_add_test(tc_core, test_specifier_i);
  tcase_add_test(tc_core, test_specifier_e);
  tcase_add_test(tc_core, test_specifier_E);
  tcase_add_test(tc_core, test_specifier_f);
  tcase_add_test(tc_core, test_specifier_g);
  tcase_add_test(tc_core, test_specifier_G);
  tcase_add_test(tc_core, test_specifier_o);
  tcase_add_test(tc_core, test_specifier_s);
  tcase_add_test(tc_core, test_specifier_u);
  tcase_add_test(tc_core, test_specifier_x);
  tcase_add_test(tc_core, test_specifier_X);
  tcase_add_test(tc_core, test_specifier_p);
  tcase_add_test(tc_core, test_specifier_n);

  tcase_add_test(tc_core, test_flag_minus_d);
  tcase_add_test(tc_core, test_flag_plus_f);
  tcase_add_test(tc_core, test_flag_plus_d);
  tcase_add_test(tc_core, test_flag_space_g);
  tcase_add_test(tc_core, test_flag_space_minus_g);
  tcase_add_test(tc_core, test_flag_sharp_o);
  tcase_add_test(tc_core, test_flag_sharp_x);
  tcase_add_test(tc_core, test_flag_sharp_e);
  tcase_add_test(tc_core, test_flag_sharp_f);
  tcase_add_test(tc_core, test_flag_sharp_g);
  tcase_add_test(tc_core, test_flag_zero_with_width_g);

  tcase_add_test(tc_core, test_width_eq_zero_x);
  tcase_add_test(tc_core, test_width_g);
  tcase_add_test(tc_core, test_width_variable_E);

  tcase_add_test(tc_core, test_accuracy_d);
  tcase_add_test(tc_core, test_accuracy_o);
  tcase_add_test(tc_core, test_accuracy_u);
  tcase_add_test(tc_core, test_accuracy_f);
  tcase_add_test(tc_core, test_accuracy_g);
  tcase_add_test(tc_core, test_accuracy_s);
  tcase_add_test(tc_core, test_accuracy_with_variable_X);

  tcase_add_test(tc_core, test_length_h_i);
  tcase_add_test(tc_core, test_length_h_d);
  tcase_add_test(tc_core, test_length_h_o);
  tcase_add_test(tc_core, test_length_h_u);
  tcase_add_test(tc_core, test_length_h_x);
  tcase_add_test(tc_core, test_length_h_X);

  tcase_add_test(tc_core, test_length_l_i);
  tcase_add_test(tc_core, test_length_ll_d);
  tcase_add_test(tc_core, test_length_ll_o);
  tcase_add_test(tc_core, test_length_ll_u);
  tcase_add_test(tc_core, test_length_ll_x);
  tcase_add_test(tc_core, test_length_ll_X);
  tcase_add_test(tc_core, test_length_l_d);
  tcase_add_test(tc_core, test_length_l_o);
  tcase_add_test(tc_core, test_length_l_u);
  tcase_add_test(tc_core, test_length_l_x);
  tcase_add_test(tc_core, test_length_l_X);
  tcase_add_test(tc_core, test_length_l_c);
  tcase_add_test(tc_core, test_length_l_s);

  tcase_add_test(tc_core, test_length_L_e);
  tcase_add_test(tc_core, test_length_L_E);
  tcase_add_test(tc_core, test_length_L_f);
  tcase_add_test(tc_core, test_length_L_g);
  tcase_add_test(tc_core, test_length_L_G);

  tcase_add_test(tc_core, test_length_l_f_positive_inf);
  tcase_add_test(tc_core, test_length_l_f_negative_inf);

  tcase_add_test(tc_core, test_combo_flags_width_accuracy_length_f);
  tcase_add_test(tc_core, test_combo_flags_width_length_f);
  tcase_add_test(tc_core, test_combo_flags_accuracy_length_f);
  tcase_add_test(tc_core, test_combo_flags_length_f);
  tcase_add_test(tc_core, test_combo_length_character);
  tcase_add_test(tc_core, test_combo_character);
  tcase_add_test(tc_core, test_combo_flags_character);
  tcase_add_test(tc_core, test_combo_width_acccuracy_character);
  tcase_add_test(tc_core, test_combo_width_acccuracy_length_character);
  tcase_add_test(tc_core, test_combo_width_character);

  tcase_add_test(tc_core, test_all_specifiers);
  tcase_add_test(tc_core, test_all_specifiers_with_flags);
  tcase_add_test(tc_core, test_all_specifiers_with_width);
  tcase_add_test(tc_core, test_all_specifiers_with_accuracy);
  tcase_add_test(tc_core, test_all_specifiers_with_length);

  tcase_add_test(tc_core, test_sscanf_char);
  tcase_add_test(tc_core, test_sscanf_char_star);

  tcase_add_test(tc_core, test_sscanf_decimal);
  tcase_add_test(tc_core, test_sscanf_d_count);
  tcase_add_test(tc_core, test_sscanf_d_negative);
  tcase_add_test(tc_core, test_sscanf_d_zero);
  tcase_add_test(tc_core, test_sscanf_d_zero_in_start);
  tcase_add_test(tc_core, test_sscanf_d_invalid_number);
  tcase_add_test(tc_core, test_sscanf_d_dash_in_number);
  tcase_add_test(tc_core, test_sscanf_d_spaces_before_and_after_number);
  tcase_add_test(tc_core, test_sscanf_d_number_in_single_quotes);
  tcase_add_test(tc_core, test_sscanf_d_in_double_quotes);
  tcase_add_test(tc_core, test_sscanf_d_in_single_quotes);
  tcase_add_test(tc_core, test_sscanf_number_in_brackets);
  tcase_add_test(tc_core, test_sscanf_d_with_comma);
  tcase_add_test(tc_core, test_sscanf_d_with_dot_and_negative);

  tcase_add_test(tc_core, test_sscanf_i_negative);
  tcase_add_test(tc_core, test_sscanf_i_negative_star);
  tcase_add_test(tc_core, test_sscanf_i_positive);
  tcase_add_test(tc_core, test_sscanf_i_hexadecimal);
  tcase_add_test(tc_core, test_sscanf_i_octal);
  tcase_add_test(tc_core, test_sscanf_i_hex);
  tcase_add_test(tc_core, test_sscanf_i_not_exist);

  tcase_add_test(tc_core, test_sscanf_e);
  tcase_add_test(tc_core, test_sscanf_e_star);

  tcase_add_test(tc_core, test_sscanf_E);
  tcase_add_test(tc_core, test_sscanf_E_positive);

  tcase_add_test(tc_core, test_sscanf_f_with_exp_comma_and_space);
  tcase_add_test(tc_core, test_sscanf_float_negative);
  tcase_add_test(tc_core, test_sscanf_f_exponential);
  tcase_add_test(tc_core, test_sscanf_f_positive);
  tcase_add_test(tc_core, test_sscanf_f_space_in_start);
  tcase_add_test(tc_core, test_sscanf_f_zero_exponential);
  tcase_add_test(tc_core, test_sscanf_f_spaces_around_comma);
  tcase_add_test(tc_core, test_sscanf_f_space_around_percent);
  tcase_add_test(tc_core, test_sscanf_f_percent);

  tcase_add_test(tc_core, test_sscanf_g_negative);
  tcase_add_test(tc_core, test_sscanf_g_positive);

  tcase_add_test(tc_core, test_sscanf_G_positive);
  tcase_add_test(tc_core, test_sscanf_G);

  tcase_add_test(tc_core, test_sscanf_o_decimal);
  tcase_add_test(tc_core, test_sscanf_o_decimal_star);
  tcase_add_test(tc_core, test_sscanf_o_octal);
  tcase_add_test(tc_core, test_sscanf_o_zero);
  tcase_add_test(tc_core, test_sscanf_o_negative_octal);

  tcase_add_test(tc_core, test_sscanf_s_empty_string);
  tcase_add_test(tc_core, test_sscanf_string);
  tcase_add_test(tc_core, test_sscanf_string_star);
  tcase_add_test(tc_core, test_sscanf_s_newline_string);
  tcase_add_test(tc_core, test_sscanf_s_with_spaces);
  tcase_add_test(tc_core, test_sscanf_s_multiple_spaces);
  tcase_add_test(tc_core, test_sscanf_s_invalid_characters);

  tcase_add_test(tc_core, test_sscanf_u);
  tcase_add_test(tc_core, test_sscanf_u_star);
  tcase_add_test(tc_core, test_sscanf_u_negative);

  tcase_add_test(tc_core, test_sscanf_x_hexadecimal);
  tcase_add_test(tc_core, test_sscanf_x_hexadecimal_star);
  tcase_add_test(tc_core, test_sscanf_x_hexadecimal_with_prefix);
  tcase_add_test(tc_core, test_sscanf_x_invalid_hexadecimal);
  tcase_add_test(tc_core, test_sscanf_x_hexadecimal_positive);
  tcase_add_test(tc_core, test_sscanf_x_negative_hex_number);
  tcase_add_test(tc_core, test_sscanf_x_zero_hex_number);
  tcase_add_test(tc_core, test_sscanf_x_hex_with_space_after_comma);

  tcase_add_test(tc_core, test_sscanf_X_hex);
  tcase_add_test(tc_core, test_sscanf_X_hex_negative);

  tcase_add_test(tc_core, test_sscanf_p_pointer);
  tcase_add_test(tc_core, test_sscanf_p_pointer_star);
  tcase_add_test(tc_core, test_sscanf_p_pointer_2);

  tcase_add_test(tc_core, test_sscanf_n);
  tcase_add_test(tc_core, test_sscanf_n_star);
  tcase_add_test(tc_core, test_sscanf_n_and_s);

  tcase_add_test(tc_core, test_sscanf_empty_format);
  tcase_add_test(tc_core, test_sscanf_multiple_formats);
  tcase_add_test(tc_core, test_sscanf_min_len);
  tcase_add_test(tc_core, test_sscanf_ignor);

  tcase_add_test(tc_core, test_sscanf_short_int);
  tcase_add_test(tc_core, test_sscanf_long_int);
  tcase_add_test(tc_core, test_sscanf_long_str);
  tcase_add_test(tc_core, test_sscanf_long_char);
  tcase_add_test(tc_core, test_sscanf_long_char_clear);
  tcase_add_test(tc_core, test_sscanf_long_double);
  tcase_add_test(tc_core, test_sscanf_unsigned_long);
  tcase_add_test(tc_core, test_sscanf_unsigned_short);
  tcase_add_test(tc_core, test_sscanf_d_count_2);

  suite_add_tcase(suite, tc_core);

  return suite;
}

int main() {
  int number_failed;
  SRunner *sr;

  Suite *suite = create_test_suite();
  sr = srunner_create(suite);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
