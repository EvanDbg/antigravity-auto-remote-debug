@echo off
REM ============================================================================
REM Antigravity Remote Debug Injector - Build Script
REM ============================================================================
REM 使用 MinGW-w64 编译 winmm.dll (x64)
REM ============================================================================

setlocal enabledelayedexpansion

set MINGW_PATH=C:\mingw64\bin
set PATH=%MINGW_PATH%;%PATH%

where g++ >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo [错误] 找不到 g++ 编译器!
    echo 请确保 MinGW-w64 已安装: https://winlibs.com/
    pause
    exit /b 1
)

echo ============================================================================
echo Antigravity Remote Debug Injector - 编译脚本
echo ============================================================================
echo.

set SRC_DIR=src
set OUTPUT=winmm.dll
set CFLAGS=-O2 -Wall -DNDEBUG -Wno-unused-variable

echo [1/4] 清理...
del /q *.o %OUTPUT% 2>nul

echo [2/4] 编译源文件...
g++ %CFLAGS% -I%SRC_DIR% -c %SRC_DIR%\main.cpp -o main.o
if %ERRORLEVEL% neq 0 goto :error

g++ %CFLAGS% -c %SRC_DIR%\exports.cpp -o exports.o 2>nul
if %ERRORLEVEL% neq 0 goto :error

g++ -c %SRC_DIR%\stubs.S -o stubs.o
if %ERRORLEVEL% neq 0 goto :error

echo [3/4] 链接 DLL...
g++ -shared -static -s -o %OUTPUT% main.o exports.o stubs.o -lkernel32 -luser32
if %ERRORLEVEL% neq 0 goto :error

echo [4/4] 清理中间文件...
del /q *.o 2>nul

echo.
echo ============================================================================
for %%F in (%OUTPUT%) do echo 编译成功: %%~nxF ^(%%~zF 字节^)
echo ============================================================================
echo.
echo 部署: 将 %OUTPUT% 复制到 Antigravity 安装目录
echo 验证: 浏览器访问 http://localhost:9222
echo.
pause
exit /b 0

:error
echo [错误] 编译失败!
pause
exit /b 1
