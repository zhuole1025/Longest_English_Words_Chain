# Longest_English_Words_Chain
## 结对项目：求解最长英文单词链

> 对于包含有 N个不同的英语单词的文本，可以快速找出最长的能**首尾相连**的英语单词链，每个单词最多使用**一次**，且单词大小写**不**敏感。其中，单词的定义为：被非英文字符间隔的连续英文字符序列

支持以下参数：

- `-n [text file]`：求单词链总数以及每条单词链
- `-w [text file]`：求单词数最多的单词链
- `-c [text file]`：求字符数最多的单词链
- `-h`：限定单词链的起始字母
- `-t`：限定单词链的末尾字母
- `-j`：禁止单词链起始字母
- `-r`：允许文本隐含单词环

C++语言实现的命令行版本：`\bin`文件夹下的`Wordlist.exe`

使用Python中的PyQt5库实现的GUI版本：`\guibin`文件夹下的`wordchain.exe`，调用同目录下的动态库`core.dll`

## 测试模块

`\test`目录下，`test.cpp`测试Core模块的接口，`test_main.cpp`测试对参数、文件等的异常处理

## 模块间的松耦合

在`dev-combine`分支中

- `\ourcore_with_exe`我们的核心模块与另一小组的命令行模块组合
- `\ourgui_with_core`我们的GUI界面与另一小组的核心模块组合