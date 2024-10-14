# Know_Your_Limits
+ 개인 프로젝트
+ 개발 기간 :  2023.03 ~ 2023.10
+ 장르 : 3인칭 어드벤쳐 / SinglePlayer
+ 엔진 : UE4.27

+ 업데이트
  + ```1.1 (버그 수정)```
  + ```1.2 (플레이어 피드백 반영)```

<br/>

> + 코드 리팩터링 - 2024.09.13 ~ 2024.09.19
>   + 종류별로 폴더 분리
>   + 클래스별로 기능 분리
>   + 주석 추가 및 변수 이름 변경
>   + 비효율적인 함수 재구성

<br/>

## 🚀 Trouble Shooting
## 1. 형변환 미스
```c++
AActor* Actor = Cast<AActor>(MyGameMode);
```
초반에 언리얼의 클래스 계층구조에 익숙해져있지 않아서 발생했던 문제. 이렇게 써놓고 왜 안되냐고 화냈었다😛

-> 지금은 거의 문제가 발생하지 않는다!

[이해하는 데 도움이 된 문서](https://dev.epicgames.com/community/learning/tutorials/5PKZ/unreal-engine-46ed69) 
<br/><br/>

## 2. 중복 Destroy 오류
맵에 배치된 MyEnemy가 플레이어에 의해 Destroy되고 나서도 **콜리전이 남아있는 듯한 현상**이 생겼다. 플레이어 캐릭터가 점프해서 Enemy를 파괴한 후 밑으로 떨어져야 정상인데, Enemy의 mesh는 사라졌지만 그 위치의 공중에 캐릭터가 걸려서 내려오지 않았다.

-> MyEnemy를 Destroy()하는 부분이 두 군데였는데, **한쪽 Destroy를 지우니까 해결됐다.**

[AMyCharacter :: ReachTarget()](https://github.com/cubee021/Know_Your_Limits/blob/main/Project/MyCharacter.cpp#L367)의 끝줄에 MyEnemy->Destroy()를 했었고, [AMyEnemy :: OnCharacterHit()](https://github.com/cubee021/Know_Your_Limits/blob/main/Project/MyEnemy.cpp#L107)에서도 Destroy()를 해서 문제가 생겼던 것 같다.

예상하기로는 캐릭터쪽 Destroy로 인해 MyEnemy의 콜리전 메모리가 비정상적으로 해제된 듯🤔
<br/><br/>

## 3. 플레이어 캐릭터 mesh와 capsule component 높이 차이
캐릭터 mesh보다 ACharacter에서 기본으로 제공하는 Capsule component가 더 높다. 블루프린트에서 half height를 조절하니 가운데를 기준으로 줄어들어 붕 떠버린다. 심지어 캡슐이 RootComponent라서 위치도 조정할 수가 없다.. 

이로 인해 불편한 점은 :
+ 캐릭터 머리가 object 또는 Enemy에 닿지 않았는데도 닿았다고 판정됨 - [똑같은 문제에 관한 레딧 포스트](https://www.reddit.com/r/unrealengine/comments/oei1px/how_do_i_get_my_capsule_component_height_to_match/)
+ 그래서 좁은 공간이지만 mesh는 충분히 들어갈 수 있는 지형임에도 걸려서 못들어간다🗿🗿
<br/>
-> 두 번째 프로젝트 진행하는 지금까지도 해결을 못했다...
<br/><br/>

## 4. 캡션 무한 생성
[CaptionTrigger](https://github.com/cubee021/Know_Your_Limits/blob/31996161ac37521b5470a50f90fc2dfee7734a1f/Project/Interaction/CaptionTrigger.cpp)는 플레이어가 트리거를 건드리면 화면에 캡션이 뜨게 하는 액터다. 근데 플레이어가 리스폰되거나 왔던 길을 되돌아갈때마다 재차 생성된다.
<br/>

-> IsAlreadyShown 변수를 설정하여 캐릭터 오버랩 시 한 번 이상 뜨지 않게 체크하면 된다.

https://github.com/cubee021/Know_Your_Limits/blob/31996161ac37521b5470a50f90fc2dfee7734a1f/Project/Interaction/CaptionTrigger.cpp#L54-L61

<br/><br/>

## 5. Steam OnlineSubsystem 연동과 Achievement 세팅
### Steam 연동 위해서 할것 :
1. Online Subsystem Steam 플러그인 설치
2. 빌드 파일에 "OnlineSubsystem", "OnlineSubsystemUtils" 추가
3. 밑에 Online 주석 처리 지우기
4. Binaries, Intermediate 폴더 지우고 재시작

[업적 연결 위해 참고한 글](https://www.orfeasel.com/handling-steam-achievements-steam-integration-part-2/)
**(⭐여기서 사용하는 헤더 안뜨면 NMake에 직접 경로 추가할 것!)**

[구현부](https://github.com/cubee021/Know_Your_Limits/blob/main/Project/MyCharacter.cpp#L556)
<br/><br/>

## 6. Frame dependency 문제
출시 후 PC방에서 게임을 해보니 SpeedCheckActor의 Floor가 엄청 빠른 속도로 무한 회전하다가 Fatal error로 종료됐다.

-> 해당 코드의 Rotation Speed에 **DeltaTime**을 곱하지 않아 발생한 문제였다.
https://github.com/cubee021/Know_Your_Limits/blob/f042f2288fb7c3c01da7dab0720404eb4d8d2642/Project/Interaction/SpeedCheckActor.cpp#L63-L66
<br/>

> 이전까지는 DeltaTime이 정확히 무엇인지 잘 몰랐다..

그래서 분명 집 컴퓨터에서는 정상적인데 왜 다른 컴퓨터에서는 안그럴까 고민이 많았다. 몇 주를 찾아 헤맨 끝에 알게 된 이 현상의 이름은 **"Frame dependency"** 

-말 그대로 프레임에 의존한다는 뜻이다. 컴퓨터마다 프레임 속도가 다를테니 우리집에서 맞춰놓은 Rotation Speed가 컴퓨터마다 달라질 수밖에. 이 현상을 막아주는 것이 바로 DeltaTime인 것이다👍

나중에 관련 교재를 사보니 기본중의 기본이었다. 지금은 꼬박꼬박 쓰는중
<br/><br/>

## 7. 정확하게 360도 회전시키는 법
5번 문제를 해결하고 곧 또 다른 문제가 생겼다. 원래 DegreeSum이 int32라서 ```DegreeSum[i] == 360```에 회전을 멈추는 방식이었다면, 지금은 DeltaTime을 곱하므로 float가 되어 값이 정확히 360일 수 없게 되어버린 것이다. (조금 더 가서 멈추거나 아예 계속 회전함)

-> 이를 해결하기 위해 몇 가지 방법을 시도해봤는데 :
### 1. FMath::RInterpTo()

+ 장점 : 파라미터 target rotation에 360.f를 직접 집어넣을 수 있어 편리하다. 
+ 단점 : **Gimbal Lock 발생.** 회전하는 Floor mesh의 축 특성상 pitch로 360도를 돌려야 하는데 [pitch의 회전 범위](https://forums.unrealengine.com/t/pitch-rotation-problem/315723)는 -90 ~ +90이라고 한다. 시계방향으로 90도를 넘지 못하고 파들거린다.

### 2. FQuat::Slerp()

+ 장점 : Gimbal Lock이 걸리지 않음.
+ 단점 :
  1. 0 ~ 270 / 270 ~ 360와 같이 두 번 끊어 사용해야 하는데, 교체되는 순간에 속도가 줄어 이어 붙이기가 어색하다. (함수 자체가 시작, 끝부분에 속도가 줄어든다)
  2. 파라미터로 Quaternion이 들어가는데, 원리가 어려워서 완벽하게 이해하지는 못하고 그냥 사용했다.
  3. 모든 Floor가 원래대로 돌아오지는 않았다. (어떤거는 세로로 서있고, 어떤거는 누워는 있는데 90도 돌아가있고..;;) 이를 해결하기 위해 Origin에 초기값 'Pitch, Roll Yaw'를 저장해서 target으로 지정해줬는데도 중간에 이상해진다. 월드에 놓인 축에 따라 양상이 달라지는 것 같은데.. 이유는 잘 모르겠다😥

### 3. 처음 방식 + FQuat::Slerp()
```Rotation Speed < 360```동안은 AddActorLocalRotation()으로 회전시키고, 이후부터 Slerp()로 Origin에 맞춰서 해결했다. 보간 거리가 짧아서 그런지 단점-3 문제가 생기지 않았다.

https://github.com/cubee021/Know_Your_Limits/blob/f042f2288fb7c3c01da7dab0720404eb4d8d2642/Project/Interaction/SpeedCheckActor.cpp#L63-L75
<br/><br/>

## 8. 캐릭터 리스폰 시 바닥으로 추락
플레이어 캐릭터가 게임 오버 후 마지막으로 저장된 위치에 리스폰 될 때, SetActorLocation()를 사용했더니 Speed가 그대로 보존되어서 그런지 원래 위치에서 튕겨나가는 일이 많았다🛸

-> TeleportTo() 사용하면 깔끔!

[구현부](https://github.com/cubee021/Know_Your_Limits/blob/main/Project/MyCharacter.cpp#L556)
<br/><br/>












