#pragma once
#include "Minigin.h"
#include "Scene.h"

class QBertGame : public dae::Minigin
{
public:
	QBertGame();
	void LoadLevel1(dae::Scene& scene) const;
	void LoadLevel2(dae::Scene& scene) const;
	virtual void LoadGame() const override;
private:
	
};
