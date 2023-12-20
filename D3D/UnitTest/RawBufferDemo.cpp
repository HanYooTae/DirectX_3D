#include "stdafx.h"
#include "RawBufferDemo.h"

void RawBufferDemo::Initialize()
{
	Shader* shader = new Shader(L"16_ByteAddress.fxo");

	UINT count = 10 * 8 * 3;

	struct Output
	{
		UINT GroupID[3];
		UINT GroupThreadID[3];
		UINT DispatchThreadID[3];
		UINT GroupIndex;
	};

	RawBuffer* rawBuffer = new RawBuffer(nullptr, 0, sizeof(Output) * count);
	
	shader->AsUAV("Output")->SetUnorderedAccessView(rawBuffer->UAV());
	shader->Dispatch(0, 0, 1, 1, 1);

	rawBuffer->CopyFromOutput();
}

void RawBufferDemo::Destroy()
{
}