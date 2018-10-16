// Fill out your copyright notice in the Description page of Project Settings.

#include "A_WorldChunk.h"


// Sets default values
AA_WorldChunk::AA_WorldChunk()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;



}

// Called when the game starts or when spawned
void AA_WorldChunk::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AA_WorldChunk::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

bool AA_WorldChunk::CheckTileCollidable(TSoftObjectPtr<UPaperTileSet> TileSet, int32 TileIndex)
{
    // TODO Properly implement collision check via UPaperTileSet.GetTileMetadate(TileIndex) -> CollisionData
    if (TileIndex >= 0 && TileSet != nullptr)
    {
        return true;
    }
    return false;
}

void AA_WorldChunk::PopulateMapDatabase(TArray<UPaperTileMap*> ChunkDatabaseRef)
{
    for(auto &CurrentChunk : ChunkDatabaseRef)
    {
        if (CurrentChunk == nullptr)
        {
            continue;
        }
        FMapChunk *CreatingData = new FMapChunk();
        CreatingData -> ChunkData = CurrentChunk;
        TSoftObjectPtr<UPaperTileSet> CurrentTileSet = CurrentChunk -> SelectedTileSet;
        UPaperTileLayer *CurrentLayer = CurrentChunk -> TileLayers [0];
        // * ----- Calculating Entry and Exit Area ----- * //
        // Assume all chunk have ceiling/floor in the 1st column and last column
        int32 ChunkX = CurrentLayer -> GetLayerWidth();
        int32 ChunkY = CurrentLayer -> GetLayerHeight();
        bool EntCeil = false;
        bool EntFloor = false;
        bool ExtCeil = false;
        bool ExtFloor = false;
        for (int index = 0; index < ChunkY; index = index + 1)
        {
            // ** --- Entry --- ** //
            int32 CurrentTile = CurrentLayer -> GetCell(0, index).PackedTileIndex;
            bool TileCollidable = CheckTileCollidable(CurrentTileSet, CurrentTile);
            if (EntCeil == false && EntFloor == false && TileCollidable)
            {
                // Mark Ceiling start
                EntCeil = true;
            }
            else if (EntCeil == true && EntFloor == false && ! TileCollidable)
            {
                // Mark Ceiling end
                EntFloor = true;
                CreatingData -> EntryCeil = index - 1;
            }
            else if (EntCeil == true && EntFloor == true && TileCollidable)
            {
                // Mark Floor start
                int32 EntSize = index - CreatingData -> EntryCeil;
                CreatingData -> EntryFloor = index;
                CreatingData -> EntrySize = EntSize;
                CreatingData -> EntryCenter = (EntSize / 2) + CreatingData -> EntryCeil;
                EntCeil = false;
            }
            // ** --- Exit --- ** //
            CurrentTile = CurrentLayer -> GetCell(ChunkX - 1, index).PackedTileIndex;
            TileCollidable = CheckTileCollidable(CurrentTileSet, CurrentTile);
            if (ExtCeil == false && ExtFloor == false && TileCollidable)
            {
                // Mark Ceiling start
                ExtCeil = true;
            }
            else if (ExtCeil == true && ExtFloor == false && ! TileCollidable)
            {
                // Mark Ceiling end
                ExtFloor = true;
                CreatingData -> ExitCeil = index - 1;
            }
            else if (ExtCeil == true && ExtFloor == true && TileCollidable)
            {
                // Mark Floor start
                int32 ExtSize = index - CreatingData -> ExitCeil;
                CreatingData -> ExitFloor = index;
                CreatingData -> ExitSize = ExtSize;
                CreatingData -> ExitCenter = (ExtSize / 2) + CreatingData -> ExitCeil;
                ExtCeil = false;
            }
            if (EntCeil == false && EntFloor == true && ExtCeil == false && ExtFloor == true)
            {
                break;
            }
        }
        // * ----- Assigning Chunk to MapDatabase ----- * //
        MapDatabase.Add(*CreatingData);
    }
    return;
}
