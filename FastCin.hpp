```cpp
#pragma once
#include <cstdio>
#include <charconv>
#include <string>
#include <concepts>
#include <vector>

namespace in {
    struct line {
        std::string& target;
        line(std::string& str) : target(str) {}
    };
}

class FastCin {
private:
    std::vector<char> buffer;
    FILE* stream;
    int buf_pos = 0;
    int buf_end = 0;
    bool eof_reached = false;

    void refill_buffer() {
        if (eof_reached) return;
        buf_pos = 0;
        buf_end = static_cast<int>(std::fread(buffer.data(), 1, buffer.size(), stream));
        if (buf_end < static_cast<int>(buffer.size())) {
            eof_reached = true;
        }
    }

    inline int peek_char() {
        if (buf_pos >= buf_end) {
            refill_buffer();
            if (buf_pos >= buf_end) return EOF;
        }
        return static_cast<unsigned char>(buffer[buf_pos]);
    }

    inline int next_char() {
        int ch = peek_char();
        if (ch != EOF) buf_pos++;
        return ch;
    }

    static inline bool is_ascii_space(int ch) {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || 
               ch == '\v' || ch == '\f';
    }

    void skip_whitespace() {
        while (true) {
            if (buf_pos >= buf_end) {
                refill_buffer();
                if (buf_pos >= buf_end) break;
            }
            if (!is_ascii_space(static_cast<unsigned char>(buffer[buf_pos]))) break;
            buf_pos++;
        }
    }

public:
    FastCin(FILE* input_stream = stdin, size_t buffer_size = 1 << 16) 
        : buffer(buffer_size), stream(input_stream) {}

    template <typename T>
    requires std::integral<T> || std::floating_point<T>
    FastCin& operator>>(T& value) {
        skip_whitespace();
        
        char num_buf[64];
        int i = 0;
        int ch = peek_char();
        
        int sign_start_pos = buf_pos;
        
        if (ch == '-' || ch == '+') {
            num_buf[i++] = static_cast<char>(next_char());
            ch = peek_char();
        }
        
        if (ch == EOF || is_ascii_space(ch)) {
            if (i == 1) {
                buf_pos = sign_start_pos;
            }
            value = T{};
            return *this;
        }
        
        while (ch != EOF && !is_ascii_space(ch) && i < 63) {
            num_buf[i++] = static_cast<char>(next_char());
            ch = peek_char();
        }
        
        num_buf[i] = '\0';
        
        auto [ptr, ec] = std::from_chars(num_buf, num_buf + i, value);
        if (ec != std::errc()) {
            value = T{};
        }
        
        return *this;
    }

    FastCin& operator>>(std::string& str) {
        str.clear();
        skip_whitespace();
        
        while (true) {
            if (buf_pos >= buf_end) {
                refill_buffer();
                if (buf_pos >= buf_end) break;
            }
            
            int start = buf_pos;
            while (buf_pos < buf_end && !is_ascii_space(static_cast<unsigned char>(buffer[buf_pos]))) {
                buf_pos++;
            }
            
            if (buf_pos > start) {
                str.append(&buffer[start], buf_pos - start);
            } else {
                break;
            }
        }
        return *this;
    }

    FastCin& operator>>(in::line proxy) {
        proxy.target.clear();
        
        while (true) {
            if (buf_pos >= buf_end) {
                refill_buffer();
                if (buf_pos >= buf_end) break;
            }
            
            int start = buf_pos;
            
            while (buf_pos < buf_end && 
                   buffer[buf_pos] != '\r' && 
                   buffer[buf_pos] != '\n') {
                buf_pos++;
            }
            
            if (buf_pos > start) {
                proxy.target.append(&buffer[start], buf_pos - start);
            }
            
            if (buf_pos < buf_end) {
                if (buffer[buf_pos] == '\r') {
                    buf_pos++;
                    if (buf_pos < buf_end && buffer[buf_pos] == '\n') {
                        buf_pos++;
                    }
                } else if (buffer[buf_pos] == '\n') {
                    buf_pos++;
                }
                break;
            }
        }
        
        return *this;
    }

    void getline(std::string& str) {
        *this >> in::line(str);
    }

    bool has_next() {
        skip_whitespace();
        return peek_char() != EOF;
    }

    bool is_eof() const {
        return eof_reached && buf_pos >= buf_end;
    }

    void reset(FILE* new_stream = stdin) {
        stream = new_stream;
        buf_pos = 0;
        buf_end = 0;
        eof_reached = false;
    }
};

inline FastCin cin(stdin, 1 << 16);
```
