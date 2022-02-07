NAME = a.out
CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -Wshadow -MMD -MP -std=c++98

srcsdir = ./srcs
includes = ./includes
srcs_test =
srcs = $(srcsdir)/main.cpp $(srcs_test)
objs = $(srcs:.cpp=.o)
depends = $(objs:.o=.d)

.PHONY: all
all: $(NAME)

$(NAME): $(objs)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(objs)

.PHONY: clean
clean:
	$(RM) -rf *.dSYM
	$(RM) -rf $(objs) $(depends)

.PHONY: fclean
fclean: clean
	$(RM) -rf $(NAME)

.PHONY: re
re: fclean all

.PHONY: debug
debug: CXXFLAGS += -g -fsanitize=integer -fsanitize=address -DDEBUG
debug: re

gtestdir	=	./test
gtest		=	$(gtestdir)/gtest $(gtestdir)/googletest-release-1.11.0
gbench	=	$(gtestdir)/benchmark

testdir = ./gtest
benchdir = ./gbench

$(gtest):
	mkdir -p $(dir ../test)
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -xvzf release-1.11.0.tar.gz googletest-release-1.11.0
	rm -rf release-1.11.0.tar.gz
	python googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(gtestdir)
	mv googletest-release-1.11.0 $(gtestdir)

$(gbench):
	mkdir -p $(dir ../test)
	# git clone https://github.com/google/benchmark.git $(gtestdir)/benchmark
	cmake -E make_directory "build"
	cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../
	cmake --build "build" --config Release

test: $(gtest) fclean
	clang++ -std=c++11 $(testdir)/gtest.cpp $(gtestdir)/googletest-release-1.11.0/googletest/src/gtest_main.cc $(gtestdir)/gtest/gtest-all.cc \
	-DDEBUG -g -fsanitize=address -fsanitize=undefined -fsanitize=leak \
	-I$(gtestdir) -I/usr/local/opt/llvm/include -I$(includes) -lpthread $(srcs_test) -o tester
	./tester
	# rm -rf tester
	# rm -rf tester.dSYM

cave: $(gtest) fclean
	clang++ -std=c++11 $(testdir)/gtest.cpp $(gtestdir)/googletest-release-1.11.0/googletest/src/gtest_main.cc $(gtestdir)/gtest/gtest-all.cc \
	-DDEBUG \
	-I$(gtestdir) -I/usr/local/opt/llvm/include -I$(includes) -lpthread $(srcs_test) -o tester -fprofile-arcs -ftest-coverage -lgtest -g 
	./tester
	lcov -c -b . -d . -o cov_test.info
	genhtml cov_test.info -o cov_test
	rm -rf cov_test.info
	# rm -rf tester
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	# rm -rf tester.dSYM
	open cov_test/index-sort-f.html

bench: $(gbench)
	g++ -std=c++11 -O2 $(benchdir)/gbench.cpp -isystem $(gbench)/include \
  -L$(gbench)/build/src -lbenchmark -lpthread \
	-I$(gtestdir) -I/usr/local/opt/llvm/include -I$(includes) -I$(benchdir) -o benchmark
	./benchmark

-include $(depends)
