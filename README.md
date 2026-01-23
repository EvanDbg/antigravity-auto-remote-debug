# Antigravity Remote Debug Injector

通过 DLL 劫持为 Antigravity 应用注入 `--remote-debugging-port` 启动参数，启用 Chrome DevTools 远程调试功能。

## 功能特性

- ✅ 自动注入远程调试端口参数
- ✅ 通过配置文件自定义端口
- ✅ 只对主进程注入，子进程不受影响
- ✅ 无需修改原程序

## 快速开始

### 1. 编译

需要 [MinGW-w64](https://winlibs.com/) 编译器。

```batch
build.bat
```

### 2. 部署

将 `winmm.dll` 复制到 Antigravity 安装目录：

```
C:\Users\<用户名>\AppData\Local\Programs\Antigravity\
```

### 3. 配置（可选） --- 不配置的话，默认功能开启并使用9222端口

`antigravity_debug.ini`。

```ini
[RemoteDebug]
Port=9222
Enabled=1
```

### 4. 验证

1. 启动 Antigravity
2. 浏览器访问 `http://localhost:9222`
3. 应显示可调试的页面列表

## 项目结构

```
├── src/
│   ├── main.cpp          # 主逻辑和内联 Hook
│   ├── exports.cpp       # winmm 函数指针
│   ├── stubs.S           # 汇编转发跳板
│   └── config.h          # 配置定义
├── build.bat             # 编译脚本
├── antigravity_debug.ini # 配置示例
└── README.md
```

## 技术原理

1. **DLL 劫持**: Windows 优先加载程序目录下的 DLL
2. **函数转发**: 将所有 winmm 函数调用转发到系统原版 DLL
3. **内联 Hook**: 拦截 `kernel32!GetCommandLineW` 修改命令行参数
4. **进程过滤**: 通过检测 `--type=` 参数识别子进程

## 卸载

删除 Antigravity 目录下的 `winmm.dll` 和 `antigravity_debug.ini`。

## 注意事项

> ⚠️ 此工具使用 DLL 劫持技术，可能被杀毒软件误报。请将 DLL 添加到白名单。

## 许可证

MIT License
