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
//--------------------------------------------------------------------------------
class ModelMesh
{

};

//--------------------------------------------------------------------------------
// ModelPart
//--------------------------------------------------------------------------------
class ModelMeshPart
{

};