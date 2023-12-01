#pragma once

#include "stdafx.h"

struct asBone
{
	int Index;	// root == -1
	string Name;

	int Parent;
	Matrix Transform;
};

struct asMeshPart
{
	string MaterialName;

	UINT StartVertex;
	UINT VertexCount;
	UINT StartIndex;
	UINT IndexCount;

	//shader->DrawIndex(0, 0, IndexCount, StartIndex);
};

struct asMesh
{
	int BoneIndex;
	vector<Model::VertexModel> Vertices;
	vector<UINT> Indices;

	vector<asMeshPart*> MeshParts;
};