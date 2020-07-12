#pragma once

#include <unordered_map>

#include "ref.hpp"



namespace elona::eobject
{

template <typename T>
class IdTable
{
public:
    static IdTable& instance()
    {
        static IdTable the_instance;
        return the_instance;
    }



    void add(Ref<T> ref)
    {
        _id2ref.insert_or_assign(ref->obj_id, std::move(ref));
    }



    void remove(const Id& obj_id)
    {
        _id2ref.erase(obj_id);
    }



    OptionalRef<T> get(const Id& obj_id)
    {
        const auto itr = _id2ref.find(obj_id);
        if (itr == _id2ref.end())
        {
            return nullptr;
        }
        else
        {
            return itr->second;
        }
    }



private:
    std::unordered_map<Id, Ref<T>> _id2ref;

    IdTable() = default;
};

} // namespace elona::eobject
