#include <tool/redirect.hpp>
#include <tool/json.hpp>
#include <field.hpp>

using namespace std;
using json = nlohmann::json;

std::string read_file(const std::string& filename) {
    EFLOG(LogLevel::DEBUG, "尝试打开文件: " + filename);
    std::ifstream file(filename);
    if (!file.is_open()) {
        EFLOG(LogLevel::ERROR, "无法打开文件: " + filename);
        throw std::runtime_error("无法打开文件: " + filename);
    }

    EFLOG(LogLevel::DEBUG, "文件成功打开: " + filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    EFLOG(LogLevel::DEBUG, "文件内容已读取并关闭: " + filename);
    return buffer.str();
}

std::string redirect(std::string context) {
    EFLOG(LogLevel::DEBUG, "开始重定向处理，上下文: " + context);
    try {
        // 解析 JSON 数据
        EFLOG(LogLevel::DEBUG, "读取并解析配置文件: " + Private_path + "config.json");
        auto j = json::parse(read_file(Private_path + "config.json"));

        EFLOG(LogLevel::DEBUG, "配置文件解析成功");
        for (const auto& item : j) {
            std::string original_file = item["Original"];
            std::string redirect_file = item["Redirect"];

            EFLOG(LogLevel::DEBUG, "处理重定向，从: " + original_file + " 到: " + redirect_file);
            // 读取 Original 文件的内容
            std::string original_content = read_file(Private_path + original_file);

            // 比较内容
            if (original_content == context) {
                EFLOG(LogLevel::DEBUG, "找到与上下文匹配的文件: ", original_file);
                // 读取 Redirect 文件的内容
                EFLOG(LogLevel::DEBUG, "读取重定向文件: " + redirect_file);
                return read_file(Private_path + redirect_file);
            }
        }

        EFLOG(LogLevel::DEBUG, "未找到与给定上下文匹配的文件，取消重定向");
        // 如果没有匹配的文件，返回原内容
        return context;
    } catch (const std::exception& e) {
        EFLOG(LogLevel::ERROR, "重定向处理过程中捕获异常: " + (string)e.what());
        // 发生异常，返回原内容
        return context;
    }
}