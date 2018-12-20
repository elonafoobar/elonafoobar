#include "autopick.hpp"
#include "elona.hpp"
#include "util.hpp"
#include "variables.hpp"



namespace elona
{

Autopick& Autopick::instance()
{
    static Autopick the_instance;
    return the_instance;
}



void Autopick::load(const std::string& player_id)
{
    _clear();

    // Priority: save/xxx/autopick > save/autopick > /autopick
    for (const auto directory : {filesystem::dir::save(player_id),
                                 filesystem::dir::save(),
                                 filesystem::dir::exe()})
    {
        for (const auto filename :
             {u8"autopick", u8"autopick.txt", u8"autopick.txt.txt"})
        {
            const auto filepath = directory / filename;
            bool file_exists = _try_load(filepath);
            if (file_exists)
                break;
        }
    }
}



void Autopick::_clear()
{
    matchers.clear();
}



Autopick::Matcher Autopick::_parse_each_line(std::string line)
{
    Operation op{Operation::Type::pick_up};

    if (strutil::starts_with(line, u8"%=") ||
        strutil::starts_with(line, u8"=%"))
    {
        op.type = Operation::Type::save_and_no_drop;
        line = line.substr(2);
    }
    else
    {
        switch (line.front())
        {
        case '~':
            op.type = Operation::Type::do_nothing;
            line = line.substr(1);
            break;
        case '%':
            op.type = Operation::Type::save;
            line = line.substr(1);
            break;
        case '=':
            op.type = Operation::Type::no_drop;
            line = line.substr(1);
            break;
        case '!':
            op.type = Operation::Type::destroy;
            line = line.substr(1);
            break;
        case '+':
            op.type = Operation::Type::open;
            line = line.substr(1);
            break;
        default: break;
        }
    }

    // xxx:sound.wav?
    if (!line.empty() && line.back() == '?')
    {
        op.show_prompt = true;
        line = line.substr(0, line.size() - 1);
    }

    // sound
    const auto colon = line.find(':');
    if (colon != std::string::npos)
    {
        auto sound_id = line.substr(colon + 1);
        if (!strutil::contains(op.sound, "."))
        {
            // Adds "core" if no mod prefix.
            sound_id = "core." + sound_id;
        }
        op.sound = SharedId(sound_id);
        line = line.substr(0, colon);
    }

    // xxx?:sound.wav
    if (!line.empty() && line.back() == '?')
    {
        op.show_prompt = true;
        line = line.substr(0, line.size() - 1);
    }

    return {line, op};
}



bool Autopick::_try_load(const fs::path& filepath)
{
    if (!fs::exists(filepath))
        return false;

    for (const auto& line : fileutil::read_by_line(filepath))
    {
        if (line.empty())
        {
            continue;
        }
        if (strutil::starts_with(line, u8"#"))
        {
            continue;
        }

        matchers.push_back(_parse_each_line(line));
    }

    return true;
}



Autopick::Operation Autopick::get_operation(const Item& ci)
{
    for (const auto& m : matchers)
    {
        if (m.matches(ci))
        {
            return m.op;
        }
    }

    return Operation{};
}



bool Autopick::Matcher::matches(const Item& ci) const
{
    const auto id = ci.id;
    const auto name = cnvitemname(id);
    return ci.identification_state != IdentifyState::unidentified &&
        name.find(text) != std::string::npos;
}

} // namespace elona
