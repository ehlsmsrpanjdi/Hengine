#include "pch.h"
#include "EngineCore.h"
#include "EngineHelper/EngineTime.h"
#include "Actor.h"
#include "EngineHelper/EngineImage.h"
#include "EngineHelper/EngineResource.h"
#include "EngineHelper/EngineKey.h"
#include "EngineCollision.h"
EngineCore* EngineCore::MainCore = nullptr;

EngineCore::EngineCore(HINSTANCE _inst, int _x, int _y) {
	EngineKey::InitKey();
	TimeManager = new EngineTime();
	MainWindow.SetWindowSize(_x, _y);
	MainWindow.WindowRegister(_inst);
	MainWindow.WindowOpen();
}

void EngineCore::EngineStart() {
	MainCore = this;
	ImageInit::ImageIniteralize(MainCore->GetWindow().GetHDC());
	BeginPlay();
	MainWindow.WindowStart(std::bind(&EngineCore::EngineTick, this), std::bind(&EngineCore::EngineEnd, this));
}

void EngineCore::BeginPlay() {

}

void EngineCore::EngineTick() {
	float DeltaTime = static_cast<float>(TimeManager->UpdateDeltaTime());
	EngineKey::KeyCheck();

	for (Actor* Act : Actors) {
		Act->Tick(DeltaTime);
	}
	if (CollisionRendering == true) {
		for (std::pair<const int, std::unordered_set<EngineCollision*>>& pa : EngineCollision::Collisions) {
			for (EngineCollision* Collision : pa.second) {
				Collision->CollisionDraw(GetWindow().GetHDC());
			}
		}
	}
}
void EngineCore::EngineEnd() {
	for (Actor* Act : Actors) {
		delete Act;
	}
	EngineResource::GetInst()->ReleaseResources();
	delete EngineResource::GetInst();
	ImageInit::ImageExit();
	delete TimeManager;
}