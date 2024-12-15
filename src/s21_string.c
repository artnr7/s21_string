#include "s21_string.h"

void s21_swapc(char *lhs, char *rhs) {
  char temp = *lhs;
  *lhs = *rhs;
  *rhs = temp;
}

void s21_reverse_str(char *start, char *end) {
  while (start < end) {
    s21_swapc(start++, end--);
  }
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const char *ptr = str;
  ptr++;
  ptr--;
  int found = 0;
  s21_size_t cntr = 0;
  while (!found && cntr < n) {
    if (*ptr == c) {
      found = 1;
    }
    if (found == 0) {
      ptr++;
    }
    cntr++;
  }
  if (found == 0) {
    ptr = S21_NULL;
  }
  return (void *)ptr;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *ptr1 = (const unsigned char *)str1;
  const unsigned char *ptr2 = (const unsigned char *)str2;
  s21_size_t cntr = 0;
  int flag = 0;
  while (*ptr1 == *ptr2 && cntr < n) {
    ptr1++;
    ptr2++;
    cntr++;
    flag = 1;
  }
  if (cntr == n && flag) {
    ptr1--;
    ptr2--;
  }
  return *ptr1 - *ptr2;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dst = (char *)dest;
  const char *sc = (const char *)src;
  s21_size_t cntr = 0;
  while (cntr < n) {
    dst[cntr] = sc[cntr];
    cntr++;
  }
  return (void *)dst;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  s21_size_t cntr = 0;
  while (cntr < n) {
    ptr[cntr++] = c;
  }
  return (void *)ptr;
}

void *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t cntr = 0, src_len = s21_strlen(src);
  if (src_len > n) {
    src_len = n;
  }
  while (dest[cntr] != '\0') {
    cntr++;
  }
  s21_size_t src_cntr = 0;
  while (*src != '\0' && src_cntr < src_len) {
    dest[cntr++] = src[src_cntr++];
  }
  dest[cntr] = '\0';
  return (void *)dest;
}

char *s21_strchr(const char *str, int c) {
  int flag = 1;
  char *sym = S21_NULL;
  while (*str != '\0' && flag) {
    if (*str == c) {
      sym = (char *)str;
      flag = 0;
    }
    str++;
  }
  str--;
  if (*(str + 1) == '\0' && c == '\0') {
    sym = (char *)(str + 1);
  }
  return sym;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t cntr = 1;
  while (*str1 && (*str1 == *str2) && cntr < n) {
    str1++;
    str2++;
    cntr++;
  }
  return *str1 - *str2;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t cntr = 0, src_len = s21_strlen(src);
  if (src_len > n) {
    src_len = n;
  }
  while (cntr < src_len) {
    dest[cntr] = src[cntr];
    cntr++;
  }
  if (src_len < n) {
    while (cntr < n) {
      dest[cntr] = '\0';
      cntr++;
    }
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int flag = 1, cntr = 0;
  while (flag && str1[cntr] != '\0') {
    int i = 0;
    while (flag && str2[i] != '\0') {
      if (str1[cntr] == str2[i++]) flag = 0;
    }
    if (flag) {
      cntr++;
    }
  }
  return cntr;
}

char *s21_strerror(int errnum) {
  static char *errors_arr[SIZE_OF_ERROR_LIST] = ERROR_LIST;
  static char result_error[1024];
  int is_negative = 0;

  if (errnum >= 0 && errnum < SIZE_OF_ERROR_LIST) {
    s21_strncpy(result_error, errors_arr[errnum],
                s21_strlen(errors_arr[errnum]) + 1);
  } else {
    s21_strncpy(result_error, UNKNOWN, s21_strlen(UNKNOWN));

    if (errnum < 0) {
      is_negative = 1;
      errnum = -errnum;
    }

    char *result_error_ptr = result_error;
    char *result_error_begin_ptr = result_error;
    while (*result_error_ptr) {
      result_error_ptr++;
      result_error_begin_ptr++;
    }
    do {
      *result_error_ptr++ = (errnum % 10) + '0';
      errnum /= 10;
    } while (errnum > 0);

    if (is_negative) {
      *result_error_ptr++ = '-';
    }
    *result_error_ptr = '\0';

    s21_reverse_str(result_error_begin_ptr, result_error_ptr - 1);
  }

  return result_error;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t cntr = 0;
  while (str[cntr] != '\0') {
    cntr++;
  }
  return cntr;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  int flag = 1;
  const char *ch;
  while (flag && *str1 != '\0') {
    int i = 0;
    while (flag && str2[i] != '\0') {
      if (*str1 == str2[i]) {
        flag = 0;
        ch = str1;
      }
      i++;
    }
    str1++;
  }
  if (flag) {
    ch = S21_NULL;
  }
  return (char *)ch;
}

void *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;

  const char *last_ch = S21_NULL;
  char ch = (char)c;

  while (*str != '\0') {
    if (*str == ch) {
      last_ch = (char *)str;
    }
    str++;
  }
  if (ch == '\0') {
    result = (char *)str;
  } else {
    result = (char *)last_ch;
  }

  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  int flag = 1;
  if (*needle == '\0') {
    result = (char *)haystack;
    flag = 0;
  } else if (*haystack == '\0') {
    result = S21_NULL;
    flag = 0;
  }

  if (*needle != '\0' && *haystack != '\0' && flag) {
    while (*haystack && flag) {
      const char *str1 = haystack;
      const char *str2 = needle;
      while (*str2 && (*str1 == *str2)) {
        str1++;
        str2++;
      }
      if (*str2 == '\0') {
        result = (char *)haystack;
        flag = 0;
      }
      haystack++;
    }
  }
  return result;
}

char *s21_strtok(char *s, const char *delim) {
  static char *end_s = S21_NULL;
  char *result = S21_NULL;

  if (s == S21_NULL) {
    s = end_s;
  }

  while (s && *s && s21_strchr(delim, *s)) {
    s++;
  }

  if (s == S21_NULL || *s == '\0') {
    end_s = S21_NULL;
    result = S21_NULL;
  } else {
    result = s;
    while (*s && !s21_strchr(delim, *s)) {
      s++;
    }
    if (*s != '\0') {
      *s = '\0';
      end_s = s + 1;
    } else {
      end_s = S21_NULL;
    }
  }
  return result;
}
