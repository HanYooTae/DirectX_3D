#pragma once

class Converter
{
public:
	Converter();
	~Converter();

	//fbx ���� �о����
	void ReadFile(wstring file);

	//scene�� meshes, bones ������ *.mesh
public:
	void ExportMesh(wstring savePath);

private:
	void ReadBoneData(aiNode* node, int index, int parent);
	void ReadMeshData(aiNode* node, int index);
	void WriteMeshData(wstring savePath);

	//scene�� maetrial ������ *.material(xml)
public:
	void ExportMaterial(wstring savePath, bool bOverwrite = true);

private:
	void ReadMaterialData();
	bool FoundMaterialData(aiMaterial* material);
	void WriteMaterialData(wstring savePath);
	string WriteTexture(string saveFolder, string File);

private:
	wstring file;

	Assimp::Importer* importer;
	const aiScene* scene;

	vector<struct asBone*> bones;
	vector<struct asMesh*> meshes;

	vector<struct asMaterial*> materials;
};