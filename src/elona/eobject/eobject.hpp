#pragma once

#include "id.hpp"
#include "ref.hpp"



namespace elona
{
using ObjId = eobject::Id;



template <typename T>
using ObjRef = eobject::Ref<T>;

template <typename T>
using OptionalObjRef = eobject::OptionalRef<T>;



struct Item;

using ItemRef = ObjRef<Item>;
using OptionalItemRef = OptionalObjRef<Item>;

} // namespace elona
