#include "TimePausedObject.h"

ATimePausedObject::ATimePausedObject()
{
	PrimaryActorTick.bCanEverTick = false;

    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    RootComponent = SplineComponent;

    MovingMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MovingMeshComponent"));
    MovingMeshComponent -> SetupAttachment(RootComponent);

    CurrentDistanceAlongSpline = 0.0f;    
    
}


void ATimePausedObject::PauseObject_Implementation(float PauseTime, float SlowdownTime)
{
}

void ATimePausedObject::BeginPlay()
{
	Super::BeginPlay();
    
    CurrentMovementSpeed = DefaultMovementSpeed;
    SplineLenght = SplineComponent->GetSplineLength();

    MovingMeshComponent->SetWorldLocation(SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World));
    MovingMeshComponent->SetWorldRotation(SplineComponent->GetRotationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World));

    DefaultObjectRotator = this->GetActorRotation();
    GetWorldTimerManager().SetTimer(MovementTimerHandle, this, &ATimePausedObject::MovementTimerTick, MovementDuration, true, 0.5f);
	
}

void ATimePausedObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);

    Super::EndPlay(EndPlayReason);
}

void ATimePausedObject::MovementTimerTick()
{
    
    if (IsForwardMoving == true)
    {
        UE_LOG(LogTemp, Display, TEXT("Forward move"))
            CurrentDistanceAlongSpline += CurrentMovementSpeed * MovementDuration;
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Backward move"))
            CurrentDistanceAlongSpline -= CurrentMovementSpeed * MovementDuration;
    }
    
    if(CurrentDistanceAlongSpline < 0)
    {
        IsForwardMoving = true;
        
    }

    if(CurrentDistanceAlongSpline > SplineLenght)
    {
        IsForwardMoving = false;
        
    }
    
    FVector NewObjectLocation = SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World);
    FRotator NewObjectRotation = SplineComponent->GetRotationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World);
   

    MovingMeshComponent ->SetWorldLocationAndRotation(NewObjectLocation, FRotator(DefaultObjectRotator.Pitch, NewObjectRotation.Yaw, DefaultObjectRotator.Roll));

}


