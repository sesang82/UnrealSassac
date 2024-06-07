#pragma once

#include "EngineMinimal.h"

// 로그 사용가능하게 하는 함수 (디버깅용으로 출력 로그 사용할 수 있음)

/*

아래와같이 쓰면 모든 경고를 출력로그에 쓰인다.

근데 declare_Log를 쓰려면 정의부를 써줘야하는데 이건 .cpp에 만들어야하므로

.cpp파일 생성했다. 첫번째 인자에는 프로젝트 이름 쓰면 됨

*/
DECLARE_LOG_CATEGORY_EXTERN(Sac6, Warning, All);
