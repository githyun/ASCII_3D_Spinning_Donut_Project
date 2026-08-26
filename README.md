# 🍩 3D ASCII Spinning Donut

<img width="400" height="400" alt="Spinning_Donut_GIF" src="https://github.com/user-attachments/assets/fd779212-4fe3-4cfa-b610-4774cd48b4d2" />


C++와 수학적 원리를 활용하여 콘솔 터미널에 3D 회전 도넛을 렌더링하는 프로젝트입니다.

## 💡 프로젝트 개요
* **제작자:** 권현성
* **제작년도:** 2025년 (고3)
* **사용 언어:** C++
* **해상도:** 80 x 24 (가로 x 세로)
* **핵심 기술:** 수학적 공간 기하(벡터/행렬), Z-buffer를 이용한 3D-2D 투영, ANSI 이스케이프 시퀀스 기반 터미널 제어

## 📐 핵심 원리 및 수학적 배경

### 1. 도넛(Torus) 생성 (벡터 합성)
원점으로부터 일정 거리 떨어진 2차원 원을 생성합니다. 이는 수학적으로 벡터의 합성과 같습니다.
- 중심점까지의 거리 `R2`와 원의 반지름 `R1`을 이용하여 원의 둘레 좌표를 구합니다.
- `(x, y, z) = (R2, 0, 0) + (R1*cos(theta), R1*sin(theta), 0)`

### 2. 3D 공간에서의 회전 (행렬 연산)
생성된 원을 특정 축을 기준으로 회전시켜 도넛 모양(Torus)을 만들고, 전체 구조물을 X축 및 Z축으로 회전시킵니다.
- `x, y, z` 축에 대한 각각의 회전 행렬을 기존 좌표에 점곱(Dot Product)하여 3D 공간 회전을 구현합니다.

### 3. 2D 화면 투영 (직각삼각형의 닮음)
3차원 좌표로 계산된 도넛을 2차원 모니터(터미널)에 보여주기 위해 투영을 진행합니다.
- 카메라(눈)와 스크린, 객체 간의 직각삼각형 닮음비를 이용합니다.
- 투영 공식: `x' = x * k1 / (k2 + z)`

### 4. 깊이 판별 (Z-Buffer) 및 렌더링
- **Z-Buffer:** 3차원 물체의 앞면이 뒷면을 가리도록 깊이 정보를 저장합니다. 본 프로젝트에서는 깊이 `z`의 역수인 `1/z` 값을 버퍼에 저장하여, 값이 클수록(가까울수록) 화면에 표시되게 구현했습니다.
- **명암(Luminance):** 도넛 표면의 법선 벡터(Surface Normal)를 구한 뒤, 지정된 조명 방향 벡터와 내적하여 표면 밝기를 계산합니다.
- 밝기 값에 따라 `.,-~:;=!*#$@` 순서로 아스키(ASCII) 문자를 매핑하여 입체감을 더했습니다.

## 🛠 주요 트러블슈팅 및 구현 디테일

* **Windows 터미널 ANSI 시퀀스 활성화:** 
  Windows 기본 콘솔은 색상이나 커서 이동을 위한 ANSI 이스케이프 시퀀스를 기본 지원하지 않습니다. 이를 해결하기 위해 `<windows.h>`의 `GetConsoleMode`, `SetConsoleMode` API를 사용하여 `ENABLE_VIRTUAL_TERMINAL_PROCESSING` 플래그를 활성화했습니다.
* **오타 및 수학적 디버깅:**
  처음 구현 후 도넛의 형상이 찌그러지고 빛 반사가 비정상적으로 나오는 문제가 있었습니다. 코드를 한 줄씩 꼼꼼히 점검한 결과, Z좌표 계산 식에서 `sin(pi)`를 `sin(theta)`로 잘못 입력한 오타를 발견하여 수정했습니다. 


---
*참고한 자료: [I Coded a 3D Spinning Donut - Green Code](https://www.youtube.com/watch?v=74FJ8TTMM5E), [How does the Spinning Cube work? - Code Fiction](https://www.youtube.com/watch?v=0E0UBphVRhY), [Donut math: how donut.c works](https://www.a1k0n.net/2011/07/20/donut-math.html), [ASCII-Donut-Animation - sherwinvishesh](https://github.com/sherwinvishesh/ASCII-Donut-Animation/blob/main/src/circle.cpp), [[C/C++ ] ANSI 이스케이프 시퀀스 사용해서 커서 이동 + 터미널 조작하기](https://eteo.tistory.com/746)*
