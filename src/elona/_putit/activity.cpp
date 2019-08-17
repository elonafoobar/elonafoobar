/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{
#define PUTIT_SERIALIZE_FIELD(field_name) _putit_archive_(this->field_name, #field_name)
    PUTIT_SERIALIZE_FIELD(type);
    PUTIT_SERIALIZE_FIELD(turn);
    PUTIT_SERIALIZE_FIELD(item);
}
#undef PUTIT_SERIALIZE_FIELD
/* clang-format on */
