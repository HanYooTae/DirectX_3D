## Overview

- DirectX11 Project

- Shader 파일을 생성하여 클래스에서 동적 할당하는 방식으로 진행

- FX파일로 실습
    - 기본적인 실습
    - 배경화면 렌더링(Unreal Engine의 Sky_Sphere)
    - SkeletalMesh와 Material 파일로 Actor생성
    - Animation Clip파일로 Actor의 애니메이션 생성

- ImGui 활용

## Outcomes

1. LineDemo
    - 정점을 2개찍고 VertexBuffer로 2개의 점을 생성
    - PrimitiveTopology의 LineList로 이어붙임

![DX11_3D(1)](https://github.com/user-attachments/assets/9931ce91-280b-4b66-a886-28099930828f)


2. LineColorDemo
    - LineDemo에서 Developing
    - 버퍼에 Color정보를 추가로 태워서 보냄

![DX11_3D(2)](https://github.com/user-attachments/assets/64bb5a36-dee8-4d8b-a2e8-e488cb1bf32d)


3. MultiLineDemo
    - Primitive Topology를 배열로 생성
        - 0번 인덱스 : LineList
        - 1번 인덱스 : LineStrip

[![image](https://github.com/user-attachments/assets/6d074eda-eb89-44c2-812e-7017de38a756)
](https://youtu.be/oRQivS921H8)

4. PolygonDemo
    - 정점을 PrimitiveTopology의 TriangleList로 이어붙임
    - 폴리곤의 색상 변경

[![image](https://github.com/user-attachments/assets/87d6590d-79cd-48ff-91ad-7ae3b2b56fec)
](https://youtu.be/aVUVNUBrPXw)

5. PlaneDemo
    - 정점 6개를 생성하여 2개의 TriangleList를 생성하여 이어붙임
    - RS단계에서 FillMode를 WireFrame으로 설정하였으며, ImGui CheckBox를 이용하여 FillMode를 WireFrame으로 할지말지 결정

[![image](https://github.com/user-attachments/assets/32032992-7c98-44da-8ab1-0e8b476c0bd0)](https://www.youtube.com/watch?v=oxhjLHgTttw)

6. WorldDemo
    - PlaneDemo에서 Developing
    - D3DXMatrixRotationZ함수를 활용하여 Z축을 중심으로 회전

[![image](https://github.com/user-attachments/assets/a478001e-f1d3-4321-9720-2945fb77bef9)
](https://www.youtube.com/watch?v=aZP9rXUfUJA)

7. IndexBufferDemo
    - Index Buffer를 이용한 Box 생성

![DX11_3D(3)](https://github.com/user-attachments/assets/ca19216e-0e73-4d57-b1a7-322f838d05d4)


8. GridDemo
    - Width와 Height를 설정
    - Width와 Height로 2중 for문을 돌려 정점과 Index의 갯수를 설정

[![image](https://github.com/user-attachments/assets/11d535f3-94be-4cc3-8a28-0fd6b48cd775)
](https://youtu.be/g0JN_50Mm5w)

9. CubeDemo
    - 직육면체 렌더링
    - 한 면당 4개의 정점을 찍어 IndexBuffer를 이용. 총 24개의 정점 사용

[![image](https://github.com/user-attachments/assets/d848ddb3-6624-4a48-b530-677479b3acbd)
](https://youtu.be/r4AXK595ZXY)

10. TextureDemo
    - TexMetaData의 경로를 받아 초기 Texture를 동적 할당
    - Texture들을 저장한 경로에 있는 Texture 중 하나를 선택하여 기존의 Texture를 Delete하고 새롭게 동적 할당시켜줌
    
[![image](https://github.com/user-attachments/assets/ad69737b-1244-4d83-8f77-76026fca9af5)
](https://youtu.be/0P6OheXQVkc)
    
- Windows 캡쳐를 이용하였기 때문에 파일 경로로 들어가서 변경하는 부분은 녹화가 안되었음

11. SamplerStateDemo
    - TextureDemo에서 Developing
    - SamplerState를 이용하여 UV값을 대응시켜 Cropping

[![image](https://github.com/user-attachments/assets/13a7435b-c230-4a31-bcf9-402d597833c3)
](https://youtu.be/7v6shXzyaYo)

- Windows 캡쳐를 이용하였기 때문에 파일 경로로 들어가서 변경하는 부분은 녹화가 안되었음

12. TerrainDemo
    - BaseMap, LayerMap, AlphaMap 3가지를 동시에 Rendering
    - Lambert 연산으로 빛의 방향을 조절
    - Texture를 Tile화하여 하나의 Texture공간에 여러 개의 동일한 Texture로 채워줌
    - Normal Vector 랜더링

[![image](https://github.com/user-attachments/assets/c2502825-3748-4d38-a077-24f7480a51fb)
](https://youtu.be/A5zufmZf1ks)

13. StaticMeshDemo
    - 앞의 내용들을 응용하여 동시에 여러 오브젝트들을 렌더링

[![image](https://github.com/user-attachments/assets/0dd53f14-f7c2-4b63-8f0e-01f749ca74aa)
](https://youtu.be/RVa3EXLgeOU)

14. CubeMapDemo
    - StaticMeshDemo에서 Developing
    - Sphere를 만들어서 Texture를 입힌 후 TextureCube 형태의 SkyMap을 샘플링

[![image](https://github.com/user-attachments/assets/dd77ce2d-82a5-4143-8d41-a0d722012e85)
](https://youtu.be/CaTSUChA2Y8)

15. TextureBufferDemo
    - ComputeShader의 Thread GroupID를 활용한 메인 BackBuffer 렌더링

[![image](https://github.com/user-attachments/assets/6e43be68-03d3-4c30-b427-144c847c7bb9)
](https://youtu.be/-93o3Wtdjh8)

16. SkeletalMeshDemo
    - fbx, obj 파일에서 렌더링에 필요한 데이터를 추출하여 binary파일로 저장하여 렌더링
    - Material은 컴파일하여 xml파일에 저장
    
[![image](https://github.com/user-attachments/assets/ade4b2bc-55a2-4924-bf86-125dee2fa4f7)
](https://youtu.be/QcD5olAW-vc)
    

17. AnimationDemo
    - SkeletalMeshDemo에서 Developing
    - 정점의 Skinning data를 통해 렌더링
    - 각 프레임, clip 전환 구간마다 보간을 걸어 부드럽게 렌더링
    - Unreal Engine의 BlendSpace 구현

[![image](https://github.com/user-attachments/assets/4711c3e1-ef64-4b83-8e29-c4712132562a)
](https://youtu.be/kBKPv9vFpWo)
