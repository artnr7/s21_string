#include <stdlib.h>

#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  s21_size_t str_length = s21_strlen(str);
  char *ptr = S21_NULL;
  if (str_length == 0) {
    ptr = malloc(1);
    if (ptr != S21_NULL) {
      ptr[0] = '\0';
    }
  } else {
    ptr = malloc(str_length + 1);
  }
  if (ptr != S21_NULL && str_length != 0) {
    char *temp_ptr = ptr;
    while (*str != '\0') {
      if (*str >= 97 && *str <= 122) {
        *temp_ptr++ = *str++ - 32;
      } else {
        *temp_ptr++ = *str++;
      }
    }
    *temp_ptr = '\0';
  }
  return ptr;
}

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  s21_size_t str_length = s21_strlen(str);
  char *ptr = S21_NULL;
  if (str_length == 0) {
    ptr = malloc(1);
    if (ptr != S21_NULL) {
      ptr[0] = '\0';
    }
  } else {
    ptr = malloc(str_length + 1);
  }
  if (ptr != S21_NULL && str_length != 0) {
    char *temp_ptr = ptr;
    while (*str != '\0') {
      if (*str >= 65 && *str <= 90) {
        *temp_ptr++ = *str++ + 32;
      } else {
        *temp_ptr++ = *str++;
      }
    }
    *temp_ptr = '\0';
  }
  return ptr;
}
void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL) return S21_NULL;
  int stop = 0;
  int left = 0;
  for (; src[left] != '\0' && !stop; left++) {
    int count = 0;
    for (int j = 0; trim_chars[j] != '\0'; j++) {
      if (src[left] == trim_chars[j] || src[left] == ' ') {
        count++;
      }
    }
    if (count == 0) {
      stop = 1;
    }
  }
  left--;
  int len = s21_strlen(src);
  int right = len == 0 ? 0 : len - 1;
  stop = 0;

  for (; right >= 0 && !stop && left != right; right--) {
    int count = 0;
    for (int j = 0; trim_chars[j] != '\0'; j++) {
      if (src[right] == trim_chars[j] || src[right] == ' ') {
        count++;
      }
    }
    if (count == 0) {
      stop = 1;
    }
  }
  if (left != right) {
    right++;
  }
  char *str = malloc(right - left + 2);
  if (str != S21_NULL && left != right) {
    int j = 0;
    for (int i = left; i <= right; i++) {
      str[j] = src[i];
      j++;
    }
    str[j] = '\0';
  } else
    str[0] = '\0';
  return str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) return S21_NULL;
  s21_size_t cntr = 0, srcind = 0, strind = 0, src_length = s21_strlen(src),
             str_length = s21_strlen(str);
  char *ptr = S21_NULL;
  if (src_length >= start_index) {
    if (src_length + str_length == 0) {
      ptr = malloc(1);
      if (ptr != S21_NULL) {
        ptr[0] = '\0';
      }
    } else {
      ptr = malloc(src_length + str_length + 1);
    }
    if (ptr != S21_NULL && src_length + str_length != 0) {
      char *temp_ptr = ptr;
      while (cntr < start_index) {
        temp_ptr[cntr] = src[srcind];
        cntr++;
        srcind++;
      }
      while (str[strind] != '\0') {
        temp_ptr[cntr] = str[strind];
        strind++;
        cntr++;
      }
      while (src[srcind] != '\0') {
        temp_ptr[cntr] = src[srcind];
        srcind++;
        cntr++;
      }
      temp_ptr[cntr] = '\0';
    }
  }

  return ptr;
}
