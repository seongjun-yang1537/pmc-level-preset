#pragma once

#include "CoreMinimal.h"

struct FLevelPresetData
{
	FString Prefix;
	FString LevelPath;

	FLevelPresetData(){}
	FLevelPresetData(FString prefix, FString levelPath) : Prefix(prefix), LevelPath(levelPath) {};
};

bool operator==(const FLevelPresetData& lhs, const FLevelPresetData& rhs);
