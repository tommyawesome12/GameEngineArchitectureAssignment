// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class CPPACTORTEST_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	

public:
	//primary draw call for HUD
	virtual void DrawHUD() override;

protected:
	//this will be drawn at the center of te screem
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
};


