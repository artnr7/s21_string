#include <stdarg.h>

#ifndef STRING_H
#define STRING_H

#define S21_NULL 0
typedef long unsigned int s21_size_t;

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
void s21_swapc(char *lhs, char *rhs);
void s21_reverse_str(char *start, char *end);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
void *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#ifdef __linux__

#define SIZE_OF_ERROR_LIST 134
#define UNKNOWN "Unknown error "

#define ERROR_LIST                                      \
  {"Success",                                           \
   "Operation not permitted",                           \
   "No such file or directory",                         \
   "No such process",                                   \
   "Interrupted system call",                           \
   "Input/output error",                                \
   "No such device or address",                         \
   "Argument list too long",                            \
   "Exec format error",                                 \
   "Bad file descriptor",                               \
   "No child processes",                                \
   "Resource temporarily unavailable",                  \
   "Cannot allocate memory",                            \
   "Permission denied",                                 \
   "Bad address",                                       \
   "Block device required",                             \
   "Device or resource busy",                           \
   "File exists",                                       \
   "Invalid cross-device link",                         \
   "No such device",                                    \
   "Not a directory",                                   \
   "Is a directory",                                    \
   "Invalid argument",                                  \
   "Too many open files in system",                     \
   "Too many open files",                               \
   "Inappropriate ioctl for device",                    \
   "Text file busy",                                    \
   "File too large",                                    \
   "No space left on device",                           \
   "Illegal seek",                                      \
   "Read-only file system",                             \
   "Too many links",                                    \
   "Broken pipe",                                       \
   "Numerical argument out of domain",                  \
   "Numerical result out of range",                     \
   "Resource deadlock avoided",                         \
   "File name too long",                                \
   "No locks available",                                \
   "Function not implemented",                          \
   "Directory not empty",                               \
   "Too many levels of symbolic links",                 \
   "Unknown error 41",                                  \
   "No message of desired type",                        \
   "Identifier removed",                                \
   "Channel number out of range",                       \
   "Level 2 not synchronized",                          \
   "Level 3 halted",                                    \
   "Level 3 reset",                                     \
   "Link number out of range",                          \
   "Protocol driver not attached",                      \
   "No CSI structure available",                        \
   "Level 2 halted",                                    \
   "Invalid exchange",                                  \
   "Invalid request descriptor",                        \
   "Exchange full",                                     \
   "No anode",                                          \
   "Invalid request code",                              \
   "Invalid slot",                                      \
   "Unknown error 58",                                  \
   "Bad font file format",                              \
   "Device not a stream",                               \
   "No data available",                                 \
   "Timer expired",                                     \
   "Out of streams resources",                          \
   "Machine is not on the network",                     \
   "Package not installed",                             \
   "Object is remote",                                  \
   "Link has been severed",                             \
   "Advertise error",                                   \
   "Srmount error",                                     \
   "Communication error on send",                       \
   "Protocol error",                                    \
   "Multihop attempted",                                \
   "RFS specific error",                                \
   "Bad message",                                       \
   "Value too large for defined data type",             \
   "Name not unique on network",                        \
   "File descriptor in bad state",                      \
   "Remote address changed",                            \
   "Can not access a needed shared library",            \
   "Accessing a corrupted shared library",              \
   ".lib section in a.out corrupted",                   \
   "Attempting to link in too many shared libraries",   \
   "Cannot exec a shared library directly",             \
   "Invalid or incomplete multibyte or wide character", \
   "Interrupted system call should be restarted",       \
   "Streams pipe error",                                \
   "Too many users",                                    \
   "Socket operation on non-socket",                    \
   "Destination address required",                      \
   "Message too long",                                  \
   "Protocol wrong type for socket",                    \
   "Protocol not available",                            \
   "Protocol not supported",                            \
   "Socket type not supported",                         \
   "Operation not supported",                           \
   "Protocol family not supported",                     \
   "Address family not supported by protocol",          \
   "Address already in use",                            \
   "Cannot assign requested address",                   \
   "Network is down",                                   \
   "Network is unreachable",                            \
   "Network dropped connection on reset",               \
   "Software caused connection abort",                  \
   "Connection reset by peer",                          \
   "No buffer space available",                         \
   "Transport endpoint is already connected",           \
   "Transport endpoint is not connected",               \
   "Cannot send after transport endpoint shutdown",     \
   "Too many references: cannot splice",                \
   "Connection timed out",                              \
   "Connection refused",                                \
   "Host is down",                                      \
   "No route to host",                                  \
   "Operation already in progress",                     \
   "Operation now in progress",                         \
   "Stale file handle",                                 \
   "Structure needs cleaning",                          \
   "Not a XENIX named type file",                       \
   "No XENIX semaphores available",                     \
   "Is a named type file",                              \
   "Remote I/O error",                                  \
   "Disk quota exceeded",                               \
   "No medium found",                                   \
   "Wrong medium type",                                 \
   "Operation canceled",                                \
   "Required key not available",                        \
   "Key has expired",                                   \
   "Key has been revoked",                              \
   "Key was rejected by service",                       \
   "Owner died",                                        \
   "State not recoverable",                             \
   "Operation not possible due to RF-kill",             \
   "Memory page has hardware error"}

#endif

#ifdef __APPLE__

#define SIZE_OF_ERROR_LIST 107
#define UNKNOWN "Unknown error: "

#define ERROR_LIST                                    \
  {"Undefined error: 0",                              \
   "Operation not permitted",                         \
   "No such file or directory",                       \
   "No such process",                                 \
   "Interrupted system call",                         \
   "Input/output error",                              \
   "Device not configured",                           \
   "Argument list too long",                          \
   "Exec format error",                               \
   "Bad file descriptor",                             \
   "No child processes",                              \
   "Resource deadlock avoided",                       \
   "Cannot allocate memory",                          \
   "Permission denied",                               \
   "Bad address",                                     \
   "Block device required",                           \
   "Resource busy",                                   \
   "File exists",                                     \
   "Cross-device link",                               \
   "Operation not supported by device",               \
   "Not a directory",                                 \
   "Is a directory",                                  \
   "Invalid argument",                                \
   "Too many open files in system",                   \
   "Too many open files",                             \
   "Inappropriate ioctl for device",                  \
   "Text file busy",                                  \
   "File too large",                                  \
   "No space left on device",                         \
   "Illegal seek",                                    \
   "Read-only file system",                           \
   "Too many links",                                  \
   "Broken pipe",                                     \
   "Numerical argument out of domain",                \
   "Result too large",                                \
   "Resource temporarily unavailable",                \
   "Operation now in progress",                       \
   "Operation already in progress",                   \
   "Socket operation on non-socket",                  \
   "Destination address required",                    \
   "Message too long",                                \
   "Protocol wrong type for socket",                  \
   "Protocol not available",                          \
   "Protocol not supported",                          \
   "Socket type not supported",                       \
   "Operation not supported",                         \
   "Protocol family not supported",                   \
   "Address family not supported by protocol family", \
   "Address already in use",                          \
   "Can't assign requested address",                  \
   "Network is down",                                 \
   "Network is unreachable",                          \
   "Network dropped connection on reset",             \
   "Software caused connection abort",                \
   "Connection reset by peer",                        \
   "No buffer space available",                       \
   "Socket is already connected",                     \
   "Socket is not connected",                         \
   "Can't send after socket shutdown",                \
   "Too many references: can't splice",               \
   "Operation timed out",                             \
   "Connection refused",                              \
   "Too many levels of symbolic links",               \
   "File name too long",                              \
   "Host is down",                                    \
   "No route to host",                                \
   "Directory not empty",                             \
   "Too many processes",                              \
   "Too many users",                                  \
   "Disc quota exceeded",                             \
   "Stale NFS file handle",                           \
   "Too many levels of remote in path",               \
   "RPC struct is bad",                               \
   "RPC version wrong",                               \
   "RPC prog. not avail",                             \
   "Program version wrong",                           \
   "Bad procedure for program",                       \
   "No locks available",                              \
   "Function not implemented",                        \
   "Inappropriate file type or format",               \
   "Authentication error",                            \
   "Need authenticator",                              \
   "Device power is off",                             \
   "Device error",                                    \
   "Value too large to be stored in data type",       \
   "Bad executable (or shared library)",              \
   "Bad CPU type in executable",                      \
   "Shared library version mismatch",                 \
   "Malformed Mach-o file",                           \
   "Operation canceled",                              \
   "Identifier removed",                              \
   "No message of desired type",                      \
   "Illegal byte sequence",                           \
   "Attribute not found",                             \
   "Bad message",                                     \
   "EMULTIHOP (Reserved)",                            \
   "No message available on STREAM",                  \
   "ENOLINK (Reserved)",                              \
   "No STREAM resources",                             \
   "Not a STREAM",                                    \
   "Protocol error",                                  \
   "STREAM ioctl timeout",                            \
   "Operation not supported on socket",               \
   "Policy not found",                                \
   "State not recoverable",                           \
   "Previous owner died",                             \
   "Interface output queue is full"}
#endif

typedef struct {
  int star;
  int width;
  int len;
  int count;
} flags_spec;

typedef enum {
  stateCharacters,
  stateStart,
  stateFlags,
  stateWidth,
  stateAccuracy,
  stateLength
} StateFormat;

typedef struct {
  int sharp, space, plus, minus, zero;
} Flags;

typedef struct {
  int h, l, L;
} Length;

typedef struct {
  int width;
  int accuracy;
  int accuracy_activate;
  char specifier;
  int error;
  int count_passed_symbols;
  int count_symbols;
  int infinity;
  Flags flags;
  Length length;
} FormatSpecifiers;

void reset_format_specificators(FormatSpecifiers *format_spec);
void swapc(char *lhs, char *rhs);
void reverse_str(char *start, char *end);
char *incremetn_str(char *begin, char *end, long long *exponent);
int is_digit(char number);
int is_specifier(char symbol);
int is_flags(char symbol);
int is_length_spec(char symbol);
void str_to_int(char symbol, int *num);
void set_flags(char symbol, FormatSpecifiers *format_spec);
void set_length(char symbol, FormatSpecifiers *format_spec);
char *convert_to_base(char *digits, char *buffer, long long unsigned int num,
                      int base, int *not_zero);
char *convert_base_upper_to_buffer(char *buffer, long long unsigned int num,
                                   int base, int *not_zero);
char *convert_base_lower_to_buffer(char *buffer, long long unsigned int num,
                                   int base, int *not_zero);
char *unsigned_int_to_buffer(char *buffer, long long unsigned int number);
char *int_to_buffer(char *buffer, long int number,
                    FormatSpecifiers *format_spec);
char *write_inf_to_buffer(char *buffer, int inf_sign,
                          FormatSpecifiers *format_spec);
char *round_number_in_str(char *buffer, char *begin_buffer,
                          long long int number_end, long long *exponent,
                          int is_negative);
char *double_to_buffer(char *buffer, long double num, long long *exponent,
                       FormatSpecifiers *format_spec);
void count_exponent(long long *exponent, long double *number);
char *exponent_to_buffer(char *buffer, long double number, int flag_g,
                         FormatSpecifiers *format_spec, int size_e);
char *flag_g_to_buffer(char *buffer, long double number,
                       FormatSpecifiers *format_spec, int size_g);
char *pointer_to_buffer(char *buffer, void *pointer,
                        FormatSpecifiers *format_spec);
char *write_null(char *buffer);
char *str_to_buffer(char *buffer, char *string, FormatSpecifiers *format_spec);
char *long_str_to_buffer(char *buffer, unsigned int *string,
                         FormatSpecifiers *format_spec);
void decimal_accuracy(char **str, char *buffer, FormatSpecifiers *format_spec);
char *write_str_buffer(char *buffer, const char *str, char *start,
                       FormatSpecifiers *format_spec);
char *process_specifier_d_i(char **str, va_list *args,
                            FormatSpecifiers *format_spec);
char *process_specifier_c(char **str, va_list *args,
                          FormatSpecifiers *format_spec);
char *process_specifier_s(char **str, va_list *args,
                          FormatSpecifiers *format_spec);
char *process_specifier_f(char **str, va_list *args,
                          FormatSpecifiers *format_spec);
char *process_specifier_e_E(char **str, const char *format, va_list *args,
                            FormatSpecifiers *format_spec);
char *process_specifier_g_G(char **str, const char *format, va_list *args,
                            FormatSpecifiers *format_spec);
char *process_specifier_u(char **str, char *buffer_begin, va_list *args,
                          FormatSpecifiers *format_spec);
void process_specifier_o(char **str, char *buffer_begin, va_list *args,
                         FormatSpecifiers *format_spec);
void process_specifier_x_X(char **str, const char *format, char *buffer_begin,
                           va_list *args, FormatSpecifiers *format_spec);
void process_specifier_p(char **str, va_list *args,
                         FormatSpecifiers *format_spec);
void process_specifier_n(va_list *args, FormatSpecifiers *format_spec);
void process_format_specifiers(char **str, const char *format,
                               char *buffer_begin,
                               FormatSpecifiers *format_spec);
void process_specifiers(char **str, const char *format, va_list *args,
                        FormatSpecifiers *format_spec);
void process_characte_save(char **str, const char *format,
                           FormatSpecifiers *format_spec);
void process_state_characters(char **buffer, const char *format,
                              char **percent_begin, StateFormat *state,
                              FormatSpecifiers *format_spec);
void process_state_start(char **buffer, const char *format,
                         char **percent_begin, va_list *args,
                         StateFormat *state, FormatSpecifiers *format_spec);
void process_state_flags(char **buffer, const char *format,
                         char **percent_begin, va_list *args,
                         StateFormat *state, FormatSpecifiers *format_spec);
void process_state_width(char **buffer, const char *format,
                         char **percent_begin, va_list *args,
                         StateFormat *state, FormatSpecifiers *format_spec);
void process_state_accuracy(char **buffer, const char *format,
                            char **percent_begin, va_list *args,
                            StateFormat *state, FormatSpecifiers *format_spec);
void process_state_length(char **buffer, const char *format,
                          char **percent_begin, va_list *args,
                          StateFormat *state, FormatSpecifiers *format_spec);
int s21_sprintf(char *str, const char *format, ...);

int s21_sscanf(const char *str, const char *format, ...);
const char *flags(flags_spec *fs, const char *format);
const char *format_o(const char *str, va_list vars, flags_spec *fs);
const char *format_i(const char *str, va_list vars, flags_spec *fs);
const char *format_d(const char *str, va_list vars, flags_spec *fs);
const char *format_efg(const char *str, va_list vars, flags_spec *fs);
const char *format_u(const char *str, va_list vars, flags_spec *fs);
const char *format_x(const char *str, va_list vars, flags_spec *fs);
const char *format_p(const char *str, va_list vars, flags_spec *fs);
const char *format_s(const char *str, va_list vars, flags_spec *fs);
const char *format_c(const char *str, va_list vars, flags_spec *fs);
void format_n(va_list vars, flags_spec *fs, const char *begin_str,
              const char *str);
void int_len(long int value, va_list vars, flags_spec *fs);
void unsigned_int_len(unsigned long int value, va_list vars, flags_spec *fs);
int sign_value(const char **str, int *width_count);
const char *cycle_efg(const char *str, int *width_count, int *flag,
                      int *is_fraction, double *number, double *fraction,
                      double *divisor, flags_spec *fs);
#endif
