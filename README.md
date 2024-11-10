# 文件重定向功能说明文档

## 1. 文档概述

本文档旨在详细介绍一个文件重定向功能的使用方法。该功能通过配置文件来决定哪些文件的内容会被重定向到其他文件的内容。本文档将涵盖以下几个方面：

- 配置文件的格式和位置
- 文件的放置位置
- 使用示例
- 注意事项

## 2. 配置文件

### 2.1 配置文件的位置

配置文件名为 `config.json`，位于 `Private_path` 目录下。`Private_path` 是一个预定义的路径变量，代表配置文件所在的目录。

### 2.2 配置文件的格式

配置文件是一个 JSON 格式的文件，每个条目包含两个字段：

- `"Original"`：原始文件的相对路径。
- `"Redirect"`：目标文件的相对路径，即原始文件的内容将被替换为该文件的内容。

示例配置文件内容如下：

```json
[
    {
        "Original": "Original/example.txt",
        "Redirect": "Redirect/redirected_example.txt"
    },
    {
        "Original": "Original/another_file.txt",
        "Redirect": "Redirect/another_redirect.txt"
    }
]
```

## 3. 文件放置

### 3.1 文件夹结构

- **`Private_path`**：主目录，包含配置文件和其他子目录。
- **`Original`**：存放原始文件的文件夹。
- **`Redirect`**：存放重定向后文件的文件夹。
- **`Export`**：存放所有可以被重定向的文件的文件夹。

### 3.2 文件放置位置

- **原始文件**：这些文件是您希望其内容被重定向的文件。它们应该放在 `Original` 文件夹下。
- **目标文件**：这些文件包含了您希望显示在原始文件位置的内容。它们应该放在 `Redirect` 文件夹下。
- **可重定向文件**：所有可以被重定向的文件应该放在 `Export` 文件夹下。

### 3.3 示例

修改 `Private/config.json` 配置文件：

```json
[
    {
        "Original": "Original/example.txt",
        "Redirect": "Redirect/redirected_example.txt"
    }
]
```

- **example.txt** 应该放在 `/home/user/configs/Original/` 目录下。
- **redirected_example.txt** 应该放在 `/home/user/configs/Redirect/` 目录下。
- **example.txt** 和 **redirected_example.txt** 也应该放在 `/home/user/configs/Export/` 目录下。

## [4. 重新编译Mod](https://github.com/2079541547/EFMod)


## 5. 使用示例

### 5.1 配置文件

假设您的 `config.json` 文件内容如下：

```json
[
    {
        "Original": "Original/example.txt",
        "Redirect": "Redirect/redirected_example.txt"
    }
]
```

### 5.2 文件内容

- **Original/example.txt** 内容：
  ```
  This is the content of example.txt.
  ```

- **Redirect/redirected_example.txt** 内容：
  ```
  This is the redirected content.
  ```

- **Export/example.txt** 和 **Export/redirected_example.txt** 也应该存在，内容与 `Original` 和 `Redirect` 文件相同。

### 5.3 重定向过程

1. **读取配置文件**：程序首先会读取 `config.json` 文件，并将其内容解析为 JSON 对象。
2. **遍历配置项**：对于配置文件中的每一个条目，程序会检查 `Original` 文件的内容是否与传入的 `context` 参数相匹配。
3. **内容重定向**：如果找到了匹配的文件，程序将读取 `Redirect` 文件的内容，并将其作为结果返回。
4. **无匹配情况**：如果没有找到匹配的文件，程序将直接返回传入的 `context` 内容。

### 5.4 结果

假设传入的 `context` 是 `Original/example.txt` 的内容：

```
This is the content of example.txt.
```

程序将返回 `Redirect/redirected_example.txt` 的内容：

```
This is the redirected content.
```

## 5. 注意事项

- 确保所有文件路径都是相对于 `Private_path` 的正确路径。
- 在实际部署前，测试配置文件和文件路径以确保一切按预期工作。
- 确保日志级别（`LogLevel::DEBUG` 和 `LogLevel::ERROR`）已经正确配置，以便能够查看程序运行时的日志输出，这对于调试非常有帮助。

## 6. 附录

### 6.1 日志输出示例

- **调试日志**：
  ```
  [DEBUG] 尝试打开文件: /home/user/configs/Original/example.txt
  [DEBUG] 文件成功打开: /home/user/configs/Original/example.txt
  [DEBUG] 文件内容已读取并关闭: /home/user/configs/Original/example.txt
  [DEBUG] 开始重定向处理，上下文: This is the content of example.txt.
  [DEBUG] 读取并解析配置文件: /home/user/configs/config.json
  [DEBUG] 配置文件解析成功
  [DEBUG] 处理重定向，从: Original/example.txt 到: Redirect/redirected_example.txt
  [DEBUG] 找到与上下文匹配的文件: Original/example.txt
  [DEBUG] 读取重定向文件: /home/user/configs/Redirect/redirected_example.txt
  ```

- **错误日志**：
  ```
  [ERROR] 无法打开文件: /home/user/configs/Original/nonexistent.txt
  [ERROR] 重定向处理过程中捕获异常: No such file or directory
  ```