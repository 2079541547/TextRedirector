#include <field.hpp>
#include <BNM/UserSettings/GlobalSettings.hpp>
#include <initialize.hpp>
#include <iostream>
#include <log.hpp>
#include <BNM/Class.hpp>
#include <BNM/Field.hpp>
#include <BNM/Method.hpp>
#include <BNM/Property.hpp>
#include <BNM/Operators.hpp>
#include <BNM/BasicMonoStructures.hpp>
#include <tool/export.hpp>
#include <tool/redirect.hpp>

using namespace std;
using namespace BNM;
using namespace BNM::Structures;
using namespace BNM::Operators;


Mono::String* (*old_get_text)(BNM::UnityEngine::Object *);
Mono::String* new_get_text(BNM::UnityEngine::Object *instance) {

    string org = old_get_text(instance)->str();
    exportToFile(org,
                 Private_path + "Export");

    return CreateMonoString(redirect(org));
}





void initialize() {
    try {
        // 记录初始化开始的信息
        EFLOG(LogLevel::INFO, "initialize", "尝试劫持引擎获取文本函数...");

        // 获取 TextAsset 类
        // TextAsset 是 Unity 引擎中的一个类，用于表示文本资源
        auto TextAsset = Class("UnityEngine", "TextAsset", BNM::Image("UnityEngine.CoreModule.dll"));
        if (!TextAsset) {
            // 如果无法获取 TextAsset 类，记录错误信息并提前返回
            EFLOG(LogLevel::ERROR, "initialize", "无法获取 TextAsset 类");
            return;
        }
        // 记录成功获取 TextAsset 类的信息
        EFLOG(LogLevel::INFO, "initialize", "已获取 TextAsset 类");

        // 获取 get_text 方法
        // get_text 是 TextAsset 类的一个方法，用于获取文本内容
        auto get_text = TextAsset.GetMethod("get_text", 0);

        // 记录成功获取 get_text 方法的信息
        EFLOG(LogLevel::INFO, "initialize", "已获取 get_text 函数");

        // 开始劫持 get_text 函数
        // 使用 HOOK 函数将原 get_text 方法替换为新的实现 new_get_text
        // old_get_text 将保存原 get_text 方法的指针
        EFLOG(LogLevel::INFO, "initialize", "开始劫持 get_text 函数");
        HOOK(get_text, new_get_text, old_get_text);

        // 记录初始化完成的信息
        EFLOG(LogLevel::INFO, "initialize", "初始化完成！");
    } catch (const std::exception& e) {
        // 捕获标准异常并记录异常信息
        EFLOG(LogLevel::ERROR, "initialize", "初始化过程中发生异常: %s", e.what());
    } catch (...) {
        // 捕获所有其他类型的异常并记录未知异常信息
        EFLOG(LogLevel::ERROR, "initialize", "初始化过程中发生未知异常");
    }
}