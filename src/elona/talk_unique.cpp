#include "character.hpp"
#include "dialog.hpp"
#include "talk.hpp"
#include "variables.hpp"

namespace elona
{

TalkResult talk_unique()
{
    listmax = 0;

    auto& chara = cdata[tc];
    const auto& dialog_id = the_character_db[charaid2int(chara.id)]->dialog_id;

    if (dialog_id)
    {
        dialog_start(chara, *dialog_id);
        return TalkResult::talk_end;
    }

    return TalkResult::talk_ignored;
}

} // namespace elona
