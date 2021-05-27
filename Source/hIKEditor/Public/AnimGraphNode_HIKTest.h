// Copyright (c) Mathew Wang 2021

#pragma once
#include "hIKEditor.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "AnimNode_HIKTest.h"
#include "AnimGraphNode_HIKTest.generated.h"

UCLASS()
class HIKEDITOR_API UAnimGraphNode_HIKTest : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_BODY()

public:

	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	FLinearColor GetNodeTitleColor() const override;
	FString GetNodeCategory() const override;
	virtual const FAnimNode_SkeletalControlBase* GetNode() const override { return &Node; }

protected:
	virtual FText GetControllerDescription() const;
protected:
	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_HIKTest Node;

};