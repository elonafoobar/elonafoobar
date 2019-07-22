/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{
#define PUTIT_SERIALIZE_FIELD(field_name) _putit_archive_(this->field_name, #field_name)
    PUTIT_SERIALIZE_FIELD(number_);
    PUTIT_SERIALIZE_FIELD(value);
    PUTIT_SERIALIZE_FIELD(image);
    PUTIT_SERIALIZE_FIELD(id);
    PUTIT_SERIALIZE_FIELD(quality);
    PUTIT_SERIALIZE_FIELD(position);
    PUTIT_SERIALIZE_FIELD(weight);
    PUTIT_SERIALIZE_FIELD(identify_state);
    PUTIT_SERIALIZE_FIELD(count);
    PUTIT_SERIALIZE_FIELD(dice_x);
    PUTIT_SERIALIZE_FIELD(dice_y);
    PUTIT_SERIALIZE_FIELD(damage_bonus);
    PUTIT_SERIALIZE_FIELD(hit_bonus);
    PUTIT_SERIALIZE_FIELD(dv);
    PUTIT_SERIALIZE_FIELD(pv);
    PUTIT_SERIALIZE_FIELD(skill);
    PUTIT_SERIALIZE_FIELD(curse_state);
    PUTIT_SERIALIZE_FIELD(body_part);
    PUTIT_SERIALIZE_FIELD(function);
    PUTIT_SERIALIZE_FIELD(enhancement);
    PUTIT_SERIALIZE_FIELD(own_state);
    PUTIT_SERIALIZE_FIELD(color);
    PUTIT_SERIALIZE_FIELD(subname);
    PUTIT_SERIALIZE_FIELD(material);
    PUTIT_SERIALIZE_FIELD(param1);
    PUTIT_SERIALIZE_FIELD(param2);
    PUTIT_SERIALIZE_FIELD(param3);
    PUTIT_SERIALIZE_FIELD(param4);
    PUTIT_SERIALIZE_FIELD(difficulty_of_identification);
    PUTIT_SERIALIZE_FIELD(turn);
    PUTIT_SERIALIZE_FIELD(_flags);
    PUTIT_SERIALIZE_FIELD(enchantments);
}
#undef PUTIT_SERIALIZE_FIELD
/* clang-format on */
