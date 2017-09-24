rm ./bin/gav*

echo Building with GCC
gcc -Wall -Wextra -Ofast -m64 -march=native -fwhole-program -fomit-frame-pointer -fPIC -pipe -fexpensive-optimizations gav.c -o ./bin/gav_gcc
strip -S ./bin/gav_gcc
time ./bin/gav_gcc>./bin/gav.ppm
echo GCC results

echo

echo Building with Clang
clang -Wall -Wextra -Ofast -m64 -march=native -fomit-frame-pointer -fPIC -pipe gav.c -o ./bin/gav_clang
strip -S ./bin/gav_clang
time ./bin/gav_clang>/dev/null
echo Clang results

display ./bin/gav.ppm

