#include <jni.h>
#include <string>
#include <field.hpp>
#include <BNM/UserSettings/GlobalSettings.hpp>
#include <BNM/Loading.hpp>
#include <log.hpp>
#include <initialize.hpp>

using namespace std;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, [[maybe_unused]] void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    Private_path = "/sdcard/Android/data/" + getPackageNameAsString(env) + "/files/EFMod-Private/TextRedirector-EternalFuture/";

    try {
        BNM::Loading::TryLoadByJNI(env); // 初始化
        EFLOG(LogLevel::INFO, "初始化成功！");
    } catch (const std::exception& e) {
        EFLOG(LogLevel::INFO, "初始化失败：" +  (string)e.what());
    } catch (...) {
        EFLOG(LogLevel::INFO, "初始化失败：未知异常");
    }

    BNM::Loading::AddOnLoadedEvent(initialize);


    return JNI_VERSION_1_6;
}