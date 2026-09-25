#pragma once
#include <cstdio>
#include <string>
#include <type_traits>

template <typename T>
inline void print(const T& v_ref) {
    using D = std::decay_t<T>;
    
    if constexpr (std::is_same_v<D, int>) {
        printf("%d\n", v_ref);
    } else if constexpr (std::is_same_v<D, long>) {
        printf("%ld\n", v_ref);
    } else if constexpr (std::is_same_v<D, long long>) {
        printf("%lld\n", v_ref);
    } else if constexpr (std::is_same_v<D, unsigned int>) {
        printf("%u\n", v_ref);
    } else if constexpr (std::is_same_v<D, unsigned long>) {
        printf("%lu\n", v_ref);
    } else if constexpr (std::is_same_v<D, unsigned long long>) {
        printf("%llu\n", v_ref);
    } else if constexpr (std::is_same_v<D, double>) {
        printf("%g\n", v_ref);
    } else if constexpr (std::is_same_v<D, float>) {
        printf("%g\n", (double)v_ref);
    } else if constexpr (std::is_same_v<D, std::string>) {
        printf("%s\n", v_ref.c_str());
    } else if constexpr (std::is_same_v<D, char*> || std::is_same_v<D, const char*>) {
        printf("%s\n", v_ref);
    } else if constexpr (std::is_same_v<D, char>) {
        printf("%c\n", v_ref);
    } else {
        printf("%s\n", v_ref);
    }
    fflush(stdout);
}

template <typename First, typename... Rest>
inline void print(const First& f, const Rest&... r) {
    using D = std::decay_t<First>;
    
    if constexpr (std::is_same_v<D, int>) {
        printf("%d", f);
    } else if constexpr (std::is_same_v<D, long>) {
        printf("%ld", f);
    } else if constexpr (std::is_same_v<D, long long>) {
        printf("%lld", f);
    } else if constexpr (std::is_same_v<D, unsigned int>) {
        printf("%u", f);
    } else if constexpr (std::is_same_v<D, unsigned long>) {
        printf("%lu", f);
    } else if constexpr (std::is_same_v<D, unsigned long long>) {
        printf("%llu", f);
    } else if constexpr (std::is_same_v<D, double>) {
        printf("%g", f);
    } else if constexpr (std::is_same_v<D, float>) {
        printf("%g", (double)f);
    } else if constexpr (std::is_same_v<D, std::string>) {
        printf("%s", f.c_str());
    } else if constexpr (std::is_same_v<D, char*> || std::is_same_v<D, const char*>) {
        printf("%s", f);
    } else if constexpr (std::is_same_v<D, char>) {
        printf("%c", f);
    } else {
        printf("%s", f);
    } 
//My head hurts so much
    
    if constexpr (sizeof...(r) > 0) {
        printf(" ");
        print(r...);
    } else {
        printf("\n");
        fflush(stdout);
    }
}

inline void println() {
    putchar('\n');
    fflush(stdout);
}
inline void flush_output() {
    fflush(stdout);
}
