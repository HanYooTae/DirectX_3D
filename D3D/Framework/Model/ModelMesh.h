#pragma once

//--------------------------------------------------------------------------------
// ModelBone
// @ *.mesh의 bones data를 저장받을 class
// @ Tree형태로 저장
//--------------------------------------------------------------------------------
class ModelBone
{
	friend class Model;

private:
	ModelBone() = default;
	~ModelBone() = default;

public:
	int Index() { return index; }
	int ParentIndex() { return parentIndex; }
	ModelBone* Parent() { return parent; }
	wstring Name() { return name; }
	Matrix& Transform() { return transform; }
	void Transform(Matrix& matrix) { transform = matrix; }

	vector<ModelBone*>& Children() { return children; }

private:
	int index;
	wstring name;

	int parentIndex;
	ModelBone* parent;

	Matrix transform;
	vector<ModelBone*> children;
};

//--------------------------------------------------------------------------------
// ModelMesh
// *.mesh의 mesh data를 저장받을 클래스
// VertexBuffer, IndexBuffer 생성
// 모든 Bone의 Matrix를 boneBuffer(CBuffer)로 복사
// Transform 객체 생성(Root Bone의 위치)
//--------------------------------------------------------------------------------
class ModelMesh
{
public:
	friend class Model;

private:
	ModelMesh();
	~ModelMesh();

	// (1) 이 Mesh를 그리기 위한 VertexBuffer, IndexBuffer 생성
	// (2) meshPart->Binding() 호출, material이 각각 할당
	void Binding(Model* model);

public:
	// 파이프라인 변경용
	void Pass(UINT val);

	// 쉐이더가 변경되면 transform, perFrame, cBuffer도 변경된 shader로 적용되어야 함.
	void SetShader(Shader* shader);

	// 현재 mesh가 그려져야 할 boneIndex를 Get
	void Update();

	// Rendering 자원들을 shader로 전송
	void Render();

	int BoneIndex() { return boneIndex; }
	ModelBone* Bone() { return bone; }

	void Transforms(Matrix* transforms);	// CBuffer의 전체 Bone 배열 세팅용
	void SetTransform(Transform* transforms);	// RootBone의 월드위치 세팅용

private:
	struct BoneDesc
	{
		Matrix Transforms[MAX_MODEL_TRANSFORMS];	// 전체 Bone의 배열

		UINT BoneIndex;		// 현재 내가 붙어야 할 BoneIndex
		float Padding[3];
	} boneDesc;



private:
	Shader* shader;

	Transform* transform = nullptr;		// Root Bone
	PerFrame* perFrame = nullptr;		// VP

	int boneIndex;
	ModelBone* bone;

	VertexBuffer* vertexBuffer;
	UINT vertexCount;
	Model::VertexModel* vertices;

	IndexBuffer* indexBuffer;
	UINT indexCount;
	UINT* indices;

	ConstantBuffer* boneBuffer;
	ID3DX11EffectConstantBuffer* sBoneBuffer;

	vector<class ModelMeshPart*> meshParts;
};

//--------------------------------------------------------------------------------
// ModelPart
// @ 설계 (DP)Draw Primitive Call(shader->DrawIndexed)
// @ Material 단위로 구별됨
// @ 자기 부위만 그릴거임
//--------------------------------------------------------------------------------
class ModelMeshPart
{
public:
	friend class Model;
	friend class ModelMesh;

private:
	ModelMeshPart();
	~ModelMeshPart();

	void Update();
	void Render();

	// DiffuesMap, MormalMap Texture Shader와 연결
	void Binding(Model* model);

	// Draw Primitive Call을 담당할 Shader 세팅용
	void SetShader(Shader* shader);

	// 파이프라인 변경용
	void Pass(UINT val) { pass = val; }

private:
	Shader* shader;
	UINT pass = 0;

	wstring materialName;

	UINT startVertex;
	UINT vertexCount;

	UINT startIndex;
	UINT indexCount;
};