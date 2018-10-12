// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileMap.h"
#include "PaperTileLayer.h"
#include "PaperTileSet.h"
#include "PaperTileMapComponent.h"
#include "A_WorldChunk.generated.h"


USTRUCT(BlueprintType)
struct FMapChunk
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float EntryCenter;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 EntrySize;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float ExitCenter;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 ExitSize;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 EntryCeil;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 EntryFloor;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 ExitCeil;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 ExitFloor;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPaperTileMap *ChunkData;
};

USTRUCT(BlueprintType)
struct FLoadedChunk
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FMapChunk ChunkData;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPaperTileMapComponent *OnScreenChunk;
};

UCLASS()
    class GRAPPLINGHOOK_API AA_WorldChunk : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void PopulateMapDatabase(TArray<UPaperTileMap*> ChunkDatabaseRef);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FMapChunk> MapDatabase;

    bool CheckTileCollidable(TSoftObjectPtr<UPaperTileSet> TileSet, int32 TileIndex);

    // Sets default values for this actor's properties
    AA_WorldChunk();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
