CXX := gcc
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -fsanitize=address
TESTFLAGS := -lgtest -lpthread
GCOVFLAGS := --coverage
OS = $(shell uname)

TEST_FILES :=  stack_tests.cc vector_tests.cc  set_tests.cc  multiset_tests.cc  list_tests.cc  unit-tests.cc  map_tests.cc array_tests.cc  queue_tests.cc
TESTS_DIR := tests
BUILD_DIR := build
REPORT_DIR := report

SOURCES := $(wildcard *.cc)
OBJECTS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(SOURCES))

LIBRARY := $(BUILD_DIR)/containersplus.a
TEST_EXEC := $(BUILD_DIR)/unit-tests

ifeq ($(OS), Darwin)
	TESTFLAGS = -lm -lgtest -lstdc++
else
	TESTFLAGS += -lstdc++ -lm
endif

all: containersplus.a test check gcov_report

containersplus.a: $(OBJECTS) | $(BUILD_DIR)
	ar rcs $(LIBRARY) $^

$(BUILD_DIR)/%.o: %.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

$(BUILD_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.cc | $(BUILD_DIR) $(BUILD_DIR)/$(TESTS_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TESTS_DIR):
	mkdir -p $@

$(TEST_EXEC): $(LIBRARY) $(addprefix $(BUILD_DIR)/$(TESTS_DIR)/, $(patsubst %.cc, %.o, $(TEST_FILES))) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TESTFLAGS) -lgtest_main

test: containersplus.a $(TEST_EXEC)
	./$(TEST_EXEC)


clean:
	rm -rf $(BUILD_DIR) $(REPORT_DIR) *.o *.info *.gcda *.gcno *.gcov *.gch *.out *.a *.txt test

gcov_report: | $(REPORT_DIR)
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(SOURCES) $(TESTS_DIR)/$(TEST_FILE) -o test $(TESTFLAGS)
	./test
	lcov -t "test" -c -d ./ --no-external --output-file ./$(REPORT_DIR)/coverage.info
	genhtml ./$(REPORT_DIR)/coverage.info --output-directory ./$(REPORT_DIR)
	open ./$(REPORT_DIR)/index.html

leaks:
	CK_FORK=no leaks -quiet -atExit -- ./$(BUILD_DIR)/unit-tests

valgrind:
	CK_FORK=no valgrind --tool=memcheck ./$(BUILD_DIR)/unit-tests

valgrind_check: 
	valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./$(BUILD_DIR)/unit-tests
	
check:
	@echo ---------------------CLANG_FORMAT----------------------
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -verbose -n *.h $(TESTS_DIR)/*.h 2>&1 | tee clang_format_output.txt
	@rm .clang-format
	@echo -------------------------------------------------
	@echo "CLANG output:"
	@cat clang_format_output.txt
	@echo -------------------------------------------------
	@rm clang_format_output.txt

rebuild:	clean	test

