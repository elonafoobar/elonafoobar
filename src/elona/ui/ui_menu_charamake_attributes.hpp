#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuCharamakeAttributes : public UIMenu<elona_vector1<int>>
{
public:
    UIMenuCharamakeAttributes(
        const std::string& race,
        const std::string& klass,
        elona_vector1<int> attributes,
        elona_vector1<int>& locked_attributes)
        : _race(race)
        , _klass(klass)
        , _attributes(attributes)
        , _locked_attributes(locked_attributes)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCharamakeAttributes::ResultType> on_key(
        const std::string& key);

private:
    void _draw_window_background();
    void _draw_window_topic();
    void _draw_window_desc(int);
    void _draw_window(int);
    void _draw_attribute_locked(int);
    void _draw_attribute_value(int, int, bool);
    void _draw_attribute(int, int, const std::string&, bool);

    void _reroll_attributes();

    std::string _race;
    std::string _klass;
    elona_vector1<int> _attributes;
    elona_vector1<int>& _locked_attributes;

    bool _minimum = false;
};

} // namespace ui
} // namespace elona
