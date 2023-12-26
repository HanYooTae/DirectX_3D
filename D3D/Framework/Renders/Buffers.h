#pragma once

//-----------------------------------------------------------------------------
// VertexBuffer
//-----------------------------------------------------------------------------
class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT count, UINT stride, UINT slot = 0, bool bCpuWrite = false, bool bGpuWrite = false);
	~VertexBuffer();

	UINT Count() { return count; }
	UINT Stride() { return stride; }
	ID3D11Buffer* Buffer() { return  buffer; }

	void Render();

private:
	ID3D11Buffer* buffer;

	void* data;
	UINT count;
	UINT stride;
	UINT slot;

	bool bCpuWrite;
	bool bGpuWrite;
};

//-----------------------------------------------------------------------------
// IndexBuffer
//-----------------------------------------------------------------------------
class IndexBuffer
{
public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	UINT Count() { return count; }
	ID3D11Buffer* Buffer() { return buffer; }

	void Render();

private:
	ID3D11Buffer* buffer;

	void* data;
	UINT count;
};

//-----------------------------------------------------------------------------
// ConstantBuffer
//-----------------------------------------------------------------------------
class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	~ConstantBuffer();

	ID3D11Buffer* Buffer() { return buffer; }

	void Render();

private:
	ID3D11Buffer* buffer;

	void* data;
	UINT dataSize;
};

//-----------------------------------------------------------------------------
// ComputeBuffer(Super)
//-----------------------------------------------------------------------------
class ComputeBuffer
{
public:
	ComputeBuffer() = default;
	virtual ~ComputeBuffer();

protected:
	virtual void CreateInput() {}
	virtual void CreateSRV() {}

	virtual void CreateOutput() {}
	virtual void CreateUAV() {}

	void CreateBuffer();

public:
	ID3D11ShaderResourceView* SRV() { return srv; }
	ID3D11UnorderedAccessView* UAV() { return uav; }

protected:
	ID3D11Resource* input = nullptr;
	ID3D11ShaderResourceView* srv = nullptr;

	ID3D11Resource* output = nullptr;
	ID3D11UnorderedAccessView* uav = nullptr;
};

//-----------------------------------------------------------------------------
// RawBuffer(C++), ByteAddress(HLSL)
//-----------------------------------------------------------------------------
class RawBuffer : public ComputeBuffer
{
public:
	RawBuffer(void* inputData, UINT inputByte, UINT outputByte);
	~RawBuffer();

	virtual void CreateInput() override;
	virtual void CreateSRV() override;

	virtual void CreateOutput()  override;
	virtual void CreateUAV()  override;

public:
	void CopyToInput(void* data);
	void CopyFromOutput(void* data);

private:
	void* inputData;
	UINT inputByte;
	UINT outputByte;
};

//-----------------------------------------------------------------------------
// TextureBuffer
//-----------------------------------------------------------------------------
class TextureBuffer : public ComputeBuffer
{
public:
	TextureBuffer(ID3D11Texture2D* src);
	~TextureBuffer();

private:
	virtual void CreateSRV() override;

	virtual void CreateOutput() override;
	virtual void CreateUAV() override;

public:
	void CopyToInput(ID3D11Texture2D* texture);
	
	UINT Width() { return width; }
	UINT Height() { return height; }
	UINT ArraySize() { return arraySize; }
	ID3D11ShaderResourceView* OutputSRV() { return outputSRV; }
	ID3D11Texture2D* Result() { return (ID3D11Texture2D*)output; }

	ID3D11Texture2D* CopyFromOutput();

private:
	UINT width, height, arraySize;
	DXGI_FORMAT format;

	ID3D11ShaderResourceView* outputSRV;
	ID3D11Texture2D* result = nullptr;
};

//-----------------------------------------------------------------------------
// StructuredBuffer
//-----------------------------------------------------------------------------
class StructuredBuffer : public ComputeBuffer
{
public:
	StructuredBuffer(void* inputData, UINT inputStride, UINT inputCount, UINT outputStride = 0, UINT outputCount = 0);
	~StructuredBuffer();

public:
	void CreateInput() override;
	void CreateSRV() override;

	void CreateOutput() override;
	void CreateUAV() override;

public:
	UINT InputByteWidth() { return inputStride * inputCount; }
	UINT OutputByteWidth() { return outputStride * outputCount; }

	void CopyToInput(void* data);
	void CopyFromOutput(void* data);

private:
	void* inputData;
	UINT inputStride;
	UINT inputCount;

	UINT outputStride;
	UINT outputCount;
};