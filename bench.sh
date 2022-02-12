set -eux
DIR=result
RESULT_FILE=$DIR/bench_result.txt
FT_BENCH_FILE=$DIR/ftbench_map_clang_O2.txt
STD_BENCH_FILE=$DIR/stdbench_map_clang_O2.txt

echo "" >> $RESULT_FILE
date >> $RESULT_FILE
make bench &> $FT_BENCH_FILE
make stdbench &> $STD_BENCH_FILE

cat $FT_BENCH_FILE  | gawk 'NR==1{print}' >> $RESULT_FILE
cat $FT_BENCH_FILE  | gawk 'NR>16{time+=$2; cpu+=$4} END {printf "ft  time: %d, cpu: %d\n", time, cpu}' >> $RESULT_FILE
cat $STD_BENCH_FILE | gawk 'NR>16{time+=$2; cpu+=$4} END {printf "std time: %d, cpu: %d\n", time, cpu}' >> $RESULT_FILE
ft=$(cat $RESULT_FILE | tail -r | ggrep "ft" | gawk 'NR==1{print $NF}')
std=$(cat $RESULT_FILE | tail -r | ggrep "std" | gawk 'NR==1{print $NF}')
rate=$(echo "scale=2; $std/$ft" | bc)
echo "rate: $rate" >> $RESULT_FILE
