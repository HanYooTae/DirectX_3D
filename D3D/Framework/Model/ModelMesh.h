#pragma once

//--------------------------------------------------------------------------------
// ModelBone
// @ *.mesh�� bones data�� ������� class
// @ Tree���·� ����
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
// *.mesh�� mesh data�� ������� Ŭ����
// VertexBuffer, IndexBuffer ����
// ��� Bone�� Matrix�� boneBuffer(CBuffer)�� ����
// Transform ��ü ����(Root Bone�� ��ġ)
//--------------------------------------------------------------------------------
class ModelMesh
{
public:
	friend class Model;

private:
	ModelMesh();
	~ModelMesh();

	// (1) �� Mesh�� �׸��� ���� VertexBuffer, IndexBuffer ����
	// (2) meshPart->Binding() ȣ��, material�� ���� �Ҵ�
	void Binding(Model* model);

public:
	// ���������� �����
	void Pass(UINT val);

	// ���̴��� ����Ǹ� transform, perFrame, cBuffer�� ����� shader�� ����Ǿ�� ��.
	void SetShader(Shader* shader);

	// ���� mesh�� �׷����� �� boneIndex�� Get
	void Update();

	// Rendering �ڿ����� shader�� ����
	void Render();

	int BoneIndex() { return boneIndex; }
	ModelBone* Bone() { return bone; }

	void Transforms(Matrix* transforms);	// CBuffer�� ��ü Bone �迭 ���ÿ�
	void SetTransform(Transform* transforms);	// RootBone�� ������ġ ���ÿ�

private:
	struct BoneDesc
	{
		Matrix Transforms[MAX_MODEL_TRANSFORMS];	// ��ü Bone�� �迭

		UINT BoneIndex;		// ���� ���� �پ�� �� BoneIndex
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
// @ ���� (DP)Draw Primitive Call(shader->DrawIndexed)
// @ Material ������ ������
// @ �ڱ� ������ �׸�����
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

	// DiffuesMap, MormalMap Texture Shader�� ����
	void Binding(Model* model);

	// Draw Primitive Call�� ����� Shader ���ÿ�
	void SetShader(Shader* shader);

	// ���������� �����
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