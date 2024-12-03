#include "EngineCore.h"
#include "EngineHelper/EngineTime.h"
#include "Actor.h"

EngineCore::EngineCore(HINSTANCE _inst, int _x, int _y) {
	TimeManager = new EngineTime();
	TimeManager->InitializeTimer();
	MainWindow.SetWindowSize(_x, _y);
	MainWindow.WindowRegister(_inst);
	MainWindow.WindowOpen();
}

void EngineCore::EngineStart() {
	BeginPlay();
	MainWindow.WindowStart(std::bind(&EngineCore::EngineTick, this), std::bind(&EngineCore::EngineEnd, this));
}

void EngineCore::BeginPlay() {

}

void EngineCore::EngineTick() {
	float DeltaTime = static_cast<float>(TimeManager->UpdateDeltaTime());

	for (Actor* Act : Actors) {
		Act->Tick(DeltaTime);
	}

}
void EngineCore::EngineEnd() {
	int a = 0;
}