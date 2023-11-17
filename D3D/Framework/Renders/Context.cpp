#include "Framework.h"
#include "Context.h"
#include "Viewer/Viewport.h"
#include "Viewer/Perspective.h"

Context* Context::instance = NULL;

Context * Context::Get()
{
	//assert(instance != NULL);

	return instance;
}

void Context::Create()
{
	assert(instance == NULL);

	instance = new Context();
}

void Context::Delete()
{
	SafeDelete(instance);
}

Context::Context()
{
	D3DDesc desc = D3D::GetDesc();

	perspective = new Perspective(desc.Width, desc.Height);
	viewport = new Viewport(desc.Width, desc.Height);


	//position = D3DXVECTOR3(0, 0, -10);
	//D3DXVECTOR3 forward(0, 0, 1);
	//D3DXVECTOR3 right(1, 0, 0);
	//D3DXVECTOR3 up(0, 1, 0);
	//
	//// 상대적인 위치
	//D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);
	camera = new Freedom();
}

Context::~Context()
{
	SafeDelete(camera);
	SafeDelete(viewport);
	SafeDelete(perspective);
}

void Context::ResizeScreen()
{
	perspective->Set(D3D::Width(), D3D::Height());
	viewport->Set(D3D::Width(), D3D::Height());
}

void Context::Update()
{
	/*ImGui::SliderFloat("Eye X", &position.x, 0, 128);
	ImGui::SliderFloat("Eye Y", &position.y, -20, 20);
	ImGui::SliderFloat("Eye Z", &position.z, -118, 118);

	D3DXVECTOR3 forward(0, 0, 1);
	D3DXVECTOR3 right(1, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);

	D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);*/
	camera->Update();
}

void Context::Render()
{
	viewport->RSSetViewport();

	Vector3 viewPosition;
	camera->Position(&viewPosition);

	Vector3 viewRotation;
	camera->RotationDegrees(&viewRotation);

	string str;

	str = "FPS : " + to_string(ImGui::GetIO().Framerate);

	Gui::Get()->RenderText(Vector2(5, 5), Color(1, 1, 1, 1), str);

	str = "Camera Position : ";
	str +=
		to_string(viewPosition.x) + ", " +
		to_string(viewPosition.y) + ", " +
		to_string(viewPosition.z);

	Gui::Get()->RenderText(Vector2(5, 20), Color(1, 1, 1, 1), str);

	str = "Camera Rotation : ";
	str +=
		to_string(viewRotation.x) + ", " +
		to_string(viewRotation.y) + ", " +
		to_string(viewRotation.z);

	Gui::Get()->RenderText(Vector2(5, 35), Color(1, 1, 1, 1), str);
}

D3DXMATRIX Context::View()
{
	Matrix view;
	camera->GetMatrix(&view);
	return view;
}

D3DXMATRIX Context::Projection()
{
	D3DXMATRIX projection;
	perspective->GetMatrix(&projection);

	return projection;
}
