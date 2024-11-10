#pragma once

#include <android/log.h>
#include <chrono>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <ctime>
#include <cstring>

enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Log {
public:
    // 获取当前时间的字符串表示
    static std::string getCurrentTime();

    // 内部日志记录方法
    static void logInternal(LogLevel level, const std::string &fullMessage);

    // 日志记录方法
    static void LOG(LogLevel level, const std::string &message, const char* file, int line);
    static void LOG(LogLevel level, const std::string &function, const std::string &message, const char* file, int line);
    static void LOG(LogLevel level, const std::string &Class, const std::string &function, const std::string &message, const char* file, int line);
    static void LOG(LogLevel level, const std::string &Namespace, const std::string &Class, const std::string &function, const std::string &message, const char* file, int line);

private:
    // 将日志级别转换为字符串
    static std::string logLevelToString(LogLevel level);
};

#define EFLOG(level, ...) Log::LOG(level, ##__VA_ARGS__, __FILE__, __LINE__)