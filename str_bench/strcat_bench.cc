#include "fmt/format.h"
#include "absl/strings/str_cat.h"
#include "folly/FBString.h"
#include <benchmark/benchmark.h>
#include <cstring>
#include <sstream>
#include <string>
#include <utility>

constexpr auto s1_glob { "very very long long string 1 very very long long string 1 very very long long string 1" };
constexpr auto s2_glob { "very very long long string 2 very very long long string 2 very very long long string 2" };
constexpr auto s3_glob { "very very long long string 3 very very long long string 3 very very long long string 3" };
constexpr auto len { std::strlen(s1_glob) };

static void BENCH_STL_PLUS(benchmark::State &state) {
	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		auto s = s1 + s2 + s3;
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_STL_APPEND(benchmark::State &state) {
	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		std::string s { };
		s = s.append(s1).append(s2).append(s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_STL_APPEND_RESERVE(benchmark::State &state) {
	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		std::string s { };
		s.reserve(s1.size() + s2.size() + s3.size());
		s = s.append(s1).append(s2).append(s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_ABSEIL_STRCAT(benchmark::State &state) {
	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		std::string s = absl::StrCat(s1, s2, s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_ABSEIL_APPEND(benchmark::State &state) {
	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		std::string s { };
		absl::StrAppend(&s, s1, s2, s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_FOLLY_PLUS(benchmark::State &state) {
	folly::fbstring s1 { s1_glob, len / state.range(0) };
	folly::fbstring s2 { s1_glob, len / state.range(0) };
	folly::fbstring s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		auto s = s1 + s2 + s3;
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_FOLLY_APPEND(benchmark::State &state) {
	folly::fbstring s1 { s1_glob, len / state.range(0) };
	folly::fbstring s2 { s1_glob, len / state.range(0) };
	folly::fbstring s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		folly::fbstring s { };
		s = s.append(s1).append(s2).append(s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_FOLLY_APPEND_RESERVE(benchmark::State &state) {
	folly::fbstring s1 { s1_glob, len / state.range(0) };
	folly::fbstring s2 { s1_glob, len / state.range(0) };
	folly::fbstring s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		folly::fbstring s { };
		s.reserve(s1.size() + s2.size() + s3.size());
		s = s.append(s1).append(s2).append(s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_C_SNPRINTF(benchmark::State &state) {

	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		std::string s { };
		s.resize(s1.size() + s2.size() + s3.size());
		std::snprintf(&s[0], s.size(), "%s%s%s", s1.c_str(), s2.c_str(), s3.c_str());
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_C_STRCAT(benchmark::State &state) {
	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		std::string s { };
		s.resize(s1.size() + s2.size() + s3.size());
		std::strcat(&s[0], s1.c_str());
		std::strcat(&s[0], s2.c_str());
		std::strcat(&s[0], s3.c_str());
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_FMT(benchmark::State &state) {
	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		auto s = fmt::format("{}{}{}", s1, s2, s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_STL_OSTREAM(benchmark::State &state) {
	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		std::ostringstream oss { };
		oss << s1 << s2 << s3;
		std::string s { std::move(oss.str()) };
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_STL_SSTREAM(benchmark::State &state) {
	std::string s1 { s1_glob, len / state.range(0) };
	std::string s2 { s1_glob, len / state.range(0) };
	std::string s3 { s1_glob, len / state.range(0) };
	for (auto _ : state) {
		std::stringstream ss { };
		ss << s1 << s2 << s3;
		std::string s { std::move(ss.str()) };
		benchmark::DoNotOptimize(s);
	}
}


BENCHMARK(BENCH_STL_PLUS)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_STL_APPEND)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_STL_APPEND_RESERVE)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_STL_OSTREAM)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_STL_SSTREAM)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_FMT)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_C_STRCAT)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_C_SNPRINTF)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_ABSEIL_STRCAT)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_ABSEIL_APPEND)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_FOLLY_PLUS)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_FOLLY_APPEND)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);
BENCHMARK(BENCH_FOLLY_APPEND_RESERVE)->Unit(benchmark::kNanosecond)->Arg(3)->Arg(2)->Arg(1);


BENCHMARK_MAIN();

