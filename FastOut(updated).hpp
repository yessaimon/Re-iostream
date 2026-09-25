#pragma once

#include <cstdio>
#include <charconv>
#include <cstring>
#include <string>
#include <type_traits>

class FastOut {
private:
    static constexpr std::size_t BUFFER_SIZE = 65536;

    char buffer[BUFFER_SIZE];
    std::size_t pos = 0;

    void flush_buffer() {
        if (pos) {
            std::fwrite(buffer, 1, pos, stdout);
            pos = 0;
        }
    }

    void put(char c) {
        if (pos == BUFFER_SIZE)
            flush_buffer();

        buffer[pos++] = c;
    }

    void write(const char* data, std::size_t size) {
        while (size) {
            std::size_t space = BUFFER_SIZE - pos;
            std::size_t n = size < space ? size : space;

            std::memcpy(buffer + pos, data, n);

            pos += n;
            data += n;
            size -= n;

            if (pos == BUFFER_SIZE)
                flush_buffer();
        }
    }

    template <typename T>
    void write_number(T value) {
        char tmp[32];

        auto result = std::to_chars(
            tmp,
            tmp + sizeof(tmp),
            value
        );

        if (result.ec == std::errc())
            write(tmp, result.ptr - tmp);
    }

    template <typename T>
    void write_one(const T& value) {
        using D = std::decay_t<T>;

        if constexpr (std::is_same_v<D, std::string>) {
            write(value.data(), value.size());
        }
        else if constexpr (
            std::is_same_v<D, const char*> ||
            std::is_same_v<D, char*>
        ) {
            write(value, std::strlen(value));
        }
        else if constexpr (std::is_same_v<D, char>) {
            put(value);
        }
        else if constexpr (
            std::is_integral_v<D>
        ) {
            write_number(value);
        }
        else if constexpr (
            std::is_floating_point_v<D>
        ) {
            write_number(value);
        }
    }

public:
    ~FastOut() {
        flush();
    }

    void flush() {
        flush_buffer();
    }

    template <typename T>
    void print(const T& value) {
        write_one(value);
        put('\n');
    }

    template <typename First, typename... Rest>
    void print(const First& first, const Rest&... rest) {
        write_one(first);

        ((put(' '), write_one(rest)), ...);

        put('\n');
    }
};

inline FastOut out;


//This version should be faster, but I'm afraid to use it; still, I'll keep improving it and might replace it eventually.
