
// MIT License
//
// Copyright (c) 2019 degski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdint>

#include <vector>

// The below define is just for my (degski) private purposes, it directs auto-
// linking (to the correct lib), both for vc and clang. It has no effect,
// otherwise.
#if defined( _WIN32 )
#    if not defined( USE_MIMALLOC_LTO )
#        define USE_MIMALLOC_LTO 1
#    endif
#    if not defined( USE_KSMALLOC_LTO )
#        define USE_KSMALLOC_LTO 1
#    endif
#endif

#include <mi_allocator.hpp>

#include <ks_allocator.hpp>

#include <benchmark/benchmark.h>

#ifdef _WIN32
#    pragma comment( lib, "Shlwapi.lib" )
#    ifndef NDEBUG
#        pragma comment( lib, "benchmark_maind.lib" )
#        pragma comment( lib, "benchmarkd.lib" )
#    else
#        pragma comment( lib, "benchmark_main.lib" )
#        pragma comment( lib, "benchmark.lib" )
#    endif
#endif

#include <sax/jsf.hpp>
#include <sax/uniform_int_distribution.hpp>

template<typename ValueType>
static void custom_arguments ( benchmark::internal::Benchmark * b ) {
    long long const bs = 2ll, es = 1ll << 27;
    for ( long long i = bs; i <= es; i <<= 2 )
        b->Args ( { i, es } );
}

template<class Container>
void bm_emplace_back_random1 ( benchmark::State & state ) noexcept {
    using value_type = typename Container::value_type;
    using size_type  = typename Container::size_type;
    static sax::jsf64 gen ( 123ull );
    for ( auto _ : state ) {
        state.PauseTiming ( );
        size_type const is =
            sax::uniform_int_distribution<size_type> ( size_type{ 0 }, static_cast<size_type> ( state.range ( 0u ) - 1 ) ) ( gen );
        state.ResumeTiming ( );
        Container data ( static_cast<size_type> ( is ) );
        benchmark::DoNotOptimize ( data.data ( ) );
        state.PauseTiming ( );
        size_type i =
            sax::uniform_int_distribution<size_type> ( size_type{ 1 }, static_cast<size_type> ( state.range ( 0u ) - is ) ) ( gen );
        state.ResumeTiming ( );
        while ( i-- )
            data.emplace_back ( static_cast<value_type> ( i ) );
        benchmark::ClobberMemory ( );
    }
}

template<class Container>
void bm_emplace_back_random2 ( benchmark::State & state ) noexcept {
    using value_type = typename Container::value_type;
    using size_type  = typename Container::size_type;
    static sax::jsf64 gen ( 123ull );
    for ( auto _ : state ) {
        state.PauseTiming ( );
        size_type const is =
            sax::uniform_int_distribution<size_type> ( size_type{ 0 }, static_cast<size_type> ( state.range ( 0u ) - 1 ) ) ( gen );
        state.ResumeTiming ( );
        Container data ( static_cast<size_type> ( is ) );
        benchmark::DoNotOptimize ( data.data ( ) );
        state.PauseTiming ( );
        size_type i =
            sax::uniform_int_distribution<size_type> ( size_type{ 1 }, static_cast<size_type> ( state.range ( 0u ) - is ) ) ( gen );
        state.ResumeTiming ( );
        while ( i-- )
            data.emplace_back ( static_cast<value_type> ( i ) );
        benchmark::ClobberMemory ( );
    }
}

template<class Container>
void bm_emplace_back_random3 ( benchmark::State & state ) noexcept {
    using value_type = typename Container::value_type;
    using size_type  = typename Container::size_type;
    static sax::jsf64 gen ( 123ull );
    for ( auto _ : state ) {
        state.PauseTiming ( );
        size_type const is =
            sax::uniform_int_distribution<size_type> ( size_type{ 0 }, static_cast<size_type> ( state.range ( 0u ) - 1 ) ) ( gen );
        state.ResumeTiming ( );
        Container data ( static_cast<size_type> ( is ) );
        benchmark::DoNotOptimize ( data.data ( ) );
        state.PauseTiming ( );
        size_type i =
            sax::uniform_int_distribution<size_type> ( size_type{ 1 }, static_cast<size_type> ( state.range ( 0u ) - is ) ) ( gen );
        state.ResumeTiming ( );
        while ( i-- )
            data.emplace_back ( static_cast<value_type> ( i ) );
        benchmark::ClobberMemory ( );
    }
}

template<class Container>
void bm_emplace_back_random4 ( benchmark::State & state ) noexcept {
    using value_type = typename Container::value_type;
    using size_type  = typename Container::size_type;
    static sax::jsf64 gen ( 123ull );
    for ( auto _ : state ) {
        state.PauseTiming ( );
        size_type const is =
            sax::uniform_int_distribution<size_type> ( size_type{ 0 }, static_cast<size_type> ( state.range ( 0u ) - 1 ) ) ( gen );
        state.ResumeTiming ( );
        Container data ( static_cast<size_type> ( is ) );
        benchmark::DoNotOptimize ( data.data ( ) );
        state.PauseTiming ( );
        size_type i =
            sax::uniform_int_distribution<size_type> ( size_type{ 1 }, static_cast<size_type> ( state.range ( 0u ) - is ) ) ( gen );
        state.ResumeTiming ( );
        while ( i-- )
            data.emplace_back ( static_cast<value_type> ( i ) );
        benchmark::ClobberMemory ( );
    }
}

#include <pector/malloc_allocator.h>
#include <pector/mimalloc_allocator.h>
#include <pector/pector.h>

template<typename T, typename S>
using alpector = pt::pector<T, std::allocator<T>, S, pt::default_recommended_size, false>;
template<typename T, typename S>
using mapector = pt::pector<T, pt::malloc_allocator<T, true, false>, S, pt::default_recommended_size, false>;
template<typename T, typename S>
using mipector = pt::pector<T, pt::mimalloc_allocator<T, true, false>, S, pt::default_recommended_size, false>;

constexpr int repeats = 8;
using value_type      = std::uint32_t;
using size_type       = std::uint64_t;

BENCHMARK_TEMPLATE ( bm_emplace_back_random1, std::vector<value_type> )
    ->Apply ( custom_arguments<value_type> )
    ->Repetitions ( repeats )
    ->ReportAggregatesOnly ( true );
BENCHMARK_TEMPLATE ( bm_emplace_back_random2, std::vector<value_type, sax::mi_allocator<value_type>> )
    ->Apply ( custom_arguments<value_type> )
    ->Repetitions ( repeats )
    ->ReportAggregatesOnly ( true );
BENCHMARK_TEMPLATE ( bm_emplace_back_random3, std::vector<value_type, sax::ks_allocator<value_type>> )
    ->Apply ( custom_arguments<value_type> )
    ->Repetitions ( repeats )
    ->ReportAggregatesOnly ( true );
BENCHMARK_TEMPLATE ( bm_emplace_back_random4, mipector<value_type, size_type> )
    ->Apply ( custom_arguments<value_type> )
    ->Repetitions ( repeats )
    ->ReportAggregatesOnly ( true );
