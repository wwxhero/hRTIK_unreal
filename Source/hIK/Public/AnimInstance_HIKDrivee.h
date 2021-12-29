#pragma once
#include "hIK.h"
#include "CoreMinimal.h"
#include "AnimInstance_MotionPipe.h"
#include "Misc/ScopeTryLock.h"
#include "AnimInstance_HIKDrivee.generated.h"

UENUM()
enum TRACKER_ID
{
	RH = 0	UMETA(DisplayName = "RightHand"),
	LH		UMETA(DisplayName = "LeftHand"),
	RF		UMETA(DisplayName = "RightFoot"),
	LF		UMETA(DisplayName = "LeftFoot"),
	PW		UMETA(DisplayName = "Pelvis"),
	HMD		UMETA(DisplayName = "Head"),
	RCTRL 	UMETA(DisplayName = "RightCtrl"),
	LCTRL 	UMETA(DisplayName = "LeftCtrl"),
	N_TRACKERS,
	N_SPECTRAKS = HMD,
	Unknown
};

struct FVRTrackingBind
{
	TRACKER_ID trID;
	int32	tarID;
	FTransform tar2tr;
};

UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType, meta = (BlueprintThreadSafe), Within = SkeletalMeshComponent)
class HIK_API UAnimInstance_HIKDrivee : public UAnimInstance_MotionPipe
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault))
	int32 DBG_VisBody_i;

public:
	UAnimInstance_HIKDrivee();

	~UAnimInstance_HIKDrivee()
	{
	}

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUninitializeAnimation() override;

	virtual void PreUpdateAnimation(float DeltaSeconds) override;


	FORCEINLINE void PushUpdateTargets(const TArray<Target>& targets)
	{
		m_nUpdateTargets ++;
		m_targets = targets;
	}

	void VRIK_Connect(const TArray<USceneComponent*>& trackers);
	void VRIK_Disconnect();
	
	FORCEINLINE void VRIK_PushUpdateTargets()
	{
		m_nUpdateTargets ++;
		check(m_targets.Num() == m_bindings.Num());
		for (auto bind_i : m_bindings)
		{
			auto tracker_i = m_trackers[bind_i.trID];
			FTransform tr2w = tracker_i->GetComponentTransform();
			FTransform tar2w = bind_i.tar2tr * tr2w;
			m_targets[bind_i.tarID].tm_l2w = tar2w;
		}
	}

private:
	virtual void OnPreUpdate(FAnimInstanceProxy_MotionPipe* proxy) const override;
	virtual void OnPostUpdate(const FAnimInstanceProxy_MotionPipe* proxy) override;

private:
	TArray<Target> m_targets;

	TArray<FVRTrackingBind> m_bindings;
	TArray<USceneComponent*> m_trackers;
	int m_nUpdateTargets;
	int m_nIKReset;
};
