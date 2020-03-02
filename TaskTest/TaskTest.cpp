// TaskTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

int maxSleep = 150;
int minSleep = 100;

void LeftClick()
{
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    SendInput(1, &input, sizeof(INPUT));
    ZeroMemory(&input, sizeof(INPUT));

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(1, &input, sizeof(INPUT));
}

void RightClick()
{
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    SendInput(1, &input, sizeof(INPUT));
    ZeroMemory(&input, sizeof(INPUT));

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    SendInput(1, &input, sizeof(INPUT));
}

void UseMp(POINT posPersonagem, POINT posMp)
{
    srand((int)time(0));

    int time = minSleep + (rand() % (maxSleep - minSleep + 1));
    long variacaoPosicao = -10 + (rand() % (10 + 10 + 1));

    INPUT inputKeyboard = { 0 };
    inputKeyboard.type = INPUT_KEYBOARD;
    inputKeyboard.ki.wScan = 0;
    inputKeyboard.ki.time = 0;
    inputKeyboard.ki.dwExtraInfo = 0;

    INPUT inputMouse = { 0 };
    inputMouse.type = INPUT_MOUSE;

    // move to mana pot position
    SetCursorPos(posMp.x + variacaoPosicao, posMp.y + variacaoPosicao);
    
    Sleep(time);

    // control hold
    inputKeyboard.ki.wVk = VK_CONTROL;
    inputKeyboard.ki.dwFlags = 0;
    SendInput(1, &inputKeyboard, sizeof(INPUT));

    Sleep(time);

    // left mouse button hold
    inputMouse.type = INPUT_MOUSE;
    inputMouse.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &inputMouse, sizeof(INPUT));

    Sleep(time);

    // release left mouse button 
    inputMouse.type = INPUT_MOUSE;
    inputMouse.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &inputMouse, sizeof(INPUT));

    Sleep(time);

    // release control
    inputKeyboard.ki.wVk = VK_CONTROL;
    inputKeyboard.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &inputKeyboard, sizeof(INPUT));

    Sleep(time);

    // move character position
    SetCursorPos(posPersonagem.x + variacaoPosicao, posPersonagem.y + variacaoPosicao);

    Sleep(time);

    LeftClick();

    Sleep(time);
}

void DiscardMp(POINT posMp, POINT posDescartMp)
{
    srand((int)time(0));

    int time = minSleep + (rand() % (maxSleep - minSleep + 1));
    long variacaoPosicao = -10 + (rand() % (10 + 10 + 1));


    INPUT inputMouse = { 0 };
    inputMouse.type = INPUT_MOUSE;

    // move to used mana pot position
    SetCursorPos(posMp.x + variacaoPosicao, posMp.y + variacaoPosicao);

    Sleep(time);

    // left mouse button hold
    inputMouse.type = INPUT_MOUSE;
    inputMouse.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &inputMouse, sizeof(INPUT));
    
    Sleep(time);

    // move character position
    SetCursorPos(posDescartMp.x + variacaoPosicao, posDescartMp.y + variacaoPosicao);

    Sleep(time);

    // release left mouse button 
    inputMouse.type = INPUT_MOUSE;
    inputMouse.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &inputMouse, sizeof(INPUT));

    Sleep(time);
}

int main()
{
    POINT posPersonagem;

    cout << "Clique na posicao do personagem\n";
    while ((GetKeyState(VK_LBUTTON) & 0x100) == 0);

    GetCursorPos(&posPersonagem);

    Sleep(500);

    POINT posMp;

    cout << "Clique na posição da mana pot\n";
    while ((GetKeyState(VK_LBUTTON) & 0x100) == 0);

    GetCursorPos(&posMp);

    Sleep(500);

    POINT posDescarteMp;

    cout << "Clique na posicao de descarte da mana pot\n";
    while ((GetKeyState(VK_LBUTTON) & 0x100) == 0);

    GetCursorPos(&posDescarteMp);

    Sleep(500);

    cout << "Aperte enter para iniciar\n";
    cin.ignore();

    cout << "personagem: " << posPersonagem.x << " " << posPersonagem.y << "\n";
    cout << "MP: " << posMp.x << " " << posMp.y << "\n";
    cout << "descarte: " << posDescarteMp.x << " " << posDescarteMp.y << "\n";

    int contadorUsoMp = 0;

    while (true)
    {
        srand((int)time(0));

        int time = minSleep + (rand() % (maxSleep - minSleep + 1));

        UseMp(posPersonagem, posMp);
        contadorUsoMp++;
        
        Sleep(time);

        DiscardMp(posMp, posDescarteMp);

        Sleep(time);

        if (contadorUsoMp == 4)
        {
            contadorUsoMp = 0;

            INPUT inputKeyboard = { 0 };
            inputKeyboard.type = INPUT_KEYBOARD;
            inputKeyboard.ki.wScan = 0;
            inputKeyboard.ki.time = 0;
            inputKeyboard.ki.dwExtraInfo = 0;

            Sleep(time);

            // control hold
            inputKeyboard.ki.wVk = VK_F12;
            inputKeyboard.ki.dwFlags = 0;
            SendInput(1, &inputKeyboard, sizeof(INPUT));

            Sleep(10);

            // release control
            inputKeyboard.ki.wVk = VK_F12;
            inputKeyboard.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &inputKeyboard, sizeof(INPUT));

            Sleep(time);
        }
    }

    return 0;
}


