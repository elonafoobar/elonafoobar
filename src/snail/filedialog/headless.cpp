namespace elona
{
namespace snail
{

FileDialogResult OpenFileDialog::show()
{
    return {FileDialogResultType::cancel, ""};
}



FileDialogResultMultiple OpenMultipleFileDialog::show()
{
    return {FileDialogResultType::cancel, {}};
}



FileDialogResult SaveFileDialog::show()
{
    return {FileDialogResultType::cancel, ""};
}



FileDialogResult OpenFolderDialog::show()
{
    return {FileDialogResultType::cancel, ""};
}

} // namespace snail
} // namespace elona
