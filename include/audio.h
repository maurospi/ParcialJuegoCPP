// Disclaimer: Partes de este codigo fueron generadas o sugeridas por IA para cumplir con los requerimientos del proyecto.
#ifndef AUDIO_H
#define AUDIO_H

#include <stdio.h>
#include "constants.h"

static const char* SFX_ATTACK = COLOR_YELLOW " ¡ZAS! " COLOR_RESET;
static const char* SFX_DAMAGE = COLOR_RED " ¡AUCH! " COLOR_RESET;
static const char* SFX_PICKUP = COLOR_GREEN " ¡CLINK! " COLOR_RESET;
static const char* SFX_DOOR   = COLOR_BLUE " *CREEEAK* " COLOR_RESET;

#ifdef _WIN32

#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <atomic>

inline void playBeep(int frequency) {
    printf("\a");
    fflush(stdout);
}

inline std::string getAbsoluteAudioPath(const std::string& relativePath) {
    char fullPath[MAX_PATH];

    std::string normalized = relativePath;
    for (char &c : normalized) {
        if (c == '/') c = '\\';
    }

    if (GetFileAttributesA(normalized.c_str()) != INVALID_FILE_ATTRIBUTES) {
        if (GetFullPathNameA(normalized.c_str(), MAX_PATH, fullPath, NULL) != 0) {
            return std::string(fullPath);
        }
    }

    std::string parentPath = "..\\" + normalized;
    if (GetFileAttributesA(parentPath.c_str()) != INVALID_FILE_ATTRIBUTES) {
        if (GetFullPathNameA(parentPath.c_str(), MAX_PATH, fullPath, NULL) != 0) {
            return std::string(fullPath);
        }
    }

    if (GetFullPathNameA(normalized.c_str(), MAX_PATH, fullPath, NULL) != 0) {
        return std::string(fullPath);
    }

    return normalized;
}

inline std::atomic<int>& getActiveSfxCount() {
    static std::atomic<int> count(0);
    return count;
}

struct PlaySoundThreadData {
    std::string path;
    int sfxId;
};

inline DWORD WINAPI PlaySoundThreadFunc(LPVOID lpParam) {
    PlaySoundThreadData* data = (PlaySoundThreadData*)lpParam;
    if (!data) return 0;

    std::string absPath = data->path;
    int currentId = data->sfxId;
    delete data;

    PlaySoundA(NULL, NULL, 0);
    PlaySoundA(absPath.c_str(), NULL, SND_FILENAME | SND_SYNC);

    std::atomic<int>& activeSfx = getActiveSfxCount();
    if (currentId == activeSfx.load()) {
        std::string bgmPath = getAbsoluteAudioPath("assets/Musica.wav");
        waveOutSetVolume(NULL, 0xFFFFFFFF);
        PlaySoundA(bgmPath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }

    return 0;
}

inline void startBackgroundMusic() {
    std::string absPath = getAbsoluteAudioPath("assets/Musica.wav");
    waveOutSetVolume(NULL, 0xFFFFFFFF);
    PlaySoundA(absPath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

inline void stopBackgroundMusic() {
    PlaySoundA(NULL, NULL, 0);
}

inline void playGameSound(const char* relativePath) {
    std::string absPath = getAbsoluteAudioPath(relativePath);

    waveOutSetVolume(NULL, 0xFFFFFFFF);

    std::atomic<int>& activeSfx = getActiveSfxCount();
    activeSfx++;
    int currentId = activeSfx.load();

    PlaySoundThreadData* data = new PlaySoundThreadData();
    data->path = absPath;
    data->sfxId = currentId;

    HANDLE hThread = CreateThread(NULL, 0, PlaySoundThreadFunc, data, 0, NULL);
    if (hThread) {
        CloseHandle(hThread);
    }
}

#else

inline void playBeep(int frequency) {
    printf("\a");
    fflush(stdout);
}

inline void startBackgroundMusic() {}
inline void stopBackgroundMusic() {}
inline void playGameSound(const char* relativePath) {}

#endif

#endif
