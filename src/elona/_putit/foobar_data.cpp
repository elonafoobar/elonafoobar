/* clang-format off */
template <typename Archive>
void serialize(Archive& _putit_archive_)
{
    _putit_archive_(this->is_autodig_enabled);
}
/* clang-format on */
