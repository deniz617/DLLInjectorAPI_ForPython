// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <Windows.h>

extern "C" { // for demangling
    __declspec(dllexport) bool InjectDLL(int pid, const char* dllPath)
    {
        auto lenPath = strlen(dllPath);
        if (lenPath <= 0)
            return false;

        // First we need open process
        auto hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
        if (hProcess != nullptr)
        {
            // Now we need to get LoadLibrary Address
             // We dont need to get loadlib address of target process its always same.
            auto hMod = GetModuleHandle(L"kernel32.dll");
            if (hMod && hMod != INVALID_HANDLE_VALUE)
            {
                auto pLoadLib = GetProcAddress(hMod, "LoadLibraryW");
                if (pLoadLib != nullptr)
                {
                    // Now we need to allocate mem for args
                    auto pMem = VirtualAllocEx(hProcess, nullptr, lenPath + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
                    if (pMem != 0)
                    {
                        // Now we need to write dllPath to mem
                        WriteProcessMemory(hProcess, pMem, dllPath, lenPath + 1, 0);
                        // Now we need to create thread on LoadLibrary
                        auto hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)pLoadLib, pMem, 0, 0);
                        if (hThread)
                        {
                            WaitForSingleObject(hThread, 15000);
                            CloseHandle(hThread);
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

