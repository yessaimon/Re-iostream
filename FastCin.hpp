#pragma once
#include <cstdio>
#include <charconv>
#include <string>
#include <unistd.h>

class FastCin {
private:
    char buffer[65536];
    int fd;
    int pos = 0;
    int end = 0;

    void fill() {
        pos = 0;
        end = read(fd, buffer, 65536);
        if (end < 0) end = 0;
    }

    int peek() {
        if (pos >= end) {
            fill();
            if (pos >= end) return EOF;
        }
        return (unsigned char)buffer[pos];
    }

    int get() {
        int c = peek();
        if (c != EOF) pos++;
        return c;
    }

public:
    FastCin(int file_descriptor = 0) : fd(file_descriptor) {
    }

    template <typename T>
    FastCin& operator>>(T& v) {
        while (peek() <= 32 && peek() != EOF) pos++;
        
        char tmp[64];
        int i = 0;
        int c = peek();
        
        if ((c == '-' || c == '+') && i < 63) {
            tmp[i++] = get();
        }
        
        while ((c = peek()) > 32 && c != EOF && i < 63) {
            tmp[i++] = get();
        }
        
        if (i > 0) {
            tmp[i] = 0;
            std::from_chars(tmp, tmp + i, v);
        }
        
        return *this;
    }

    FastCin& operator>>(std::string& s) {
        s.clear();
        while (peek() <= 32 && peek() != EOF) pos++;
        
        int c = peek();
        while (c > 32 && c != EOF) {
            s += (char)get();
            c = peek();
        }
        return *this;
    }
};

FastCin cin(0);
