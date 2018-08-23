#pragma once

#include <string>
#include "filesystem.hpp"
#include "item.hpp"
#include "lib/noncopyable.hpp"


namespace elona
{


class autopick : public lib::noncopyable
{
public:
    struct operation
    {
        enum class Type
        {
            do_nothing = 0,
            pick_up = 1,
            save = 2,
            no_drop = 4,
            save_and_no_drop = save | no_drop,
            destroy = 8,
            open = 16,
        };

        explicit operation(Type type = Type::do_nothing)
            : type(type)
        {
        }

        Type type = Type::do_nothing;
        bool show_prompt = false;
        std::string sound;
    };

    static autopick& instance();

    void load(const std::string& player_id);

    operation get_operation(const item&);


private:
    struct matcher
    {
        matcher(const std::string& text, const operation& op)
            : text(text)
            , op(op)
        {
        }

        std::string text;
        operation op;

        bool matches(const item&) const;
    };


    std::vector<matcher> matchers;
    autopick() = default;


    void clear();
    bool try_load(const fs::path&);
};



} // namespace elona
