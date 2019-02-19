/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{
    _putit_archive_(this->x);
    _putit_archive_(this->y);
}
/* clang-format on */
