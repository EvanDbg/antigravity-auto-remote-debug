// ============================================================================
// Antigravity Remote Debug Injector - winmm.dll Export Forwarding
// ============================================================================
// 使用动态加载实现系统 winmm.dll 函数转发
// ============================================================================

#include <windows.h>

// 系统原版 winmm.dll 句柄
extern "C" HMODULE g_hWinmmOriginal = NULL;

// ============================================================================
// 原始函数指针声明
// ============================================================================

#define DECL_FP(name) extern "C" FARPROC fp_##name = NULL;

// PlaySound
DECL_FP(PlaySoundA)
DECL_FP(PlaySoundW)

// 时间函数
DECL_FP(timeGetTime)
DECL_FP(timeGetDevCaps)
DECL_FP(timeBeginPeriod)
DECL_FP(timeEndPeriod)
DECL_FP(timeGetSystemTime)
DECL_FP(timeSetEvent)
DECL_FP(timeKillEvent)

// Wave 输出
DECL_FP(waveOutGetNumDevs)
DECL_FP(waveOutGetDevCapsA)
DECL_FP(waveOutGetDevCapsW)
DECL_FP(waveOutGetVolume)
DECL_FP(waveOutSetVolume)
DECL_FP(waveOutGetErrorTextA)
DECL_FP(waveOutGetErrorTextW)
DECL_FP(waveOutOpen)
DECL_FP(waveOutClose)
DECL_FP(waveOutPrepareHeader)
DECL_FP(waveOutUnprepareHeader)
DECL_FP(waveOutWrite)
DECL_FP(waveOutPause)
DECL_FP(waveOutRestart)
DECL_FP(waveOutReset)
DECL_FP(waveOutBreakLoop)
DECL_FP(waveOutGetPosition)
DECL_FP(waveOutGetPitch)
DECL_FP(waveOutSetPitch)
DECL_FP(waveOutGetPlaybackRate)
DECL_FP(waveOutSetPlaybackRate)
DECL_FP(waveOutGetID)
DECL_FP(waveOutMessage)

// Wave 输入
DECL_FP(waveInGetNumDevs)
DECL_FP(waveInGetDevCapsA)
DECL_FP(waveInGetDevCapsW)
DECL_FP(waveInGetErrorTextA)
DECL_FP(waveInGetErrorTextW)
DECL_FP(waveInOpen)
DECL_FP(waveInClose)
DECL_FP(waveInPrepareHeader)
DECL_FP(waveInUnprepareHeader)
DECL_FP(waveInAddBuffer)
DECL_FP(waveInStart)
DECL_FP(waveInStop)
DECL_FP(waveInReset)
DECL_FP(waveInGetPosition)
DECL_FP(waveInGetID)
DECL_FP(waveInMessage)

// MIDI 输出
DECL_FP(midiOutGetNumDevs)
DECL_FP(midiOutGetDevCapsA)
DECL_FP(midiOutGetDevCapsW)
DECL_FP(midiOutGetVolume)
DECL_FP(midiOutSetVolume)
DECL_FP(midiOutGetErrorTextA)
DECL_FP(midiOutGetErrorTextW)
DECL_FP(midiOutOpen)
DECL_FP(midiOutClose)
DECL_FP(midiOutPrepareHeader)
DECL_FP(midiOutUnprepareHeader)
DECL_FP(midiOutShortMsg)
DECL_FP(midiOutLongMsg)
DECL_FP(midiOutReset)
DECL_FP(midiOutCachePatches)
DECL_FP(midiOutCacheDrumPatches)
DECL_FP(midiOutGetID)
DECL_FP(midiOutMessage)

// MIDI 输入
DECL_FP(midiInGetNumDevs)
DECL_FP(midiInGetDevCapsA)
DECL_FP(midiInGetDevCapsW)
DECL_FP(midiInGetErrorTextA)
DECL_FP(midiInGetErrorTextW)
DECL_FP(midiInOpen)
DECL_FP(midiInClose)
DECL_FP(midiInPrepareHeader)
DECL_FP(midiInUnprepareHeader)
DECL_FP(midiInAddBuffer)
DECL_FP(midiInStart)
DECL_FP(midiInStop)
DECL_FP(midiInReset)
DECL_FP(midiInGetID)
DECL_FP(midiInMessage)

// MIDI Stream
DECL_FP(midiStreamOpen)
DECL_FP(midiStreamClose)
DECL_FP(midiStreamProperty)
DECL_FP(midiStreamPosition)
DECL_FP(midiStreamOut)
DECL_FP(midiStreamPause)
DECL_FP(midiStreamRestart)
DECL_FP(midiStreamStop)
DECL_FP(midiConnect)
DECL_FP(midiDisconnect)

// Aux
DECL_FP(auxGetNumDevs)
DECL_FP(auxGetDevCapsA)
DECL_FP(auxGetDevCapsW)
DECL_FP(auxSetVolume)
DECL_FP(auxGetVolume)
DECL_FP(auxOutMessage)

// Mixer
DECL_FP(mixerGetNumDevs)
DECL_FP(mixerGetDevCapsA)
DECL_FP(mixerGetDevCapsW)
DECL_FP(mixerOpen)
DECL_FP(mixerClose)
DECL_FP(mixerMessage)
DECL_FP(mixerGetLineInfoA)
DECL_FP(mixerGetLineInfoW)
DECL_FP(mixerGetID)
DECL_FP(mixerGetLineControlsA)
DECL_FP(mixerGetLineControlsW)
DECL_FP(mixerGetControlDetailsA)
DECL_FP(mixerGetControlDetailsW)
DECL_FP(mixerSetControlDetails)

// Joy
DECL_FP(joyGetNumDevs)
DECL_FP(joyGetDevCapsA)
DECL_FP(joyGetDevCapsW)
DECL_FP(joyGetPos)
DECL_FP(joyGetPosEx)
DECL_FP(joyGetThreshold)
DECL_FP(joyReleaseCapture)
DECL_FP(joySetCapture)
DECL_FP(joySetThreshold)
DECL_FP(joyConfigChanged)

// MCI
DECL_FP(mciSendCommandA)
DECL_FP(mciSendCommandW)
DECL_FP(mciSendStringA)
DECL_FP(mciSendStringW)
DECL_FP(mciGetDeviceIDA)
DECL_FP(mciGetDeviceIDW)
DECL_FP(mciGetDeviceIDFromElementIDA)
DECL_FP(mciGetDeviceIDFromElementIDW)
DECL_FP(mciGetDriverData)
DECL_FP(mciGetErrorStringA)
DECL_FP(mciGetErrorStringW)
DECL_FP(mciSetDriverData)
DECL_FP(mciDriverNotify)
DECL_FP(mciDriverYield)
DECL_FP(mciFreeCommandResource)
DECL_FP(mciLoadCommandResource)
DECL_FP(mciSetYieldProc)
DECL_FP(mciGetYieldProc)
DECL_FP(mciGetCreatorTask)
DECL_FP(mciExecute)

// MMIO
DECL_FP(mmioOpenA)
DECL_FP(mmioOpenW)
DECL_FP(mmioClose)
DECL_FP(mmioRead)
DECL_FP(mmioWrite)
DECL_FP(mmioSeek)
DECL_FP(mmioGetInfo)
DECL_FP(mmioSetInfo)
DECL_FP(mmioSetBuffer)
DECL_FP(mmioFlush)
DECL_FP(mmioAdvance)
DECL_FP(mmioStringToFOURCCA)
DECL_FP(mmioStringToFOURCCW)
DECL_FP(mmioInstallIOProcA)
DECL_FP(mmioInstallIOProcW)
DECL_FP(mmioSendMessage)
DECL_FP(mmioDescend)
DECL_FP(mmioAscend)
DECL_FP(mmioCreateChunk)
DECL_FP(mmioRenameA)
DECL_FP(mmioRenameW)

// Driver
DECL_FP(OpenDriver)
DECL_FP(CloseDriver)
DECL_FP(SendDriverMessage)
DECL_FP(DefDriverProc)
DECL_FP(DrvGetModuleHandle)
DECL_FP(GetDriverModuleHandle)
DECL_FP(DriverCallback)

// 其他
DECL_FP(sndPlaySoundA)
DECL_FP(sndPlaySoundW)
DECL_FP(mmsystemGetVersion)

// ============================================================================
// 初始化所有函数指针
// ============================================================================

#define INIT_FP(name) fp_##name = GetProcAddress(g_hWinmmOriginal, #name)

extern "C" BOOL InitializeForwarding(void) {
    if (g_hWinmmOriginal) return TRUE;
    
    // 获取系统目录
    wchar_t systemDir[MAX_PATH];
    GetSystemDirectoryW(systemDir, MAX_PATH);
    
    // 构建系统 winmm.dll 完整路径
    wchar_t winmmPath[MAX_PATH];
    wsprintfW(winmmPath, L"%s\\winmm.dll", systemDir);
    
    // 加载系统原版 winmm.dll
    g_hWinmmOriginal = LoadLibraryW(winmmPath);
    if (!g_hWinmmOriginal) return FALSE;
    
    // 初始化所有函数指针
    INIT_FP(PlaySoundA);
    INIT_FP(PlaySoundW);
    INIT_FP(timeGetTime);
    INIT_FP(timeGetDevCaps);
    INIT_FP(timeBeginPeriod);
    INIT_FP(timeEndPeriod);
    INIT_FP(timeGetSystemTime);
    INIT_FP(timeSetEvent);
    INIT_FP(timeKillEvent);
    INIT_FP(waveOutGetNumDevs);
    INIT_FP(waveOutGetDevCapsA);
    INIT_FP(waveOutGetDevCapsW);
    INIT_FP(waveOutGetVolume);
    INIT_FP(waveOutSetVolume);
    INIT_FP(waveOutGetErrorTextA);
    INIT_FP(waveOutGetErrorTextW);
    INIT_FP(waveOutOpen);
    INIT_FP(waveOutClose);
    INIT_FP(waveOutPrepareHeader);
    INIT_FP(waveOutUnprepareHeader);
    INIT_FP(waveOutWrite);
    INIT_FP(waveOutPause);
    INIT_FP(waveOutRestart);
    INIT_FP(waveOutReset);
    INIT_FP(waveOutBreakLoop);
    INIT_FP(waveOutGetPosition);
    INIT_FP(waveOutGetPitch);
    INIT_FP(waveOutSetPitch);
    INIT_FP(waveOutGetPlaybackRate);
    INIT_FP(waveOutSetPlaybackRate);
    INIT_FP(waveOutGetID);
    INIT_FP(waveOutMessage);
    INIT_FP(waveInGetNumDevs);
    INIT_FP(waveInGetDevCapsA);
    INIT_FP(waveInGetDevCapsW);
    INIT_FP(waveInGetErrorTextA);
    INIT_FP(waveInGetErrorTextW);
    INIT_FP(waveInOpen);
    INIT_FP(waveInClose);
    INIT_FP(waveInPrepareHeader);
    INIT_FP(waveInUnprepareHeader);
    INIT_FP(waveInAddBuffer);
    INIT_FP(waveInStart);
    INIT_FP(waveInStop);
    INIT_FP(waveInReset);
    INIT_FP(waveInGetPosition);
    INIT_FP(waveInGetID);
    INIT_FP(waveInMessage);
    INIT_FP(midiOutGetNumDevs);
    INIT_FP(midiOutGetDevCapsA);
    INIT_FP(midiOutGetDevCapsW);
    INIT_FP(midiOutGetVolume);
    INIT_FP(midiOutSetVolume);
    INIT_FP(midiOutGetErrorTextA);
    INIT_FP(midiOutGetErrorTextW);
    INIT_FP(midiOutOpen);
    INIT_FP(midiOutClose);
    INIT_FP(midiOutPrepareHeader);
    INIT_FP(midiOutUnprepareHeader);
    INIT_FP(midiOutShortMsg);
    INIT_FP(midiOutLongMsg);
    INIT_FP(midiOutReset);
    INIT_FP(midiOutCachePatches);
    INIT_FP(midiOutCacheDrumPatches);
    INIT_FP(midiOutGetID);
    INIT_FP(midiOutMessage);
    INIT_FP(midiInGetNumDevs);
    INIT_FP(midiInGetDevCapsA);
    INIT_FP(midiInGetDevCapsW);
    INIT_FP(midiInGetErrorTextA);
    INIT_FP(midiInGetErrorTextW);
    INIT_FP(midiInOpen);
    INIT_FP(midiInClose);
    INIT_FP(midiInPrepareHeader);
    INIT_FP(midiInUnprepareHeader);
    INIT_FP(midiInAddBuffer);
    INIT_FP(midiInStart);
    INIT_FP(midiInStop);
    INIT_FP(midiInReset);
    INIT_FP(midiInGetID);
    INIT_FP(midiInMessage);
    INIT_FP(midiStreamOpen);
    INIT_FP(midiStreamClose);
    INIT_FP(midiStreamProperty);
    INIT_FP(midiStreamPosition);
    INIT_FP(midiStreamOut);
    INIT_FP(midiStreamPause);
    INIT_FP(midiStreamRestart);
    INIT_FP(midiStreamStop);
    INIT_FP(midiConnect);
    INIT_FP(midiDisconnect);
    INIT_FP(auxGetNumDevs);
    INIT_FP(auxGetDevCapsA);
    INIT_FP(auxGetDevCapsW);
    INIT_FP(auxSetVolume);
    INIT_FP(auxGetVolume);
    INIT_FP(auxOutMessage);
    INIT_FP(mixerGetNumDevs);
    INIT_FP(mixerGetDevCapsA);
    INIT_FP(mixerGetDevCapsW);
    INIT_FP(mixerOpen);
    INIT_FP(mixerClose);
    INIT_FP(mixerMessage);
    INIT_FP(mixerGetLineInfoA);
    INIT_FP(mixerGetLineInfoW);
    INIT_FP(mixerGetID);
    INIT_FP(mixerGetLineControlsA);
    INIT_FP(mixerGetLineControlsW);
    INIT_FP(mixerGetControlDetailsA);
    INIT_FP(mixerGetControlDetailsW);
    INIT_FP(mixerSetControlDetails);
    INIT_FP(joyGetNumDevs);
    INIT_FP(joyGetDevCapsA);
    INIT_FP(joyGetDevCapsW);
    INIT_FP(joyGetPos);
    INIT_FP(joyGetPosEx);
    INIT_FP(joyGetThreshold);
    INIT_FP(joyReleaseCapture);
    INIT_FP(joySetCapture);
    INIT_FP(joySetThreshold);
    INIT_FP(joyConfigChanged);
    INIT_FP(mciSendCommandA);
    INIT_FP(mciSendCommandW);
    INIT_FP(mciSendStringA);
    INIT_FP(mciSendStringW);
    INIT_FP(mciGetDeviceIDA);
    INIT_FP(mciGetDeviceIDW);
    INIT_FP(mciGetDeviceIDFromElementIDA);
    INIT_FP(mciGetDeviceIDFromElementIDW);
    INIT_FP(mciGetDriverData);
    INIT_FP(mciGetErrorStringA);
    INIT_FP(mciGetErrorStringW);
    INIT_FP(mciSetDriverData);
    INIT_FP(mciDriverNotify);
    INIT_FP(mciDriverYield);
    INIT_FP(mciFreeCommandResource);
    INIT_FP(mciLoadCommandResource);
    INIT_FP(mciSetYieldProc);
    INIT_FP(mciGetYieldProc);
    INIT_FP(mciGetCreatorTask);
    INIT_FP(mciExecute);
    INIT_FP(mmioOpenA);
    INIT_FP(mmioOpenW);
    INIT_FP(mmioClose);
    INIT_FP(mmioRead);
    INIT_FP(mmioWrite);
    INIT_FP(mmioSeek);
    INIT_FP(mmioGetInfo);
    INIT_FP(mmioSetInfo);
    INIT_FP(mmioSetBuffer);
    INIT_FP(mmioFlush);
    INIT_FP(mmioAdvance);
    INIT_FP(mmioStringToFOURCCA);
    INIT_FP(mmioStringToFOURCCW);
    INIT_FP(mmioInstallIOProcA);
    INIT_FP(mmioInstallIOProcW);
    INIT_FP(mmioSendMessage);
    INIT_FP(mmioDescend);
    INIT_FP(mmioAscend);
    INIT_FP(mmioCreateChunk);
    INIT_FP(mmioRenameA);
    INIT_FP(mmioRenameW);
    INIT_FP(OpenDriver);
    INIT_FP(CloseDriver);
    INIT_FP(SendDriverMessage);
    INIT_FP(DefDriverProc);
    INIT_FP(DrvGetModuleHandle);
    INIT_FP(GetDriverModuleHandle);
    INIT_FP(DriverCallback);
    INIT_FP(sndPlaySoundA);
    INIT_FP(sndPlaySoundW);
    INIT_FP(mmsystemGetVersion);
    
    return TRUE;
}

extern "C" void CleanupForwarding() {
    if (g_hWinmmOriginal) {
        FreeLibrary(g_hWinmmOriginal);
        g_hWinmmOriginal = NULL;
    }
}
