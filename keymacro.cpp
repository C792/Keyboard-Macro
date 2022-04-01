#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <ostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <conio.h>

#define PSH presskey(VK_SHIFT); SHIFT++
#define EH presskey(VK_HANGUL); HANGUL++
#define onKP(i) if (GetAsyncKeyState(i) == CLICK_EVENT) ReplaceKey(i);
#define CLICK_EVENT (-32767)
using namespace std;

string testcase = "`1234567890!@#$%^&*()-=qwertyuiop[]\\asdfghjkl;\'zxcvbnm,./~_+{}|:\"<>?";
string arr = "Thank you. I\'m honored to be with you today for your commencement from one of the finest universities in the world. Truth be told, I never graduated from college and this is the closest I\'ve ever gotten to a college graduation. Today I want to tell you three stories from my life. That\'s it. No big deal. Just three stories.";
//Steve Jobs Stanford Speech

int CTRL, SHIFT, HANGUL, ACTRL, ASHIFT, AALT;
void KeyInput(char c) {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    int i = c;
    //cout << i << endl;
    ip.ki.wVk = i;
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}
void presskey(int c) {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(INPUT));
}
void releasekey(int c) {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

char convert(char a) {
    switch (a) {
    case ';':
        return VK_OEM_1;
    case ':':
        PSH;
        return VK_OEM_1;
    case '/':
        return VK_OEM_2;
    case '?':
        PSH;
        return VK_OEM_2;
    case '`':
        return VK_OEM_3;
    case '~':
        PSH;
        return VK_OEM_3;
    case '-':
        return VK_OEM_MINUS;
    case '_':
        PSH;
        return VK_OEM_MINUS;
    case '=':
        return VK_OEM_PLUS;
    case '+':
        PSH;
        return VK_OEM_PLUS;
    case '[':
        return VK_OEM_4;
    case '{':
        PSH;
        return VK_OEM_4;
    case '\\':
        return VK_OEM_5;
    case '|':
        PSH;
        return VK_OEM_5;
    case ']':
        return VK_OEM_6;
    case '}':
        PSH;
        return VK_OEM_6;
    case '\'':
        return VK_OEM_7;
    case '\"':
        PSH;
        return VK_OEM_7;
    case ',':
        return VK_OEM_COMMA;
    case '<':
        PSH;
        return VK_OEM_COMMA;
    case '.':
        return VK_OEM_PERIOD;
    case '>':
        PSH;
        return VK_OEM_PERIOD;
    case '!':
        PSH;
        return '1';
    case '@':
        PSH;
        return '2';
    case '#':
        PSH;
        return '3';
    case '$':
        PSH;
        return '4';
    case '%':
        PSH;
        return '5';
    case '^':
        PSH;
        return '6';
    case '&':
        PSH;
        return '7';
    case '*':
        PSH;
        return '8';
    case '(':
        PSH;
        return '9';
    case ')':
        PSH;
        return '0';
    case '\n':
        return VK_RETURN;
    }
    if (a >= 'a' && a <= 'z') {
        PSH;
        return a ^ 32;
    }

    return a;
}
int ri;
void ReplaceKey(int in) {
    KeyInput(8);
    //char a = arr[ri];
    char a = arr[ri % (arr.length() + 1)];
    if (ri % (arr.length() + 1) == arr.length()) KeyInput(32);
    else {
        KeyInput(convert(a));
        if (SHIFT) {
            releasekey(VK_SHIFT);
            SHIFT--;
        }
    }
    ri++;
}

bool program_initalizer = false;
void KeyListen() {
    if (program_initalizer) {
        for (int c = 32; c < 'Z' + 2; c++) {
            onKP(c);
            if (c == 32) c = '0' - 1;
        }
        for (int i = VK_OEM_1; i <= VK_OEM_3; i++) onKP(i);
        for (int i = VK_OEM_4; i < VK_OEM_8; i++) onKP(i);
        if (GetAsyncKeyState(VK_F7) == CLICK_EVENT) {
            program_initalizer = false;
            cout << "OFF" << endl;
        }
        /*for (int i = VK_SHIFT; i < VK_MENU; i++)
            if (GetAsyncKeyState(i) == CLICK_EVENT)
                releasekey(i);*/
    }
    else {
        if (GetAsyncKeyState(VK_F7) == CLICK_EVENT) {
            program_initalizer = true;
            cout << "ON" << endl;
        }
    }
    return;
}

bool ReadArr() {
    ifstream readFile;
    string inputarr;
    readFile.open("macro.txt");
    if (readFile.is_open())
    {
        while (!readFile.eof())
        {
            getline(readFile, inputarr);
            arr.append(inputarr);
            arr.push_back('\n');
        }
        readFile.close();
        return true;
    }
    return false;
}

int main() {
    bool WindowShow = true;
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window, WindowShow);
    if (!ReadArr()) {
        cout << "Cannot find \"macro.txt\".\nPlease check if the macro.txt file exists in the current directory." << endl << endl << "Press any key to close...";
        _getch();
        return 0;
    }
    for_each(arr.begin(), arr.end(), [](char& c) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) c = c ^ 32;
        });
    while (1) {
        KeyListen();
        if (GetAsyncKeyState(VK_F6) == CLICK_EVENT) {
            WindowShow = !WindowShow;
            ShowWindow(window, WindowShow);
        }
    }
}
