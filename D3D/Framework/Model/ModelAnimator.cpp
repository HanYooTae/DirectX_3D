#include "Framework.h"
#include "ModelAnimator.h"

ModelAnimator::ModelAnimator(Shader* shader)
	:shader(shader)
{
	model = new Model();
	transform = new Transform(shader);

	frameBuffer = new ConstantBuffer(&keyFrameDesc, sizeof(KeyFrameDesc));
}

ModelAnimator::~ModelAnimator()
{
	SafeDelete(model);
	SafeDelete(transform);

	SafeDeleteArray(clipTransform);
	SafeRelease(texture);
	SafeRelease(transformsSRV);

	SafeDelete(frameBuffer);
}

void ModelAnimator::Update()
{
	// Test
	ModelClip* clip = model->ClipByIndex(keyFrameDesc.Clip);
	ImGui::InputInt("Clip Index", &keyFrameDesc.Clip);

	if (texture == nullptr)
	{
		SetShader(shader, true);
		CreateTexture();
	}

	for (ModelMesh* mesh : model->meshes)
		mesh->Update();
}

void ModelAnimator::Render()
{
	frameBuffer->Render();
	sFrameBuffer->SetConstantBuffer(frameBuffer->Buffer());

	sTransformsSRV->SetResource(transformsSRV);

	for (ModelMesh* mesh : model->meshes)
	{
		mesh->SetTransform(transform);
		mesh->Render();
	}
}

void ModelAnimator::ReadMesh(wstring file)
{
	model->ReadMesh(file);
}

void ModelAnimator::ReadMaterial(wstring file)
{
	model->ReadMaterial(file);
}

void ModelAnimator::ReadClip(wstring file)
{
	model->ReadClip(file);
}

void ModelAnimator::SetShader(Shader* shader, bool bDontCreateNewTransform)
{
	this->shader = shader;

	if (bDontCreateNewTransform == false)
	{
		SafeDelete(transform);
		transform = new Transform(shader);
	}

	sTransformsSRV = shader->AsSRV("TransformsMap");
	sFrameBuffer = shader->AsConstantBuffer("CB_KeyFrames");

	for (ModelMesh* mesh : model->Meshes())
		mesh->SetShader(shader);
}

void ModelAnimator::Pass(UINT pass)
{
	for (ModelMesh* mesh : model->Meshes())
		mesh->Pass(pass);
}

void ModelAnimator::CreateTexture()
{
	clipTransform = new ClipTransform[model->ClipCount()];
	for (UINT i = 0; i < model->ClipCount(); i++)
		CreateClipTransform(i);

	// Create Texture
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = MAX_MODEL_TRANSFORMS * 4;
		desc.Height = MAX_MODEL_KEYFRAMES;
		desc.ArraySize = model->ClipCount();
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	// 16byte
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;

		UINT pageSize = MAX_MODEL_TRANSFORMS * MAX_MODEL_KEYFRAMES * sizeof(Matrix);
		void* p = VirtualAlloc(nullptr, pageSize * model->ClipCount(), MEM_RESERVE, PAGE_READWRITE);	// malloc

		for (UINT c = 0; c < model->ClipCount(); c++)
		{
			UINT clipStart = pageSize * c;

			for (UINT k = 0; k < MAX_MODEL_KEYFRAMES; k++)
			{
				void* temp = (BYTE*)p + MAX_MODEL_TRANSFORMS * k * sizeof(Matrix) + clipStart;

				VirtualAlloc(temp, MAX_MODEL_TRANSFORMS * sizeof(Matrix), MEM_COMMIT, PAGE_READWRITE);

				memcpy(temp, clipTransform[c].Transform[k], MAX_MODEL_TRANSFORMS * sizeof(Matrix));
			}
		}

		D3D11_SUBRESOURCE_DATA* subResource = new D3D11_SUBRESOURCE_DATA[model->ClipCount()];
		for (UINT c = 0; c < model->ClipCount(); c++)
		{
			void* temp = (BYTE*)p + c * pageSize;

			subResource[c].pSysMem = temp;
			subResource[c].SysMemPitch = MAX_MODEL_TRANSFORMS * sizeof(Matrix);
			subResource[c].SysMemSlicePitch = pageSize;
		}

		Check(D3D::GetDevice()->CreateTexture2D(&desc, subResource, &texture));

		SafeDeleteArray(subResource);
		VirtualFree(p, 0, MEM_RELEASE);
	}

	// Create SRV
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2DArray.MipLevels = 1;
		desc.Texture2DArray.ArraySize = model->ClipCount();

		Check(D3D::GetDevice()->CreateShaderResourceView(texture, &desc, &transformsSRV));
	}
}

void ModelAnimator::CreateClipTransform(UINT index)
{
	Matrix* bones = new Matrix[MAX_MODEL_TRANSFORMS];

	ModelClip* clip = model->ClipByIndex(index);

	for (UINT f = 0; f < clip->FrameCount(); f++)
	{
		for (UINT b = 0; b < model->BoneCount(); b++)
		{
			// MeshBone을 얻어와서 역행렬을 건다
			ModelBone* bone = model->BoneByIndex(b);

			Matrix inv = bone->Transform();
			D3DXMatrixInverse(&inv, nullptr, &inv);

			// ParentBone을 가져온다
			Matrix parent;
			int parentIndex = bone->ParentIndex();
			if (parentIndex < 0)
				D3DXMatrixIdentity(&parent);

			else
				parent = bones[parentIndex];

			// ModelClip에 저장된 SRT들을 얻어온다
			Matrix animation;

			ModelKeyFrame* frame = clip->Keyframe(bone->Name());

			if (frame != nullptr)
			{
				ModelKeyFrameData& data = frame->Transforms[f];

				Matrix S, R, T;
				D3DXMatrixScaling(&S, data.Scale.x, data.Scale.y, data.Scale.z);
				D3DXMatrixRotationQuaternion(&R, &data.Rotation);
				D3DXMatrixTranslation(&T, data.Translation.x, data.Translation.y, data.Translation.z);

				animation = S * R * T;
			}
			else
			{
				D3DXMatrixIdentity(&animation);
			}

			bones[b] = animation * parent;
			clipTransform[index].Transform[f][b] = inv * bones[b];
			//-> (inv * animation) * parent;
		}
	}

}