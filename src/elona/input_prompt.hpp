#pragma once
#include <string>
#include <vector>
#include "../snail/input.hpp"
#include "optional.hpp"

namespace elona
{

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
        : _locale_key_root("")
        , _type(type)
    {
    }

    Prompt(I18NKey locale_key_root, Type type = Type::can_cancel)
        : _locale_key_root(locale_key_root)
        , _type(type)
    {
    }

    void append(const I18NKey& locale_key, snail::Key key = snail::Key::none)
    {
        _entries.emplace_back(key, locale_key, _promptmax);
        _promptmax++;
    }
    void append(const I18NKey& locale_key, snail::Key key, int value)
    {
        _entries.emplace_back(key, locale_key, value);
        _promptmax++;
    }
    void append(const I18NKey& locale_key, int value)
    {
        append(locale_key, snail::Key::none, value);
    }

    int query(int x, int y, int width);

protected:
    virtual void _draw_box(){};
    virtual void _draw_window(){};
    virtual void _draw_window2(){};
    virtual void _modify_result(const std::string&){};

    I18NKey _locale_key_root;

private:
    void _draw_keys_and_background(int x, int y, int width);
    void _draw_main_frame(int width);
    void _draw_entries();
    void _replace_null_keys_from_key_select();

    Type _type;
    std::vector<Entry> _entries;
    int _promptmax{};
};

class PromptWithNumber : public Prompt
{
public:
    PromptWithNumber(int number, I18NKey locale_key_root)
        : Prompt(locale_key_root)
    {
        _number = number;
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
