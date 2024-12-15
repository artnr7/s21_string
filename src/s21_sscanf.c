#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list vars;
  flags_spec fs = {0, 0, 0, 0};
  va_start(vars, format);
  fs.count = 0;
  int flag = 0;
  const char *begin_str_ptr = str;
  while (*format && !flag) {
    while (*format == ' ') format++;
    if (*format == '%') {
      format = flags(&fs, format);
      if (*format == 'o') {
        str = format_o(str, vars, &fs);
      } else if (*format == 'i') {
        str = format_i(str, vars, &fs);
      } else if (*format == 'd') {
        str = format_d(str, vars, &fs);
      } else if (*format == 'f' || *format == 'e' || *format == 'E' ||
                 *format == 'g' || *format == 'G') {
        str = format_efg(str, vars, &fs);
      } else if (*format == 's') {
        str = format_s(str, vars, &fs);
      } else if (*format == 'c') {
        str = format_c(str, vars, &fs);
      } else if (*format == 'u') {
        str = format_u(str, vars, &fs);
      } else if (*format == 'x' || *format == 'X') {
        str = format_x(str, vars, &fs);
      } else if (*format == 'p') {
        str = format_p(str, vars, &fs);
      } else if (*format == 'n') {
        format_n(vars, &fs, begin_str_ptr, str);
      }
      format++;
    } else {
      if (*str == *format) {
        str++;
        format++;
      } else {
        flag = 1;
      }
    }
  }
  va_end(vars);
  return fs.count;
}

const char *format_o(const char *str, va_list vars, flags_spec *fs) {
  while (*str == ' ') str++;
  int width_count = 0;
  int sign = sign_value(&str, &width_count);
  long unsigned int number = 0;
  while (*str >= '0' && *str <= '7' &&
         (width_count++ < fs->width || fs->width == -1)) {
    number = number * 8 + (*str - '0');
    str++;
  }
  fs->width = -1;
  number = number * sign;
  if (!fs->star) {
    unsigned_int_len(number, vars, fs);
  } else {
    fs->star = 0;
  }
  fs->count++;
  return str;
}

const char *format_i(const char *str, va_list vars, flags_spec *fs) {
  int width_count = 0;
  while (*str == ' ') str++;
  int sign = sign_value(&str, &width_count);
  int base = 10;
  if (*str == '0') {
    str++;
    width_count++;
    if (*str == 'x' || *str == 'X') {
      base = 16;
      str++;
      width_count++;
    } else {
      base = 8;
    }
  }
  int number = 0, flag = 0;
  while ((width_count++ < fs->width || fs->width == -1) && !flag &&
         ((*str >= '0' && *str <= '9') ||
          (base == 16 &&
           ((*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F'))))) {
    if (*str >= '0' && *str <= '9') {
      number = number * base + (*str - '0');
    } else if (*str >= 'a' && *str <= 'f') {
      number = number * base + (*str - 'a' + 10);
    } else if (*str >= 'A' && *str <= 'F') {
      number = number * base + (*str - 'A' + 10);
    }
    str++;
  }
  int value = sign * number;
  fs->width = -1;
  if (!fs->star) {
    int_len(value, vars, fs);
  } else {
    fs->star = 0;
  }
  fs->count++;
  return str;
}

const char *format_d(const char *str, va_list vars, flags_spec *fs) {
  int width_count = 0;
  while (*str == ' ') {
    str++;
  }
  int sign = sign_value(&str, &width_count);
  int number = 0;
  while (*str >= '0' && *str <= '9' &&
         (width_count++ < fs->width || fs->width == -1)) {
    number = number * 10 + (*str - '0');
    str++;
  }
  int value = sign * number;
  fs->width = -1;
  if (!fs->star) {
    int_len(value, vars, fs);
  } else {
    fs->star = 0;
  }
  fs->count++;
  return str;
}

const char *format_efg(const char *str, va_list vars, flags_spec *fs) {
  int width_count = 0;
  while (*str == ' ') str++;
  int sign = sign_value(&str, &width_count);
  double number = 0.0, fraction = 0.0, divisor = 10.0;
  int is_fraction = 0, exponent = 0, exp_sign = 1, flag = 0;
  str = cycle_efg(str, &width_count, &flag, &is_fraction, &number, &fraction,
                  &divisor, fs);
  if (*str == 'e' || *str == 'E') {
    str++;
    if (*str == '-') {
      exp_sign = -1;
      str++;
    } else if (*str == '+')
      str++;
    while (*str >= '0' && *str <= '9') {
      exponent = exponent * 10 + (*str - '0');
      str++;
    }
  }
  double result = sign * (number + fraction);
  if (exponent != 0) {
    int n = exp_sign * exponent;
    if (n > 0) {
      for (int i = 0; i < n; i++) result *= 10;
    } else if (n < 0) {
      for (int i = 0; i < -n; i++) result /= 10;
    }
  }
  fs->width = -1;
  if (!fs->star) {
    if (fs->len == 'L') {
      long double *dbl_ptr = va_arg(vars, long double *);
      *dbl_ptr = (long double)result;
      fs->len = 0;
    } else {
      float *dbl_ptr = va_arg(vars, float *);
      *dbl_ptr = (float)result;
      fs->len = 0;
    }
  } else {
    fs->star = 0;
  }
  fs->count++;
  return str;
}

const char *format_u(const char *str, va_list vars, flags_spec *fs) {
  int width_count = 0;
  while (*str == ' ') str++;
  int sign = sign_value(&str, &width_count);
  int number = 0;
  while (*str >= '0' && *str <= '9' &&
         (width_count++ < fs->width || fs->width == -1)) {
    number = number * 10 + (*str - '0');
    str++;
  }
  int value = sign * number;
  fs->width = -1;
  if (!fs->star) {
    unsigned_int_len(value, vars, fs);
  } else {
    fs->star = 0;
  }
  fs->count++;
  return str;
}

const char *format_x(const char *str, va_list vars, flags_spec *fs) {
  while (*str == ' ') str++;
  unsigned int number = 0;
  int width_count = 0;
  int sign = sign_value(&str, &width_count);
  if (*str == '0') {
    str++;
    width_count++;
    if (*str == 'x' || *str == 'X') {
      width_count++;
      str++;
    }
  }
  while ((width_count++ < fs->width || fs->width == -1) &&
         ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f') ||
          (*str >= 'A' && *str <= 'F'))) {
    if (*str >= '0' && *str <= '9') {
      number = number * 16 + (*str - '0');
    } else if (*str >= 'a' && *str <= 'f') {
      number = number * 16 + (*str - 'a' + 10);
    } else if (*str >= 'A' && *str <= 'F') {
      number = number * 16 + (*str - 'A' + 10);
    }
    str++;
  }
  fs->width = -1;
  number = number * sign;
  if (!fs->star) {
    unsigned_int_len(number, vars, fs);
  } else {
    fs->star = 0;
  }
  fs->count++;
  return str;
}

const char *format_p(const char *str, va_list vars, flags_spec *fs) {
  while (*str == ' ') str++;
  int width_count = 0;
  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
    width_count += 2;
  }
  unsigned long long address = 0;
  while ((width_count++ < fs->width || fs->width == -1) &&
         ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f') ||
          (*str >= 'A' && *str <= 'F'))) {
    if (*str >= '0' && *str <= '9') {
      address = address * 16 + (*str - '0');
    } else if (*str >= 'a' && *str <= 'f') {
      address = address * 16 + (*str - 'a' + 10);
    } else if (*str >= 'A' && *str <= 'F') {
      address = address * 16 + (*str - 'A' + 10);
    }
    str++;
  }
  fs->width = -1;
  if (!fs->star) {
    void **ptr = va_arg(vars, void **);
    *ptr = (void *)address;
  } else {
    fs->star = 0;
  }
  fs->count++;
  return str;
}

const char *format_s(const char *str, va_list vars, flags_spec *fs) {
  int width_count = 0;
  while (*str == ' ') str++;
  if (!fs->star) {
    if (fs->len == 'l') {
      int *str_ptr = va_arg(vars, int *);
      while (*str && *str != ' ' && *str != '\n' &&
             (width_count++ < fs->width || fs->width == -1)) {
        *str_ptr++ = *str++;
      }
      *str_ptr = '\0';
      fs->len = 0;
    } else {
      char *str_ptr = va_arg(vars, char *);
      while (*str && *str != ' ' && *str != '\n' &&
             (width_count++ < fs->width || fs->width == -1)) {
        *str_ptr++ = *str++;
      }
      *str_ptr = '\0';
      fs->len = 0;
    }
    fs->width = -1;
  } else {
    fs->star = 0;
  }
  fs->count++;
  return str;
}

const char *format_c(const char *str, va_list vars, flags_spec *fs) {
  int width_count = 0;
  if (!fs->star) {
    if (fs->len == 'l') {
      int *char_ptr = va_arg(vars, int *);
      *char_ptr = *str++;
      fs->len = 0;
    } else {
      char *char_ptr = va_arg(vars, char *);
      *char_ptr = *str++;
    }
    width_count++;
  } else {
    str++;
    fs->star = 0;
  }
  fs->width = -1;
  fs->count++;
  return str;
}

void format_n(va_list vars, flags_spec *fs, const char *begin_str,
              const char *str) {
  if (!fs->star) {
    int *int_ptr = va_arg(vars, int *);
    *int_ptr = str - begin_str;
  } else {
    fs->star = 0;
  }
  fs->count++;
}

const char *flags(flags_spec *fs, const char *format) {
  format++;
  if (*format == '*') {
    fs->star = 1;
    format++;
  }
  fs->width = -1;
  if (*format >= '1' && *format <= '9') {
    fs->width = *format - '0';
    format++;
    while (*format >= '1' && *format <= '9') {
      fs->width = 10 * fs->width + (*format - '0');
      format++;
    }
  }
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    fs->len = *format;
    format++;
  }
  return format;
}

void int_len(long int value, va_list vars, flags_spec *fs) {
  if (fs->len == 'h') {
    short int *int_ptr = va_arg(vars, short int *);
    *int_ptr = value;
    fs->len = 0;
  } else if (fs->len == 'l') {
    long int *int_ptr = va_arg(vars, long int *);
    *int_ptr = value;
    fs->len = 0;
  } else {
    int *int_ptr = va_arg(vars, int *);
    *int_ptr = value;
    fs->len = 0;
  }
}

void unsigned_int_len(unsigned long int value, va_list vars, flags_spec *fs) {
  if (fs->len == 'h') {
    unsigned short int *int_ptr = va_arg(vars, unsigned short int *);
    *int_ptr = value;
    fs->len = 0;
  } else if (fs->len == 'l') {
    unsigned long int *int_ptr = va_arg(vars, unsigned long int *);
    *int_ptr = value;
    fs->len = 0;
  } else {
    unsigned int *int_ptr = va_arg(vars, unsigned int *);
    *int_ptr = value;
    fs->len = 0;
  }
}

int sign_value(const char **str, int *width_count) {
  int sign = 1;
  if (**str == '-') {
    sign = -1;
    ++*str;
    ++*width_count;
  } else if (**str == '+') {
    ++*str;
    ++*width_count;
  }
  return sign;
}

const char *cycle_efg(const char *str, int *width_count, int *flag,
                      int *is_fraction, double *number, double *fraction,
                      double *divisor, flags_spec *fs) {
  while (((*width_count)++ <= fs->width || fs->width == -1) &&
         ((*str >= '0' && *str <= '9') || *str == '.')) {
    *flag = 0;
    if (*str == '.') {
      *is_fraction = 1;
      str++;
      (*width_count)++;
      *flag = 1;
    }
    if (!*flag) {
      if (!*is_fraction) {
        *number = *number * 10.0 + (*str - '0');
      } else {
        *fraction += (*str - '0') / *divisor;
        *divisor *= 10.0;
      }
      str++;
    }
  }
  return str;
}
