// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHUD.h"

void AFPSHUD::DrawHUD() 
{
	Super::DrawHUD();

	if (CrosshairTexture)
	{
		//Find the center of our canvas
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5);

		//offset by half of the textures dimensions so that the center of the texture aligns with the center of the canvas
		FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5));

		//Draw the crosshair at the center point
		FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}