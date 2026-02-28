# 【开源发布】Antigravity 远程调试注入器 - 让开发调试更自由

## 📢 项目简介

各位开发者好！今天给大家分享一个我开发的小工具 —— **Antigravity Remote Debug Injector**。

这是一个基于 DLL 劫持技术的工具，可以为 Antigravity 应用自动注入 `--remote-debugging-port` 启动参数，从而启用 Chrome DevTools 远程调试功能。

**GitHub 地址**：https://github.com/EvanDbg/antigravity-auto-remote-debug

---

## 💡 设计初衷

用过 Antigravity 的朋友都知道，在使用过程中经常会弹出 **"Retry"** 错误窗口，需要手动点击才能继续。这在长时间运行任务时非常烦人，尤其是离开电脑一会儿回来发现任务早就因为 Retry 弹窗卡住了……

为了解决这个问题，社区已经有两个非常实用的 Auto-Retry 插件：

- 🔗 [Antigravity Auto-Accept 自动接受和重试插件](https://linux.do/t/topic/1500512)
- 🔗 [Antigravity 自动重试插件](https://linux.do/t/topic/1494666)

这些插件通过 Chrome DevTools Protocol (CDP) 远程调试接口来自动检测并点击 Retry 按钮。

但是，要使用 CDP 就必须在启动 Antigravity 时加上 `--remote-debugging-port=9222` 参数。

**之前的解决方案有两个痛点：**

| 方案 | 问题 |
|------|------|
| 修改快捷方式 | 操作繁琐，每次更新都要重新设置 |
| 通过 Antigravity Tools 重启 | 会导致调试端口失效，Auto-Retry 功能失灵 |

**这就是这个项目诞生的原因！**

使用 DLL 注入方式后，**无论你通过什么方式启动或重启 Antigravity**（快捷方式、Antigravity Tools、甚至命令行），远程调试端口都会自动开启，Auto-Retry 功能始终有效。

一劳永逸，再也不用担心 Retry 弹窗卡住任务了！ 🎉

---

## 🎯 解决什么问题？

使用 Antigravity 进行开发时，有时候我们需要：
- 调试 Electron 应用内部的网页内容
- 分析网络请求和响应
- 检查 DOM 结构和 CSS 样式
- 进行性能分析

但是 Antigravity 默认没有开启远程调试端口，想要调试只能修改快捷方式或启动脚本，操作繁琐且容易出错。

**这个工具就是为了解决这个问题！** 只需要放一个 DLL 文件，就能自动开启调试端口，零配置开箱即用。

---

## ✨ 功能特性

| 功能 | 说明 |
|------|------|
| ✅ 自动注入 | 自动添加 `--remote-debugging-port` 参数 |
| ✅ 端口可配置 | 通过配置文件自定义调试端口 |
| ✅ 智能过滤 | 只对主进程注入，子进程不受影响 |
| ✅ 无侵入性 | 无需修改原程序，卸载即恢复 |
| ✅ 开箱即用 | 默认使用 9222 端口，无需配置 |

---

## 🚀 快速开始

### 方式一：直接使用（推荐）

1. 从 [Releases](https://github.com/EvanDbg/antigravity-auto-remote-debug/releases) 下载 `winmm.dll`
2. 将 `winmm.dll` 复制到 Antigravity 安装目录：
   ```
   C:\Users\<用户名>\AppData\Local\Programs\Antigravity\
   ```
3. 启动 Antigravity
4. 浏览器访问 `http://localhost:9222` 即可看到调试页面列表

### 方式二：自行编译

需要 [MinGW-w64](https://winlibs.com/) 编译器：

```batch
git clone https://github.com/EvanDbg/antigravity-auto-remote-debug.git
cd antigravity-auto-remote-debug
build.bat
```

---

## ⚙️ 配置说明

如果需要自定义端口，可以在 Antigravity 目录下创建 `antigravity_debug.ini`：

```ini
[RemoteDebug]
; 远程调试端口 (1-65535)
Port=9222

; 是否启用注入 (1=启用, 0=禁用)
Enabled=1
```

---

## 🔧 技术原理

简单说明一下实现原理，有兴趣的可以看源码：

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

核心代码很简洁，主要逻辑不到 200 行 C++ 代码。

---

## 🛡️ 安全说明

> ⚠️ **重要提示**
> 
> 由于使用了 DLL 劫持和内联 Hook 技术，可能会被杀毒软件误报为病毒。这是正常现象，代码完全开源透明，请放心使用。
> 
> 如遇误报，请将 DLL 添加到杀毒软件白名单。

---

## 📦 卸载方法

删除 Antigravity 目录下的以下文件即可完全卸载：
- `winmm.dll`
- `antigravity_debug.ini`（如有）

---

## 🤝 参与贡献

欢迎 Star ⭐、Fork 和 PR！

如果这个工具对你有帮助，请给个 Star 支持一下~ 🙏

**项目地址**：https://github.com/EvanDbg/antigravity-auto-remote-debug

---

## 📜 开源许可

MIT License - 随便用，不用担心版权问题。

---

**感谢阅读！如有问题欢迎在评论区交流，或在 GitHub 提 Issue。** 😊
