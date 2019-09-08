
# mi_allocator

C++17 drop-in replacement for `std::allocator`, using `mi_malloc` for a back-end.


## Benchmarking

Below the results for pushing a random number of values into a `std::vector` that is already filled with a random number of values (the total size after the operation is at most 4, 64, 1024 etc.), comparing the `std::allocator` and `sax::mi_allocator`. Binary compiled with vc-16.2.4, AVX2, /LTCG.

`sax::mi_allocator` is 60% faster for allocations up to size 4, up till 325% faster for (consecutive) allocations up till 4'194'304. After that (at some point) on my machine, disk-swapping starts to kick in.

    09/08/19 10:40:55
    Running Y:\REPOS\mi_allocator\x64\Release\mi_allocator.exe
    Run on (4 X 1995 MHz CPU s)
    CPU Caches:
      L1 Data 32K (x2)
      L1 Instruction 32K (x2)
      L2 Unified 262K (x2)
      L3 Unified 3145K (x1)
    ----------------------------------------------------------------------------------------------------------------------------------------------------------
    Benchmark                                                                                                                Time             CPU   Iterations
    ----------------------------------------------------------------------------------------------------------------------------------------------------------
    bm_emplace_back_random<std::vector<value_type>>/4/4194304/repeats:4_mean                                               654 ns          652 ns            4
    bm_emplace_back_random<std::vector<value_type>>/4/4194304/repeats:4_median                                             652 ns          656 ns            4
    bm_emplace_back_random<std::vector<value_type>>/4/4194304/repeats:4_stddev                                            13.4 ns         34.6 ns            4
    bm_emplace_back_random<std::vector<value_type>>/64/4194304/repeats:4_mean                                              948 ns          994 ns            4
    bm_emplace_back_random<std::vector<value_type>>/64/4194304/repeats:4_median                                            954 ns          994 ns            4
    bm_emplace_back_random<std::vector<value_type>>/64/4194304/repeats:4_stddev                                           15.7 ns         65.1 ns            4
    bm_emplace_back_random<std::vector<value_type>>/1024/4194304/repeats:4_mean                                           3626 ns         3632 ns            4
    bm_emplace_back_random<std::vector<value_type>>/1024/4194304/repeats:4_median                                         3524 ns         3498 ns            4
    bm_emplace_back_random<std::vector<value_type>>/1024/4194304/repeats:4_stddev                                          354 ns          354 ns            4
    bm_emplace_back_random<std::vector<value_type>>/16384/4194304/repeats:4_mean                                         25006 ns        23228 ns            4
    bm_emplace_back_random<std::vector<value_type>>/16384/4194304/repeats:4_median                                       25019 ns        22600 ns            4
    bm_emplace_back_random<std::vector<value_type>>/16384/4194304/repeats:4_stddev                                         386 ns         2234 ns            4
    bm_emplace_back_random<std::vector<value_type>>/262144/4194304/repeats:4_mean                                      1742890 ns      1811594 ns            4
    bm_emplace_back_random<std::vector<value_type>>/262144/4194304/repeats:4_median                                    1745266 ns      1788949 ns            4
    bm_emplace_back_random<std::vector<value_type>>/262144/4194304/repeats:4_stddev                                      10217 ns        97837 ns            4
    bm_emplace_back_random<std::vector<value_type>>/4194304/4194304/repeats:4_mean                                    34633198 ns     34268466 ns            4
    bm_emplace_back_random<std::vector<value_type>>/4194304/4194304/repeats:4_median                                  34621030 ns     33735795 ns            4
    bm_emplace_back_random<std::vector<value_type>>/4194304/4194304/repeats:4_stddev                                    562463 ns      1867866 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/4/4194304/repeats:4_mean                409 ns          398 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/4/4194304/repeats:4_median              409 ns          401 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/4/4194304/repeats:4_stddev             2.78 ns         10.3 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/64/4194304/repeats:4_mean               533 ns          499 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/64/4194304/repeats:4_median             532 ns          467 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/64/4194304/repeats:4_stddev            2.28 ns         77.6 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/1024/4194304/repeats:4_mean            1802 ns         1750 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/1024/4194304/repeats:4_median          1803 ns         1742 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/1024/4194304/repeats:4_stddev          4.89 ns          159 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/16384/4194304/repeats:4_mean          36056 ns        35871 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/16384/4194304/repeats:4_median        36080 ns        35679 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/16384/4194304/repeats:4_stddev          165 ns          735 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/262144/4194304/repeats:4_mean        525654 ns       498744 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/262144/4194304/repeats:4_median      526444 ns       481306 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/262144/4194304/repeats:4_stddev       10658 ns        50139 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/4194304/4194304/repeats:4_mean     10638554 ns     10463170 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/4194304/4194304/repeats:4_median   10649298 ns     10742188 ns            4
    bm_emplace_back_random<std::vector<value_type, sax::mi_allocator<value_type>>>/4194304/4194304/repeats:4_stddev      74735 ns       867502 ns            4


## Dependencies

* [benchmark](https://github.com/google/benchmark) (for benchmarking)
* [mimalloc](https://github.com/microsoft/mimalloc)
* [Sax](https://github.com/degski/Sax) (for benchmarking)
