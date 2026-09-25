[yessaimon@archlinux fastcin_bench]$ python3 bench_fastout.py
========================================
Generating FastOut benchmark
========================================

========================================
Building
========================================
[ 23%]: <cout> cache compiling.release bench_cout.cpp
[ 28%]: <fastout_new> cache compiling.release bench_fastout_new.cpp
[ 28%]: <fastout_old> cache compiling.release bench_fastout_old.cpp
[ 28%]: <printf> cache compiling.release bench_printf.cpp
[ 28%]: <reference> cache compiling.release bench_reference.cpp
[ 28%]: <cout> linking.release cout
[ 42%]: <printf> linking.release printf
[ 47%]: <reference> linking.release reference
[ 71%]: <fastout_old> linking.release fastout_old
[ 85%]: <fastout_new> linking.release fastout_new
[100%]: build ok, spent 1.017s

========================================
FASTOUT BENCHMARK
10,000,000 integers
stdout -> /dev/null
========================================

--- fastout_old ---
time = 6.272464 s

--- fastout_new ---
time = 0.119423 s

--- printf ---
time = 0.502108 s

--- cout ---
time = 0.334303 s

--- reference ---
time = 0.117674 s

========================================
RESULTS
========================================
FastOut old : 6.272464 s
FastOut2    : 0.119423 s
printf      : 0.502108 s
cout        : 0.334303 s
reference   : 0.117674 s

Speed relative to FastOut2:
old FastOut / FastOut2 = 52.52x
printf / FastOut2      = 4.20x
cout / FastOut2        = 2.80x
reference / FastOut2   = 0.99x

Speedup of FastOut2 over old FastOut:
52.52x

========================================
DONE
========================================



the benchmark
