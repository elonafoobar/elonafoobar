#pragma once
#include <string>
#include <vector>
#include "optional.hpp"

namespace elona
{

namespace snail
{
enum class Key;
}

typedef std::string I18NKey;

class Prompt
{
public:
    enum class Type
    {
        can_cancel,
        cannot_cancel
    };

private:
    struct Entry
    {
        Entry(snail::Key key, I18NKey locale_key, int value)
            : key(key)
            , locale_key(locale_key)
            , value(value)
        {
        }

        snail::Key key;
        I18NKey locale_key;
        int value;
    };

public:
    Prompt(Type type = Type::can_cancel)
        : _type(type)
    {
    }

    void append(snail::Key key, const I18NKey& locale_key)
    {
        _entries.emplace_back(key, locale_key, _promptmax);
        _promptmax++;
    }
    void append(snail::Key key, const I18NKey& locale_key, int value)
    {
        _entries.emplace_back(key, locale_key, value);
        _promptmax = std::max(_promptmax, value) + 1;
    }

    int query(int x, int y);

protected:
    virtual void _draw_box(){};
    virtual void _draw_window(){};
    virtual void _draw_window2(){};
    virtual void _modify_result(const std::string&){};

private:
    void _draw_keys_and_background();
    void _draw_main_frame();
    void _draw_entries();

    Type _type;
    std::vector<Entry> _entries;
    int _promptmax{};
};

class PromptWithNumber : public Prompt
{
public:
    PromptWithNumber(int number)
        : _number(number)
    {
    }

protected:
    void _draw_box() override;
    void _draw_window() override;
    void _draw_window2() override;
    void _modify_result(const std::string& action) override;

private:
    int _number;
    int _max;
};

} // namespace elona
