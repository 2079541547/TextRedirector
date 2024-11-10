#include <tool/export.hpp>
#include <log.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <functional>


using namespace std;

void exportToFile(const std::string& context, const std::string& folderPath) {
    try {
        // 创建文件夹路径对象
        std::filesystem::path path(folderPath);

        // 确保文件夹存在
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path);
            EFLOG(LogLevel::INFO, "exportToFile", "创建文件夹: " + folderPath);
        }

        // 使用字符串内容的哈希值作为文件名
        std::hash<std::string> hasher;
        size_t hashValue = hasher(context);
        std::stringstream ss;
        ss << hashValue;
        std::string filename = ss.str() + ".export"; // 可以根据需要更改扩展名

        // 构建完整的文件路径
        std::string fullPath = (folderPath.back() == '/' || folderPath.back() == '\\') ?
                               folderPath + filename : folderPath + "/" + filename;

        // 记录开始写入文件的信息
        EFLOG(LogLevel::INFO, "exportToFile", "尝试将字符串写入文件: " + fullPath);

        // 打开文件
        std::ofstream file(fullPath, std::ios::out);

        // 检查文件是否成功打开
        if (!file.is_open()) {
            EFLOG(LogLevel::ERROR, "exportToFile", "无法打开文件: " + fullPath);
            return;
        }

        // 将字符串内容写入文件
        file << context;

        // 检查写入是否成功
        if (!file) {
            EFLOG(LogLevel::ERROR, "exportToFile", "写入文件时发生错误: " + fullPath);
            return;
        }

        // 关闭文件
        file.close();

        // 记录写入文件成功的消息
        EFLOG(LogLevel::INFO, "exportToFile", "文件写入成功: " + fullPath);
    } catch (const std::exception& e) {
        EFLOG(LogLevel::ERROR, "exportToFile", "写入文件时发生异常: " + std::string(e.what()));
    } catch (...) {
        EFLOG(LogLevel::ERROR, "exportToFile", "写入文件时发生未知异常");
    }
}