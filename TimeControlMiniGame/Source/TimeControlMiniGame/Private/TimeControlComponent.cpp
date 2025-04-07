#include "TimeControlComponent.h"
#include <Kismet/GameplayStatics.h>

UTimeControlComponent::UTimeControlComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UTimeControlComponent::BeginPlay()
{
	FindAllTimePausedObjects();
}


void UTimeControlComponent::PauseTimeForObjects()
{
	
	for(ATimePausedObject* Object : TimePausedObjects)
	{
		Object->PauseObject(PauseTime, SlowDownTime);
	}
	
}

void UTimeControlComponent::FindAllTimePausedObjects()
{
	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimePausedObject::StaticClass(), Actors);
			
		for (AActor* Actor : Actors)
		{
			if (ATimePausedObject* TimeObj = Cast<ATimePausedObject>(Actor))
			{
				TimePausedObjects.Add(TimeObj);
			}
		}
	});
}



