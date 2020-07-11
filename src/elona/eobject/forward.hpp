#pragma once



namespace elona::eobject
{

struct Id;

template <typename>
struct Ref;

template <typename>
struct OptionalRef;

} // namespace elona::eobject



namespace elona
{

namespace eobject
{

struct Id;

template <typename>
struct Ref;

template <typename>
struct OptionalRef;

} // namespace eobject



using ObjId = eobject::Id;



template <typename T>
using ObjRef = eobject::Ref<T>;

template <typename T>
using OptionalObjRef = eobject::OptionalRef<T>;



struct Item;

using ItemRef = ObjRef<Item>;
using OptionalItemRef = OptionalObjRef<Item>;

} // namespace elona
