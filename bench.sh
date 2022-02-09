set -eux
DIR=result
RESULT_FILE=$DIR/bench_result.txt
FT_BENCH_FILE=$DIR/ftbench_clangO2.txt
STD_BENCH_FILE=$DIR/stdbench_clangO2.txt

echo "" >> $RESULT_FILE
echo "clang++ -O2" >> $RESULT_FILE
date >> $RESULT_FILE
make bench &> $FT_BENCH_FILE
make stdbench &> $STD_BENCH_FILE
cat $FT_BENCH_FILE  | gawk 'NR>16{time+=$2; cpu+=$4} END {printf "ft  time: %d, cpu: %d\n", time, cpu}' >> $RESULT_FILE
cat $STD_BENCH_FILE | gawk 'NR>16{time+=$2; cpu+=$4} END {printf "std time: %d, cpu: %d\n", time, cpu}' >> $RESULT_FILE
ft=$(cat $RESULT_FILE | tail -r | ggrep "ft" | gawk 'NR==1{print $NF}')
std=$(cat $RESULT_FILE | tail -r | ggrep "std" | gawk 'NR==1{print $NF}')
rate=$(echo "scale=2; $std/$ft" | bc)
echo "rate: $rate" >> $RESULT_FILE
