# Antigravity Remote Debug Injector

通过 DLL 劫持为 Antigravity 应用自动注入 `--remote-debugging-port` 启动参数，启用 Chrome DevTools 远程调试功能。

## 💡 设计初衷

Antigravity 使用过程中经常弹出 **"Retry"** 错误窗口，社区已有基于 CDP（Chrome DevTools Protocol）的 Auto-Retry 插件：

- [Antigravity Auto-Accept 自动接受和重试插件](https://linux.do/t/topic/1500512)
- [Antigravity 自动重试插件](https://linux.do/t/topic/1494666)

但这些插件依赖 `--remote-debugging-port` 参数，之前的方案要么修改快捷方式（每次更新失效），要么通过 Antigravity Tools 重启（导致调试端口失效）。

**本工具通过 DLL 注入一劳永逸地解决了这个问题** —— 无论通过什么方式启动或重启 Antigravity，远程调试端口都会自动开启。

## ✨ 功能特性

| 功能 | 说明 |
|------|------|
| ✅ 自动注入 | 自动添加 `--remote-debugging-port` 参数 |
| ✅ 端口可配置 | 通过 INI 配置文件自定义调试端口（1-65535） |
| ✅ 智能过滤 | 只对主进程注入，子进程（渲染进程、GPU 进程等）不受影响 |
| ✅ 无侵入性 | 无需修改原程序，删除 DLL 即恢复 |
| ✅ 开箱即用 | 默认使用 9222 端口，零配置即可工作 |

## 🚀 快速开始

### 方式一：直接使用（推荐）

1. 从 [Releases](https://github.com/EvanDbg/antigravity-auto-remote-debug/releases) 下载 `winmm.dll`
2. 将 `winmm.dll` 复制到 Antigravity 安装目录：
   ```
   C:\Users\<用户名>\AppData\Local\Programs\Antigravity\
   ```
3. 启动 Antigravity
4. 浏览器访问 `http://localhost:9222` 验证调试页面列表

### 方式二：自行编译

需要 [MinGW-w64](https://winlibs.com/) 编译器（x64）：

```batch
git clone https://github.com/EvanDbg/antigravity-auto-remote-debug.git
cd antigravity-auto-remote-debug
build.bat
```

## ⚙️ 配置说明

默认即可使用，无需额外配置。如需自定义，在 Antigravity 安装目录下创建 `antigravity_debug.ini`：

```ini
[RemoteDebug]
; 远程调试端口 (1-65535)
Port=9222

; 是否启用注入 (1=启用, 0=禁用)
Enabled=1
```

## 📁 项目结构

```
├── src/
│   ├── main.cpp          # 主逻辑：配置加载、内联 Hook、命令行注入
│   ├── exports.cpp       # winmm 函数指针声明与初始化
│   ├── stubs.S           # x64 汇编转发跳板（FORWARD_STUB 宏）
│   └── config.h          # 编译期配置常量
├── build.bat             # MinGW-w64 编译脚本
├── antigravity_debug.ini # 配置文件示例
├── FORUM_POST.md         # 论坛发布帖
└── README.md
```

## 🔧 技术原理

```
┌─────────────────────────────────────────────────────────────┐
│                    技术实现流程                              │
├─────────────────────────────────────────────────────────────┤
│  1. DLL 劫持   → Windows 优先加载程序目录下的 winmm.dll     │
│  2. 函数转发   → 将 winmm 函数调用转发到系统原版 DLL        │
│  3. 内联 Hook  → 拦截 kernel32!GetCommandLineW             │
│  4. 参数注入   → 在命令行末尾追加调试端口参数               │
│  5. 进程过滤   → 通过 --type= 参数识别并跳过子进程          │
└─────────────────────────────────────────────────────────────┘
```

核心代码约 200 行 C++，无第三方依赖（不依赖 MinHook 等库），手动实现 x64 内联 Hook（`JMP [RIP+0]` 14 字节跳板）。

## 🛡️ 安全说明

> ⚠️ 由于使用了 DLL 劫持和内联 Hook 技术，可能被杀毒软件误报。代码完全开源透明，如遇误报请将 DLL 添加到白名单。

## 📦 卸载

删除 Antigravity 安装目录下的以下文件即可：
- `winmm.dll`
- `antigravity_debug.ini`（如有）

## 📜 许可证

MIT License
