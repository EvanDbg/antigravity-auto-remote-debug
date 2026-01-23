// ============================================================================
// Antigravity Remote Debug Injector - Simple Inline Hook Version
// ============================================================================
// 不使用 MinHook，使用手动内联 Hook，更简单更可靠
// ============================================================================

#include <windows.h>
#include <stdio.h>
#include "config.h"

// ============================================================================
// 全局变量
// ============================================================================

typedef LPWSTR (WINAPI *GetCommandLineW_t)(void);
static GetCommandLineW_t fpOriginalGetCommandLineW = NULL;

static wchar_t g_modifiedCommandLine[32768];
static BOOL g_commandLineModified = FALSE;
static BOOL g_hookInstalled = FALSE;

static int g_remoteDebugPort = DEFAULT_REMOTE_DEBUG_PORT;
static BOOL g_injectEnabled = TRUE;
static HMODULE g_hSelfModule = NULL;

// 用于保存原始函数字节
static BYTE g_originalBytes[14];
static LPVOID g_pGetCommandLineW = NULL;

// Hook 函数前向声明
static LPWSTR WINAPI HookedGetCommandLineW(void);

// ============================================================================
// 辅助函数
// ============================================================================

static void GetCurrentDllDirectory(wchar_t* buffer, size_t bufferSize) {
    if (g_hSelfModule && buffer && bufferSize > 0) {
        GetModuleFileNameW(g_hSelfModule, buffer, (DWORD)bufferSize);
        wchar_t* lastSlash = wcsrchr(buffer, L'\\');
        if (lastSlash) {
            *(lastSlash + 1) = L'\0';
        }
    }
}

static void LoadConfiguration(void) {
    wchar_t configPath[MAX_PATH];
    GetCurrentDllDirectory(configPath, MAX_PATH);
    wcscat(configPath, CONFIG_FILE_NAME);
    
    g_remoteDebugPort = GetPrivateProfileIntW(
        CONFIG_SECTION_NAME, CONFIG_KEY_PORT,
        DEFAULT_REMOTE_DEBUG_PORT, configPath);
    
    g_injectEnabled = GetPrivateProfileIntW(
        CONFIG_SECTION_NAME, CONFIG_KEY_ENABLED, 1, configPath) != 0;
    
    if (g_remoteDebugPort < 1 || g_remoteDebugPort > 65535) {
        g_remoteDebugPort = DEFAULT_REMOTE_DEBUG_PORT;
    }
}

// 调用原始函数（临时恢复原始字节）
static LPWSTR CallOriginalGetCommandLineW(void) {
    // 暂时恢复原始字节
    DWORD oldProtect;
    VirtualProtect(g_pGetCommandLineW, 14, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(g_pGetCommandLineW, g_originalBytes, 14);
    VirtualProtect(g_pGetCommandLineW, 14, oldProtect, &oldProtect);
    FlushInstructionCache(GetCurrentProcess(), g_pGetCommandLineW, 14);
    
    // 调用原始函数
    LPWSTR result = fpOriginalGetCommandLineW();
    
    // 重新安装 Hook
    BYTE hookCode[14] = {
        0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,  // JMP [RIP+0]
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 目标地址
    };
    *(UINT64*)&hookCode[6] = (UINT64)&HookedGetCommandLineW;
    
    VirtualProtect(g_pGetCommandLineW, 14, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(g_pGetCommandLineW, hookCode, 14);
    VirtualProtect(g_pGetCommandLineW, 14, oldProtect, &oldProtect);
    FlushInstructionCache(GetCurrentProcess(), g_pGetCommandLineW, 14);
    
    return result;
}

// ============================================================================
// Hook 函数
// ============================================================================

static LPWSTR WINAPI HookedGetCommandLineW(void) {
    if (g_commandLineModified) {
        return g_modifiedCommandLine;
    }
    
    LPWSTR originalCmd = CallOriginalGetCommandLineW();
    if (originalCmd == NULL) {
        return NULL;
    }
    
    wcsncpy(g_modifiedCommandLine, originalCmd, 32767);
    g_modifiedCommandLine[32767] = L'\0';
    
    if (!g_injectEnabled) {
        g_commandLineModified = TRUE;
        return g_modifiedCommandLine;
    }
    
    // 只对主进程注入（不包含 --type= 参数）
    if (wcsstr(g_modifiedCommandLine, SUBPROCESS_TYPE_ARG) == NULL) {
        if (wcsstr(g_modifiedCommandLine, L"--remote-debugging-port") == NULL) {
            wchar_t argBuffer[64];
            swprintf(argBuffer, 64, REMOTE_DEBUG_ARG_TEMPLATE, g_remoteDebugPort);
            wcscat(g_modifiedCommandLine, argBuffer);
        }
    }
    
    g_commandLineModified = TRUE;
    return g_modifiedCommandLine;
}

// ============================================================================
// 简单内联 Hook
// ============================================================================

static BOOL InstallSimpleHook(void) {
    if (g_hookInstalled) {
        return TRUE;
    }
    
    // 获取 GetCommandLineW 地址
    HMODULE hKernel32 = GetModuleHandleW(L"kernel32.dll");
    if (!hKernel32) {
        return FALSE;
    }
    
    g_pGetCommandLineW = (LPVOID)GetProcAddress(hKernel32, "GetCommandLineW");
    if (!g_pGetCommandLineW) {
        return FALSE;
    }
    
    fpOriginalGetCommandLineW = (GetCommandLineW_t)g_pGetCommandLineW;
    
    // 保存原始字节
    memcpy(g_originalBytes, g_pGetCommandLineW, 14);
    
    // 构建 JMP 指令 (JMP [RIP+0])
    BYTE hookCode[14] = {
        0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,  // JMP [RIP+0]
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 目标地址
    };
    *(UINT64*)&hookCode[6] = (UINT64)&HookedGetCommandLineW;
    
    // 修改内存保护并写入 Hook
    DWORD oldProtect;
    if (!VirtualProtect(g_pGetCommandLineW, 14, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        return FALSE;
    }
    
    memcpy(g_pGetCommandLineW, hookCode, 14);
    
    VirtualProtect(g_pGetCommandLineW, 14, oldProtect, &oldProtect);
    FlushInstructionCache(GetCurrentProcess(), g_pGetCommandLineW, 14);
    
    g_hookInstalled = TRUE;
    return TRUE;
}

static void UninstallSimpleHook(void) {
    if (!g_hookInstalled || !g_pGetCommandLineW) {
        return;
    }
    
    // 恢复原始字节
    DWORD oldProtect;
    VirtualProtect(g_pGetCommandLineW, 14, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(g_pGetCommandLineW, g_originalBytes, 14);
    VirtualProtect(g_pGetCommandLineW, 14, oldProtect, &oldProtect);
    FlushInstructionCache(GetCurrentProcess(), g_pGetCommandLineW, 14);
    
    g_hookInstalled = FALSE;
}

// ============================================================================
// DLL 入口点
// ============================================================================

extern "C" BOOL InitializeForwarding(void);
extern "C" void CleanupForwarding(void);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    (void)lpReserved;
    
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            g_hSelfModule = hModule;
            DisableThreadLibraryCalls(hModule);
            
            // 初始化 winmm 转发
            if (!InitializeForwarding()) {
                return FALSE;
            }
            
            // 加载配置
            LoadConfiguration();
            
            // 安装简单内联 Hook
            InstallSimpleHook();
            break;
            
        case DLL_PROCESS_DETACH:
            UninstallSimpleHook();
            CleanupForwarding();
            break;
            
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    
    return TRUE;
}
