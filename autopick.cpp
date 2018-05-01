#include "autopick.hpp"
#include "elona.hpp"
#include "util.hpp"
#include "variables.hpp"


namespace elona
{


autopick& autopick::instance()
{
    static autopick the_instance;
    return the_instance;
}



void autopick::load(const std::string& player_id)
{
    clear();

    for (const auto directory : {"save/"s + player_id, "save"s, ""s})
    {
        for (const auto filename :
             {u8"autopick", u8"autopick.txt", u8"autopick.txt.txt"})
        {
            const auto filepath = filesystem::path(directory) / filename;
            bool file_exists = try_load(filepath);
            if (file_exists)
                break;
        }
    }
}



void autopick::clear()
{
    matchers.clear();
}



bool autopick::try_load(const fs::path& filepath)
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
        operation op{operation::type_t::pick_up};

        if (strutil::starts_with(line_, u8"*=")
            || strutil::starts_with(line_, u8"=*"))
        {
            op.type = operation::type_t::save_and_no_drop;
            line_ = line_.substr(2);
        }
        else
        {
            switch (line_.front())
            {
            case '~':
                op.type = operation::type_t::do_nothing;
                line_ = line_.substr(1);
                break;
            case '*':
                op.type = operation::type_t::save;
                line_ = line_.substr(1);
                break;
            case '=':
                op.type = operation::type_t::no_drop;
                line_ = line_.substr(1);
                break;
            case '!':
                op.type = operation::type_t::destroy;
                line_ = line_.substr(1);
                break;
            case '+':
                op.type = operation::type_t::open;
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



autopick::operation autopick::get_operation(const item& ci)
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



bool autopick::matcher::matches(const item& ci) const
{
    const auto id = ci.id;
    const auto name = cnvitemname(id);
    return ci.identification_state != identification_state_t::unidentified
        && name.find(text) != std::string::npos;
}

} // namespace elona
