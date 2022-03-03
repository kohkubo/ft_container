NAME = a.out
CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -Wshadow -MMD -MP -std=c++98

srcsdir = ./srcs
includes = ./includes
srcs_test =
srcs = $(srcsdir)/main.cpp
objs = $(srcs:.cpp=.o)
depends = $(objs:.o=.d)

.PHONY: all
all: $(NAME)

$(NAME): $(objs)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(objs)

.PHONY: clean
clean:
	$(RM) -rf *.dSYM
	$(RM) -rf tester
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
	# cmake -E make_directory "$(gtestdir)/benchmark/build"
	# cmake -E chdir "$(gtestdir)/benchmark/build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release $(gtestdir)/benchmark/../
	# cmake --build "$(gtestdir)/benchmark/build" --config Release

.PHONY: test
test: $(gtest) fclean
	clang++ -std=c++11 \
	$(testdir)/gtest.cpp $(gtestdir)/googletest-release-1.11.0/googletest/src/gtest_main.cc $(gtestdir)/gtest/gtest-all.cc \
	-DDEBUG -g -fsanitize=address -fsanitize=undefined -fsanitize=leak \
	-I$(gtestdir) -I/usr/local/opt/llvm/include -I$(includes) -lpthread $(srcs_test) -o tester
	./tester
	rm -rf tester
	rm -rf tester.dSYM

.PHONY: test_std
test_std: $(gtest) fclean
	clang++ -std=c++11 \
	$(testdir)/gtest.cpp $(gtestdir)/googletest-release-1.11.0/googletest/src/gtest_main.cc $(gtestdir)/gtest/gtest-all.cc \
	-DLIB=std -g -fsanitize=address -fsanitize=undefined -fsanitize=leak \
	-I$(gtestdir) -I/usr/local/opt/llvm/include -I$(includes) -lpthread $(srcs_test) -o tester
	./tester
	rm -rf tester
	rm -rf tester.dSYM

.PHONY: mytest
mytest:
	$(CXX) -Wall -Werror -Wextra -Wshadow -std=c++98 -o mytest_exe gtest/testlib_main.cpp -I$(includes) -I$(gtestdir)
	./mytest_exe

.PHONY: mytest_std
mytest_std:
	$(CXX) -Wall -Werror -Wextra -Wshadow -std=c++98 -o mytest_std_exe gtest/testlib_main.cpp -DLIB=std -I$(includes) -I$(gtestdir)
	./mytest_std_exe

.PHONY: cave
cave: $(gtest) fclean
	clang++ -std=c++11 -O0 $(testdir)/gtest.cpp $(gtestdir)/googletest-release-1.11.0/googletest/src/gtest_main.cc $(gtestdir)/gtest/gtest-all.cc \
	-DDEBUG \
	-I$(gtestdir) -I/usr/local/opt/llvm/include -I$(includes) -lpthread $(srcs_test) -o tester -fprofile-arcs -ftest-coverage
	./tester
	lcov -c -b . -d . -o cov_test.info
	lcov -r cov_test.info "*gtest*" -o cov_test.info
	genhtml cov_test.info -o cov_test
	rm -rf cov_test.info
	# rm -rf tester
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	# rm -rf tester.dSYM
	open cov_test/index-sort-f.html

benchflg = clang++ -std=c++11 -O2

.PHONY: bench
bench: $(gbench)
	$(benchflg) $(benchdir)/gbench.cpp \
	-isystem $(gbench)/include \
	-L$(gbench)/build/src -lbenchmark -lpthread \
	-DUSE_LIB=ft \
	-I$(gtestdir) -I/usr/local/opt/llvm/include -I$(includes) -I$(benchdir) -o benchmark
	./benchmark --benchmark_out_format=csv --benchmark_out=benchmark.csv

.PHONY: stdbench
stdbench: $(gbench)
	$(benchflg) $(benchdir)/gbench.cpp \
	-isystem $(gbench)/include \
	-L$(gbench)/build/src -lbenchmark -lpthread \
	-DUSE_LIB=std \
	-I$(gtestdir) -I/usr/local/opt/llvm/include -I$(includes) -I$(benchdir) -o benchmark
	./benchmark --benchmark_out_format=csv --benchmark_out=benchmark_std.csv

.PHONY: mybench
mybench:
	@$(CXX) $(CXXFLAGS) -o mybenchmark_exe mybenchmark/mybench.cpp -I$(includes) -O0
	@./mybenchmark_exe

.PHONY: mybench_std
mybench_std:
	@$(CXX) $(CXXFLAGS) -o mybenchmark_exe mybenchmark/mybench.cpp -I$(includes) -O0 -DLIB=std
	@./mybenchmark_exe

-include $(depends)
