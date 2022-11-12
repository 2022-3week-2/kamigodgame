#pragma once
#include "SpMath.h"
#include <Object3D.h>
#include <memory>
#include <list>

class Field
{
private:
	std::unique_ptr<Object3D> fieldObj;
	std::unique_ptr<Model> fieldModel;

public:
	Field();
	void Load();
	void Init();
	void Update();
	void DrawModel();


public:
	// ƒQƒbƒ^[
	inline Vec3 GetPosition() { return fieldObj->position; }
};

