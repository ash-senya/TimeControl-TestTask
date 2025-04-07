#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "TimePausedObject.generated.h"

/*
 * A base class that is subject to time stops and also has basic logic for moving along a spline
 *
 * The class has a timer that moves the mesh along a spline. It has a velocity field that changes, thus creating the effect of "stopping time".
 */
UCLASS()
class TIMECONTROLMINIGAME_API ATimePausedObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimePausedObject();

	/*Spline acting as a trajectory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USplineComponent* SplineComponent;

	/*A mesh that moves along a spline*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MovingMeshComponent;

	/*Default speed value, overridden in blueprint.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultMovementSpeed = 10;

	/*The current speed value that will change.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CurrentMovementSpeed = 10;

	/*Timer refresh rate. Default is 1, this is enough for comfortable gaming.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MovementDuration = 1.0f;

	/*A function that is redefined in Blueprint. The logic is simple but voluminous, so it is moved to BP.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PauseObject(float PauseTime, float SlowdownTime);

	void PauseObject_Implementation(float PauseTime, float SlowdownTime);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	/*A flag that indicates which direction the platform should be moving at the moment.*/
	UPROPERTY()
	bool IsForwardMoving = true;

	/*The calculated distance (position) where the mesh should be at a certain moment*/
	UPROPERTY()
	float CurrentDistanceAlongSpline;

	/*Total length of spline*/
	UPROPERTY()
	float SplineLenght;

	/*Rotate the object in the initial position to keep it throughout the movement, and rotate it only by the yaw.*/
	UPROPERTY()
	FRotator DefaultObjectRotator;

	/*A timer that calls a function to update the object's position*/
	UPROPERTY()
	FTimerHandle MovementTimerHandle;

	/*Function to update the position of an object (mesh) on a spline*/
	void MovementTimerTick();
};
