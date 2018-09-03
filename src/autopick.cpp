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
    clear();

    for (const auto directory : {filesystem::dir::save(player_id),
                                 filesystem::dir::save(),
                                 filesystem::dir::exe()})
    {
        for (const auto filename :
             {u8"autopick", u8"autopick.txt", u8"autopick.txt.txt"})
        {
            const auto filepath = directory / filename;
            bool file_exists = try_load(filepath);
            if (file_exists)
                break;
        }
    }
}



void Autopick::clear()
{
    matchers.clear();
}



bool Autopick::try_load(const fs::path& filepath)
{
    if (!fs::exists(filepath))
        return false;

    for (const auto& line : fileutil::read_by_line{filepath})
    {
        if (line.empty())
            continue;
        if (strutil::starts_with(line, u8"#"))
            continue;

        std::string line_ = line;
        operation op{operation::Type::pick_up};

        if (strutil::starts_with(line_, u8"%=")
            || strutil::starts_with(line_, u8"=%"))
        {
            op.type = operation::Type::save_and_no_drop;
            line_ = line_.substr(2);
        }
        else
        {
            switch (line_.front())
            {
            case '~':
                op.type = operation::Type::do_nothing;
                line_ = line_.substr(1);
                break;
            case '%':
                op.type = operation::Type::save;
                line_ = line_.substr(1);
                break;
            case '=':
                op.type = operation::Type::no_drop;
                line_ = line_.substr(1);
                break;
            case '!':
                op.type = operation::Type::destroy;
                line_ = line_.substr(1);
                break;
            case '+':
                op.type = operation::Type::open;
                line_ = line_.substr(1);
                break;
            default: break;
            }
        }

        // xxx:sound.wav?
        if (line_.back() == '?')
        {
            op.show_prompt = true;
            line_ = line_.substr(0, line_.size() - 1);
        }

        // sound
        const auto colon = line_.find(':');
        if (colon != std::string::npos)
        {
            op.sound = line_.substr(colon + 1);
            line_ = line_.substr(0, colon);
        }

        // xxx?:sound.wav
        if (line_.back() == '?')
        {
            op.show_prompt = true;
            line_ = line_.substr(0, line_.size() - 1);
        }

        matchers.emplace_back(std::string{line_}, op);
    }

    return true;
}



Autopick::operation Autopick::get_operation(const item& ci)
{
    for (const auto& m : matchers)
    {
        if (m.matches(ci))
        {
            return m.op;
        }
    }

    return operation{};
}



bool Autopick::matcher::matches(const item& ci) const
{
    const auto id = ci.id;
    const auto name = cnvitemname(id);
    return ci.identification_state != IdentifyState::unidentified
        && name.find(text) != std::string::npos;
}

} // namespace elona
