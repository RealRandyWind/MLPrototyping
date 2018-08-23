#include "stdafx.h"
#include "Resource.h"

using namespace MLPrototyping;

size_t CResource::_NextId = 0;
size_t CResource::_Count = 0;
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
	Slot.Pointer = nullptr;
	Slot.Id = _NextId;
	_NextId = _Id;
}

size_t CResource::Id()
{
	return _Id;
}

const size_t CResource::Id() const
{
	return _Id;
}

CResource &CResource::Reference(size_t ResourceId)
{
	if (ResourceId >= _List.Size()) { exit(failure); }
	auto Resource = _List[ResourceId].Pointer;
	if (!Resource) { exit(failure); }
	return *Resource;
}

CResource *CResource::Pointer(size_t ResourceId)
{
	if (ResourceId >= _List.Size()) { return nullptr; }
	return _List[ResourceId].Pointer;
}

size_t CResource::ResourceCount()
{
	return _Count;
}

size_t CResource::ResourceBufferSize()
{
	return _List.BufferSize();
}