#pragma once
#include "Stone.h"
#include "SpMath.h"
#include <Object3D.h>
#include <memory>
#include <list>

class Field
{
private:
	std::unique_ptr<Object3D> fieldObj;
	std::unique_ptr<Model> fieldModel;
	std::list<std::unique_ptr<Stone>> stones;
	std::unique_ptr<Model> stoneModel;

private:
	void StoneInit();
	void StoneGenerate();
	void StoneUpdate();
	void StoneDraw();

public:
	Field();
	void Load();
	void Init();
	void Update();
	void DrawModel();


public:
	// ƒQƒbƒ^[
	inline Vec3 GetPosition() { return fieldObj->position; }
	inline Model* GetStoneModel() { return stoneModel.get(); }
	inline std::list<std::unique_ptr<Stone>>* GetStones() { return &stones; }
};

