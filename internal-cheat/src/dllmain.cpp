// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "offsets.h"
#include "toggle.h"
#include "mem.h"

BOOL WINAPI HackThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Dulge Internal Hack\n";
    std::cout << "\n";
    std::cout << "[F1]" << "GODMODE\n";
    std::cout << "[F2]" << "AMMO\n";
    std::cout << "[F3]" << "RECOIL\n";
    std::cout << "[F4]" << "ARMOUR\n";
    
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    uintptr_t localPlayerPtr = *(uintptr_t*)(moduleBase + 0x10f4f4);
    uintptr_t localPlayer = moduleBase + 0x10f4f4;


    while (!GetAsyncKeyState(VK_END) & 1)
    {
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            toggle::health = !toggle::health;
        }

        if (GetAsyncKeyState(VK_F2) & 1)
        {
            toggle::ammo = !toggle::ammo;
        }

        if (GetAsyncKeyState(VK_F3) & 1)
        {
            toggle::recoil = !toggle::recoil;
        }

        if (GetAsyncKeyState(VK_F4) & 1)
        {
            toggle::armour = !toggle::armour;
        }


        if (localPlayerPtr)
        {
            if (toggle::health)
            {
                uintptr_t healthAddr = localPlayerPtr + offsets::health;
                *(uintptr_t*)healthAddr = 1337;
            }

            if (toggle::ammo)
            {
                uintptr_t ammoAddr = mem::FindDMAAddy(localPlayer, offsets::currentAmmo);
                *(uintptr_t*)ammoAddr = 1337;
            }

            if (toggle::recoil)
            {
                mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
            }
            else
            {
                mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
            }

            if (toggle::armour)
            {
                uintptr_t armourAddr = localPlayerPtr + offsets::armour;
                *(uintptr_t*)armourAddr = 1337;
            }

        }

        Sleep(5);

    }


    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

