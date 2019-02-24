#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>



namespace tinyargparser
{

class ArgParser;



struct Result
{
    bool has(const std::string& long_name) const
    {
        return _options.find(long_name) != std::end(_options);
    }

    std::string get_or(
        const std::string& long_name,
        const std::string& default_value) const
    {
        const auto itr = _options.find(long_name);
        if (itr == std::end(_options))
        {
            return default_value;
        }
        else
        {
            return itr->second;
        }
    }

private:
    friend ArgParser;

    std::unordered_map<std::string, std::string> _options;

    Result(std::unordered_map<std::string, std::string> options)
        : _options(options)
    {
    }
};



class ArgParser
{
private:
    struct Option
    {
        char short_name;
        std::string long_name;
        std::string parameter_name;
        std::string description;



        Option(
            char short_name,
            const std::string& long_name,
            const std::string& description)
            : short_name(short_name)
            , long_name(long_name)
            , description(description)
        {
        }



        Option(
            char short_name,
            const std::string& long_name,
            const std::string& parameter_name,
            const std::string& description)
            : short_name(short_name)
            , long_name(long_name)
            , parameter_name(parameter_name)
            , description(description)
        {
        }



        bool has_parameter() const
        {
            return !parameter_name.empty();
        }



        std::pair<std::string, std::string> help() const
        {
            if (has_parameter())
            {
                return std::make_pair(
                    std::string("-") + short_name + ", --" + long_name + "=" +
                        parameter_name,
                    description);
            }
            else
            {
                return std::make_pair(
                    std::string("-") + short_name + ", --" + long_name,
                    description);
            }
        }



        std::pair<bool, std::string> match(const std::string& arg) const
        {
            if (arg.size() == 2)
            {
                const auto first = arg[0];
                const auto second = arg[1];
                if (first == '-' && second == short_name)
                {
                    return {true, ""};
                }
            }
            else if (arg.size() >= 3)
            {
                const auto first = arg[0];
                const auto second = arg[1];
                if (first == '-' && second == short_name)
                {
                    return {
                        true,
                        arg.substr(3),
                    };
                }
                else if (first == '-' && second == '-')
                {
                    const auto rest = arg.substr(2);
                    if (rest.find(long_name) == 0)
                    {
                        if (rest.size() - long_name.size() > 0)
                        {
                            return {true, rest.substr(long_name.size() + 1)};
                        }
                        else
                        {
                            return {true, ""};
                        }
                    }
                }
            }
            return {false, ""};
        }
    };



public:
    ArgParser(const std::string& name)
        : _name(name)
    {
        add('h', "help", "Show help.");
    }



    std::string help() const
    {
        return _name + " [OPTIONS]" + "\n" + "\n" + "OPTIONS:\n" +
            _get_option_help();
    }



    ArgParser& add(
        char short_name,
        const std::string& long_name,
        const std::string& description)
    {
        _options.emplace_back(short_name, long_name, description);
        return *this;
    }



    ArgParser& add(
        char short_name,
        const std::string& long_name,
        const std::string& parameter_name,
        const std::string& description)
    {
        _options.emplace_back(
            short_name, long_name, parameter_name, description);
        return *this;
    }



    Result parse(int argc, const char* const* argv) const
    {
        std::vector<std::string> argv_;
        for (int i = 0; i < argc; ++i)
        {
            argv_.push_back(argv[i]);
        }
        return parse(argv_);
    }



    Result parse(const std::vector<std::string>& argv) const
    {
        std::unordered_map<std::string, std::string> opts;

        auto is_first = true;
        for (const auto& arg : argv)
        {
            if (is_first)
            {
                is_first = false;
                continue;
            }

            bool match;
            std::string value;
            for (const auto& option : _options)
            {
                std::tie(match, value) = option.match(arg);
                if (match)
                {
                    opts[option.long_name] = value;
                    break;
                }
            }
        }

        return Result(opts);
    }



private:
    std::string _name;
    std::vector<Option> _options;



    std::string _get_option_help() const
    {
        std::string ret;

        std::vector<std::pair<std::string, std::string>> helps;
        for (const auto& option : _options)
        {
            helps.push_back(option.help());
        }
        std::sort(
            std::begin(helps),
            std::end(helps),
            [](const auto& lhs, const auto& rhs) {
                return lhs.first < rhs.first;
            });
        size_t longest = 0;
        for (const auto& help : helps)
        {
            if (longest < help.first.size())
            {
                longest = help.first.size();
            }
        }
        for (const auto& help : helps)
        {
            std::string padding(longest - help.first.size(), ' ');
            ret += "    " + help.first + padding + "    " + help.second + "\n";
        }

        return ret;
    }
};

} // namespace tinyargparser
