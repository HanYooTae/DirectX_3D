#include "stdafx.h"
#include "ModelDemo.h"
#include "Converter.h"

void ModelDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(12, 0, 0);
	Context::Get()->GetCamera()->Position(2, 4, -12);

	shader = new Shader(L"21_OnlyPS.fxo");
	
	Tank();
	Tower();
	Airplane();

	sky = new CubeSky(L"Environment/GrassCube1024.dds");
	sky->Pass(2);

	plane = new MeshPlane(shader, 6, 6);
	plane->GetTransform()->Scale(12, 1, 12);
	plane->DiffuseMap(L"Floor.png");
}

void ModelDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(tank);
	SafeDelete(tower);
	SafeDelete(airplane);

	SafeDelete(sky);
	SafeDelete(plane);
}

void ModelDemo::Update()
{	
	sky->Update();
	plane->Update();

	if (tank != nullptr)
	{
		//tank->Pass(pass);
		tank->Update();
	}

	if (tower != nullptr)
	{
		//tower->Pass(pass);
		tower->Update();
	}

	if (airplane != nullptr)
	{
		//airplane->Pass(pass);
		airplane->Update();
	}
}

void ModelDemo::Render()
{
	sky->Render();

	plane->Pass(0);
	plane->Render();

	if (tank != nullptr)
	{
		tank->Pass(1);
		tank->Render();
	}

	if (tower != nullptr)
	{
		tower->Pass(1);
		tower->Render();
	}

	if (airplane != nullptr)
	{
		airplane->Pass(1);
		airplane->Render();
	}
}

void ModelDemo::Tank()
{
	tank = new ModelRender(shader);
	tank->ReadMesh(L"Tank/Tank");
	tank->ReadMaterial(L"Tank/Tank");
}

void ModelDemo::Tower()
{
	tower = new ModelRender(shader);
	tower->ReadMesh(L"Tower/Tower");
	tower->ReadMaterial(L"Tower/Tower");
	tower->GetTransform()->Position(-5, 0, 0);
	tower->GetTransform()->Scale(0.01f, 0.01f, 0.01f);
}

void ModelDemo::Airplane()
{
	airplane = new ModelRender(shader);
	airplane->ReadMesh(L"B787/Airplane");
	airplane->ReadMaterial(L"B787/Airplane");
	airplane->GetTransform()->Position(-10, 0, 0);
	airplane->GetTransform()->Scale(0.001f, 0.001f, 0.001f);
}
