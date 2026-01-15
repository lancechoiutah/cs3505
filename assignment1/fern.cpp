#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <bitset>

using std::cout;
using std::endl;

void printBinary(unsigned int n, std::string name) {
    cout << name << ": " << (int)n << "\t (이진수: " << std::bitset<8>(n) << ")" << endl;
}

int main(){
    cout << "=== 1. Shift 연산 (<<) 연습 ===" << endl;
    unsigned char x = 1;
    printBinary(x, "x 초기값");

    unsigned char shifted = x << 2;
    printBinary(shifted, "x << 2   ");

    shifted = x << 5;
    printBinary(shifted, "x << 5   ");
    cout << endl;

    cout << "=== 2. Bit 켜기 (OR 연산 |) 연습 ===" << endl;
    // 과제의 setPixel과 같은 원리입니다.
    unsigned char pixelByte = 0; // 00000000 (아무것도 안 켜짐)
    printBinary(pixelByte, "초기 상태");

    // 3번째 비트(인덱스 2)를 켜보겠습니다. (1 << 2)
    cout << ">> 3번째 비트 켜기 (1 << 2 적용)..." << endl;
    pixelByte = pixelByte | (1 << 2); 
    printBinary(pixelByte, "결과     ");

    // 이번엔 7번째 비트(인덱스 6)를 추가로 켜보겠습니다. (1 << 6)
    cout << ">> 7번째 비트 추가로 켜기 (1 << 6 적용)..." << endl;
    pixelByte = pixelByte | (1 << 6);
    printBinary(pixelByte, "결과     ");
    cout << endl;

    cout << "=== 3. Bit 확인하기 (AND 연산 &) 연습 ===" << endl;
    // 과제의 getPixel과 같은 원리입니다.
    // 현재 pixelByte는 01000100 입니다. (2번, 6번 비트가 켜짐)

    int checkIndex = 2; // 3번째 비트 확인
    cout << checkIndex + 1 << "번째 비트 확인 중..." << endl;
    
    // (1 << 2)는 00000100 입니다.
    // 01000100 & 00000100 = 00000100 (0이 아님 -> 켜져있음!)
    if ((pixelByte & (1 << checkIndex)) != 0) {
        cout << "-> 켜져 있습니다 (ON)" << endl;
    } else {
        cout << "-> 꺼져 있습니다 (OFF)" << endl;
    }
    checkIndex = 0; // 1번째 비트 확인 (안 켜져 있음)
    cout << checkIndex + 1 << "번째 비트 확인 중..." << endl;
    
    if ((pixelByte & (1 << checkIndex)) != 0) {
        cout << "-> 켜져 있습니다 (ON)" << endl;
    } else {
        cout << "-> 꺼져 있습니다 (OFF)" << endl;
    }
    cout << endl;
    cout << "=== 4. (심화) 실제 픽셀 배열 흉내내기 ===" << endl;
    // 가로 8픽셀, 세로 2픽셀짜리 작은 이미지를 상상해 봅시다. (총 16픽셀 -> 2바이트 필요)
    unsigned char image[2] = {0, 0}; 

    // (3, 0) 좌표에 점을 찍는다고 가정 (윗줄 4번째)
    // 3번 픽셀 -> 0번 바이트의 3번 비트
    image[0] = image[0] | (1 << 3);
    cout << "image[0] (윗줄): " << std::bitset<8>(image[0]) << endl;

    // (10, 0) 좌표는 없지만, 일렬로 늘어섰을 때 10번째 픽셀에 점을 찍는다고 가정 (아랫줄 3번째)
    // 10번 픽셀 -> 1번째 바이트의 (10 % 8 = 2)번 비트
    image[1] = image[1] | (1 << (10 % 8));
    cout << "image[1] (아랫줄): " << std::bitset<8>(image[1]) << endl;

    return 0;
}