# ============================================================================
# Antigravity Remote Debug Injector - Assembly Forwarding Stubs
# ============================================================================
# 这个文件包含所有 winmm.dll 导出函数的汇编跳板
# 每个跳板加载对应的函数指针并跳转到原始函数
# ============================================================================

.intel_syntax noprefix
.text

# 宏定义：生成转发跳板
# 参数: name - 函数名
.macro FORWARD_STUB name
    .globl \name
    .def \name; .scl 2; .type 32; .endef
\name:
    mov rax, qword ptr [rip + fp_\name]
    test rax, rax
    jz .L\name\()_null
    jmp rax
.L\name\()_null:
    xor eax, eax
    ret
.endm

# ============================================================================
# 导出函数跳板
# ============================================================================

# PlaySound
FORWARD_STUB PlaySoundA
FORWARD_STUB PlaySoundW

# 时间函数
FORWARD_STUB timeGetTime
FORWARD_STUB timeGetDevCaps
FORWARD_STUB timeBeginPeriod
FORWARD_STUB timeEndPeriod
FORWARD_STUB timeGetSystemTime
FORWARD_STUB timeSetEvent
FORWARD_STUB timeKillEvent

# Wave 输出
FORWARD_STUB waveOutGetNumDevs
FORWARD_STUB waveOutGetDevCapsA
FORWARD_STUB waveOutGetDevCapsW
FORWARD_STUB waveOutGetVolume
FORWARD_STUB waveOutSetVolume
FORWARD_STUB waveOutGetErrorTextA
FORWARD_STUB waveOutGetErrorTextW
FORWARD_STUB waveOutOpen
FORWARD_STUB waveOutClose
FORWARD_STUB waveOutPrepareHeader
FORWARD_STUB waveOutUnprepareHeader
FORWARD_STUB waveOutWrite
FORWARD_STUB waveOutPause
FORWARD_STUB waveOutRestart
FORWARD_STUB waveOutReset
FORWARD_STUB waveOutBreakLoop
FORWARD_STUB waveOutGetPosition
FORWARD_STUB waveOutGetPitch
FORWARD_STUB waveOutSetPitch
FORWARD_STUB waveOutGetPlaybackRate
FORWARD_STUB waveOutSetPlaybackRate
FORWARD_STUB waveOutGetID
FORWARD_STUB waveOutMessage

# Wave 输入
FORWARD_STUB waveInGetNumDevs
FORWARD_STUB waveInGetDevCapsA
FORWARD_STUB waveInGetDevCapsW
FORWARD_STUB waveInGetErrorTextA
FORWARD_STUB waveInGetErrorTextW
FORWARD_STUB waveInOpen
FORWARD_STUB waveInClose
FORWARD_STUB waveInPrepareHeader
FORWARD_STUB waveInUnprepareHeader
FORWARD_STUB waveInAddBuffer
FORWARD_STUB waveInStart
FORWARD_STUB waveInStop
FORWARD_STUB waveInReset
FORWARD_STUB waveInGetPosition
FORWARD_STUB waveInGetID
FORWARD_STUB waveInMessage

# MIDI 输出
FORWARD_STUB midiOutGetNumDevs
FORWARD_STUB midiOutGetDevCapsA
FORWARD_STUB midiOutGetDevCapsW
FORWARD_STUB midiOutGetVolume
FORWARD_STUB midiOutSetVolume
FORWARD_STUB midiOutGetErrorTextA
FORWARD_STUB midiOutGetErrorTextW
FORWARD_STUB midiOutOpen
FORWARD_STUB midiOutClose
FORWARD_STUB midiOutPrepareHeader
FORWARD_STUB midiOutUnprepareHeader
FORWARD_STUB midiOutShortMsg
FORWARD_STUB midiOutLongMsg
FORWARD_STUB midiOutReset
FORWARD_STUB midiOutCachePatches
FORWARD_STUB midiOutCacheDrumPatches
FORWARD_STUB midiOutGetID
FORWARD_STUB midiOutMessage

# MIDI 输入
FORWARD_STUB midiInGetNumDevs
FORWARD_STUB midiInGetDevCapsA
FORWARD_STUB midiInGetDevCapsW
FORWARD_STUB midiInGetErrorTextA
FORWARD_STUB midiInGetErrorTextW
FORWARD_STUB midiInOpen
FORWARD_STUB midiInClose
FORWARD_STUB midiInPrepareHeader
FORWARD_STUB midiInUnprepareHeader
FORWARD_STUB midiInAddBuffer
FORWARD_STUB midiInStart
FORWARD_STUB midiInStop
FORWARD_STUB midiInReset
FORWARD_STUB midiInGetID
FORWARD_STUB midiInMessage

# MIDI Stream
FORWARD_STUB midiStreamOpen
FORWARD_STUB midiStreamClose
FORWARD_STUB midiStreamProperty
FORWARD_STUB midiStreamPosition
FORWARD_STUB midiStreamOut
FORWARD_STUB midiStreamPause
FORWARD_STUB midiStreamRestart
FORWARD_STUB midiStreamStop
FORWARD_STUB midiConnect
FORWARD_STUB midiDisconnect

# Aux
FORWARD_STUB auxGetNumDevs
FORWARD_STUB auxGetDevCapsA
FORWARD_STUB auxGetDevCapsW
FORWARD_STUB auxSetVolume
FORWARD_STUB auxGetVolume
FORWARD_STUB auxOutMessage

# Mixer
FORWARD_STUB mixerGetNumDevs
FORWARD_STUB mixerGetDevCapsA
FORWARD_STUB mixerGetDevCapsW
FORWARD_STUB mixerOpen
FORWARD_STUB mixerClose
FORWARD_STUB mixerMessage
FORWARD_STUB mixerGetLineInfoA
FORWARD_STUB mixerGetLineInfoW
FORWARD_STUB mixerGetID
FORWARD_STUB mixerGetLineControlsA
FORWARD_STUB mixerGetLineControlsW
FORWARD_STUB mixerGetControlDetailsA
FORWARD_STUB mixerGetControlDetailsW
FORWARD_STUB mixerSetControlDetails

# Joy
FORWARD_STUB joyGetNumDevs
FORWARD_STUB joyGetDevCapsA
FORWARD_STUB joyGetDevCapsW
FORWARD_STUB joyGetPos
FORWARD_STUB joyGetPosEx
FORWARD_STUB joyGetThreshold
FORWARD_STUB joyReleaseCapture
FORWARD_STUB joySetCapture
FORWARD_STUB joySetThreshold
FORWARD_STUB joyConfigChanged

# MCI
FORWARD_STUB mciSendCommandA
FORWARD_STUB mciSendCommandW
FORWARD_STUB mciSendStringA
FORWARD_STUB mciSendStringW
FORWARD_STUB mciGetDeviceIDA
FORWARD_STUB mciGetDeviceIDW
FORWARD_STUB mciGetDeviceIDFromElementIDA
FORWARD_STUB mciGetDeviceIDFromElementIDW
FORWARD_STUB mciGetDriverData
FORWARD_STUB mciGetErrorStringA
FORWARD_STUB mciGetErrorStringW
FORWARD_STUB mciSetDriverData
FORWARD_STUB mciDriverNotify
FORWARD_STUB mciDriverYield
FORWARD_STUB mciFreeCommandResource
FORWARD_STUB mciLoadCommandResource
FORWARD_STUB mciSetYieldProc
FORWARD_STUB mciGetYieldProc
FORWARD_STUB mciGetCreatorTask
FORWARD_STUB mciExecute

# MMIO
FORWARD_STUB mmioOpenA
FORWARD_STUB mmioOpenW
FORWARD_STUB mmioClose
FORWARD_STUB mmioRead
FORWARD_STUB mmioWrite
FORWARD_STUB mmioSeek
FORWARD_STUB mmioGetInfo
FORWARD_STUB mmioSetInfo
FORWARD_STUB mmioSetBuffer
FORWARD_STUB mmioFlush
FORWARD_STUB mmioAdvance
FORWARD_STUB mmioStringToFOURCCA
FORWARD_STUB mmioStringToFOURCCW
FORWARD_STUB mmioInstallIOProcA
FORWARD_STUB mmioInstallIOProcW
FORWARD_STUB mmioSendMessage
FORWARD_STUB mmioDescend
FORWARD_STUB mmioAscend
FORWARD_STUB mmioCreateChunk
FORWARD_STUB mmioRenameA
FORWARD_STUB mmioRenameW

# Driver
FORWARD_STUB OpenDriver
FORWARD_STUB CloseDriver
FORWARD_STUB SendDriverMessage
FORWARD_STUB DefDriverProc
FORWARD_STUB DrvGetModuleHandle
FORWARD_STUB GetDriverModuleHandle
FORWARD_STUB DriverCallback

# 其他
FORWARD_STUB sndPlaySoundA
FORWARD_STUB sndPlaySoundW
FORWARD_STUB mmsystemGetVersion
