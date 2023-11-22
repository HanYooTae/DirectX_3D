#pragma once

#define MAX_DEBUG_LINE 150000

class DebugLine
{
public:
	friend class Window;

private:
	static void Create();
	static void Delete();

public:
	static DebugLine* Get();

public:
	void RenderLine(Vector3& start, Vector3& end);
	void RenderLine(Vector3& start, Vector3& end, Color& Color);
	void RenderLine(Vector3& start, Vector3& end, float r, float g, float b);

	void RenderLine(float x, float y, float z, float x2, float y2, float z2);
	void RenderLine(float x, float y, float z, float x2, float y2, float z2, float r, float g, float b);
	void RenderLine(float x, float y, float z, float x2, float y2, float z2, Color& color);

private:
	void Update();	// WVP
	void Render();

private:
	DebugLine();
	~DebugLine();

private:
	struct VertexLine
	{
		Vector3 Position;
		Color Color;
	};

private:
	static DebugLine* instance;

private:
	Shader* shader;

	Matrix world;
	
	ID3D11Buffer* vertexBuffer;
	VertexLine* vertices;

	UINT drawCount = 0;

	// RenderLine(start, end, color)

};