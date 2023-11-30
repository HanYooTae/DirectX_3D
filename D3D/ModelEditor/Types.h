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
	// Todo.
};

struct asMesh
{
	int BoneIndex;
	vector<Model::VertexModel> Vertices;
	vector<UINT> Indices;
};