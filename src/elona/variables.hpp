#pragma once

#include "elona.hpp"
#include "optional.hpp"
#include "position.hpp"
#include "random.hpp"
#include "talk.hpp"



namespace elona
{

struct Item;
struct Character;



inline elona_vector1<int> ap;
inline int nooracle;

// casino.cpp / casino_card.cpp
inline std::string atxbg;
inline std::string atxbgbk;
inline elona_vector1<std::string> atxinfon;
inline elona_vector1<int> fsetwear;
inline elona_vector1<int> fsetitem;
inline int txtadvscreenupdate;
inline elona_vector2<int> matref;
inline elona_vector1<std::string> matname;

// fov.cpp
inline elona_vector2<int> route;
inline int maxroute;

// building.cpp
inline int tlocinitx;
inline int tlocinity;
inline elona_vector1<int> isethirerole;
inline elona_vector1<int> isethire;
inline elona_vector1<int> income;
inline elona_vector2<std::string> rankn;
inline int renewmulti;
inline elona_vector2<int> bdref;

// ui.cpp
inline int inf_clocky;
inline int inf_msgh;
inline int inf_ver;

// ui.cpp/menu.cpp
inline int autoturn;
inline int firstautoturn;
inline int racount;
inline elona_vector1<std::string> matdesc;
inline std::string nquestdate;
inline int lv;
inline elona_vector3<int> pochart;
inline elona_vector2<int> podata;
inline int refreshmode;
inline bool quest_teleport;
inline int gspdorg;
inline int gspd;
inline int scposval;
inline int weatherbk;


// crafting.cpp / blending.cpp
inline elona_vector1<int> rpsourcelist;
inline int prodtype;
inline elona_vector2<int> matspot;

// quest.cpp
inline elona_vector1<int> fsetcollect;
inline elona_vector1<int> asettown;
inline elona_vector1<int> fsetdeliver;
inline elona_vector1<int> fsetsupply;
inline elona_vector1<int> fsetmagic;
inline elona_vector1<int> fsetarmor;
inline elona_vector1<int> fsetweapon;
inline elona_vector1<int> fsetrewardsupply;

// map.cpp/mapgen.cpp
inline int tile_trap;
inline int tile_doorclosed4;
inline int tile_dooropen;
inline int tile_downlocked;
inline int tile_re;
inline int tile_plant;
inline elona_vector1<int> isetgod;
inline elona_vector1<int> isetcrop;
inline int rdtry;

// food.cpp
inline int enc;

// talk.cpp
inline elona_vector2<std::string> actor;

// mef.cpp
inline elona_vector2<int> mef;
inline elona_vector2<int> mefsubref;

// map_cell.cpp
inline int cellchara;
inline int cellfeat;

// enchantment.cpp
inline elona_vector2<int> encammoref;

// item.hpp/itemgen.hpp
inline elona_vector1<int> isetbook;
inline elona_vector1<int> moneybox;

// ai.cpp
inline elona_vector1<int> isetthrowpotionminor;
inline elona_vector1<int> isetthrowpotionmajor;
inline elona_vector1<int> isetthrowpotiongreater;

// command.cpp
inline int usermapid;
inline int refx;
inline int refy;
inline int movx;
inline int movy;
inline int ri;

// dmgheal.cpp
inline std::string ndeathcause;
inline int catitem;
inline int rollanatomy;
inline int rtdmg;

// turn_sequence.cpp
inline int tgloc;
inline int dbg_skipevent;
inline int findlocmode;
inline int dirsub;
inline int mousex;
inline int mousey;

// initialize_map.cpp
inline int noaggrorefresh;

inline elona_vector1<int> arenaop;
inline elona_vector1<int> commark;
inline elona_vector1<int> cyclemax;
inline elona_vector1<int> deck;
inline elona_vector1<int> deliver;
inline elona_vector1<int> dir;
inline elona_vector1<int> drop;
inline elona_vector1<int> dx;
inline elona_vector1<int> feat;
inline elona_vector1<int> fishanime;
inline elona_vector1<int> fixeditemenc;
inline elona_vector1<int> floorstack;
inline elona_vector1<int> followerexist;
inline elona_vector1<int> followerin;
inline elona_vector1<int> fsetchest;
inline elona_vector1<int> gdata;
inline elona_vector1<int> genetemp;
inline elona_vector1<int> giftvalue;
inline elona_vector1<int> i;
inline elona_vector1<int> ilight;
inline elona_vector1<int> invcontainer;
inline elona_vector1<int> invctrl;
inline elona_vector1<int> invicon;
inline elona_vector1<int> invmark;
inline elona_vector1<int> iorgweight;
inline elona_vector1<int> ipicref;
inline elona_vector1<int> irandomname;
inline elona_vector1<int> isetfruit;
inline elona_vector1<int> mainskill;
inline elona_vector1<int> mat;
inline elona_vector1<int> mdata;
inline elona_vector1<int> mdatatmp;
inline elona_vector1<int> p;
inline elona_vector1<int> recipememory;
inline elona_vector1<int> reph;
inline elona_vector1<int> repw;
inline elona_vector1<int> rowactre;
inline elona_vector1<int> rtval;
inline elona_vector1<int> spact;
inline elona_vector1<int> spell;
inline elona_vector1<int> sx;
inline elona_vector1<int> sy;
inline elona_vector1<int> tc;
inline elona_vector1<int> tile;
inline elona_vector1<int> tile_default;
inline elona_vector1<int> tile_fog;
inline elona_vector1<int> tile_room;
inline elona_vector1<int> tile_tunnel;
inline elona_vector1<int> tile_wall;
inline elona_vector1<int> trait;
inline elona_vector1<int> traitref;
inline elona_vector1<int> trate;
inline elona_vector1<int> windowshadow;
inline elona_vector1<int> x;
inline elona_vector1<int> y;
inline elona_vector1<std::string> ammoname;
inline std::vector<std::string> artifactlocation;
inline elona_vector1<std::string> booktitle;
inline elona_vector1<std::string> buff;
inline elona_vector1<std::string> buffboard;
inline elona_vector1<std::string> description;
inline elona_vector1<std::string> egominorn;
inline elona_vector1<std::string> egoname;
inline elona_vector1<std::string> filtern;
inline elona_vector1<std::string> fltnrace;
inline elona_vector1<std::string> ialphanameref;
inline elona_vector1<std::string> iknownnameref;
inline elona_vector1<std::string> inputlog;
inline elona_vector1<std::string> invkey;
inline elona_vector1<std::string> ioriginalnameref2;
inline elona_vector1<std::string> ioriginalnameref;
inline elona_vector1<std::string> key;
inline std::string key_identify;
inline std::string key_pageup;
inline std::string key_pagedown;
inline std::string key_cancel;
inline std::string key_help;
inline std::string key_msglog;
inline std::string key_enter;
inline std::string key_save;
inline std::string key_skill;
inline std::string key_close;
inline std::string key_cast;
inline std::string key_drink;
inline std::string key_read;
inline std::string key_zap;
inline std::string key_fire;
inline std::string key_search;
inline std::string key_target;
inline std::string key_dig;
inline std::string key_wait;
inline std::string key_inventory;
inline std::string key_drop;
inline std::string key_get;
inline std::string key_charainfo;
inline std::string key_eat;
inline std::string key_wear;
inline std::string key_godown;
inline std::string key_goup;
inline std::string key_interact;
inline std::string key_use;
inline std::string key_bash;
inline std::string key_open;
inline std::string key_dip;
inline std::string key_pray;
inline std::string key_offer;
inline std::string key_journal;
inline std::string key_material;
inline std::string key_trait;
inline std::string key_give;
inline std::string key_prev;
inline std::string key_next;
inline std::string key_throw;
inline std::string key_mode;
inline std::string key_ammo;
inline std::string key_mode2;
inline elona_vector1<std::string> key_list;
inline elona_vector1<std::string> key_select;
inline elona_vector1<std::string> keylog;
inline elona_vector1<std::string> mdatan;
inline elona_vector1<std::string> newsbuff;
inline elona_vector1<std::string> playerheader;
inline elona_vector1<std::string> q;
inline elona_vector1<std::string> qname;
inline elona_vector1<std::string> s1;
inline elona_vector1<std::string> s;
inline elona_vector1<std::string> traitrefn2;
inline elona_vector1<std::string> traitrefn;
inline elona_vector2<int> adata;
inline elona_vector2<int> breathlist;
inline elona_vector2<int> c_col;
inline elona_vector2<int> card;
inline elona_vector2<int> cmapdata;
inline elona_vector2<int> cycle;
inline elona_vector2<int> dblist;
inline elona_vector2<int> dirxy;
inline elona_vector2<int> encprocref;
inline elona_vector1<int> eqweapon1;
inline elona_vector1<int> eqrange;
inline elona_vector1<int> eqammo;
inline elona_vector1<int> eqring1;
inline elona_vector2<int> itemmemory;
inline elona_vector2<int> list;
inline elona_vector2<int> mapsync;
inline elona_vector2<int> npcmemory;
inline elona_vector2<int> pcc;
inline elona_vector2<int> picfood;
inline elona_vector2<int> qdata;
inline elona_vector2<int> slight;
inline elona_vector2<std::string> _melee;
inline elona_vector2<std::string> cdatan;
inline elona_vector2<std::string> listn;
inline elona_vector2<std::string> mapnamerd;
inline elona_vector3<int> bddata;
inline elona_vector3<int> efmap;
inline elona_vector3<int> map;
inline int ammo;
inline int ammoproc;
inline int ammoprocbk;
inline int animode;
inline int area;
inline int attacknum;
inline int attackrange;
inline int attackskill;
inline int atxspot;
inline int body;
inline int bonus;
inline int camera;
inline int cc;
inline int ccbk;
inline int cellaccess;
inline int chatesc;
inline int chatteleport;
inline int ci;
inline int cidip;
inline int client;
inline int cm;
inline int cmbg;
inline int cmsex;
inline int cmshade;
inline int creaturepack;
inline int critical;
inline int crop;
inline int cs;
inline int cs_bk2;
inline int cs_bk;
inline int cspecialeq;
inline int cw;
inline int cxinit;
inline int cyinit;
inline int damage;
inline int dbg_revealmap;
inline int dbid;
inline int dice1;
inline int dice2;
inline int distance;
inline int dmg;
inline int dmgfix;
inline double dmgmulti;
inline int dy;
inline int efcancel;
inline int efid;
inline int efp;
inline int efsource;
inline CurseState efstatus;
inline int egolv;
inline int ele;
inline int elep;
inline int en;
inline int encounter;
inline int encounterlv;
inline int encounterref;
inline int enemyteam;
inline int eqmultiweapon;
inline int eqtwohand;
inline int equip;
inline int exp;
inline int f2;
inline int f;
inline int filtermax;
inline int firstturn;
inline int fish;
inline int fishx;
inline int fishy;
inline Quality fixlv;
inline int fixmaterial;
inline int fixtransfermap;
inline int fltselect;
inline int flttypemajor;
inline int flttypeminor;
inline int foot;
inline int grown;
inline int hire;
inline int homemapmode;
inline int ichargelevel;
inline IdentifyState idtresult;
inline int in;
inline int inf_maxlog;
inline size_t inf_maxmsglen;
inline int inf_msgspace;
inline int inf_msgx;
inline int inf_msgy;
inline int inf_screenh;
inline int inf_screenw;
inline int inf_screenx;
inline int inf_screeny;
inline int inf_tiles;
inline int inf_verh;
inline int inf_very;
inline int initeco;
inline int initlv;
inline int invally;
inline int invfile;
inline int invhead;
inline int invrange;
inline int invsc;
inline int invsubroutine;
inline int jp;
inline bool key_escape;
inline int keybd_attacking;
inline int keybd_wait;
inline int keyrange;
inline int keywait;
inline int lastctrl;
inline int len;
inline int levelexitby;
inline int listmax;
inline int lomiaseaster;
inline int mapstartx;
inline int mapstarty;
inline int mapsubroutine;
inline int mapupdate;
inline int marry;
inline int maxbreath;
inline int maxitemid;
inline int menucycle;
inline int minlevel;
inline int mode;
inline int msync;
inline int mtilefilecur;
inline int musicloop;
inline int nostack;
inline int novoidlv;
inline int nowindowanime;
inline int objfix;
inline int objlv;
inline int obvious;
inline int oc;
inline int orgdmg;
inline int page;
inline int page_bk;
inline int pagemax;
inline int pagesize;
inline int pcattacker;
inline int petarenawin;
inline int potionspill;
inline int potionthrow;
inline int promptx;
inline int prompty;
inline int prot;
inline int protdice1;
inline int protdice2;
inline int quickpage;
inline int r2;
inline int r;
inline int range_;
inline int rapidmagic;
inline int rc;
inline int reftype;
inline int reftypeminor;
inline int returnfromidentify;
inline int rq;
inline int running;
inline int sc;
inline int scene_cut;
inline int sceneid;
inline int scenemode;
inline int screenupdate;
inline int scroll;
inline int scrollanime;
inline int scrollp;
inline int scrturn;
inline int scx;
inline int scxbk;
inline int scy;
inline int scybk;
inline int shoptrade;
inline int size;
inline int sizefix;
inline int sound;
inline int strsize;
inline int supply;
inline int sxfix;
inline int syfix;
inline int t;
inline int tail;
inline int tcbk;
inline int tg;
inline int ti;
inline int tile_doorclosed;
inline int tile_downstairs;
inline int tile_hidden;
inline int tile_upstairs;
inline int time_begin;
inline int time_warn;
inline int tlocx;
inline int tlocy;
inline int tx;
inline int txt3rd;
inline int ty;
inline int vfix;
inline int voidlv;
inline int windowh;
inline int windoww;
inline int wh;
inline int ww;
inline int wx;
inline int wy;
inline int x1;
inline int x2;
inline int y1;
inline int y2;
inline std::string cmaka;
inline std::string defload;
inline std::string fmapfile;
inline std::string geneuse;
inline std::string mid;
inline std::string playerid;
inline std::string s2;
inline std::string strhint1;
inline std::string strhint2;
inline std::string strhint3;
inline std::string strhint3b;
inline std::string strhint4;
inline std::string strhint5;
inline std::string strhint5b;
inline std::string strhint7;

inline optional<int> chatval_unique_chara_id;

//// Game formulae
int calcincome(int = 0);
int calcmagiccontrol(int = 0, int = 0);
int calcstartcard(int = 0);
int randskill();

//// Init
void initialize_pc_character();
int initialize_world_map();
void initialize_rankn();
void initialize_post_data();
void initialize_building_data();
void initialize_nefia_names();
void initialize_picfood();
void initialize_cloud_data();
void initialize_item_material_data();
void initialize_set_of_random_generation();
void initialize_economy();
void clear_existing_quest_list();


//// Character querying
int relationbetween(int, int);


//// Character manipulation
void refresh_burden_state();
int new_ally_joins();
void go_hostile();
void get_pregnant();
void wet(int = 0, int = 0);

// Character revival
void revive_character();
void do_chara_revival();
void chara_set_revived_status();
void chara_clear_status_effects_b();
void chara_clear_status_effects();
void revive_player();

// Trait
void clear_trait_data();
void gain_race_feat();


//// Items

// Item status querying
bool cargocheck(const Item& item);

// Item manipulation
int convertartifact(int = 0, int = 0);
int discsetmc();
void set_item_info();

// Item generation
int random_material(int = 0, int = 0);
int randattb();

// Equipment
int equip_item(int);
void unequip_item(int);

// Inventory
std::pair<int, int> inv_getheader(int);


// Math utility functions
int direction(int = 0, int = 0, int = 0, int = 0);
int dist(int = 0, int = 0, int = 0, int = 0);
int roll(int, int, int);
int roll_max(int, int, int);
int roundmargin(int = 0, int = 0);


// Player-owned building
int getworker(int = 0, int = 0);
void removeworker(int = 0);


//// flt
int fltsetdungeon();
std::string fltname(int = 0);
void flt(int = 0, Quality quality = Quality::none);
void fltn(const std::string&);


// Input translation
int key_direction(const std::string& action);


//// Actions

// Querying input
int ask_direction();
int target_position(bool target_chara = true);
int prompt_magic_location();
int prompt_really_attack();

// Action calculation
int find_enemy_target(bool silent = false);
int can_do_ranged_attack();

// Main action body
int try_to_reveal();
int can_evade_trap();
int try_to_disarm_trap();
int try_to_perceive_npc(int);

bool read_textbook(Item& textbook);
int decode_book();
int read_normal_book();

int try_to_cast_spell();
int do_cast_magic();
int do_cast_magic_attempt();

int drink_potion();
int drink_well();
int read_scroll();
int do_zap();
int do_magic_attempt();
int pick_up_item(bool play_sound = true);
int unlock_box(int);
void do_ranged_attack();

//// Command
TurnResult step_into_gate(Item& moon_gate);
optional<TurnResult> check_angband();
TurnResult do_bash();
TurnResult do_enter_strange_gate();
TurnResult do_gatcha(Item& gatcha_machine);
TurnResult do_use_magic();
TurnResult do_use_stairs_command(int);
TurnResult try_interact_with_npc();
TurnResult try_to_open_locked_door();

// Attacking
void build_target_list();
void equip_melee_weapon();
void get_inheritance();

void try_to_melee_attack();
void do_physical_attack();
void proc_weapon_enchantments();

// Planting
TurnResult do_plant();
void grow_plant(int);
void try_to_grow_plant(int = 0);
void harvest_plant(int);
void create_harvested_item();

// Searching
void disarm_trap(Character& chara, int x, int y);
void discover_trap();
void discover_hidden_path();

// Sleeping
void draw_sleep_background_frame();
void load_sleep_background();
void sleep_start();
void wake_up();
void do_rest();

// Opening
void open_box();
void open_new_year_gift();

// NPC interact
TurnResult call_npc();


//// Action effect
void dipcursed(int = 0, int = 0);
void start_stealing();
void hostileaction(int = 0, int = 0);
void turn_aggro(int = 0, int = 0, int = 0);
void ride_begin(int = 0);
void ride_end();
void make_sound(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);


//// pass_one_turn
void proc_pregnant();
void proc_negative_enchantments(Character& chara);
void damage_by_cursed_equipments();


//// proc_movement_event
TurnResult proc_movement_event();
void map_global_proc_travel_events();
void move_character();
void sense_map_feats_on_move();


//// Magic
int breath_list();
int efstatusfix(int = 0, int = 0, int = 0, int = 0);
int route_info(int&, int&, int = 0);
void try_to_return();
void heal_both_rider_and_mount();
void heal_completely();
void incognitobegin();
void incognitoend();
void lovemiracle(int = 0);


//// Blending
int blending_find_required_mat();
int blending_spend_materials();
void blending_start_attempt();
void blending_proc_on_success_events();

//// Map
int map_barrel(int = 0, int = 0);
int map_connectroom();
int map_createroom(int = 0);
int map_digcheck(int = 0, int = 0);
int map_placedownstairs(int = 0, int = 0);
int map_placeupstairs(int = 0, int = 0);
int map_trap(int = 0, int = 0, int = 0, int = 0);
int map_web(int = 0, int = 0, int = 0);
int mapitemfind(int = 0, int = 0, int = 0);

// Map drawing
void cell_draw();
void addefmap(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);

// Map animation
void animeblood(int = 0, int = 0, int = 0);
void animeload(int = 0, int = 0);
void spillblood(int = 0, int = 0, int = 0);
void spillfrag(int = 0, int = 0, int = 0);

// Mef
void delmef(int = 0);

// Map initialization
TurnResult initialize_map();
void initialize_map_from_map_type();
void map_global_proc_diastrophism();
void map_global_prepare();
void map_global_place_entrances();
void map_clear_material_spots_and_light();

// Map lifecycle
TurnResult exit_map();
void prepare_charas_for_map_unload();
void save_map_local_data();


//// Map generation
void initialize_cell_object_data();
void initialize_random_nefia_rdtype6();
void initialize_quest_map_town();
void initialize_random_nefia_rdtype8();
void initialize_random_nefia_rdtype9();
void mapgen_dig_maze();
void initialize_random_nefia_rdtype10();


//// weather_changes
void supply_income();


//// list/listn
void sort_list_by_column1();
void sort_list_and_listn_by_column1();


//// Special items

// Gene engineering
int gain_skills_by_geen_engineering();
int transplant_body_parts();

// objet of heart
void cnvbonus(int = 0, int = 0);


//// UI
void help_halt();
int winposy(int = 0, int = 0);
void txttargetnpc(int x, int y);

// character sheet
void append_accuracy_info(int);
void show_weapon_dice(int);

// Screen refresh
void auto_turn(int delay);
void house_board_update_screen();

// inventory
void savecycle();


//// Text parsing
int talk_conv(std::string&, int = 0);
void parse_quest_board_text(int);
void parse_talk_file();
void read_talk_file(const std::string&);
void get_npc_talk();
void text_replace_tags_in_quest_board();
void text_replace_tags_in_quest_text();


//// Text

// Text manipulation
std::string zentohan(const std::string&);
std::string cnven(const std::string&);
std::string fixtxt(const std::string&, int = 0);
std::string sncnv(const std::string&);
void cutname(std::string&, int = 0);
void lenfix(std::string&, int = 0);



// Text fragments
std::string cnvarticle(const std::string&);
std::string cnvdate(int, bool = true);
std::string cnveqweight(int = 0);
std::string cnvfix(int = 0);
std::string cnvitemname(int = 0);
std::string cnvplaytime(int = 0);
std::string cnvrank(int = 0);
std::string cnvrare(int = 0);
std::string cnvweight(int = 0);

// Whole message creation
std::string getnpctxt(const std::string&, const std::string&);
std::string txtbuilding(int x, int y);
std::string txtitemoncell(int = 0, int = 0);
std::string txtskillchange(int, int, bool);
std::string txttargetlevel(int, int);
std::string cheer_up_message(int);


// Name retrieval
std::string name(int = 0);
std::string itemname(int = 0, int = 0, int = 0);
std::string guildname();
std::string maplevel(int = 0);
std::string mapname(int, bool = false);
std::string ranktitle(int = 0);

// Job names
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


//// Casino/ATX
void atxinit();

// Save manipulation
void begintempinv();
void exittempinv();
void migrate_save_data(const fs::path& filepath);
void load_gene_files();
void save_gene();
void dump_player_info();


//// dmgheal
void character_drops_item();
void check_kill(int = 0, int = 0);


//// Journal
void append_subquest_journal(int);
void append_quest_item_journal();


//// turn_begin
void auto_identify();
void monster_respawn();


//// weather
void weather_changes();


//// Religion
void god_fail_to_take_over_penalty();


//// ether disease
void lost_body_part(int);


//// Scene
void do_play_scene();
void scene_fade_to_black();


//// Scenario
void conquer_lesimas();
void play_the_last_scene_again();


//// Game lifecycle
void proc_turn_end(int);
TurnResult pc_died();
void show_game_score_ranking();
void finish_elona();


//// Status manipulation
void modrank(int = 0, int = 0, int = 0);


//// item_show_description
void page_load();
void page_save();

} // namespace elona
