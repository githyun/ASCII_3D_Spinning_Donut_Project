#include <iostream> 
#include <windows.h> 
#include <string> 
#include <cmath> 
#include <vector> 
 
using namespace std; 
 
void enableAnsi() { 
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); 
    DWORD dwMode = 0; 
    GetConsoleMode(hOut, &dwMode); 
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; 
    SetConsoleMode(hOut, dwMode); 
} 
 
int main() { 
 
    enableAnsi(); 
 
    int screenWidth = 80; //화면가로 
    int screenHeight = 24; //화면세로 
    float R1 = 1, R2 = 2, K2 = 5; // R1: 원 중심에서 반지름, R2: 원점에서 원중심까지 거리, K2: 도넛중심에서 시점까지의 거리 
    float K1 = screenWidth * K2 / (5*(R1 + R2));// K1: 화면에서 시점까지의 거리 
 
    float theta = 0, pi = 0, A = 0, B = 0; //각들_ theta, pi: 도넛 / A,B : 회전  
 
    float theta_plus = 0.06, pi_plus = 0.02, A_plus = 0.04, B_plus = 0.02; //각들 증가값 
 
    vector<char> b( screenWidth * screenHeight , ' '); // 80*24 크기라서 1920 
    vector<int> c(screenWidth * screenHeight, 0); // 색상 
    vector<float> z_buffer( screenWidth * screenHeight , 0); // z_buffer의 역할 
 
    const float PI = 3.141592; // 파이값 
 
    cout << "\x1B[?25l"; // 커서숨기기 
    cout << "\x1b[2J"; // 전체화면 지우기 
    cout << "\x1b[0m"; // 기본색상으로 돌아감 
 
    while (true) { 
 
        fill(b.begin(), b.end(), ' '); // b 초기화  
        fill(z_buffer.begin(), z_buffer.end(), 0); // z_buffer 초기화 
 
        for (theta = 0; theta < PI * 2; theta = theta + theta_plus) { 
            for (pi = 0; pi < PI * 2; pi = pi + pi_plus) { 
 
                float x = (R2 + R1 * cos(theta)) * (cos(B) * cos(pi) + sin(A) * sin(B) * sin(pi)) - R1 * cos(A) * sin(B) * sin(theta); // x좌표 
                float y = (R2 + R1 * cos(theta)) * (cos(pi) * sin(B) - cos(B) * sin(A) * sin(pi)) + R1 * cos(A) * cos(B) * sin(theta); // y좌표 
                float z = K2 + cos(A) * (R2 + R1 * cos(theta)) * sin(pi) + R1 * sin(A) * sin(theta); 
                // z좌표 - sin(pi)를 sin(theta)로 썼네 이거 때문에 계속 들여다 봤네 ㅠㅠ 
 
                float z_inverse = 1 / z;// z 역수 값 
                int xp = screenWidth / 2 + (x * K1 * z_inverse);// 화면에서 x좌표 
                int yp = screenHeight / 2 - (y * K1 * z_inverse * 0.5); // 화면에서 y좌표 ( y값은 위로 갈수록 커지지만, 배열은 아래로 갈수록 커짐 ) 
 
                // 빛 
                float luminance = cos(pi) * cos(theta) * sin(B) - cos(A) * cos(theta) * sin(pi) - sin(A) * sin(theta) + cos(B) * (cos(A) * sin(theta) - cos(theta) * sin(A) * sin(pi)); 
 
                int n = xp + yp * screenWidth; 
 
                if (luminance < 0) { // 중간에 도넛이 뚤려서 그냥 음수는 0으로하기로 했다 
                    luminance = 0; 
                } 
 
                if (xp > 0 && xp < screenWidth && yp > 0 && yp < screenHeight) { 
                    if (z_buffer[n] < z_inverse) { 
                        int luminance_index = 8 * luminance; 
                        z_buffer[n] = z_inverse; 
                        b[n] = ".,-~:;=!*#$@"[luminance_index]; 
                        c[n] = (theta < PI) ? 1 : 0; 
                   } 
                } 
            } 
        } 
        cout << " \x1B[0;0H"; // 커서 제일 위로 옮기기 
 
        for (int i = 0; i < screenWidth * screenHeight; i++) { 
            if (c[i] == 0) { 
                cout << "\033[96m"; //밝은 하늘색 
            } 
            else { 
                cout << "\033[33m"; //노란색 
            } 
 
            if (i % screenWidth != 0) { 
                cout << b[i]; // 출력 
            } 
            else { 
                cout << endl; // 줄바꿈 
            } 
        } 
 
        A += A_plus; 
        B += B_plus; 
        Sleep(20); // 딜레이 
    } 
} 
