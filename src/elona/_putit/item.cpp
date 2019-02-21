/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{
    _putit_archive_(this->number_);
    _putit_archive_(this->value);
    _putit_archive_(this->image);
    _putit_archive_(this->id);
    _putit_archive_(this->quality);
    _putit_archive_(this->position);
    _putit_archive_(this->weight);
    _putit_archive_(this->identification_state);
    _putit_archive_(this->count);
    _putit_archive_(this->dice_x);
    _putit_archive_(this->dice_y);
    _putit_archive_(this->damage_bonus);
    _putit_archive_(this->hit_bonus);
    _putit_archive_(this->dv);
    _putit_archive_(this->pv);
    _putit_archive_(this->skill);
    _putit_archive_(this->curse_state);
    _putit_archive_(this->body_part);
    _putit_archive_(this->function);
    _putit_archive_(this->enhancement);
    _putit_archive_(this->own_state);
    _putit_archive_(this->color);
    _putit_archive_(this->subname);
    _putit_archive_(this->material);
    _putit_archive_(this->param1);
    _putit_archive_(this->param2);
    _putit_archive_(this->param3);
    _putit_archive_(this->param4);
    _putit_archive_(this->difficulty_of_identification);
    _putit_archive_(this->turn);
    _putit_archive_(this->_flags);
    _putit_archive_(this->enchantments);
}
/* clang-format on */
