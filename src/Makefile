CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
GCOV_FLAGS = --coverage
CHECK_FLAGS = -lcheck -lm -lsubunit

CFILES = s21_csharp.c s21_sscanf.c s21_sprintf.c s21_string.c
OBJS = $(CFILES:.c=.o)

TEST_FILE = s21_test.c 
LIB_FILE = s21_string.a

###--------→ TARGETS ←---------------------------------------------------------------###
.PHONY: all
all: $(LIB_FILE)
	@echo "Make done"	 

.PHONY: rebuild
rebuild: clean all
	@echo "Report done"	 


.PHONY: test
test: $(LIB_FILE)
	@$(CC) $(FLAGS) $(TEST_FILE) -L. $(LIB_FILE) $(CHECK_FLAGS) -o test
	@./test
	@echo "Test done"	 

.PHONY: gcov_report
gcov_report:
	@$(CC) $(FLAGS) $(TEST_FILE) $(CFILES) $(CHECK_FLAGS) $(GCOV_FLAGS) -o gcov_test
	@./gcov_test
	@mkdir -p report_gcov
	@gcovr --exclude 's21_test\.c' --html-details -o ./report_gcov/report.html
	@echo "Gcov_report done"	 

.PHONY: lcov_report
lcov_report:
	@$(CC) $(FLAGS) $(TEST_FILE) $(CFILES) $(CHECK_FLAGS) $(GCOV_FLAGS) -o gcov_test_lcov
	@./gcov_test_lcov
	@lcov --capture --directory . --output-file coverage.info --rc branch_coverage=1
	@lcov --remove coverage.info '*s21_test.c' -o coverage.info --rc branch_coverage=1
	@genhtml --branch-coverage coverage.info --output-directory report_lcov
	@echo "Lcov_report done"	 

.PHONY: $(LIB_FILE)
$(LIB_FILE): $(OBJS)
	@ar rcs $@ $^
	@ranlib $@
	@echo "Lib compiled"	 

.PHONY: %.o
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

###--------→ CLANG ←---------------------------------------------------------------###
CLANG_FILES := $(shell find . \( -name '*.c' -o -name '*.h' \))

clangn:
	@cp ../materials/linters/.clang-format . 
	@clang-format-18 -n $(CLANG_FILES)
	@rm .clang-format
	@echo "Clang done"

clangi:
	@cp ../materials/linters/.clang-format . 
	@clang-format-18 -i $(CLANG_FILES)
	@rm .clang-format
	@echo "Clang done"

###--------→ CLEAN ←------------------------------------------------------------###
FILES_REPORT = *.gcno *.gcda gcov_test coverage.info gcov_test_lcov report_gcov report_lcov
FILES_TO_DEL := *.o *.a report $(FILES_REPORT) test

clean: 
	@rm -rf $(FILES_TO_DEL)
	@echo "Clean done"	 
