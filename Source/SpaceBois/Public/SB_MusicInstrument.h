// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"

#include "SB_Interactable.h"
#include "SB_MusicInstrument.generated.h"

UENUM()
enum class EMusicLetter
{
	EMN_A,
	EMN_B,
	EMN_C,
	EMN_D,
	EMN_E,
	EMN_F,
	EMN_G,
};

UENUM()
enum class EMusicNoteAccidental
{
	EMNA_Natural,
	EMNA_Flat,
	EMNA_Sharp,
};

USTRUCT(Blueprintable)
struct FMusicNote
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMusicLetter Letter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMusicNoteAccidental Accidental;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Octave;

	FMusicNote();
	FMusicNote(EMusicLetter letter);
};

USTRUCT(Blueprintable)
struct FMusicBeat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMusicNote> Notes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PostDelay;
};

UCLASS(Blueprintable)
class SPACEBOIS_API ASB_MusicInstrument : public AActor, public ISB_Interactable
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AudioComponent = nullptr;

	TArray<UAudioComponent*> SecondaryAudioComponents;

	TArray<FMusicBeat> Beats;
	TArray<FMusicNote> NoteStates;
	float CurrentTempo;
	float CurrentBeatInterval;
	int NumPlays;

	int BeatIndex;
	float NextBeatTime;

	UAudioComponent* GetAvailableAudioComponent();

	void CreateNoteState(EMusicLetter letter);
	void ResetNoteStates();

	EMusicNoteAccidental GetNoteAccidental(EMusicLetter letter) const;
	void SetNoteAccidental(EMusicLetter letter, EMusicNoteAccidental accidental);

	int32 GetNoteOctave(EMusicLetter letter) const;
	void SetNoteOctave(EMusicLetter letter, int32 octave);

	void ResetNotes(UAudioComponent* audioComponent);
	void PrimeNote(UAudioComponent* audioComponent, FMusicNote note);
	
public:
	// Sets default values for this actor's properties
	ASB_MusicInstrument();

	UFUNCTION(BlueprintCallable)
	void PlaySongFromString(FString song, float bpm, int numPlays);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
