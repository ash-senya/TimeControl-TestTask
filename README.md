# Time Control System - Unreal Engine 5
## Project Overview
This project implements a time manipulation system with two core C++ classes that work together to create dynamic time-stopping mechanics:

## Core Classes
`1. ATimePausedObject` *(Base Actor Class)*

Purpose: Objects that can be affected by time manipulation and move along splines.

Key Components:

* SplineComponent: Defines movement path

* MovingMeshComponent: Visual representation that moves along spline

Movement Properties:

* DefaultMovementSpeed: Base speed (editable in BP)

* CurrentMovementSpeed: Active speed (changes during time effects)

* MovementDuration: Update frequency (default 1sec)

Time Control:

* PauseObject(): BlueprintNativeEvent for time manipulation

* PauseTime: Duration of full pause

* SlowdownTime: Time to reach full stop

Internal Logic:

* Automatic spline following with direction switching

* Timer-based position updates

* Spline length calculations

`2. UTimeControlComponent` *(Actor Component)*

Purpose: Manages time manipulation for all TimePausedObjects.

Key Properties:

* PauseTime: Duration of time stop

* SlowDownTime: Time to reach full stop

* TimePausedObjects: Array of affected objects

Functions:

* PauseTimeForObjects(): Initiates time stop sequence

* FindAllTimePausedObjects(): Discovers eligible objects

## Implementation Details

### TimePausedObject Behavior
1. Moves continuously along spline path

2. Responds to time manipulation calls:

    * Gradually slows down over SlowDownTime

    * Stays paused for PauseTime

    * Gradually resumes normal speed

TimeControl Workflow
1. Component finds all TimePausedObjects

2. When triggered, applies time effects to all objects

3. Each object handles its own speed interpolation

## Blueprint Integration
For TimePausedObject:

* Override PauseObject event for custom time effects

* Adjust default properties in instances

* Create varied movement patterns through splines

For TimeControlComponent:

* Add to any actor to enable time control

* Configure pause parameters

* Trigger via PauseTimeForObjects()