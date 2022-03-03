set -eu

rm -rf bench.log bench_std.log
make mybench > bench.log
make mybench_std > bench_std.log
paste bench.log bench_std.log | gawk '{printf "scale=2; %d/%d\n", $5, $2}' | bc &> tmp.log
paste bench.log tmp.log | gawk '{printf "%-35s %s\n", $1, $4}'
rm -rf tmp.log