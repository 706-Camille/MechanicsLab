### 🚀 어빌리티 활성화 (Ability Activation Flow)

시스템의 모든 어빌리티는 `FGameplayTag`를 통해 활성화됩니다.

1.  **`TryActivateAbilityByTag(const FGameplayTag& InAbilityTag)`**
    * `UMLCombatComponent`의 메인 함수입니다.
    * **클라이언트 호출 시:** `ServerTryActivateAbilityByTag` RPC를 호출하여 서버에 실행을 요청합니다.
    * **서버 호출 시:** 자신이 소유한 `Abilities` 배열을 순회하며 `InAbilityTag`와 일치하는 `AbilityTag`를 가진 `UMLAbilityBase`를 찾습니다.
    * 일치하는 어빌리티를 찾으면 `Ability->ActivateAbility()`를 호출합니다.

### 🌐 멀티플레이 공격 판정 (Server-Authoritative Attack)

모든 공격 판정은 서버에서만 수행되어야 합니다.

1.  **(Client)** 플레이어가 공격 입력을 누릅니다.
2.  **(Client)** `AnimNotify` 또는 입력 이벤트에서 `Server_ExecuteAttackTrace()` (서버 RPC)를 호출합니다.
3.  **(Server)** `Server_ExecuteAttackTrace_Implementation` 함수가 실행됩니다.
4.  **(Server)** `BoxTraceMultiForObjects` 등을 사용해 충돌한 액터를 감지합니다.
5.  **(Server)** 감지된 적 액터(`HitActor`)에서 `UMLCombatComponent`를 가져옵니다.
6.  **(Server)** `EnemyCombatComponent->TryActivateAbilityByTag("Enemy.HitReact")`를 호출하여 적의 피격 반응을 **서버가 직접** 트리거합니다.

### 🤸 피격 반응 (Hit Reaction System)

피격 반응은 "상태"와 "구현"이 분리된 유연한 구조를 가집니다.

* **활성화 태그:** `Enemy.HitReact` (공격자가 이 태그로 어빌리티를 활성화시킴)
* **상태 태그:** `Effect.HitReact` (피격 어빌리티가 **스스로에게** 적용하여 "피격 중" 상태임을 알림)
    * 모든 공격/이동 어빌리티는 `ActivateAbility` 시작 시 "만약 나에게 `Effect.HitReact` 태그가 있다면 어빌리티를 중단한다"는 로직을 추가해야 합니다.

**`GA_Enemy_HitReact` (`UMLAbilityBase` 상속)의 로직:**

1.  `ActivateAbility`가 실행됩니다.
2.  (권장) 자신에게 `Effect.HitReact` 상태 태그를 적용합니다. (다른 행동 차단)
3.  `ActorInfo`에서 `AvatarActor` (적 캐릭터)를 가져옵니다.
4.  (선택 사항) `EffectContext` 등에서 피격 방향(`Direction`) 정보를 가져옵니다.
5.  `AvatarActor`에서 `IEnemyInterface`를 가져와 `GetHitReactMontage(Direction)`를 호출합니다.
6.  `PlayMontage`를 실행하여 반환된 몽타주를 재생합니다. (몽타주 재생은 자동으로 리플리케이트됩니다.)
7.  (권장) 몽타주 종료 시점에 바인딩된 델리게이트에서 `Effect.HitReact` 상태 태그를 제거합니다.