# HTTP Client

A high-performance, modular **C++ HTTP client** designed for seamless client-server communication. This client enables sending HTTP requests, managing responses, and handling various request types efficiently.

Built with an **abstract command pattern**, it ensures **scalability**, **maintainability**, and **extensibility**.

## ✨ Features

- **Full HTTP Request Support** – Handles GET, POST, PUT, DELETE requests.
- **Custom Headers & Authentication** – Allows adding headers (e.g., `Authorization`, `Cookie`).
- **JSON Parsing** – Uses `nlohmann::json` for handling request/response payloads.
- **TCP Socket Communication** – Implements low-level networking using POSIX sockets.
- **Command-Based Architecture** – Uses an abstract command pattern for better organization.
- **Efficient Error Handling** – Handles network failures and incorrect responses gracefully.

## ⚡ Technology Stack

- **C++ (C++11 or later)** – Core programming language for high-performance execution.
- **POSIX Sockets** – Enables low-level TCP communication for HTTP requests.
- **nlohmann JSON** – Lightweight and efficient JSON parsing library.
- **Makefile** – Simplifies the build process for compiling the project.

## ⚙️ Build & Installation

### Prerequisites

Before building the project, ensure you have the following installed:

- **C++ Compiler** (GCC or Clang, supporting C++11 or later)
- **Make** (for compiling the project)
- **POSIX-compliant system** (Linux/macOS; Windows users can use WSL or MinGW)
- **nlohmann JSON library** (included automatically)

### Build Instructions

Follow these steps to clone, build, and run the HTTP client:

```sh
# Clone the repository
git clone https://github.com/andreiv03/http-client.git
cd http-client

# Build the project
make

# Run the HTTP client
make run
```

## 🤝 Contributing

Contributions are welcome! If you'd like to enhance the project, follow these steps:

1. **Fork** the repository
2. Create a **feature branch** (`git checkout -b feature-branch`)
3. **Commit** your changes (`git commit -m "feat: add new feature"`)
4. **Push** your changes (`git push origin feature-branch`)
5. Open a **Pull Request** 🚀

For suggestions or bug reports, feel free to open an issue with the appropriate label.

⭐ **If you find this project useful, consider giving it a star!** ⭐

## 📜 License

Distributed under the **MIT License**. See `LICENSE.txt` for details.
