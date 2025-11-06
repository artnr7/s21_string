#include "s21_string.h"

void reset_format_specificators(FormatSpecifiers *format_spec) {
  format_spec->width = 0;
  format_spec->accuracy = 6;
  format_spec->accuracy_activate = 0;
  format_spec->specifier = '\0';
  format_spec->infinity = 0;

  format_spec->flags.minus = 0;
  format_spec->flags.plus = 0;
  format_spec->flags.sharp = 0;
  format_spec->flags.space = 0;
  format_spec->flags.zero = 0;

  format_spec->length.l = 0;
  format_spec->length.L = 0;
  format_spec->length.h = 0;
}

void swapc(char *lhs, char *rhs) {
  char temp = *lhs;
  *lhs = *rhs;
  *rhs = temp;
}

void reverse_str(char *start, char *end) {
  while (start < end) {
    swapc(start++, end--);
  }
}

char *incremetn_str(char *begin, char *end, long long *exponent) {
  int prec = 1;

  while (begin < end) {
    if (*begin == '.') {
      begin++;
    }
    if (*begin == '9' && prec) {
      *begin = '0';
      prec = 1;
    } else {
      *begin = (*begin - '0') + prec + '0';
      prec = 0;
    }
    begin++;
  }
  if (prec == 1) {
    if (exponent != S21_NULL) {
      ++(*exponent);
    }
    begin--;
    *begin++ = '1';
    *begin = '\0';
  }
  return begin;
}

int is_digit(char number) {
  int result = 0;
  if (number >= '0' && number <= '9') {
    result = 1;
  }
  return result;
}

int is_specifier(char symbol) {
  int result = 0;
  if (symbol == 'c' || symbol == 'd' || symbol == 'i' || symbol == 'e' ||
      symbol == 'E' || symbol == 'f' || symbol == 'g' || symbol == 'G' ||
      symbol == 'o' || symbol == 's' || symbol == 'u' || symbol == 'x' ||
      symbol == 'X' || symbol == 'p' || symbol == 'n') {
    result = 1;
  }
  return result;
}

int is_flags(char symbol) {
  int result = 0;
  if (symbol == '-' || symbol == '+' || symbol == ' ' || symbol == '#' ||
      symbol == '0') {
    result = 1;
  }
  return result;
}

int is_length_spec(char symbol) {
  int result = 0;
  if (symbol == 'h' || symbol == 'L' || symbol == 'l') {
    result = 1;
  }
  return result;
}

void str_to_int(char symbol, int *num) { *num = (*num * 10) + (symbol - '0'); }

void set_flags(char symbol, FormatSpecifiers *format_spec) {
  if (symbol == '-') {
    format_spec->flags.minus = 1;
  } else if (symbol == '+') {
    format_spec->flags.plus = 1;
  } else if (symbol == ' ') {
    format_spec->flags.space = 1;
  } else if (symbol == '#') {
    format_spec->flags.sharp = 1;
  } else if (symbol == '0') {
    format_spec->flags.zero = 1;
  }
}

void set_length(char symbol, FormatSpecifiers *format_spec) {
  if (symbol == 'h') {
    format_spec->length.h++;
    if (format_spec->length.h > 2 || format_spec->length.L != 0 ||
        format_spec->length.l != 0) {
      format_spec->error = 1;
    }
  } else if (symbol == 'l') {
    format_spec->length.l++;
    if (format_spec->length.l > 2 || format_spec->length.h != 0 ||
        format_spec->length.L != 0) {
      format_spec->error = 1;
    }
  } else if (symbol == 'L') {
    format_spec->length.L++;
    if (format_spec->length.L > 1 || format_spec->length.h != 0 ||
        format_spec->length.l != 0) {
      format_spec->error = 1;
    }
  }
}

char *convert_to_base(char *digits, char *buffer, long long unsigned int num,
                      int base, int *not_zero) {
  if (num == 0 && not_zero != S21_NULL) *not_zero = 0;
  do {
    *buffer++ = digits[num % base];
    num /= base;
  } while (num > 0);
  *buffer = '\0';

  return buffer;
}

char *convert_base_upper_to_buffer(char *buffer, long long unsigned int num,
                                   int base, int *not_zero) {
  char digits[] = "0123456789ABCDEF";
  return convert_to_base(digits, buffer, num, base, not_zero);
}

char *convert_base_lower_to_buffer(char *buffer, long long unsigned int num,
                                   int base, int *not_zero) {
  char digits[] = "0123456789abcdef";
  return convert_to_base(digits, buffer, num, base, not_zero);
}

char *unsigned_int_to_buffer(char *buffer, long long unsigned int number) {
  do {
    *buffer++ = (number % 10) + '0';
    number /= 10;
  } while (number);
  *buffer = '\0';
  return buffer;
}

char *int_to_buffer(char *buffer, long int number,
                    FormatSpecifiers *format_spec) {
  int num_negative = 0;
  if (number < 0) {
    num_negative = 1;
    number = -number;
  }
  buffer = unsigned_int_to_buffer(buffer, number);

  if (number != 0) {
    if (num_negative) {
      *buffer++ = '-';
      format_spec->flags.space = -1;
    }
  }
  if (!num_negative && format_spec->flags.plus) {
    *buffer++ = '+';
    format_spec->flags.space = -1;
  }
  *buffer = '\0';
  return buffer;
}

char *write_inf_to_buffer(char *buffer, int inf_sign,
                          FormatSpecifiers *format_spec) {
  format_spec->infinity = 1;
  *buffer++ = 'f';
  *buffer++ = 'n';
  *buffer++ = 'i';
  if (inf_sign) {
    *buffer++ = '-';
  }
  *buffer = '\0';
  return buffer;
}

char *round_number_in_str(char *buffer, char *begin_buffer,
                          long long int number_end, long long *exponent,
                          int is_negative) {
  if (number_end % 10 >= 5) {
    if (!is_negative) {
      reverse_str(begin_buffer, buffer - 1);
      buffer = incremetn_str(begin_buffer, buffer, exponent);
    } else {
      reverse_str(begin_buffer + 1, buffer - 1);
      buffer = incremetn_str(begin_buffer + 1, buffer, exponent);
      reverse_str(begin_buffer + 1, buffer - 1);
      reverse_str(begin_buffer, buffer - 1);
    }
  } else {
    reverse_str(begin_buffer, buffer - 1);
  }
  return buffer;
}

char *double_to_buffer(char *buffer, long double num, long long *exponent,
                       FormatSpecifiers *format_spec) {
  long double inf = 1.0 / 0.0;
  if (num == inf) {
    buffer = write_inf_to_buffer(buffer, 0, format_spec);
  } else if (num == -inf) {
    buffer = write_inf_to_buffer(buffer, 1, format_spec);
  } else {
    char *begin_buffer_ptr = buffer;
    int prec = format_spec->accuracy;

    int is_negative = 0;
    if (num < 0) {
      is_negative = 1;
      num = -num;
    }
    long long part_i = (long long)num;
    long double part_d = num - (long double)part_i;

    buffer = unsigned_int_to_buffer(buffer, part_i);

    if (is_negative) {
      *buffer++ = '-';
      format_spec->flags.space = -1;
    } else if (format_spec->flags.plus) {
      *buffer++ = '+';
      format_spec->flags.space = -1;
    }
    reverse_str(begin_buffer_ptr, buffer - 1);
    *buffer++ = '.';

    while (prec-- > 0) {
      part_d *= 10.0f;
      long long tpart_i = (long long)part_d;
      *buffer++ = tpart_i % 10 + '0';
      part_d -= (long double)tpart_i;
    }
    *buffer = '\0';

    part_d *= 10.0f;
    long long tpart_i = (long long)part_d;
    buffer = round_number_in_str(buffer, begin_buffer_ptr, tpart_i, exponent,
                                 is_negative);
  }
  return buffer;
}

void count_exponent(long long *exponent, long double *number) {
  if (*number != 0) {
    int negative_number = 0;
    if (*number < 0) {
      *number = -*number;
      negative_number = 1;
    }

    while (*number >= 1.0) {
      *number /= 10.0;
      (*exponent)++;
    }
    while (*number < 1.0) {
      *number *= 10.0;
      (*exponent)--;
    }

    if (negative_number) {
      *number = -*number;
    }
  }
}

char *exponent_to_buffer(char *buffer, long double number, int flag_g,
                         FormatSpecifiers *format_spec, int size_e) {
  long long exponent = 0;
  char *begin_buffer_ptr = buffer;
  count_exponent(&exponent, &number);
  buffer = double_to_buffer(buffer, number, &exponent, format_spec);
  reverse_str(begin_buffer_ptr, buffer - 1);

  int is_negative = 0;
  if (exponent < 0) {
    is_negative = 1;
    exponent = -exponent;
  }

  if (flag_g) {
    while (*(buffer - 1) == '0') {
      buffer--;
    }
    if (*(buffer - 1) == '.') {
      buffer--;
    }
    *buffer = '\0';
  }

  if (size_e == 0) {
    *buffer++ = 'e';
  } else {
    *buffer++ = 'E';
  }
  if (is_negative) {
    *buffer++ = '-';
  } else {
    *buffer++ = '+';
  }

  char *exponent_number_ptr = buffer;
  int exponent_numbers_count = 2;

  buffer = unsigned_int_to_buffer(buffer, exponent);
  exponent_numbers_count -= buffer - exponent_number_ptr;
  while (exponent_numbers_count-- > 0) {
    *buffer++ = '0';
  }

  *buffer = '\0';
  reverse_str(exponent_number_ptr, buffer - 1);
  reverse_str(begin_buffer_ptr, buffer - 1);
  return buffer;
}

char *flag_g_to_buffer(char *buffer, long double number,
                       FormatSpecifiers *format_spec, int size_g) {
  long long exponent = 0;
  long double temp_number = number;
  count_exponent(&exponent, &temp_number);

  if (format_spec->accuracy > exponent && format_spec->accuracy >= -4 &&
      exponent >= -4) {
    format_spec->accuracy = format_spec->accuracy - 1 - exponent;
    char *buffer_begin_ptr = buffer;
    buffer = double_to_buffer(buffer, number, S21_NULL, format_spec);

    if (!format_spec->flags.sharp) {
      reverse_str(buffer_begin_ptr, buffer - 1);
      while (*(buffer - 1) == '0') {
        buffer--;
      }
      if (*(buffer - 1) == '.') buffer--;
      *buffer = '\0';
      reverse_str(buffer_begin_ptr, buffer - 1);
    }
  } else {
    format_spec->accuracy--;
    buffer = exponent_to_buffer(buffer, number, 1, format_spec, size_g);
  }
  return buffer;
}

char *pointer_to_buffer(char *buffer, void *pointer,
                        FormatSpecifiers *format_spec) {
  unsigned long number = (unsigned long)pointer;
  char *begin_buffer_ptr = buffer;
  buffer = convert_base_lower_to_buffer(buffer, number, 16, S21_NULL);
  if (format_spec->accuracy != 0 && format_spec->accuracy_activate) {
    while (format_spec->accuracy > (buffer)-begin_buffer_ptr) {
      *buffer++ = '0';
    }
    *buffer = '\0';
  }
  *buffer++ = 'x';
  *buffer++ = '0';
  return buffer;
}

char *write_S21_NULL(char *buffer) {
  *buffer++ = ')';
  *buffer++ = 'l';
  *buffer++ = 'l';
  *buffer++ = 'u';
  *buffer++ = 'n';
  *buffer++ = '(';
  *buffer = '\0';
  return buffer;
}

char *str_to_buffer(char *buffer, char *string, FormatSpecifiers *format_spec) {
  char *begin_buffer_ptr = buffer;
  int count = 0;
  int stop = 0;
  if (string == S21_NULL) {
    buffer = write_S21_NULL(buffer);
  }

  while (*string && *string != '\0' && !stop) {
    if (format_spec->accuracy_activate && format_spec->accuracy == count)
      stop = 1;
    else {
      *buffer++ = *string++;
      count++;
    }
  }
  *buffer = '\0';
  reverse_str(begin_buffer_ptr, buffer - 1);
  return buffer;
}

char *long_str_to_buffer(char *buffer, unsigned int *string,
                         FormatSpecifiers *format_spec) {
  int count = 0;
  int stop = 0;
  char *begin_buffer_ptr = buffer;
  while (*string != '\0' && !stop) {
    if (format_spec->accuracy_activate && format_spec->accuracy == count)
      stop = 1;
    else {
      *buffer++ = (char)*string;
      string++;
      count++;
    }
  }
  *buffer = '\0';
  reverse_str(begin_buffer_ptr, buffer - 1);
  return buffer;
}

void decimal_accuracy(char **str, char *buffer, FormatSpecifiers *format_spec) {
  int is_sign = 0;
  if (format_spec->flags.space == -1) {
    reverse_str(buffer, *str - 1);
    reverse_str(buffer + 1, *str - 1);
    is_sign = 1;
  }
  if (format_spec->accuracy != 0 && format_spec->accuracy_activate) {
    while (format_spec->accuracy > (*str) - buffer - is_sign) {
      *(*str)++ = '0';
    }
    **str = '\0';
  }
  if (format_spec->flags.space == -1) {
    reverse_str(buffer + 1, *str - 1);
    reverse_str(buffer, *str - 1);
  }
}

char *write_str_buffer(char *buffer, const char *str, char *start,
                       FormatSpecifiers *format_spec) {
  while (start != S21_NULL && start <= str) {
    if (!is_length_spec(*start)) {
      *buffer++ = *start;
      format_spec->count_symbols++;
    }
    start++;
  }
  return buffer;
}

char *process_specifier_d_i(char **str, va_list *args,
                            FormatSpecifiers *format_spec) {
  if (format_spec->length.l == 1) {
    long int number = va_arg(*args, long int);
    *str = int_to_buffer((*str), number, format_spec);
  } else if (format_spec->length.l == 2) {
    long long number = va_arg(*args, long long);
    *str = int_to_buffer((*str), number, format_spec);
  } else if (format_spec->length.h >= 1) {
    short number = (short)va_arg(*args, int);
    *str = int_to_buffer((*str), number, format_spec);
  } else {
    int number = va_arg(*args, int);
    *str = int_to_buffer((*str), number, format_spec);
  }
  return *str;
}

char *process_specifier_c(char **str, va_list *args,
                          FormatSpecifiers *format_spec) {
  format_spec->flags.space = 0;
  if (format_spec->length.l == 1) {
    unsigned int symbol = va_arg(*args, unsigned int);
    *(*str)++ = symbol;
  } else {
    char symbol = (char)va_arg(*args, int);
    *(*str)++ = symbol;
  }
  return *str;
}

char *process_specifier_s(char **str, va_list *args,
                          FormatSpecifiers *format_spec) {
  if (format_spec->length.l == 1) {
    unsigned int *string = va_arg(*args, unsigned int *);
    *str = long_str_to_buffer(*str, string, format_spec);
  } else {
    char *string = va_arg(*args, char *);
    *str = str_to_buffer(*str, string, format_spec);
  }
  return *str;
}

char *process_specifier_f(char **str, va_list *args,
                          FormatSpecifiers *format_spec) {
  if (format_spec->length.l == 1) {
    double number = va_arg(*args, double);
    *str = double_to_buffer(*str, number, S21_NULL, format_spec);
  } else if (format_spec->length.l == 2 || format_spec->length.L == 1) {
    long double number = va_arg(*args, long double);
    *str = double_to_buffer(*str, number, S21_NULL, format_spec);
  } else {
    float number = (float)va_arg(*args, double);
    *str = double_to_buffer(*str, number, S21_NULL, format_spec);
  }
  return *str;
}

char *process_specifier_e_E(char **str, const char *format, va_list *args,
                            FormatSpecifiers *format_spec) {
  if (format_spec->length.L == 1) {
    long double number = va_arg(*args, long double);
    if (*format == 'e') {
      *str = exponent_to_buffer(*str, number, 0, format_spec, 0);
    } else {
      *str = exponent_to_buffer(*str, number, 0, format_spec, 1);
    }
  } else {
    long double number = va_arg(*args, double);
    if (*format == 'e') {
      *str = exponent_to_buffer(*str, number, 0, format_spec, 0);
    } else {
      *str = exponent_to_buffer(*str, number, 0, format_spec, 1);
    }
  }
  return *str;
}

char *process_specifier_g_G(char **str, const char *format, va_list *args,
                            FormatSpecifiers *format_spec) {
  if (format_spec->length.L == 1) {
    long double number = va_arg(*args, long double);
    if (*format == 'g') {
      *str = flag_g_to_buffer(*str, number, format_spec, 0);
    } else {
      *str = flag_g_to_buffer(*str, number, format_spec, 1);
    }
  } else {
    double number = va_arg(*args, double);
    if (*format == 'g') {
      *str = flag_g_to_buffer(*str, number, format_spec, 0);
    } else {
      *str = flag_g_to_buffer(*str, number, format_spec, 1);
    }
  }
  return *str;
}

char *process_specifier_u(char **str, char *buffer_begin, va_list *args,
                          FormatSpecifiers *format_spec) {
  if (format_spec->length.l == 1) {
    long unsigned int number = va_arg(*args, long unsigned int);
    *str = unsigned_int_to_buffer(*str, number);
  } else if (format_spec->length.l == 2) {
    long long unsigned number = va_arg(*args, long long unsigned);
    *str = unsigned_int_to_buffer(*str, number);
  } else if (format_spec->length.h >= 1) {
    unsigned short number = (short)va_arg(*args, unsigned int);
    *str = unsigned_int_to_buffer(*str, number);
  } else {
    unsigned int number = va_arg(*args, unsigned int);
    *str = unsigned_int_to_buffer(*str, number);
  }
  if (format_spec->accuracy != 0 && format_spec->accuracy_activate) {
    while (format_spec->accuracy > (*str) - buffer_begin) {
      *(*str)++ = '0';
    }
    **str = '\0';
  }
  return *str;
}

void process_specifier_o(char **str, char *buffer_begin, va_list *args,
                         FormatSpecifiers *format_spec) {
  int not_zero = 1;
  if (format_spec->length.l == 1) {
    long unsigned int number = va_arg(*args, long unsigned int);
    *str = convert_base_lower_to_buffer(*str, number, 8, &not_zero);
  } else if (format_spec->length.l == 2) {
    long long unsigned number = va_arg(*args, long long unsigned);
    *str = convert_base_lower_to_buffer(*str, number, 8, &not_zero);
  } else if (format_spec->length.h >= 1) {
    unsigned short number = (unsigned short)va_arg(*args, unsigned int);
    *str = convert_base_lower_to_buffer(*str, number, 8, &not_zero);
  } else {
    unsigned int number = va_arg(*args, int);
    *str = convert_base_lower_to_buffer(*str, number, 8, &not_zero);
  }
  if (format_spec->accuracy != 0 && format_spec->accuracy_activate) {
    while (format_spec->accuracy > (*str) - buffer_begin) {
      *(*str)++ = '0';
    }
    **str = '\0';
  }
  format_spec->flags.space = 0;
  if (format_spec->flags.sharp && not_zero) {
    *(*str)++ = '0';
    *(*str) = '\0';
  }
}

void process_specifier_x_X(char **str, const char *format, char *buffer_begin,
                           va_list *args, FormatSpecifiers *format_spec) {
  int not_zero = 1;
  if (format_spec->length.l == 1) {
    long unsigned int number = va_arg(*args, long unsigned int);
    if (*format == 'X') {
      *str = convert_base_upper_to_buffer(*str, number, 16, &not_zero);
    } else {
      *str = convert_base_lower_to_buffer(*str, number, 16, &not_zero);
    }
  } else if (format_spec->length.l == 2) {
    long long unsigned number = va_arg(*args, long long unsigned);
    if (*format == 'X') {
      *str = convert_base_upper_to_buffer(*str, number, 16, &not_zero);
    } else {
      *str = convert_base_lower_to_buffer(*str, number, 16, &not_zero);
    }
  } else if (format_spec->length.h >= 1) {
    unsigned short number = (unsigned short)va_arg(*args, unsigned int);
    if (*format == 'X') {
      *str = convert_base_upper_to_buffer(*str, number, 16, &not_zero);
    } else {
      *str = convert_base_lower_to_buffer(*str, number, 16, &not_zero);
    }
  } else {
    unsigned int number = va_arg(*args, int);
    if (*format == 'X') {
      *str = convert_base_upper_to_buffer(*str, number, 16, &not_zero);
    } else {
      *str = convert_base_lower_to_buffer(*str, number, 16, &not_zero);
    }
  }

  if (format_spec->accuracy != 0 && format_spec->accuracy_activate) {
    while (format_spec->accuracy > (*str) - buffer_begin) {
      *(*str)++ = '0';
    }
    **str = '\0';
  }
  if (format_spec->flags.sharp && not_zero) {
    if (*format == 'X')
      *(*str)++ = 'X';
    else
      *(*str)++ = 'x';
    *(*str)++ = '0';
    *(*str) = '\0';
  }
}

void process_specifier_p(char **str, va_list *args,
                         FormatSpecifiers *format_spec) {
  void *pointer = (void *)va_arg(*args, void *);
  if (pointer == S21_NULL) {
    *str = write_S21_NULL(*str);
  } else {
    *str = pointer_to_buffer(*str, pointer, format_spec);
  }
}

void process_specifier_n(va_list *args, FormatSpecifiers *format_spec) {
  int *count_pointer = va_arg(*args, int *);
  *count_pointer = format_spec->count_symbols;
}

void process_format_specifiers(char **str, const char *format,
                               char *buffer_begin,
                               FormatSpecifiers *format_spec) {
  if (format_spec->flags.space == 1 && !format_spec->flags.plus) {
    *(*str)++ = ' ';
    **str = '\0';
  }
  if (format_spec->flags.minus) {
    reverse_str(buffer_begin, *str - 1);
  }
  if (format_spec->width != 0) {
    int is_negative = 0;
    if (*(*str - 1) == '-' && (*format == 'g' || *format == 'G')) {
      (*str)--;
      is_negative = 1;
    }
    while (format_spec->width > (*str) - buffer_begin + is_negative) {
      if (format_spec->flags.zero && *format != 'c')
        *(*str)++ = '0';
      else
        *(*str)++ = ' ';
    }
    if (is_negative) {
      *(*str)++ = '-';
    }
  }
  if (!format_spec->flags.minus) {
    reverse_str(buffer_begin, *str - 1);
  }
  reset_format_specificators(format_spec);
  format_spec->count_symbols += (*str - buffer_begin);
}

void process_specifiers(char **str, const char *format, va_list *args,
                        FormatSpecifiers *format_spec) {
  char *buffer_begin_p = (*str);
  if (*format == 'd' || *format == 'i') {
    process_specifier_d_i(str, args, format_spec);
    decimal_accuracy(str, buffer_begin_p, format_spec);
  } else if (*format == 'c') {
    process_specifier_c(str, args, format_spec);
  } else if (*format == 's') {
    process_specifier_s(str, args, format_spec);
  } else if (*format == 'f') {
    process_specifier_f(str, args, format_spec);
  } else if (*format == 'e' || *format == 'E') {
    process_specifier_e_E(str, format, args, format_spec);
  } else if (*format == 'g' || *format == 'G') {
    process_specifier_g_G(str, format, args, format_spec);
  } else if (*format == 'u') {
    process_specifier_u(str, buffer_begin_p, args, format_spec);
  } else if (*format == 'o') {
    process_specifier_o(str, buffer_begin_p, args, format_spec);
  } else if (*format == 'x' || *format == 'X') {
    process_specifier_x_X(str, format, buffer_begin_p, args, format_spec);
  } else if (*format == 'p') {
    process_specifier_p(str, args, format_spec);
  } else if (*format == 'n') {
    process_specifier_n(args, format_spec);
  }
  process_format_specifiers(str, format, buffer_begin_p, format_spec);
}

void process_characte_save(char **str, const char *format,
                           FormatSpecifiers *format_spec) {
  format_spec->count_symbols++;
  *(*str)++ = *format;
}

void process_state_characters(char **buffer, const char *format,
                              char **percent_begin, StateFormat *state,
                              FormatSpecifiers *format_spec) {
  if (*format == '%') {
    *percent_begin = (char *)format;
    *state = stateStart;
  } else {
    process_characte_save(buffer, format, format_spec);
  }
}

void process_state_start(char **buffer, const char *format,
                         char **percent_begin, va_list *args,
                         StateFormat *state, FormatSpecifiers *format_spec) {
  if (is_flags(*format)) {
    set_flags(*format, format_spec);
    *state = stateFlags;
  } else if (*format == '*' || is_digit(*format)) {
    if (is_digit(*format)) {
      str_to_int(*format, &format_spec->width);
    } else if (*format == '*') {
      format_spec->width = va_arg(*args, int);
    }
    *state = stateWidth;
  } else if (*format == '.') {
    format_spec->accuracy = 0;
    *state = stateAccuracy;
  } else if (is_length_spec(*format)) {
    set_length(*format, format_spec);
    *state = stateLength;
  } else if (is_specifier(*format)) {
    process_specifiers(buffer, format, args, format_spec);
    *state = stateCharacters;
  } else {
    *buffer = write_str_buffer(*buffer, format, *percent_begin, format_spec);
    *state = stateCharacters;
  }
}

void process_state_flags(char **buffer, const char *format,
                         char **percent_begin, va_list *args,
                         StateFormat *state, FormatSpecifiers *format_spec) {
  if (is_flags(*format)) {
    set_flags(*format, format_spec);
  } else if (*format == '*' || is_digit(*format)) {
    if (is_digit(*format)) {
      str_to_int(*format, &format_spec->width);
    } else if (*format == '*') {
      format_spec->width = va_arg(*args, int);
    }
    *state = stateWidth;
  } else if (*format == '.') {
    format_spec->accuracy = 0;
    *state = stateAccuracy;
  } else if (is_length_spec(*format)) {
    *state = stateLength;
    set_length(*format, format_spec);
  } else if (is_specifier(*format)) {
    process_specifiers(buffer, format, args, format_spec);
    *state = stateCharacters;
  } else {
    *buffer = write_str_buffer(*buffer, format, *percent_begin, format_spec);
    *state = stateCharacters;
  }
}

void process_state_width(char **buffer, const char *format,
                         char **percent_begin, va_list *args,
                         StateFormat *state, FormatSpecifiers *format_spec) {
  if (*format == '.') {
    format_spec->accuracy = 0;
    *state = stateAccuracy;
  } else if (is_length_spec(*format)) {
    set_length(*format, format_spec);
    *state = stateLength;
  } else if (is_digit(*format)) {
    if (is_digit(*format)) {
      str_to_int(*format, &format_spec->width);
    }
  } else if (is_specifier(*format)) {
    process_specifiers(buffer, format, args, format_spec);
    *state = stateCharacters;
  } else {
    *buffer = write_str_buffer(*buffer, format, *percent_begin, format_spec);
    *state = stateCharacters;
  }
}

void process_state_accuracy(char **buffer, const char *format,
                            char **percent_begin, va_list *args,
                            StateFormat *state, FormatSpecifiers *format_spec) {
  format_spec->accuracy_activate = 1;
  if (is_length_spec(*format)) {
    set_length(*format, format_spec);
    *state = stateLength;
  } else if (is_digit(*format)) {
    str_to_int(*format, &format_spec->accuracy);
  } else if (*format == '*') {
    format_spec->accuracy = va_arg(*args, int);
  } else if (is_specifier(*format)) {
    process_specifiers(buffer, format, args, format_spec);
    *state = stateCharacters;
  } else {
    *buffer = write_str_buffer(*buffer, format, *percent_begin, format_spec);
    *state = stateCharacters;
  }
}

void process_state_length(char **buffer, const char *format,
                          char **percent_begin, va_list *args,
                          StateFormat *state, FormatSpecifiers *format_spec) {
  if (is_specifier(*format)) {
    process_specifiers(buffer, format, args, format_spec);
    *state = stateCharacters;
  } else if (is_length_spec(*format)) {
    set_length(*format, format_spec);
  } else {
    *buffer = write_str_buffer(*buffer, format, *percent_begin, format_spec);
    *state = stateCharacters;
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  StateFormat state = stateCharacters;
  FormatSpecifiers format_spec = {0};
  reset_format_specificators(&format_spec);

  va_list args;
  va_start(args, format);
  int not_count = 0;
  char *procent_start = S21_NULL;
  while (*format && !format_spec.error) {
    if (*format == '%') not_count = 1;
    if (!not_count) format_spec.count_passed_symbols++;
    switch (state) {
      case stateCharacters:
        process_state_characters(&str, format, &procent_start, &state,
                                 &format_spec);
        break;
      case stateStart:
        process_state_start(&str, format, &procent_start, &args, &state,
                            &format_spec);
        break;
      case stateFlags:
        process_state_flags(&str, format, &procent_start, &args, &state,
                            &format_spec);
        break;
      case stateWidth:
        process_state_width(&str, format, &procent_start, &args, &state,
                            &format_spec);
        break;
      case stateAccuracy:
        process_state_accuracy(&str, format, &procent_start, &args, &state,
                               &format_spec);
        break;
      case stateLength:
        process_state_length(&str, format, &procent_start, &args, &state,
                             &format_spec);
        break;
    }
    format++;
  }
  *str = '\0';
  va_end(args);

  return format_spec.count_symbols;
}