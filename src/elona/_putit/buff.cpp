/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{
    _putit_archive_(this->id);
    _putit_archive_(this->power);
    _putit_archive_(this->turns);
}
/* clang-format on */
