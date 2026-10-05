# SocketLearning

A step-by-step educational C++ solution designed to master network programming—ranging from low-level sockets up to application-layer HTTP web servers. This project is built using Visual Studio 2026, C++23, and the Win32 API (Winsock2).

Rather than just utilizing basic APIs, this repository implements robust system programming methodologies, including concurrent thread pool management, OS signal handling, non-blocking I/O multiplexing, and network bottleneck mitigation.

## 🚀 Project Evolution & Architecture

The solution contains five distinct phases organized into separate folders inside a single Visual Studio solution. This structure allows you to visually compare code diffs and analyze architectural trade-offs across different communication models.

### 📂 Shared Sub-Project (`SocketCommon`)
* **Winsock RAII Wrapper**: Implements a dedicated `WinsockManager` class that encapsulates `WSAStartup` and `WSACleanup` using the RAII pattern. This serves as the foundation for all steps, ensuring resource cleanup even during unexpected termination.

---

### 📦 Step 1: `01_Basic_Echo` (Minimal Synchronous Communication)
* **Overview**: A basic baseline project covering the absolute minimum requirements to establish a connection, exchange a single message, and exit.
* **Core Concepts**: The fundamental Winsock lifecycle: `socket` ➔ `bind` ➔ `listen` ➔ `accept` ➔ `send` / `recv`.

### 📦 Step 2: `02_Continuous_Echo` (Persistent Chat & Disconnection Detection)
* **Overview**: Introduces a continuous `while` loop that allows sustained communication until an `exit` command is sent or a connection drops.
* **Core Concepts**: Checking the return values of `recv()` (`>0` / `0` / `-1`) to precisely distinguish between graceful disconnections (FIN packets) and sudden client crashes.

### 📦 Step 3: `03_Multi_Client` (Thread Pool & Graceful Signal Handling)
* **Overview**: A robust concurrent server leveraging the native Windows Thread Pool API (`TrySubmitThreadpoolCallback`).
* **Core Concepts**:
  * **Modern C++23 Design**: Combined `std::unique_ptr` with ownership transfer (`.release()`) to safely bridge data into the legacy Win32 C-style API, completely eliminating raw `new` / `delete` usage.
  * **Encapsulation & Singleton**: Structured the server as a class using Meyers' Singleton (returning a reference). Utilized `static` member functions and `static inline` pointers to safely hide implementation details from the entry point.
  * **OS Signal Handling**: Used `SetConsoleCtrlHandler` to intercept `Ctrl+C` inputs and window close events when running outside the debugger (e.g., in PowerShell). Implemented `shutdown()` to immediately break the main thread out of its blocking `accept()` call, allowing a graceful exit route through the RAII destructor chain.
  * **Event-Driven Client**: Resolved client-side console input freezing (`std::getline`) by introducing a dedicated background thread using `std::jthread` (C++20/23 automatically joining thread) to immediately handle server drops while keeping console input highly responsive.

### 📦 Step 4: `04_NonBlocking_Select` (1-Thread I/O Multiplexing Server)
* **Overview**: An optimized single-threaded architecture capable of handling multiple connections simultaneously without spawning new threads.
* **Core Concepts**: 
  * Configuring sockets to non-blocking mode (`FIONBIO`) and monitoring them collectively using the `select` function.
  * Leveraging `std::erase_if` (C++20/23) with lambda predicates to close disconnected sockets and erase them from management vectors in a single operation.

### 📦 Step 5: `05_Web_Server` (Custom Single-Threaded HTTP Server)
* **Overview**: Transforms the multiplexed core into a functional web server that communicates with production web browsers (e.g., Google Chrome, Microsoft Edge).
* **Core Concepts**:
  * **File System Integration**: Utilizing `std::ifstream` to stream physical HTML files directly from disk into network buffers.
  * **Dynamic Routing**: Parsing the first line of incoming raw HTTP requests (e.g., `GET /sub.html HTTP/1.1`) using `std::istringstream` to dynamically fetch requested pages (`index.html` / `sub.html`) or return a proper `404 Not Found` response.
  * **Web-Compliant Half-Close Routine**: Resolved network freezes caused by parallel browser requests (such as `/favicon.ico`) and Keep-Alive behaviors. The server gracefully notifies the browser that transmission is complete using `shutdown(s, SD_SEND)`, consumes remaining incoming data, and then safely calls `closesocket()`.

---

## 🛠️ Environment & Requirements
* **Operating System**: Windows 11
* **IDE**: Visual Studio 2026 (MSVC Compiler)
* **Language Standard**: C++23 (`/std:c++latest`)
* **Dependencies**: Winsock2 Library (`ws2_32.lib`), Windows SDK

## 🏃 Getting Started
1. Open the `.sln` solution file in Visual Studio 2026.
2. Right-click the desired step's project folders (Server/Client) and configure them via "Set as StartUp Project" (or use "Multiple Startup Projects" to run both simultaneously).
3. To prevent the Visual Studio debugger from intercepting OS signals—and to fully observe the native console control handler routines (`Ctrl+C` graceful exits)—run the compiled `.exe` files directly from a terminal like PowerShell.
