/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{
#define PUTIT_SERIALIZE_FIELD(field_name) _putit_archive_(this->field_name, #field_name)
    PUTIT_SERIALIZE_FIELD(current_level);
    PUTIT_SERIALIZE_FIELD(original_level);
    PUTIT_SERIALIZE_FIELD(experience);
    PUTIT_SERIALIZE_FIELD(potential);
}
#undef PUTIT_SERIALIZE_FIELD
/* clang-format on */
