#pragma once
//=================================================================================================
// @brief 서버 명령어 테이블
//=================================================================================================
#include "Runtime/Core/Public/Containers/UnrealString.h"
namespace CommandTable
{
	const FString LoginSuccess = TEXT("로그인에 성공");
	const FString RoomListItem = TEXT("방 번호");
	const FString EnterRoom = TEXT("입장하셨습니다");
	const FString ExitRoom = TEXT("나갔습니다");
	const FString Whisper = TEXT("귓속말");
	const FString UserListItem = TEXT("유저 닉네임");
	const FString EnterRoomOtherUser = TEXT("방에 들어왔습니다");
	const FString InviteRequest = TEXT("초대 요청");
}


namespace StringTable
{

	const FString LoginSuccess = TEXT("로그인에 성공");
	const FString RoomListItem = TEXT("방 번호");
	const FString EnterRoom = TEXT("입장하셨습니다");
	const FString ExitRoom = TEXT("나갔습니다");
}