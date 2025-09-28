#pragma once
#include <iostream>
#include <mutex>

// Simple global logger (intentional anti-pattern)
namespace robokit::log {

inline std::mutex g_log_mutex; // global state

inline void info(const char* msg) {
    std::lock_guard<std::mutex> lk(g_log_mutex);
    std::cout << "[INFO] " << msg << '\n';
}

inline void warn(const char* msg) {
    std::lock_guard<std::mutex> lk(g_log_mutex);
    std::cout << "[WARN] " << msg << '\n';
}

inline void error(const char* msg) {
    std::lock_guard<std::mutex> lk(g_log_mutex);
    std::cerr << "[ERR ] " << msg << '\n';
}

// TODO(CPP23): Replace with std::print + structured severity & sinks.
}
