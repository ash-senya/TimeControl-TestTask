#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimePausedObject.h"
#include "TimeControlComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIMECONTROLMINIGAME_API UTimeControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UTimeControlComponent();

protected:
	
	virtual void BeginPlay() override;

	/*The time for which time "will be stopped"*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PauseTime = 10;

	/*Time to stop*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlowDownTime = 10;

	/*An array of objects that are subject to stop*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATimePausedObject*> TimePausedObjects;


	/*A function that stops time and calls all related events*/
	UFUNCTION(BlueprintCallable)
	void PauseTimeForObjects();

private:

	/*A function that finds all objects that are subject to stopping*/
	void FindAllTimePausedObjects();	
};
