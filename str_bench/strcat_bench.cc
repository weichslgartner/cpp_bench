#include "fmt/format.h"
#include "absl/strings/str_cat.h"
#include "folly/FBString.h"
#include <benchmark/benchmark.h>
#include <sstream>
#include <string>
#include <utility>

std::string s1 = "very very long long string 1";
std::string s2 = "very very long long string 2";
std::string s3 = "very very long long string 3";

folly::fbstring fb_s1 { s1 };
folly::fbstring fb_s2 { s2 };
folly::fbstring fb_s3 { s3 };

static void BENCH_ABSEIL_STRCAT(benchmark::State &state) {
	for (auto _ : state) {
		std::string s = absl::StrCat(s1, s2, s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_ABSEIL_APPEND(benchmark::State &state) {
	for (auto _ : state) {
		std::string s { };
		absl::StrAppend(&s, s1, s2, s3);
		benchmark::DoNotOptimize(s);
	}
}


static void BENCH_STL_PLUS(benchmark::State &state) {
	for (auto _ : state) {
		auto s = s1 + s2 + s3;
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_STL_APPEND(benchmark::State &state) {
	for (auto _ : state) {
		std::string s { };
		s = s.append(s1).append(s2).append(s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_STL_APPEND_RESERVE(benchmark::State &state) {
	for (auto _ : state) {
		std::string s { };
		s.reserve(s1.size() + s2.size() + s3.size());
		s = s.append(s1).append(s2).append(s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_STL_OSTREAM(benchmark::State &state) {
	for (auto _ : state) {
		  std::ostringstream oss{};
		  oss << s1 << s2 << s3;
		  std::string s{ std::move(oss.str())};
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_STL_SSTREAM(benchmark::State &state) {
	for (auto _ : state) {
		std::stringstream ss{};
		ss << s1 << s2 << s3;
		std::string s{ std::move(ss.str())};
		benchmark::DoNotOptimize(s);
	}
}


static void BENCH_FOLLY_PLUS(benchmark::State &state) {
	for (auto _ : state) {
		auto s = fb_s1 + fb_s2 + fb_s3;
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_FOLLY_APPEND(benchmark::State &state) {
	for (auto _ : state) {
		folly::fbstring s { };
		s = s.append(fb_s1).append(fb_s2).append(fb_s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_FOLLY_APPEND_RESERVE(benchmark::State &state) {
	for (auto _ : state) {
		folly::fbstring s { };
		s.reserve(fb_s1.size() + fb_s2.size() + fb_s3.size());
		s = s.append(fb_s1).append(fb_s2).append(fb_s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_FMT(benchmark::State &state) {
	for (auto _ : state) {
		auto s = fmt::format("{}{}{}", s1, s2, s3);
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_C_SNPRINTF(benchmark::State &state) {
	for (auto _ : state) {
		std::string s { };
		s.resize(s1.size() + s2.size() + s3.size());
		std::snprintf(&s[0], s.size(), "%s%s%s", s1.c_str(), s2.c_str(), s3.c_str());
		benchmark::DoNotOptimize(s);
	}
}

static void BENCH_C_STRCAT(benchmark::State &state) {
	for (auto _ : state) {
		std::string s { };
		s.resize(s1.size() + s2.size() + s3.size());
		std::strcat(&s[0], s1.c_str());
		std::strcat(&s[0], s2.c_str());
		std::strcat(&s[0], s3.c_str());
		benchmark::DoNotOptimize(s);
	}
}

BENCHMARK(BENCH_ABSEIL_STRCAT)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_ABSEIL_APPEND)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_STL_PLUS)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_STL_APPEND)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_STL_APPEND_RESERVE)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_STL_OSTREAM)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_STL_SSTREAM)->Unit(benchmark::kNanosecond);

BENCHMARK(BENCH_FOLLY_PLUS)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_FOLLY_APPEND)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_FOLLY_APPEND_RESERVE)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_C_STRCAT)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_C_SNPRINTF)->Unit(benchmark::kNanosecond);
BENCHMARK(BENCH_FMT)->Unit(benchmark::kNanosecond);

BENCHMARK_MAIN();

