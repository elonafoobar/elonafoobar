/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{
    _putit_archive_(this->current_level);
    _putit_archive_(this->original_level);
    _putit_archive_(this->experience);
    _putit_archive_(this->potential);
}
/* clang-format on */
