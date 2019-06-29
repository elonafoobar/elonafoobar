#pragma once

#include "elona.hpp"

namespace elona
{

typedef struct {
    int cardrefattack;
    int cardrefcost;
    int cardrefdomain;
    int cardrefhp;
    elona_vector1<std::string> cardrefn;
    int cardrefpic;
    int cardrefrare;
    int cardrefskill;
    int cardrefskillcost;
    int cardreftype;
    std::string cardrefrace;
} CardInfo;

// Card queries
int get_card_info(int dbid, CardInfo& card_info);
int card_ref(int id, CardInfo& card_info);
int cardcanblock(int = 0);
int cardcandeclareattack(int = 0);
int cardcanuseskill(int = 0);
int cdbit(int = 0, int = 0);

// Card actions
int create_card(int = 0, int = 0);
int putcard(int = 0, int = 0);

//// TCG
void actionproc();
void tcgdeck();
void tcgdraw();
void tcgdrawbg();
void tcgdrawcard(int = 0, int = 0);
void tcginit();
void tcgmain();
void gravecard(int = 0);
void calcdecksize();
void calcdomain();
void calcstartattb(int = 0);
void cardpos(int = 0, int = 0);
void cdbitmod(int = 0, int = 0, int = 0);
void cpflip();
void csfix();
void cslinedown();
void cslineup();
int pileremain();
void delbottomcard(int = 0);
int gameover();
void getrandomcard(int = 0);
void opencard(int = 0);
void saccard(int = 0, int = 0);
void makecardlist();
void efllistadd(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);

// Game phases
void tcg_game_over();
void tcg_phase_one();
void tcg_phase_two();
void tcg_phase_three();
void tcg_phase_four();
void tcg_update_mana();

// Game flow
void tcg_show_refs();
void tcg_clear_stack();
void tcg_draw_selection();
void tcg_draw_deck_editor();
void tcg_prepare_cnt2();
void tcg_update_page();
void tcg_draw_menu();
void tcg_prompt_action();
void tcg_clear_cursor();
void tcg_update_selection();
void tcg_card_selected();
void tcg_proc_ai_elist();
void tcg_proc_ai();
void tcg_proc_ai_sacrifice();
int tcg_draw_background();
int tcg_try_sacrifice();
void dmgcard(int = 0, int = 0);
void dmgplayer(int = 0, int = 0);

// Game actions
int getdecksum(int = 0);
int getholdersum(int = 0);
int getspotsum(int = 0);
void cpisenemy();
void cpisme();

} // namespace elona
