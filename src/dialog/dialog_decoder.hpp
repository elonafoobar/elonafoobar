#pragma once
#include <string>
#include "../optional.hpp"
#include "../thirdparty/sol2/sol.hpp"

namespace elona
{

namespace lua
{
class LuaEnv;
class ExportManager;
} // namespace lua

class DialogData;

class DialogDecoder
{
public:
    optional<DialogData> decode(const std::string& id);
    optional<DialogData> decode(const std::string& id, lua::LuaEnv& lua);
};

class DialogDecoderLogic
{
public:
    DialogDecoderLogic(lua::ExportManager& export_manager)
        : export_manager(export_manager)
    {
    }

public:
    DialogData decode(sol::table data);

private:
    lua::ExportManager& export_manager;
};

} // namespace elona
