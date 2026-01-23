#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// Antigravity Remote Debug Injector - Configuration
// ============================================================================

// 配置文件名称（放置于 DLL 同级目录）
#define CONFIG_FILE_NAME L"antigravity_debug.ini"

// 配置文件中的节名和键名
#define CONFIG_SECTION_NAME L"RemoteDebug"
#define CONFIG_KEY_PORT L"Port"
#define CONFIG_KEY_ENABLED L"Enabled"

// 默认远程调试端口
#define DEFAULT_REMOTE_DEBUG_PORT 9222

// 要注入的启动参数模板
#define REMOTE_DEBUG_ARG_TEMPLATE L" --remote-debugging-port=%d"

// 用于判断是否为主进程的特征参数
// Electron 子进程（渲染进程、GPU进程等）命令行中会包含此参数
#define SUBPROCESS_TYPE_ARG L"--type="

#endif // CONFIG_H
