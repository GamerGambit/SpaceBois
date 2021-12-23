// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_MusicInstrument.h"

FMusicNote::FMusicNote()
	: Letter{EMusicLetter::EMN_C}
	, Accidental{EMusicNoteAccidental::EMNA_Natural}
	, Octave{ 3 }
{
	// NOP
}
FMusicNote::FMusicNote(EMusicLetter letter)
	: FMusicNote{}
{
	Letter = letter;
}

// Sets default values
ASB_MusicInstrument::ASB_MusicInstrument()
	: BeatIndex{ 0 }
	, NextBeatTime{ 0.0f }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Primary Audio Component"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;
}

UAudioComponent* ASB_MusicInstrument::GetAvailableAudioComponent()
{
	if (!AudioComponent->IsPlaying())
		return AudioComponent;

	for (auto secondary : SecondaryAudioComponents)
	{
		if (!secondary->IsPlaying())
			return secondary;
	}

	auto newComp = NewObject<UAudioComponent>(this);
	newComp->bAutoActivate = false;
	newComp->SetSound(AudioComponent->Sound);
	newComp->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	newComp->RegisterComponent();

	SecondaryAudioComponents.Add(newComp);

	return newComp;
}

void ASB_MusicInstrument::CreateNoteState(EMusicLetter letter)
{
	for (const auto& state : NoteStates)
	{
		if (state.Letter == letter)
			return;
	}

	NoteStates.Add(FMusicNote{ letter });
}

void ASB_MusicInstrument::ResetNoteStates()
{
	NoteStates.Empty();

	for (int32 i = 0; i < 7; ++i)
	{
		FMusicNote state;
		state.Letter = (EMusicLetter)i;
		state.Accidental = EMusicNoteAccidental::EMNA_Natural;
		state.Octave = 3;
		NoteStates.Add(state);
	}
}

EMusicNoteAccidental ASB_MusicInstrument::GetNoteAccidental(EMusicLetter letter) const
{
	for (const auto& state : NoteStates)
	{
		if (state.Letter == letter)
			return state.Accidental;
	}

	check(false);
	return EMusicNoteAccidental::EMNA_Natural;
}

void ASB_MusicInstrument::SetNoteAccidental(EMusicLetter letter, EMusicNoteAccidental accidental)
{
	CreateNoteState(letter);

	for (auto& state : NoteStates)
	{
		if (state.Letter == letter)
		{
			state.Accidental = accidental;
			return;
		}
	}
}

int32 ASB_MusicInstrument::GetNoteOctave(EMusicLetter letter) const
{
	for (const auto& state : NoteStates)
	{
		if (state.Letter == letter)
			return state.Octave;
	}

	check(false);
	return 3;
}

void ASB_MusicInstrument::SetNoteOctave(EMusicLetter letter, int32 octave)
{
	CreateNoteState(letter);

	for (auto& state : NoteStates)
	{
		if (state.Letter == letter)
		{
			state.Octave = octave;
			return;
		}
	}
}

void ASB_MusicInstrument::ResetNotes(UAudioComponent* audioComponent)
{
	// 7 letters (A-G)
	for (int l = 0; l < 7; ++l)
	{
		// letter 2 is C - C can have 9 octaves, everything else only 8
		auto octaveCount = (l == 2 ? 9 : 8);

		// 3 accidentals (natural, flat, sharp)
		for (int a = 0; a < 3; ++a)
		{
			char accidental;

			// the numbers we compare `a` to are arbitrary, as long as we cover all accidentals
			if (a == 0)
			{
				accidental = 'n';
			}
			else if (a == 1)
			{
				accidental = 'b';
			}
			else if (a == 2)
			{
				accidental = '#';
			}

			for (int o = 0; o < octaveCount; ++o)
			{
				// Trim the qualifer off the enum name
				FString paramName = StaticEnum<EMusicLetter>()->GetValueAsString(static_cast<EMusicLetter>(l)).RightChop(FString("EMusicLetter::EMN_").Len());
				paramName.AppendChar(accidental);
				paramName.AppendInt(o);

				audioComponent->SetBoolParameter(FName(*paramName), false);
			}
		}
	}
}

void ASB_MusicInstrument::PrimeNote(UAudioComponent* audioComponent, FMusicNote note)
{
	if (note.Accidental == EMusicNoteAccidental::EMNA_Flat && (note.Letter == EMusicLetter::EMN_C || note.Letter == EMusicLetter::EMN_F))
	{
		if (note.Letter == EMusicLetter::EMN_C)
		{
			note.Octave--;
		}

		note.Letter = (EMusicLetter)((int)note.Letter - 1);
		note.Accidental = EMusicNoteAccidental::EMNA_Natural;
	}
	else if (note.Accidental == EMusicNoteAccidental::EMNA_Sharp && (note.Letter == EMusicLetter::EMN_B || note.Letter == EMusicLetter::EMN_E))
	{
		if (note.Letter == EMusicLetter::EMN_B)
		{
			note.Octave++;
		}

		note.Letter = (EMusicLetter)((int)note.Letter + 1);
		note.Accidental = EMusicNoteAccidental::EMNA_Natural;
	}
	else if (note.Accidental == EMusicNoteAccidental::EMNA_Sharp && note.Letter == EMusicLetter::EMN_G)
	{
		note.Letter = EMusicLetter::EMN_A;
		note.Accidental = EMusicNoteAccidental::EMNA_Flat;
	}
	else if (note.Accidental == EMusicNoteAccidental::EMNA_Sharp)
	{
		note.Letter = (EMusicLetter)((int)note.Letter + 1);
		note.Accidental = EMusicNoteAccidental::EMNA_Flat;
	}

	if (note.Octave < 1 || note.Octave >(note.Letter == EMusicLetter::EMN_C ? 9 : 8))
		return;

	// Set the accidental character
	char accidental;
	if (note.Accidental == EMusicNoteAccidental::EMNA_Natural)
	{
		accidental = 'n';
	}
	else if (note.Accidental == EMusicNoteAccidental::EMNA_Flat)
	{
		accidental = 'b';
	}
	else if (note.Accidental == EMusicNoteAccidental::EMNA_Sharp)
	{
		accidental = '#';
	}

	// Build the parameter name for the sound cue
	// Trim the qualifer off the enum name
	FString paramName = StaticEnum<EMusicLetter>()->GetValueAsString(note.Letter).RightChop(FString("EMusicLetter::EMN_").Len());
	paramName.AppendChar(accidental);
	paramName.AppendInt(note.Octave);

	audioComponent->SetBoolParameter(FName(*paramName), true);
}

void ASB_MusicInstrument::PlaySongFromString(FString song, float bpm, int numPlays)
{
	SecondaryAudioComponents.Empty();

	BeatIndex = 0;
	Beats.Empty();

	CurrentTempo = bpm;
	CurrentBeatInterval = 60.0f / bpm;
	NumPlays = numPlays;
	NextBeatTime = 0.0f;

	ResetNoteStates();

	// Split lines
	TArray<FString> lines;
	int32 lineCount = song.ParseIntoArrayLines(lines);
	for (auto line : lines)
	{
		// Split beats
		TArray<FString> beats;
		int32 beatCount = line.ToLower().ParseIntoArray(beats, TEXT(","), false);
		for (auto beat : beats)
		{
			FMusicBeat beatToAdd;

			if (beat.Len() == 0)
			{
				beatToAdd.PostDelay = CurrentBeatInterval;
				Beats.Add(beatToAdd);
				continue;
			}

			TArray<FString> timing;
			int32 timingCount = beat.ParseIntoArray(timing, TEXT("/"));

			TArray<FString> notes;
			int32 noteCount = timing[0].ParseIntoArray(notes, TEXT("-"));
			for (auto note : notes)
			{
				// Get the ascii decimal for the note letter, then get subtract 97 (ascii decimal lowercase a)
				// the result is that we can detect if the ntoe letter is within a-g
				auto letterAscii = (int32)note.GetCharArray()[0] - 97;
				if (letterAscii < 0 || letterAscii > 6)
					continue;

				auto letter = (EMusicLetter)letterAscii;

				for (int32 charIndex = 1; charIndex < note.Len(); ++charIndex)
				{
					FString ni = note.Mid(charIndex, 1);
					if (ni.IsNumeric())
					{
						SetNoteOctave(letter, FCString::Atoi(*ni));
					}
					else
					{
						if (ni.Equals(TEXT("n")))
						{
							SetNoteAccidental(letter, EMusicNoteAccidental::EMNA_Natural);
						}
						else if (ni.Equals(TEXT("b")))
						{
							SetNoteAccidental(letter, EMusicNoteAccidental::EMNA_Flat);
						}
						else if (ni.Equals(TEXT("#")) || ni.Equals(TEXT("s")))
						{
							SetNoteAccidental(letter, EMusicNoteAccidental::EMNA_Sharp);
						}
					}
				}

				FMusicNote noteToAdd;
				noteToAdd.Letter = letter;
				noteToAdd.Accidental = GetNoteAccidental(letter);
				noteToAdd.Octave = GetNoteOctave(letter);

				beatToAdd.Notes.Add(noteToAdd);
			}

			if (timingCount >= 2 && timing[1].IsNumeric())
			{
				beatToAdd.PostDelay = CurrentBeatInterval / FCString::Atof(*timing[1]);
			}
			else
			{
				beatToAdd.PostDelay = CurrentBeatInterval;
			}

			Beats.Add(beatToAdd);
			FString noteStr;
			for (auto note : beatToAdd.Notes)
			{
				noteStr.Append(FString::Printf(TEXT("%s%s%i"), *StaticEnum<EMusicLetter>()->GetValueAsString(note.Letter).RightChop(FString("EMusicLetter::EMN_").Len()), *StaticEnum<EMusicNoteAccidental>()->GetValueAsString(note.Accidental), note.Octave));
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Added beat: %s"), *noteStr));
		}
	}
}

// Called every frame
void ASB_MusicInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (NumPlays > 0 && GetWorld()->GetTimeSeconds() >= NextBeatTime && Beats.Num() > BeatIndex)
	{
		UAudioComponent* availableAudioComponent = GetAvailableAudioComponent();

		ResetNotes(availableAudioComponent);
		auto beat = Beats[BeatIndex];

		for (int i = 0; i < beat.Notes.Num(); ++i)
		{
			PrimeNote(availableAudioComponent, beat.Notes[i]);
		}

		availableAudioComponent->Play();
		BeatIndex++;
		NextBeatTime = GetWorld()->GetTimeSeconds() + beat.PostDelay;

		if (BeatIndex >= Beats.Num())
		{
			--NumPlays;
		}
	}

	// Cleanup unused secondaries
	if (NumPlays == 0 && SecondaryAudioComponents.Num() > 0)
	{
		SecondaryAudioComponents.Empty();
	}
}