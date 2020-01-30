#pragma once



namespace json5
{

enum class value_type
{
    null,
    boolean,
    integer,
    number,
    string,
    array,
    object,
};



constexpr const char* to_string(value_type type) noexcept
{
    switch (type)
    {
    case value_type::null: return "null";
    case value_type::boolean: return "boolean";
    case value_type::integer: return "integer";
    case value_type::number: return "number";
    case value_type::string: return "string";
    case value_type::array: return "array";
    case value_type::object: return "object";
    default: return "<invalid>";
    }
}

} // namespace json5
