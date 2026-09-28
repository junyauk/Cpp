## 🟢 4. gRPC Server/Client Implementation Record & Configuration Manual

This section records the procedures, architectural shifts, and Visual Studio 2026-specific workarounds applied when migrating the DCOM motor control system to modern **gRPC (Google Remote Procedure Call)**.

### ⚙️ Environment Setup & Dependency Management (vcpkg)
1. The vast ecosystem of dependencies required for C++ gRPC development (including Protocol Buffers, OpenSSL, and gRPC Core) was managed and deployed seamlessly using **`vcpkg`**.
   * Installation Command: `vcpkg install grpc:x64-windows`
2. Executing `vcpkg integrate install` enabled flawless, automatic project integration with Visual Studio 2026. This eliminated the historical burden of manually configuring include directories, linker inputs, and library paths for each project.

### 📄 .proto File Architecture & Automated Generation
* A centralized interface blueprint, `device.proto`, was created inside the `src/Shared/` directory.
* Using the host tools provided by `vcpkg` (`protoc.exe` and `grpc_cpp_plugin.exe`), a single command instantaneously generated four unified C++ source and header files (`.pb.h/.cc`, `.grpc.pb.h/.cc`). 
* Both the Server and Client projects reference these exact identical source files, completely solving the duplicate code maintenance problems that plagued the DCOM architecture.

### ⚠️ Visual Studio 2026 (MSVC) Compiler Quirks & Resolutions
Due to modern deprecations introduced within upstream dependencies (such as Abseil's `MutexLock` reference-passing changes), the strict compliance settings of the Visual Studio compiler mistakenly treated benign third-party warnings as critical compile errors (`error C4996`), causing the build engine to halt.
* **The Definitive Fix:** Navigate to `Project Properties` ＞ `C/C++` ＞ `Command Line` ＞ `Additional Options` for both `GrpcServer` and `GrpcClient` projects, and apply the compiler override switch:
  ```text
  /wd4996
  ```
* *Note:* This forcefully suppresses the `C4996` deprecation errors during compilation. Accompanying warnings such as `C4819` (character code-page mismatches caused by localized Japanese Windows environments reading Western UTF-8 text headers) and `C4251` (DLL interface warnings) can be safely ignored, as verified by successful binary execution.

### 🔷 Modern C++ Best Practices (Resolving Error C2280)
When storing a `std::unique_ptr` (such as the communication `Stub`) inside the custom `GrpcDeviceClient` wrapper class, implicit copying of the class object causes the compiler to complain with `error C2280: attempting to reference a deleted function`.
* To enforce robust memory safety, the **copy constructor and copy assignment operator were explicitly disabled (`= delete`)**, while move semantics (`std::move`) were safely white-listed, aligning the system with standard modern C++ resource-management paradigms.

## 🟢 5. OPC UA Server Implementation Record & Configuration Manual

This section records the procedures and standard integration patterns applied when migrating the system to **OPC UA (Open Platform Communications Unified Architecture)** using the `open62541` library inside Visual Studio 2026.

### ⚙️ Architecture & Package Integration (vcpkg)
1. Rather than managing volatile raw C/C++ source file streams from GitHub which introduce heavy third-party cryptographic constraints (e.g., mandatory mbedTLS headers), the server architecture was safely stabilized using **`vcpkg`**.
   * Installation Command: `vcpkg install open62541:x64-windows`
2. Mandatory link settings were enforced via `Project Properties` ＞ `Linker` ＞ `Input` ＞ `Additional Dependencies` by adding **`ws2_32.lib`** to route underlying Windows socket abstractions.

### 📄 Object-Oriented Address Space (Information Modeling)
* Implemented a structured industrial device model (`IntelligentMotorA`) directly inside the server's Address Space utilizing the `open62541` node management APIs.
* Wrapped localized text definitions and literal node IDs with explicit C-style casting `(char*)` to safely satisfy strict modern C++ type-safety compliance models.
* Structured explicit data components (`CurrentSpeed`, `TargetSpeed`, `Temperature`) under an explicit `HASCOMPONENT` folder relationship to allow standard industrial client discovery.

### ⚠️ Endpoint Optimization & Security Bypass
By default, modern `open62541` library baselines lock down generic endpoint routing for insecure connections. To enable seamless sandbox development and clear validation using GUI testing tools (UaExpert):
1. Invoked **`UA_ServerConfig_setDefault(config)`** to provision standard configuration infrastructures.
2. Invoked **`UA_ServerConfig_addAllEndpoints(config)`** to explicitly expose insecure (`None - None`) endpoint bindings natively to the host runtime.
3. This seamlessly enabled the client's "OK" validation button without forcing dangerous OS register tweaks or firewall routing script bypasses.

### 💻 6. OPC UA Client Implementation & Integration Validation

Following the successful server deployment, the custom **OPC UA Client (`OpcUaClient`)** was successfully engineered and verified using modern C++ abstractions on the `open62541` architecture.

#### 📌 Implementation Highlights
* **High-Level Client APIs:** Consumed `<open62541/client_highlevel.h>` within an explicit `extern "C"` linkage envelope to ensure flawless C++ cross-compilation with standard vcpkg static library links.
* **Strongly-Typed Attributes:** Leveraged `UA_Client_writeValueAttribute` to command a new value directly to the remote `TargetSpeed` node, validating client-side control injection.
* **Granular Polling loop:** Executed sequential `UA_Client_readValueAttribute` attribute retrievals to extract active data payloads from the server's Address Space.

#### 📋 Execution Diagnostics & Mismatch Resolution
* Encountered an initial runtime status constraint (`StatusCode: 0x80340000 / UA_STATUSCODE_BADNODEIDUNKNOWN`). 
* *Root Cause Analysis:* Diagnostic debugging isolated a fundamental data-type allocation failure inside the server node composition logic. The `CurrentSpeed` variable had accidentally been registered under the abstract `UA_NS0ID_BASEVARIABLETYPE` instead of the required runtime instantiable **`UA_NS0ID_BASEDATAVARIABLETYPE`**, causing the server core to reject node initialization.
* *Resolution:* Upon aligning the server macro with the proper runtime concrete definition and correcting literal string string references, the client successfully achieved end-to-end telemetry sync, generating clean cyclical read values (`0 rpm`) without requiring raw platform tweaks.
