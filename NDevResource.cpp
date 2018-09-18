#include "stdafx.h"	
#include "NDevResource.h"

using namespace NDev;

FSize CResource::_NextId = 0;
FSize CResource::_Count = 0;
TSequence<_FResource> CResource::_List = TSequence<_FResource>();

CResource::CResource()
{
	auto &Slot = _List[_NextId];
	_Id = _NextId;
	_NextId = Slot.Id;
	Slot.Id = _Id;
	Slot.Pointer = this;
	if (_Id >= _List.Size())
	{ 
		_List.Add(Slot);
		_NextId = _List.Size();
	}
	++_Count;
}

CResource::~CResource()
{
	--_Count;
	auto &Slot = _List[_Id];
	Slot.Pointer = NullPtr;
	Slot.Id = _NextId;
	_NextId = _Id;
}

FSize CResource::Id()
{
	return _Id;
}

const FSize CResource::Id() const
{
	return _Id;
}

CResource &CResource::Reference(FSize ResourceId)
{
	if (ResourceId >= _List.Size()) { exit(Failure); }
	auto Resource = _List[ResourceId].Pointer;
	if (!Resource) { exit(Failure); }
	return *Resource;
}

CResource *CResource::Pointer(FSize ResourceId)
{
	if (ResourceId >= _List.Size()) { return NullPtr; }
	return _List[ResourceId].Pointer;
}

FSize CResource::ResourceCount()
{
	return _Count;
}

FSize CResource::ResourceBufferSize()
{
	return _List.BufferSize();
}