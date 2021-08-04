#include "AnimInstance_HIKDrivee.h"
#include "Misc/Paths.h"
#include "ik_logger_unreal.h"


void UAnimInstance_HIKDrivee::PreUpdateAnimation(float DeltaSeconds)
{
	Super::PreUpdateAnimation(DeltaSeconds);
	int n_targets = (int)m_targets.Num();
	LOGIKVar(LogInfoInt, n_targets);
}

FString UAnimInstance_HIKDrivee::GetFileConfName() const
{
	return FString(L"HIK.xml");
}