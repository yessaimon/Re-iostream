<p align="center">
  <b>English</b> • <a href="README_RU.md">Русский</a>
</p>

---

# 🚀 FastCin — Fast I/O Replacement for `std::cin`

## Overview

**FastCin** is an ultra-fast, header-only replacement for `std::cin` in C++.

It is designed specifically for competitive programming, contests, and performance-critical applications where standard C++ I/O can become a bottleneck.

## Performance Benchmark

Reading **1,000,000 32-bit integers** on Linux with `g++ -O3`:

```text
std::cin (default):       ~1200 ms  (TLE 😢)
std::cin + sync disabled:  ~800 ms  (Still slow)
FastCin:                    ~50 ms  (AC 🏆)
```

> **Speedup: ~24× faster!** 🔥

### Why is it so fast?

* **Direct `fread()`** — reads data in large chunks instead of relying on heavyweight `streambuf` operations.
* **Cache-friendly buffer** — uses a dedicated heap buffer, 64 KB by default.
* **`std::from_chars`** — fast, allocation-free, locale-independent numeric parsing.
* **Inlined ASCII whitespace checking** — skips whitespace manually without expensive C locale functions.

---

## Bug Fixes & Edge Cases

### 🔴 Bug #1: Lost Sign on Invalid Input

**Issue:** Reading `+` or `-` without digits following the sign consumed the character and could break subsequent reads.

**Fix:** A `sign_start_pos` rollback point was added. If no digits follow the sign, the buffer position is automatically restored.

### 🔴 Bug #2: Broken Line Endings (`\r\n`)

**Issue:** `getline` could leave trailing `\n` characters when processing CRLF files.

**Fix:** Proper cross-platform handling for:

* `\r\n` — Windows
* `\n` — Linux/macOS
* `\r` — classic Mac OS

---

## Usage

### 1. Basic Input — Drop-in Replacement

```cpp
#include "FastCin.hpp"

int main() {
    int n;
    std::string s;
    double x;

    cin >> n >> s >> x;
}
```

### 2. Reading Entire Lines

```cpp
std::string line;

// Option 1: Direct method
cin.getline(line);

// Option 2: Proxy wrapper
cin >> in::line(line);
```

### 3. Reading Until EOF

```cpp
while (cin.has_next()) {
    int val;
    cin >> val;

    // Process val
}
```

### 4. Reading From a File

```cpp
FILE* f = std::fopen("input.txt", "rb");

FastCin file_cin(f, 1 << 17); // 128 KB buffer

int n;
file_cin >> n;

std::fclose(f);
```

---

## Compilation

Requires **C++20** or newer.

The library uses features such as `<concepts>` and `<charconv>`.

### GCC / Clang

```bash
g++ -O3 -std=c++20 main.cpp -o app
```

### C++23

```bash
g++ -O3 -std=c++23 main.cpp -o app
```

---

## API Reference

| Method / Operator  | Description                                                                           |
| ------------------ | ------------------------------------------------------------------------------------- |
| `cin >> x`         | Reads `int`, `long long`, `float`, `double`, `std::string`, and other supported types |
| `cin.getline(str)` | Reads an entire line up to `\n`, `\r\n`, or `\r`                                      |
| `cin.has_next()`   | Returns `true` if non-whitespace characters remain                                    |
| `cin.is_eof()`     | Returns `true` if the end of the stream has been reached                              |
| `cin.reset(FILE*)` | Rebinds the instance to another stream such as `stdin` or a file                      |

---

Made with 🔥 for competitive programmers and performance nerds.
