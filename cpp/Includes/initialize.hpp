#pragma once



/**
 * @brief 初始化函数，用于劫持 Unity 引擎的 TextAsset 类的 get_text 方法。
 *
 * 此函数的主要步骤包括：
 * 1. 获取 TextAsset 类。
 * 2. 获取 TextAsset 类的 get_text 方法。
 * 3. 劫持 get_text 方法，将其替换为新的实现。
 * 4. 记录各个步骤的日志信息。
 *
 * @details
 * - 使用 Class 函数从 UnityEngine.CoreModule.dll 中获取 TextAsset 类。
 * - 使用 GetMethod 函数从 TextAsset 类中获取 get_text 方法。
 * - 使用 HOOK 函数劫持 get_text 方法，将其替换为新的实现 new_get_text，并保存原方法的指针到 old_get_text。
 * - 使用 EFLOG 函数记录各个步骤的日志信息。
 * - 使用 try-catch 块捕获并处理可能发生的异常。
 */
void initialize();