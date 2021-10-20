#pragma once
#include <windows.h>
#define _USE_MATH_DEFINES 1
#include <cmath>
#include <cstdlib>
#include <cstdio>
#pragma comment(lib, "winmm.lib")

static unsigned long x = 123456789, y = 362436069, z = 521288629;
DWORD xs;
VOID SeedXorshift32(DWORD dwSeed) {
    xs = dwSeed;
}
DWORD xorshift32() {
    xs ^= xs << 13;
    xs ^= xs >> 17;
    xs ^= xs << 5;
    return xs;
}

COLORREF RndRGB() {
    int clr = xorshift32() % 5;
    if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}

VOID WINAPI sound1()
{
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44000, 44000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};

    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * cos(sin(tan(log(t)))));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}