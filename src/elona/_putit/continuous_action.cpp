/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{
    _putit_archive_(this->type);
    _putit_archive_(this->turn);
    _putit_archive_(this->item);
}
/* clang-format on */
