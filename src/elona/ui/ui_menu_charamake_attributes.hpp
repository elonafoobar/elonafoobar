#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuCharamakeAttributes : public UIMenu<std::vector<int>>
{
public:
    UIMenuCharamakeAttributes(
        data::InstanceId race_id,
        data::InstanceId class_id,
        elona_vector1<int> attributes,
        elona_vector1<int>& locked_attributes)
        : _race_id(race_id)
        , _class_id(class_id)
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

    data::InstanceId _race_id;
    data::InstanceId _class_id;
    elona_vector1<int> _attributes;
    elona_vector1<int>& _locked_attributes;

    bool _minimum = false;
};

} // namespace ui
} // namespace elona
