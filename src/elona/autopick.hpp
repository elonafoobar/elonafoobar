#pragma once

#include <string>

#include "../util/noncopyable.hpp"
#include "data/id.hpp"
#include "filesystem.hpp"
#include "item.hpp"



namespace elona
{


class Autopick : public lib::noncopyable
{
public:
    struct Operation
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

        explicit Operation(Type type = Type::do_nothing)
            : type(type)
        {
        }

        Type type = Type::do_nothing;
        bool show_prompt = false;
        optional<data::InstanceId> sound;
    };

    static Autopick& instance();

    void load(const std::string& player_id);

    Operation get_operation(const Item&);


private:
    struct Matcher
    {
        Matcher(const std::string& text, const Operation& op)
            : text(text)
            , op(op)
        {
        }

        std::string text;
        Operation op;

        bool matches(const Item&) const;
    };


    std::vector<Matcher> matchers;
    Autopick() = default;


    void _clear();
    bool _try_load(const fs::path&);
    Matcher _parse_each_line(std::string line);
};



} // namespace elona
