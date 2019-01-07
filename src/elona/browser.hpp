#pragma once



namespace elona
{

/**
 * CAUTION: This function's validation is NOT perfect. Passing untrusted string
 * like user input may cause serious vulnerability. Make sure that `url` is a
 * hard-coded literal.
 */
void open_browser(const char* url);

} // namespace elona
