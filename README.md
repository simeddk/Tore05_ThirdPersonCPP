아래와 같은 형태로 내가 만들고자 하는 게임의 초기 기획을 작성하시오

김경석
![image](https://github.com/user-attachments/assets/ebc1bb13-46a3-4ef0-a8d2-1ec993d4e736)


---
### 게임 요소
### 1. 다수의 무기/스킬 시스템
- 근접 공격 : 콤보 기능
![image](https://github.com/user-attachments/assets/54c36310-a310-4ae3-b833-d775e6e8e644)

- 간접 공격 : 프로젝타일 및 보조 스킬
![image](https://github.com/user-attachments/assets/551233f7-4731-4420-a3da-87013a9126f7)

### 2. 적 AI 기능
- 적 감지 및 이동(Spline, EQS)
![image](https://github.com/user-attachments/assets/70483c29-8b8e-4beb-b0d3-abacaaa05e55)

- 적 공격/스킬
![image](https://github.com/user-attachments/assets/400e7519-b180-4bda-a52e-16d14e1123dc)

### 기술 요소
- 3인칭 오버뷰 시점의 액션 게임
- 액션 시스템
   - ActionComponent(액션 등록 시스템)
   - DataAsset을 활용한 장착, 메쉬/충돌체, 동작 관리
   - 입력 바인딩 및 BP Callable을 활용한 플레이어/적 캐릭터 액션 장착
   - 장착 액션에 따른 애니메이션 포즈/컬러 변경 이벤트 기반의 제어
   - SpawnActor/SpanActorDeffered를 활용한 프로젝타일 매직볼 액션
   - 플레이어 컨트롤러 커서 지점으로 순간 이동 기능
   - 타이머를 활용한 다단 히트 액션
   - 근접 무기의 중복 대미지 체크
   - AnimNotify/AnimNotifyState를 활용한 충돌체, 상태 제어
   - StateComponent를 활용한 이벤트 기반 상태 제어
   - DataTable을 활용한 플레이어/적 캐릭터 공용 몽타쥬 관리 등
- 인공 지능
   - BehaviorTree와 BlackBoardAsset을 활용한 행동 제어
   - SplineComponent를 활용한 패트롤
   - EQS를 활용한 도주 시스템 등
- 사용자 위젯
   - UMG 액션 변경 보드 제공
   - 적 체력 및 이름 표시 기능
   - HUD를 활용한 Aim 지점 표시

### 3. 구현된 플레이어 캐릭터
   - 메쉬 및 애님인스턴스 구현
   - 다이나믹 머티리얼 적용
   - 주요 컴포넌트 어타치 완료

![image](https://github.com/user-attachments/assets/03e8e2b5-e97d-4efb-b1d0-6381943fa20c)
