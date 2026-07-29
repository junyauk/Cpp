# 09_AtomicWait

## Overview

This project demonstrates C++20 atomic wait/notify facilities (`std::atomic::wait` and `std::atomic::notify_one`) for efficient thread synchronization. The examples show producer/consumer coordination using atomic state changes without busy-waiting.

## Requirements

- C++20-capable compiler (Visual Studio 2022 recommended).
- Project configured to use the C++20 language standard.

## Build

1. Open `C++20Features.sln` in Visual Studio 2022.  
2. Ensure the C++ Language Standard is set to C++20 (Project Properties → C/C++ → __Language__ → __C++ Language Standard__).  
3. Build the `09_AtomicWait` project or the entire solution.

Precompiled headers (`pch.*`) are provided for convenience.

## Contents

- `AtomicWait_Basic.h`  
  - `AtomicWait_Basic::AtomicWaitBasic` demonstrates:
    - `consumerTask(int expectedValue)` — waits efficiently with `m_sharedCounter.wait(0)`.
    - `producerTask(int setValue)` — updates the atomic counter and calls `m_sharedCounter.notify_one()`.
    - `runWaitNotify(int expectedValue)` — runs producer and consumer threads and returns the final counter value.
  - Shows practical patterns for safe notification and handling of potential spurious wake-ups.

- `09_AtomicWait.vcxproj` — Visual Studio project file.
- `pch.h` / `pch.cpp` — precompiled header support.

## Tests

- `09_AtomicWaitTest` contains unit tests that exercise producer/consumer coordination and validate notification semantics. Run tests from Visual Studio Test Explorer or execute the produced test binary from the test project's output directory.

## Contributing

- Add focused, deterministic tests for new synchronization cases.
- Avoid long sleep-based timing assumptions in tests; prefer observable state assertions after synchronization.
- Document any platform-specific behavior or assumptions.

## License

No license file is included by default. Add a `LICENSE` file if you intend to publish or share the repository.