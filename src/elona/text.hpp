#pragma once

#include <string>



namespace elona
{

template <typename T>
struct elona_vector1;



void load_random_name_table();
std::string random_name();

void load_random_title_table();
enum class RandomTitleType
{
    character,
    weapon,
    party,
    living_weapon,
};
std::string random_title(RandomTitleType type);


void cnvbonus(int = 0, int = 0);
std::string cnveqweight(int = 0);
void cutname(std::string&, int = 0);
std::string fixtxt(const std::string&, int = 0);
std::string getnpctxt(const std::string&, const std::string&);
std::string guildname();
void initialize_rankn();
void lenfix(std::string&, int = 0);
std::string ranktitle(int = 0);
std::string txttargetlevel(int, int);
void txttargetnpc(int x, int y);
std::string fltname(int = 0);


void csvsort(
    elona_vector1<std::string>& result,
    std::string line,
    int separator);

void initialize_nefia_names();
void parse_quest_board_text(int);
void parse_talk_file();
void read_talk_file(const std::string&);
void get_npc_talk();
void text_replace_tags_in_quest_board();
void text_replace_tags_in_quest_text();
std::string zentohan(const std::string&);
std::string cnven(const std::string&);
std::string sncnv(const std::string&);
std::string cnvarticle(const std::string&);
std::string cnvdate(int, bool = true);
std::string cnvfix(int = 0);
std::string cnvitemname(int = 0);
std::string cnvplaytime(int = 0);
std::string cnvrank(int = 0);
std::string cnvweight(int = 0);
std::string txtbuilding(int x, int y);
std::string txtitemoncell(int = 0, int = 0);
std::string txtskillchange(int, int, bool);
std::string cheer_up_message(int);
std::string name(int = 0);
std::string maplevel(int = 0);
std::string mapname(int, bool = false);
std::string snarmor(const std::string&);
std::string snbakery(const std::string&);
std::string snblack(const std::string&);
std::string snfish(const std::string&);
std::string snfood(const std::string&);
std::string sngeneral(const std::string&);
std::string sngoods(const std::string&);
std::string sninn(const std::string&);
std::string snmagic(const std::string&);
std::string sntrade(const std::string&);
std::string sntrainer(const std::string&);
void append_subquest_journal(int);
void append_quest_item_journal();

} // namespace elona
