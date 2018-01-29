namespace elona
{
inline int cnt;
inline int strsize;
inline int stat;
inline std::string refstr;
// cnt :: int
// strsize :: int
// stat :: int
// refstr :: string
// abs :: (int) -> int
// atan :: (int, int) -> int
// await :: (int) -> void
// axobj :: (int, string, int, int) -> void
// bcopy :: (string, string) -> void
// bgscr :: (int, int, int, int, int) -> void
// bload :: (string, T, int, int) -> void
// boxf :: (int, int, int, int) -> void
// bsave :: (string, T) -> void
// buffer :: (int, int, int) -> void
// chgdisp :: (int, int, int) -> void
// clrobj :: (int) -> void
// cnvstow :: (ref<string>, string) -> void
// color :: (int, int, int) -> void
// delcom :: (int) -> void
// dialog :: (string, int) -> void
// dirinfo :: (int) -> string
// dirlist :: (ref<string>, string) -> void
// elona_delete :: (string) -> void
// elona_double :: (T) -> int
// elona_int :: (T) -> int
// elona_str :: (int) -> string
// exec :: (string, int) -> void
// exist :: (string) -> void
// expf :: (int) -> int
// font :: (string, int, int) -> void
// gcopy :: (int, int, int, int, int) -> void
// getkey :: (ref<int>, int) -> void
// getpath :: (string, int) -> string
// getstr :: (ref<string>, string, int, int, int) -> void
// ginfo :: (int) -> int
// gmode :: (int, int, int, int) -> void
// grotate :: (int, int, int, int, int, int) -> void
// gsel :: (int) -> void
// gzoom :: (int, int, int, int, int, int, int) -> void
// instr :: (string, int, string) -> int
// length :: (elona_vector1<T>) -> int
// length2 :: (elona_vector2<T>) -> int
// limit :: (int, int, int) -> int
// line :: (int, int, int, int) -> void
// logf :: (int) -> int
// memcpy :: (T, T, int, int) -> void
// memexpand :: (T, int) -> void
// memfile :: (T) -> void
// memset :: (T, int, int) -> void
// mes :: (string) -> void
// mesbox :: (ref<string>, int, int, int, int) -> void
// mkdir :: (string) -> void
// mmload :: (string, int, int) -> void
// mmplay :: (int) -> void
// mmstop :: () -> void
// mref :: () -> void
// noteadd :: (string, int, int) -> void
// notedel :: (int) -> void
// noteget :: (ref<string>, int) -> void
// noteinfo :: (int) -> int
// noteload :: (string) -> void
// notesave :: (string) -> void
// notesel :: (ref<string>) -> void
// noteunsel :: () -> void
// objmode :: (int, int) -> void
// objprm :: (int, string) -> void
// objsel :: (int) -> void
// peek :: (T, int) -> int
// pget :: (int, int) -> void
// picload :: (string, int) -> void
// poke :: (ref<string>, int, T) -> void
// pos :: (int, int) -> void
// randomize :: (int) -> void
// redraw :: (int) -> void
// rnd :: (int) -> int
// screen :: (int, int, int, int, int, int) -> void
// sqrt :: (int) -> int
// stick :: (ref<int>, int) -> void
// strlen :: (string) -> int
// strmid :: (string, int, int) -> string
// title :: (string) -> void
// varptr :: (string) -> int
// width :: (int) -> void
// wpeek :: (int, int) -> int
// wpoke :: (ref<int>, int, int) -> void
// exrand_randomize :: (int) -> void
// exrand_rnd :: (ref<int>, int) -> void
// func_1 :: (string, int) -> void
// xnotesel :: (ref<string>) -> void
// xnoteadd :: (string) -> void
// gfini :: (int, int) -> void
// gfdec :: (int, int, int) -> void
// gfdec2 :: (int, int, int) -> void
// gfinc :: (int, int, int) -> void
// ematan :: (int, int, int) -> void
// aplsel :: (string) -> void
// aplobj :: (string, int) -> void
// apledit :: (int, int, int) -> void
// func_2 :: () -> void
// zOpen :: (ref<int>, string, int, int) -> void
// zRead :: (T, int, int) -> void
// zWrite :: (T, int, int) -> void
// zClose :: (int) -> void
// GetOpenFileNameA :: () -> void
// GetSaveFileNameA :: () -> void
// DSINIT :: () -> void
// DSEND :: () -> void
// DSRELEASE :: (int) -> void
// DSLOADFNAME :: (string, int) -> void
// DSPLAY :: (int, int) -> void
// DSSTOP :: (int) -> void
// DSSETVOLUME :: (int, int) -> void
// DSGETMASTERVOLUME :: () -> void
// CHECKPLAY :: () -> void
// DMINIT :: () -> void
// DMEND :: () -> void
// DMLOADFNAME :: (string, int) -> void
// DMPLAY :: (int, int) -> void
// DMSTOP :: () -> void
// DIINIT :: () -> void
// DIGETJOYNUM :: () -> void
// DIGETJOYSTATE :: (int, int) -> void
// HMMBITON :: (ref<int>, int) -> void
// HMMBITOFF :: (ref<int>, int) -> void
// HMMBITCHECK :: (int, int) -> void
// sockopen :: (int, string, int) -> void
// sockclose :: () -> void
// sockget :: (string, int) -> void
// sockput :: () -> void
// netinit :: () -> void
// netexec :: (ref<int>) -> void
// neterror :: (ref<string>) -> void
// neturl :: (string) -> void
// netdlname :: (string) -> void
// netrequest :: (string) -> void
// RemoveDirectoryA :: (string) -> void
// GetLastError :: () -> void
// CreateMutexA :: (int, int, string) -> void
// CloseHandle :: (int) -> void
// func_3 :: () -> void
// LCMapStringA :: (int, int, string, int, ref<string>, int) -> int
// GetUserDefaultLCID :: () -> int
// water_getimage :: () -> void
// water_setripple :: (int, int, int, int) -> void
// water_calc :: () -> void
// water_draw :: () -> void
// AppendMenuA :: () -> void
// CheckMenuRadioItem :: () -> void
// CreateMenu :: () -> void
// CreatePopupMenu :: () -> void
// DrawMenuBar :: () -> void
// SetMenu :: () -> void
// keybd_event :: (int, int, int) -> void
// GetKeyboardState :: (unknown) -> void
// timeBeginPeriod :: (int) -> void
// timeEndPeriod :: () -> void
// timeGetTime :: () -> int
// ImmGetContext :: (int) -> int
// ImmReleaseContext :: (int, int) -> void
// ImmSetOpenStatus :: (int, int) -> void
// ImmGetOpenStatus :: (int) -> int
// op__and :: (int, int) -> int
// op__division :: (int, int) -> int
// op__equal :: (T, T) -> int
// op__greater_than :: (T, T) -> int
// op__greater_than_equal :: (T, T) -> int
// op__less_than :: (T, T) -> int
// op__less_than_equal :: (T, T) -> int
// op__minus :: (int, int) -> int
// op__modulo :: (int, int) -> int
// op__multiplication :: (int, int) -> int
// op__not_equal :: (T, T) -> int
// op__or :: (int, int) -> int
// op__plus :: (T, T) -> T
// op__shift_l :: (int, int) -> int
// uop__minus :: (int) -> int
// DIM1 :: (T) -> void
// DIM2 :: (T, int) -> void
// DIM3 :: (T, int, int) -> void
// DIM4 :: (T, int, int, int) -> void
// SDIM1 :: (T) -> void
// SDIM2 :: (T, int) -> void
// SDIM3 :: (T, int, int) -> void
// SDIM4 :: (T, int, int, int) -> void
// dup :: (T, T) -> void
// main :: () -> int
std::string randomname(int = 0);
inline elona_vector1<std::string> proclist;
inline std::string exedir;
inline std::string devfile;
inline int randseed;
void label_0192();
// prm_194 :: string
inline int res_at_m0;
inline std::string estr_at_m0;
void netload(const std::string&);
void label_0002();
// prm_209 :: string
// prm_210 :: ref<string>
// prm_211 :: int
int zentohan(const std::string&, std::string&, int = 0);
void tmset();
// prm_246 :: string
// prm_247 :: string
inline int jp;
std::string lang(const std::string&, const std::string&);
// prm_248 :: int
std::string cnvrank(int = 0);
// prm_249 :: string
std::string cnvtalk(const std::string&);
// prm_250 :: string
std::string cnvarticle(const std::string&);
// prm_251 :: int
inline elona_vector1<std::string> ioriginalnameref;
inline elona_vector1<std::string> ioriginalnameref2;
// prm_252 :: string
inline std::string s_at_m1;
inline int p_at_m1;
std::string cnven(const std::string&);
// prm_253 :: int
// prm_254 :: int
inline elona_vector2<int> cdata;
int cbit(int = 0, int = 0);
// prm_255 :: int
// prm_256 :: int
// prm_257 :: int
void cbitmod(int = 0, int = 0, int = 0);
// prm_261 :: int
// prm_262 :: int
inline int dbmode;
inline std::string dbidn;
inline elona_vector2<std::string> cdatan;
inline int dbspec;
int label_2298();
int refclass(int = 0, int = 0);
// prm_263 :: string
// prm_264 :: int
int label_2297();
int refrace(const std::string&, int = 0);
// prm_265 :: int
inline int p_at_m6;
inline elona_vector1<int> gdata;
inline elona_vector2<std::string> rankn;
inline elona_vector1<int> ranknorma;
void label_0026();
inline std::string s_at_m7;
std::string guildname();
inline elona_vector1<std::string> popostname;
inline elona_vector3<int> pochart;
inline elona_vector2<int> podata;
void label_0029();
inline elona_vector3<int> bddata;
inline elona_vector2<int> bdref;
inline elona_vector1<std::string> bdrefn;
void label_0030();
inline elona_vector2<int> bdataref;
inline elona_vector1<std::string> buffname;
inline elona_vector2<std::string> bufftxt;
inline elona_vector1<std::string> buffdesc;
void label_0031();
// prm_266 :: int
// prm_267 :: int
// prm_268 :: int
inline int dur;
inline elona_vector1<int> p_at_m8;
inline elona_vector1<std::string> skillname;
inline elona_vector2<int> sdata;
void calcbuff(int = 0, int = 0, int = 0);
inline elona_vector2<int> sdataref;
inline elona_vector1<std::string> skilldesc;
inline elona_vector1<std::string> skillencdesc;
void label_0034();
// prm_269 :: int
// prm_270 :: int
// prm_271 :: int
inline int rs_at_m9;
inline int ele;
inline int elep;
inline int dice1;
inline int dice2;
inline int bonus;
inline int ep;
int calcskill(int = 0, int = 0, int = 0);
// prm_272 :: int
// prm_273 :: int
int sorg(int = 0, int = 0);
int randskill();
int randattb();
inline elona_vector1<int> traitref;
inline elona_vector1<std::string> traitrefn;
inline elona_vector1<std::string> traitrefn2;
void label_0041();
inline int tid;
inline int traitmode;
inline elona_vector1<int> trait;
inline elona_vector1<int> spact;
int label_0042();
void label_0043();
// prm_274 :: int
// prm_275 :: int
inline elona_vector2<int> inv;
int ibit(int = 0, int = 0);
// prm_276 :: int
// prm_277 :: int
// prm_278 :: int
void ibitmod(int = 0, int = 0, int = 0);
// prm_279 :: int
// prm_280 :: int
inline int dbid;
void label_0481();
int refitem(int = 0, int = 0);
// prm_281 :: int
inline int p_at_m13;
int iequiploc(int = 0);
// prm_282 :: int
// prm_283 :: int
void setunid(int = 0, int = 0);
// prm_284 :: int
inline int f_at_m14;
inline int usernpcmax;
inline elona_vector2<std::string> userdatan;
int getunid(int = 0);
// prm_285 :: string
int findunid(const std::string&);
// prm_286 :: int
// prm_287 :: int
inline int msync;
inline elona_vector2<int> mapsync;
int synccheck(int = 0, int = 0);
inline int evnum;
inline elona_vector1<int> evlist;
int evid();
// prm_288 :: int
inline int f_at_m17;
int evfind(int = 0);
// prm_289 :: int
// prm_290 :: int
// prm_291 :: int
inline int evproc;
inline elona_vector1<int> evdata1;
inline elona_vector1<int> evdata2;
void evadd(int = 0, int = 0, int = 0);
// prm_292 :: string
// prm_293 :: int
inline int cfg_sound;
inline elona_vector1<std::string> soundfile;
void sndload(const std::string&, int = 0);
// prm_296 :: int
// prm_297 :: int
// prm_298 :: int
inline int sound_at_m18;
inline int f_at_m18;
inline elona_vector1<int> soundlist;
void snd(int = 0, int = 0, int = 0);
inline int cfg_svolume;
inline elona_vector1<std::string> folder;
void label_0066();
inline elona_vector1<std::string> s;
inline elona_vector1<std::string> buff;
inline elona_vector1<std::string> musicfile;
void label_0067();
inline int procid;
inline int ct;
inline int env;
inline int envwprev;
inline elona_vector1<int> mdata;
inline int envonly;
inline int cfg_music;
inline int music;
inline elona_vector2<int> adata;
inline int musicprev;
inline int musicloop;
inline std::string musicfolder;
inline int mp3;
void label_0068();
// prm_299 :: int
inline elona_vector1<std::string> key;
inline elona_vector1<std::string> keylog;
inline int msgalert;
inline int cfg_alert;
inline int p_at_m19;
inline int a_at_m19;
inline int mousel;
inline int f_at_m19;
inline int key_tab;
inline int key_escape;
inline int keywait;
inline int key_ctrl;
inline int keybd_wait;
inline int key_shift;
inline int cfg_joypad;
inline int j_at_m19;
inline elona_vector1<std::string> jkey;
inline std::string key_alter;
inline int prevjoy_at_m19;
inline int b_at_m19;
inline int quickkeywait;
inline std::string keyactive_at_m19;
inline int keybd_attacking;
inline int cfg_attackwait;
inline int cfg_scroll;
inline int cfg_walkwait;
inline int cfg_startrun;
inline int running;
inline int cfg_runwait;
inline int cfg_runscroll;
inline int sc;
inline int scon_at_m19;
inline int keyhalt;
void key_check(int = 0);
inline int a_at_m20;
void keyrelease();
// prm_300 :: int
void press(int = 0);
// prm_301 :: string
// prm_302 :: int
// prm_303 :: int
// prm_304 :: int
inline int pos_x_at_m21;
inline int pos_y_at_m21;
inline elona_vector1<int> mes_color_at_m21;
inline int mes_y_at_m21;
void bmes(const std::string&, int = 0, int = 0, int = 0);
// prm_305 :: string
// prm_306 :: int
inline int n_at_txtfunc;
inline std::string msgtemp_at_txtfunc;
inline int len_at_txtfunc;
inline int p2_at_txtfunc;
inline int p_at_txtfunc;
inline std::string m_at_txtfunc;
int talk_conv(std::string&, int = 0);
// prm_307 :: string
inline int mp_at_txtfunc;
inline int mark_at_txtfunc;
inline int msglen;
inline int inf_mesfont;
inline int inf_msgx;
inline int en;
inline int inf_msgline;
inline int inf_msgspace;
inline int inf_msgy;
inline elona_vector1<int> tcol_at_txtfunc;
inline std::string cfg_font1;
inline std::string cfg_font2;
void msg_write(std::string&);
inline int tmore_at_txtfunc;
void txtmore();
inline int tcontinue_at_txtfunc;
void txtcontinue();
inline int x_at_txtfunc;
inline int y_at_txtfunc;
void anime_halt();
inline int windoww;
inline int windowh;
inline int screenupdate;
void label_1419();
void msg_halt();
inline int wx;
inline elona_vector1<int> dx;
inline int wy;
inline int dy;
void help_halt();
// prm_308 :: int
inline elona_vector2<int> c_col;
inline int tcolfix_at_txtfunc;
void txtef(int = 0);
inline int cfg_exlog;
inline int msgline;
inline int inf_maxlog;
void msg_newlog();
inline elona_vector1<std::string> msg;
inline elona_vector1<std::string> msgtempprev;
void msg_newline();
inline int tnew;
void txtnew();
inline int msg_len;
inline elona_vector1<std::string> msgtemp;
void msg_clear();
inline int tcopy;
inline std::string txtcopy;
inline int cfg_msgtrans;
inline int cfg_msgaddtime;
inline int msgdup;
inline int inf_maxmsglen;
inline int b_at_txtfunc;
inline std::string mst_at_txtfunc;
void txt_conv();
// prm_309 :: int
inline std::string s_at_m23;
std::string name(int = 0);
// prm_310 :: int
std::string aln(int = 0);
// prm_311 :: int
std::string npcn(int = 0);
// prm_312 :: int
// prm_313 :: int
std::string _s(int = 0, int = 0);
// prm_314 :: int
std::string _s2(int = 0);
// prm_315 :: int
std::string is2(int = 0);
// prm_316 :: int
std::string is(int = 0);
// prm_318 :: int
std::string have(int = 0);
// prm_319 :: int
std::string does(int = 0);
// prm_320 :: int
// prm_321 :: int
std::string he(int = 0, int = 0);
// prm_322 :: int
// prm_323 :: int
std::string his(int = 0, int = 0);
// prm_324 :: int
// prm_325 :: int
std::string him(int = 0, int = 0);
// prm_326 :: int
std::string your(int = 0, int = 0);
// prm_328 :: int
std::string yourself(int = 0);
// prm_329 :: int
inline int txtvalid;
inline int cc;
inline elona_vector1<int> tc;
void txt_check(int = 0);
// prm_339 :: int
std::string cnvfix(int = 0);
// prm_340 :: int
// prm_341 :: string
// txt :: unknown
void stxt(int, const std::string&);
// prm_342 :: int
// prm_343 :: int
inline int p_at_m27;
inline int hour_at_m27;
inline int day_at_m27;
inline int month_at_m27;
inline int year_at_m27;
inline std::string s_at_m27;
std::string cnvdate(int = 0, int = 0);
// prm_344 :: int
std::string cnvplaytime(int = 0);
// prm_345 :: int
// prm_346 :: int
int roundmargin(int = 0, int = 0);
// prm_347 :: int
inline int autoturn;
inline int cfg_autoturn;
inline int scrturn;
inline int firstautoturn;
void at(int = 0);
inline elona_vector1<std::string> bodyn;
inline elona_vector1<std::string> _impression;
inline elona_vector1<std::string> _weather;
inline elona_vector1<std::string> _homename;
inline elona_vector1<std::string> _furniture;
inline elona_vector1<std::string> _weight;
inline elona_vector1<std::string> _tone;
inline elona_vector1<std::string> _reward;
inline elona_vector1<std::string> _time;
inline elona_vector1<std::string> _stats;
inline elona_vector1<std::string> _stats2;
inline elona_vector1<std::string> _hunger;
inline elona_vector1<std::string> _burden;
inline elona_vector1<std::string> _sleep;
inline elona_vector1<std::string> _consick;
inline elona_vector1<std::string> _conpoison;
inline elona_vector1<std::string> _condim;
inline elona_vector1<std::string> _conangry;
inline elona_vector1<std::string> _conbleed;
inline elona_vector1<std::string> _coninsane;
inline std::string _condrunk;
inline std::string _conwet;
inline std::string _congravity;
inline elona_vector1<std::string> _consleep;
inline std::string _conblind;
inline std::string _conparalyze;
inline std::string _conmochi;
inline std::string _conconfuse;
inline std::string _confear;
inline elona_vector1<std::string> _confatigue;
inline elona_vector1<std::string> _quality;
inline elona_vector1<std::string> _resist;
inline elona_vector1<std::string> _mark;
inline elona_vector1<std::string> _sex;
inline elona_vector1<std::string> _sex2;
inline elona_vector1<std::string> _onii;
inline elona_vector1<std::string> _syujin;
inline std::string strhint1;
inline std::string strhint2;
inline std::string strhint3;
inline std::string strhint3b;
inline std::string strhint4;
inline std::string strhint5;
inline std::string strhint5b;
inline std::string strhint6;
inline std::string strhint7;
inline std::string strmale;
inline std::string strfemale;
inline std::string strbye;
inline std::string strmore;
inline std::string strnogold;
inline std::string strinteractfail;
inline elona_vector1<std::string> invtitle;
inline elona_vector1<std::string> actlistn;
inline elona_vector1<std::string> _cast;
inline elona_vector2<std::string> _melee;
inline elona_vector1<int> randcolor;
inline elona_vector1<int> _randcolor;
inline elona_vector1<std::string> _namepotion;
inline elona_vector1<std::string> _namespellbook;
inline elona_vector1<std::string> _namescroll;
inline elona_vector1<std::string> _namestaff;
inline elona_vector1<std::string> _namering;
inline std::string homepage;
inline std::string strcursed;
inline std::string strblessed;
inline std::string stramulet;
inline std::string strring;
inline std::string strpotion;
inline std::string strspellbook;
inline std::string strscroll;
inline std::string strstaff;
inline std::string strbracketleft;
inline std::string strbracketright;
inline std::string strfix;
inline std::string strsex;
inline std::string strdoomed;
inline std::string strgold;
inline std::string strplat;
inline std::string strweight;
inline std::string stryes;
inline std::string strno;
inline std::string strblank;
void text_set();
// prm_348 :: int
inline int efid;
std::string elename(int = 0);
void txttargetlevel();
// prm_349 :: string
std::string sncnv(std::string&);
// prm_350 :: string
void sngeneral(std::string&);
// prm_351 :: string
void sninn(std::string&);
// prm_352 :: string
void sntrade(std::string&);
// prm_353 :: string
void sngoods(std::string&);
// prm_354 :: string
void snbakery(std::string&);
// prm_355 :: string
void snmagic(std::string&);
// prm_356 :: string
void snarmor(std::string&);
// prm_357 :: string
void sntrainer(std::string&);
// prm_358 :: string
void snfish(std::string&);
// prm_359 :: string
void snblack(std::string&);
// prm_360 :: string
void snfood(std::string&);
inline std::string lastword;
void txtsetlastword();
// prm_361 :: int
inline elona_vector1<int> i;
inline elona_vector1<int> p;
void txtsetwinword(int = 0);
// prm_362 :: int
// prm_363 :: int
int limitmax(int = 0, int = 0);
inline elona_vector2<std::string> mapnamerd;
void label_0140();
std::string maplevel(int = 0);
// prm_365 :: int
std::string mapfile(int = 0);
// prm_366 :: int
// prm_367 :: int
std::string mapname(int = 0, int = 0);
// prm_368 :: int
// prm_369 :: int
inline int p_at_m32;
inline std::string s_at_m32;
std::string txtbuilding(int = 0, int = 0);
// prm_370 :: int
// prm_371 :: int
// prm_372 :: int
std::string txtskillchange(int = 0, int = 0, int = 0);
// prm_373 :: int
// prm_374 :: string
// prm_375 :: int
// prm_376 :: int
inline std::string s_at_m33;
inline std::string n_at_m33;
std::string refchara_str(int = 0, int = 0);
inline int p_at_m33;
std::string foodname(int, const std::string&, int = 0, int = 0);
inline elona_vector2<int> picfood;
void label_0149();
// prm_377 :: int
inline elona_vector1<std::string> _tone_at_m34;
inline int p_at_m34;
std::string _yoro(int = 0);
// prm_378 :: int
std::string _dozo(int = 0);
// prm_379 :: int
std::string _thanks(int = 0);
// prm_380 :: int
std::string _rob(int = 0);
// prm_381 :: int
std::string _ka(int = 0);
// prm_382 :: int
std::string _da(int = 0);
// prm_383 :: int
std::string _nda(int = 0);
// prm_384 :: int
std::string _noka(int = 0);
// prm_385 :: int
std::string _kana(int = 0);
// prm_386 :: int
std::string _kimi(int = 0);
// prm_387 :: int
std::string _ru(int = 0);
// prm_388 :: int
std::string _tanomu(int = 0);
// prm_389 :: int
std::string _ore(int = 0);
// prm_390 :: int
std::string _ga(int = 0);
// prm_391 :: int
std::string _dana(int = 0);
// prm_392 :: int
std::string _kure(int = 0);
// prm_393 :: int
std::string _daro(int = 0);
// prm_394 :: int
std::string _yo(int = 0);
// prm_395 :: int
std::string _aru(int = 0);
// prm_396 :: int
std::string _u(int = 0);
// prm_397 :: int
std::string _na(int = 0);
// prm_398 :: int
std::string _ta(int = 0);
inline int talkref;
void label_0173();
void label_0174();
inline elona_vector1<std::string> valn;
void label_0175();
void label_0176();
// prm_399 :: int
inline std::string s_at_m35;
std::string cnvweight(int = 0);
// prm_400 :: int
std::string fltname(int = 0);
inline elona_vector1<std::string> s1;
void label_0180();
inline elona_vector1<int> val;
void label_0181();
void label_0182();
inline elona_vector1<std::string> buffboard;
inline elona_vector1<std::string> buff2;
void label_0183();
inline elona_vector2<int> qdata;
inline int rq;
inline std::string nquestdate;
std::string cnvitemname(int = 0);
inline elona_vector1<std::string> qname;
inline elona_vector1<int> iorgweight;
void label_0185();
void label_0184();
// prm_401 :: string
// prm_402 :: int
inline std::string n_at_m36;
inline elona_vector1<std::string> newsbuff;
void addnews2(const std::string&, int = 0);
// prm_403 :: string
// prm_404 :: string
void addnewstopic(const std::string&, const std::string&);
// prm_405 :: int
// prm_406 :: int
void addnews(int = 0, int = 0);
// prm_407 :: int
// prm_408 :: int
void txtgod(int = 0, int = 0);
inline int time_warn;
inline int time_begin;
void label_2140();
inline elona_vector1<int> rtval;
inline elona_vector1<std::string> rtvaln;
inline elona_vector1<std::string> key_select;
void label_2714();
void label_2715();
void label_2716();
void label_1415();
inline int cfg_fullscreen;
inline int windowx;
inline int windowy;
// label_2125 :: unknown
// onkey_0 :: unknown
inline int cnt2;
inline elona_vector1<int> x;
inline int inf_tiles;
inline elona_vector2<int> initeq;
inline elona_vector2<int> cmapdata;
inline elona_vector1<int> fixeditemenc;
inline elona_vector1<int> dir;
inline elona_vector2<int> dblist;
inline elona_vector1<int> unlist;
inline elona_vector1<std::string> csv;
inline elona_vector1<std::string> filemod;
inline elona_vector1<std::string> csvbuff;
inline elona_vector1<std::string> csvidx;
inline elona_vector1<std::string> inputlog;
inline elona_vector1<std::string> msgref;
inline elona_vector1<std::string> randn1;
inline elona_vector1<std::string> randn2;
inline elona_vector1<std::string> select;
inline elona_vector1<int> n;
inline elona_vector2<int> list;
inline elona_vector2<std::string> listn;
inline elona_vector1<int> invctrl;
inline elona_vector2<std::string> promptl;
inline elona_vector1<std::string> description;
inline elona_vector1<std::string> file;
inline elona_vector2<int> mef;
inline elona_vector1<int> genetemp;
inline elona_vector1<std::string> gdatan;
inline elona_vector1<int> mdatatmp;
inline elona_vector1<std::string> mdatan;
inline elona_vector1<int> spell;
inline elona_vector1<int> mat;
inline elona_vector2<int> itemmemory;
inline elona_vector2<int> npcmemory;
inline elona_vector1<int> recipememory;
inline elona_vector1<int> invmark;
inline elona_vector1<int> commark;
inline elona_vector1<int> feat;
inline elona_vector1<std::string> iname;
inline elona_vector2<int> dirchk;
inline elona_vector1<int> chatval;
inline elona_vector1<int> matneed;
inline elona_vector2<int> pcc;
inline int maxrain;
inline elona_vector1<int> rainx;
inline elona_vector1<int> rainy;
inline elona_vector1<std::string> fltnrace;
inline elona_vector2<int> card;
inline elona_vector1<int> deck;
void label_0478();
inline elona_vector2<int> rdata;
inline elona_vector1<int> idata;
inline elona_vector2<int> dirxy;
inline elona_vector1<int> val_skill;
inline elona_vector1<std::string> valn_skill;
inline elona_vector1<int> cs_posbk;
inline elona_vector1<int> floorstack;
inline elona_vector1<std::string> key_list;
inline elona_vector1<std::string> playerheader;
inline elona_vector1<std::string> artifactlocation;
inline elona_vector2<int> slight;
inline int inf_screenw;
inline int inf_screenh;
inline elona_vector2<int> slightbk;
inline std::string msg_log;
// fmode :: int | string
int label_2107();
inline elona_vector1<std::string> filter_item;
inline elona_vector1<std::string> rffilter_item;
inline elona_vector1<std::string> iknownnameref;
inline elona_vector1<std::string> ialphanameref;
inline elona_vector1<int> irandomname;
inline elona_vector1<int> icolref;
inline elona_vector1<int> keybd_st;
inline elona_vector1<int> trate;
inline elona_vector1<std::string> filtern;
inline elona_vector1<std::string> filter_creature;
inline elona_vector1<std::string> netbuf;
void label_2110();
void label_2111();
void label_2296();
void label_2655();
void label_1276();
void label_0202();
void label_1752();
void label_1618();
void label_0221();
void label_1883();
void label_1277();
void label_0262();
void label_0258();
void label_0246();
void label_1572();
void label_1921();
void label_0268();
void label_1713();
void label_2105();
inline elona_vector1<int> mainskill;
inline elona_vector2<int> cycle;
inline elona_vector1<std::string> cyclekey;
inline elona_vector1<int> cyclemax;
inline elona_vector1<int> shadowmap;
inline int lastctrl;
inline elona_vector1<int> invicon;
inline elona_vector1<std::string> invkey;
inline int cfg_autonumlock;
void label_2731();
inline int ieopen;
inline int ie_event;
inline int ie;
inline int mutex_handle;
// end :: unknown
void label_0193();
// prm_409 :: int
// prm_410 :: int
inline int i_at_m38;
inline int body_at_m38;
void label_0196();
void create_pcpic(int = 0, int = 0);
inline int p_at_m38;
// prm_411 :: int
// prm_412 :: int
// prm_413 :: int
// prm_414 :: int
// prm_415 :: int
// prm_416 :: int
inline elona_vector3<int> efmap;
void addefmap(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
inline elona_vector2<int> cloud;
void label_0200();
inline elona_vector2<int> chipm;
void label_0201();
inline elona_vector2<int> mefsubref;
inline elona_vector2<int> lightdata;
inline elona_vector1<std::string> tname;
inline elona_vector2<int> chipc;
inline elona_vector2<int> chipi;
inline elona_vector2<int> deco;
// prm_417 :: int
// prm_418 :: int
inline elona_vector2<int> cardplayer_at_cardcontrol;
inline int cardplayermax_at_cardcontrol;
inline int cardholdermax_at_cardcontrol;
void cardplayerinit(int = 0, int = 0);
// prm_419 :: int
// prm_420 :: int
// prm_421 :: int
void cardplayeradd(int = 0, int = 0, int = 0);
// prm_422 :: int
// prm_423 :: int
inline int pilex_at_cardcontrol;
inline int piley_at_cardcontrol;
inline elona_vector2<int> card_at_cardcontrol;
inline int cardmax_at_cardcontrol;
inline int nojoker;
inline elona_vector1<int> i_at_cardcontrol;
inline elona_vector1<int> p_at_cardcontrol;
void initcard(int = 0, int = 0, int = 0);
// prm_425 :: int
// prm_426 :: int
inline elona_vector1<int> col_at_cardcontrol;
inline std::string s_at_cardcontrol;
inline int tx_at_cardcontrol;
void showcard2(int = 0, int = 0);
inline int pilestack_at_cardcontrol;
void showcardpile();
void showcard();
// prm_427 :: int
inline int cardid_at_cardcontrol;
inline int dx_at_cardcontrol;
inline int dy_at_cardcontrol;
int servecard(int = 0);
void showcardholder();
// prm_428 :: int
// prm_429 :: int
int opencard2(int = 0, int = 0);
// prm_430 :: int
int trashcard(int = 0);
// prm_431 :: int
inline int ace_at_cardcontrol;
inline int c_at_cardcontrol;
int cpscore(int = 0);
// prm_432 :: int
int lastcard(int = 0);
// prm_433 :: int
int cpblackcard(int = 0);
// prm_434 :: int
int cpcardnum(int = 0);
int pileremain();
// prm_436 :: string
// prm_437 :: int
inline elona_vector1<int> p_at_m40;
// prm_435 :: elona_vector1<string>
inline int csvmax;
inline std::string titlebuff;
inline elona_vector2<std::string> rnlist;
// csvsort :: unknown
inline elona_vector1<std::string> rn1;
inline elona_vector1<std::string> rn2;
inline std::string s_at_m41;
inline elona_vector1<int> p_at_m41;
std::string label_0225();
// prm_439 :: int
inline elona_vector1<std::string> randn2_at_m41;
inline int rtval_at_m41;
inline elona_vector1<std::string> s2_at_m41;
std::string random_title(int = 0);
inline int hour_played;
void label_0230();
// prm_440 :: int
// prm_442 :: int
// prm_441 :: elona_vector1<int>
inline int p_at_m42;
inline int f_at_m42;
// prm_443 :: int
inline int objlv_at_m43;
inline int p_at_m43;
int calcobjlv(int = 0);
// prm_444 :: int
inline int fixlv_at_m43;
int calcfixlv(int = 0);
// prm_445 :: int
// prm_446 :: int
inline int filtermax;
inline int fltselect;
inline int flttypemajor;
inline int flttypeminor;
inline int objlv;
inline int fixlv;
void flt(int = 0, int = 0);
// prm_447 :: string
inline std::string s2_at_m44;
inline int p_at_m44;
void fltn(const std::string&);
int discsetmc();
inline elona_vector1<int> fsetrare;
inline elona_vector1<int> fsetwear;
inline elona_vector1<int> fsetitem;
inline int p_at_m45;
inline int i_at_m45;
int randomele();
// prm_448 :: int
void putenclv(int = 0);
// prm_449 :: int
// prm_450 :: int
int encflt(int = 0, int = 0);
inline elona_vector2<int> encref;
inline elona_vector2<int> enclist;
inline elona_vector2<int> encammoref;
inline elona_vector1<std::string> ammoname;
inline elona_vector2<int> encprocref;
inline int sid;
void label_0247();
// prm_451 :: int
inline int sum_at_m47;
inline int max_at_m47;
inline int reftype;
inline int i_at_m47;
inline elona_vector1<int> p_at_m47;
int randomenc(int = 0);
// prm_452 :: int
inline int enclv_at_m47;
int randomenclv(int = 0);
// prm_453 :: int
inline int encp_at_m47;
int randomencp(int = 0);
// prm_454 :: int
inline int f_at_m47;
inline int cnt2_at_m47;
void sortenc(int = 0);
// prm_455 :: int
// prm_456 :: int
// prm_457 :: int
inline int enc_at_m48;
inline int encp_at_m48;
inline int p_at_m48;
void encremove(int = 0, int = 0, int = 0);
// prm_458 :: int
// prm_459 :: int
// prm_460 :: int
// prm_461 :: int
// prm_462 :: int
// prm_463 :: int
// prm_464 :: int
inline int sum_at_m48;
inline int max_at_m48;
inline int i_at_m48;
int encadd(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_465 :: int
// prm_466 :: int
inline elona_vector2<int> egoenc;
void egoadd(int = 0, int = 0);
inline elona_vector1<std::string> egoname;
inline elona_vector2<int> egoref;
inline elona_vector1<int> egolist;
inline elona_vector1<std::string> egominorn;
inline int maxegominorn;
inline int ci;
inline int egolv;
void label_0259();
void label_0260();
inline int reftypeminor;
void label_0261();
inline elona_vector2<std::string> mtname;
inline elona_vector2<int> mtref;
inline elona_vector2<int> mtenc;
inline elona_vector2<int> mtbit;
inline elona_vector2<int> mtlistmetal;
inline elona_vector2<int> mtlistleather;
void label_0264();
void label_0266();
void label_0263();
inline int cm;
inline int mtlv;
inline int rc;
inline int mode;
inline int objfix;
inline int originalvalue;
inline int fixmaterial;
void label_1583();
inline int r1;
void label_1477();
void label_0265();
void label_0267();
inline elona_vector2<int> fishdata;
inline elona_vector1<std::string> fishdatan;
// prm_467 :: int
// prm_468 :: int
// prm_469 :: int
// prm_470 :: int
// prm_471 :: int
inline int itemcreatehack;
inline int initnum;
int label_1582();
int itemcreate(int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_472 :: int
inline int invhead;
inline int invrange;
void inv_getheader(int = 0);
// prm_473 :: int
int inv_getowner(int = 0);
// prm_474 :: int
// prm_475 :: int
inline int f_at_m52;
int inv_find(int = 0, int = 0);
// prm_476 :: int
// prm_477 :: int
// prm_478 :: int
inline elona_vector1<int> p_at_m52;
int item_find(int = 0, int = 0, int = 0);
// prm_479 :: int
// prm_480 :: int
inline int f_at_m53;
inline int i_at_m53;
int encfind(int = 0, int = 0);
// prm_481 :: int
// prm_482 :: int
int encfindspec(int = 0, int = 0);
// prm_483 :: int
// prm_484 :: int
inline int listmax;
void itemlist(int = 0, int = 0);
// prm_485 :: int
// prm_486 :: int
inline int f_at_m54;
int itemusingfind(int = 0, int = 0);
// prm_487 :: int
// prm_488 :: int
// prm_489 :: int
int itemfind(int = 0, int = 0, int = 0);
// prm_490 :: int
// prm_491 :: int
// prm_492 :: int
int mapitemfind(int = 0, int = 0, int = 0);
// prm_493 :: int
// prm_494 :: int
inline int p_at_m55;
inline elona_vector3<int> map;
inline elona_vector1<int> ilight;
inline elona_vector1<int> n_at_m55;
inline int cnt2_at_m55;
inline int i_at_m55;
void cell_refresh(int = 0, int = 0);
// prm_495 :: int
void itemturn(int = 0);
// prm_496 :: int
// prm_497 :: int
inline int n_at_m56;
void label_1521();
void removeitem(int = 0, int = 0);
// prm_498 :: int
// prm_499 :: int
void item_copy(int = 0, int = 0);
// prm_500 :: int
// prm_501 :: int
inline elona_vector1<int> p_at_m57;
void item_exchange(int = 0, int = 0);
// prm_502 :: int
void item_delete(int = 0);
// prm_503 :: int
int inv_getspace(int = 0);
// prm_504 :: int
int inv_sum(int = 0);
void item_compress(int = 0);
// prm_506 :: int
int inv_getfreeid(int = 0);
// prm_507 :: int
int inv_weight(int = 0);
// prm_508 :: int
// prm_509 :: int
void item_num(int = 0, int = 0);
// prm_510 :: int
inline int ti_at_m59;
int item_separate(int&);
// prm_511 :: int
inline int p_at_m59;
inline int c_at_m59;
int chara_unequip(int = 0);
// prm_512 :: int
// prm_513 :: int
// prm_514 :: int
inline int idlv_at_m60;
inline int idtresult;
int item_identify(int = 0, int = 0, int = 0);
// prm_515 :: int
void item_checkknown(int = 0);
// prm_516 :: int
inline std::string s_at_m62;
inline elona_vector1<std::string> rpdatan;
std::string rpname(int = 0);
// prm_518 :: int
inline std::string s_at_m63;
inline int a_at_m63;
inline int skip_at_m63;
void label_0311();
// prm_519 :: int
// prm_520 :: int
inline int itemnamehack;
inline int maxitemid;
inline elona_vector1<int> iqiality_at_m63;
inline int num2_at_m63;
inline std::string s2_at_m63;
inline std::string s3_at_m63;
inline int alpha_at_m63;
inline std::string s4_at_m63;
inline int len_at_m63;
inline elona_vector1<std::string> buf_at_m63;
inline int ret_at_m63;
std::string itemname(int = 0, int = 0, int = 0);
// prm_521 :: int
// prm_522 :: int
int refchara(int = 0, int = 0);
void remain_make(int = 0, int = 0);
// prm_523 :: int
// prm_524 :: int
void make_dish(int = 0, int = 0);
// prm_525 :: int
// prm_526 :: int
// prm_527 :: int
inline elona_vector1<int> p_at_m65;
inline int ti;
int item_stack(int = 0, int = 0, int = 0);
inline int i_at_m66;
void colorres(int = 0);
// prm_529 :: int
// prm_530 :: int
// prm_531 :: int
inline int p_at_m66;
inline std::string s_at_m66;
void equipinfo(int = 0, int = 0, int = 0);
// prm_533 :: string
inline std::string word_at_m67;
inline int p_at_m67;
inline int i_at_m67;
// prm_532 :: elona_vector1<string>
int cargocheck();
inline int p_at_m68;
// prm_534 :: elona_vector1<T>
inline int r_at_m68;
// i_at_m68 :: T
// prm_535 :: int
// prm_536 :: int
// prm_537 :: int
// prm_538 :: int
inline int d_at_m69;
int dist(int = 0, int = 0, int = 0, int = 0);
// prm_539 :: int
// prm_540 :: int
int winposy(int = 0, int = 0);
// prm_541 :: string
// prm_542 :: int
inline int len_at_m71;
inline elona_vector1<std::string> buf_at_m71;
inline int ret_at_m71;
inline int p_at_m71;
void cutname(std::string&, int = 0);
// prm_543 :: string
// prm_544 :: int
// prm_545 :: int
// prm_546 :: int
// prm_547 :: int
// prm_548 :: int
// prm_549 :: int
inline int cs;
inline int tx_at_m72;
inline int cs_bk;
void cs_listbk();
void gohostile();
// prm_550 :: int
// prm_551 :: int
inline int a_at_m74;
inline int max_at_m74;
void modkarma(int = 0, int = 0);
// prm_552 :: int
// prm_553 :: int
// prm_554 :: int
inline elona_vector1<int> p_at_m75;
inline int orgrank_at_m75;
inline int i_at_m75;
inline std::string s_at_m75;
std::string ranktitle(int = 0);
void modrank(int = 0, int = 0, int = 0);
// prm_555 :: int
// prm_556 :: int
int sexp(int = 0, int = 0);
// prm_557 :: int
// prm_558 :: int
int sgrowth(int = 0, int = 0);
// prm_559 :: int
// prm_560 :: int
// prm_561 :: int
inline int growth_at_m76;
void modgrowth(int = 0, int = 0, int = 0);
// prm_562 :: int
// prm_563 :: int
// prm_564 :: int
// prm_565 :: int
inline int lv_at_m76;
void skillgain(int = 0, int = 0, int = 0, int = 0);
// prm_566 :: int
// prm_567 :: int
// prm_568 :: int
inline int lv_at_m77;
inline int exp_at_m77;
inline int growth_at_m77;
inline int lvchange_at_m77;
int skillmod(int = 0, int = 0, int = 0);
// prm_569 :: int
// prm_570 :: int
// prm_571 :: int
// prm_572 :: int
// prm_573 :: int
int skillexp(int = 0, int = 0, int = 0, int = 0, int = 0);
inline int exp2_at_m77;
// prm_574 :: int
// prm_575 :: int
inline int p_at_m77;
int calcfame(int = 0, int = 0);
// prm_576 :: int
// prm_577 :: int
int decfame(int = 0, int = 0);
// prm_578 :: int
// prm_579 :: int
inline int p_at_m78;
int getworker(int = 0, int = 0);
// prm_580 :: int
void removeworker(int = 0);
int calcshopreform();
// prm_581 :: int
inline int i_at_m79;
void delmef(int = 0);
// prm_582 :: int
// prm_583 :: int
// prm_584 :: int
// prm_585 :: int
// prm_586 :: int
// prm_587 :: int
// prm_588 :: int
// prm_589 :: int
// prm_590 :: int
// prm_591 :: int
inline int p_at_m79;
void addmef(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_592 :: int
// prm_593 :: int
// prm_594 :: int
// prm_595 :: int
// prm_596 :: int
// prm_597 :: int
inline elona_vector1<int> feat_at_m80;
void cell_featset(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_598 :: int
// prm_599 :: int
int cell_featread(int = 0, int = 0, int = 0);
// prm_601 :: int
// prm_602 :: int
void cell_featclear(int = 0, int = 0);
// prm_603 :: int
// prm_604 :: int
inline int cellaccess;
inline int cellchara;
inline int cellfeat;
void cell_check(int = 0, int = 0);
// prm_605 :: int
// prm_606 :: int
// prm_607 :: int
// prm_608 :: int
inline int tc_at_m81;
inline int x2_at_m81;
inline int y2_at_m81;
void cell_swap(int = 0, int = 0, int = 0, int = 0);
// prm_609 :: int
// prm_610 :: int
// prm_611 :: int
inline int rc_at_m81;
void cell_movechara(int = 0, int = 0, int = 0);
// prm_612 :: int
// prm_613 :: int
// prm_614 :: int
inline elona_vector2<int> route;
inline int maxroute;
inline int scx;
inline int scy;
int route_info(int&, int&, int = 0);
inline elona_vector2<int> breathlist;
inline int maxbreath;
inline int breathw;
inline int ty;
inline int tx;
int breath_list();
// prm_615 :: int
// prm_616 :: int
// prm_617 :: int
void draw_emo(int = 0, int = 0, int = 0);
// prm_618 :: int
// prm_619 :: int
inline int p_at_m83;
inline int selcur;
void chara_preparepic(int = 0, int = 0);
inline int syfix_at_m85;
inline int scybk;
inline int syfix;
inline int sxfix_at_m85;
inline int scxbk;
inline int sxfix;
inline int scrturn_at_m85;
inline int scrturnbk_at_m85;
inline int scrturnnew_at_m85;
inline int light_at_m85;
inline int flick_at_m85;
inline elona_vector1<int> repw;
inline elona_vector1<int> reph;
inline int dy_at_m85;
inline int inf_screeny;
inline int ly_at_m85;
inline int y_at_m85;
inline int dx_at_m85;
inline int inf_screenx;
inline int lx_at_m85;
inline int inf_verh;
inline int sx_at_m85;
inline elona_vector1<int> p_at_m85;
inline elona_vector1<int> tile_fog;
inline int x_at_m85;
inline int px_at_m85;
inline int py_at_m85;
inline int ground_at_m85;
inline int ani_at_m85;
inline elona_vector1<int> fishanime;
inline int sel_at_m85;
inline int wall_at_m85;
inline int p2_at_m85;
inline int i_at_m85;
inline elona_vector1<int> flooritem_at_m85;
inline int stackh_at_m85;
inline int cnt2_at_m85;
inline int cfg_objectshadow;
inline int c_at_m85;
inline int col_at_m85;
inline int h_at_m85;
inline int inf_very;
inline int cfg_shadow;
inline int scrollanime;
inline int scrollp;
inline int deco2;
inline int f_at_m85;
void cell_draw();
// prm_625 :: int
// prm_626 :: int
int cell_itemlist(int = 0, int = 0);
// prm_627 :: int
// prm_628 :: int
int cell_itemoncell(int = 0, int = 0);
// prm_629 :: int
// prm_630 :: int
// prm_631 :: int
// prm_632 :: int
inline int dy_at_modfov;
inline int dx_at_modfov;
inline int ay_at_modfov;
inline int ax_at_modfov;
inline int ty_at_modfov;
inline int tx_at_modfov;
inline int sx_at_modfov;
inline int sy_at_modfov;
inline int f2_at_modfov;
inline int f1_at_modfov;
inline int qy_at_modfov;
inline int m_at_modfov;
inline int qx_at_modfov;
int label_0397();
int fov_los(int = 0, int = 0, int = 0, int = 0);
// prm_633 :: int
// prm_634 :: int
// prm_635 :: int
// prm_636 :: int
inline int p_at_modfov;
int label_0410();
int get_route(int = 0, int = 0, int = 0, int = 0);
// prm_637 :: string
// prm_638 :: int
// prm_639 :: int
void display_customkey(const std::string&, int = 0, int = 0, int = 0);
// prm_641 :: int
// prm_642 :: int
// prm_643 :: int
void display_key(int = 0, int = 0, int = 0);
inline int keyrange;
void cursor_check();
// prm_644 :: string
// prm_645 :: int
inline int p_at_m89;
void lenfix(std::string&, int = 0);
// prm_646 :: int
// prm_647 :: int
// prm_648 :: int
// prm_649 :: int
inline elona_vector1<int> windowshadow;
inline int x_at_m91;
inline int y_at_m91;
inline int x3_at_m91;
inline int y3_at_m91;
inline int cnt2_at_m91;
inline int sizefix;
inline int pagesize;
inline int page;
inline int pagemax;
void showscroll(int = 0, int = 0, int = 0, int = 0);
// prm_650 :: int
// prm_651 :: int
// prm_652 :: int
// prm_653 :: int
// prm_655 :: int
inline int dx_at_m92;
inline int dy_at_m92;
inline int x3_at_m92;
inline int y3_at_m92;
inline int p_at_m92;
inline int cnt2_at_m92;
void window(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_656 :: int
// prm_657 :: int
// prm_658 :: int
// prm_659 :: int
// prm_660 :: int
// prm_661 :: int
inline int dx_at_m93;
inline int dy_at_m93;
inline int x2_at_m93;
inline int y2_at_m93;
inline int x3_at_m93;
inline int y3_at_m93;
inline int p_at_m93;
void window2(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_662 :: int
// prm_663 :: int
// prm_664 :: int
// prm_665 :: int
// prm_666 :: int
// prm_667 :: int
void display_window2(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_668 :: int
// prm_669 :: int
// prm_670 :: int
// prm_671 :: int
// prm_672 :: int
// prm_673 :: int
inline int vfix;
inline int ww;
inline elona_vector1<int> wh;
void display_window(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_674 :: string
// prm_675 :: int
void display_note(const std::string&, int = 0);
// prm_676 :: string
// prm_677 :: int
// prm_678 :: int
void display_topic(const std::string&, int = 0, int = 0, int = 0);
// prm_680 :: int
// prm_681 :: int
inline int msgkeep;
inline int msgclear;
inline int msgy;
void label_1424();
void display_msg(int = 0, int = 0);
// prm_685 :: string
inline elona_vector1<int> crlfs_at_crlf;
inline int crlftype_at_crlf;
inline int i_at_crlf;
inline std::string tmpbuf_at_crlf;
inline int len_at_crlf;
inline std::string tmpstr_at_crlf;
void rm_crlf(std::string&);
// prm_686 :: int
// prm_687 :: int
// prm_688 :: int
inline int d_at_m97;
int role(int = 0, int = 0, int = 0);
// prm_689 :: int
// prm_690 :: int
// prm_691 :: int
int rolemax(int = 0, int = 0, int = 0);
inline int pagebk;
inline int csprev;
inline int pagesaved;
void page_save();
void page_load();
// prm_692 :: string
// prm_693 :: int
inline elona_vector1<std::string> q_at_m98;
inline int p_at_m98;
inline std::string a_at_m98;
void fileadd(const std::string&, int = 0);
inline std::string tmp;
inline int fread;
inline int fidx;
inline int cdatanfix;
inline int tg;
// invn :: unknown
inline int elona_export;
void arrayfile();
// prm_694 :: string
// prm_695 :: string
inline std::string s_at_m99;
std::string del_str(const std::string&, const std::string&);
// prm_696 :: string
// prm_697 :: string
// prm_698 :: string
inline std::string s3_at_m100;
inline int p_at_m100;
std::string cnv_str(std::string&, const std::string&, const std::string&);
// prm_699 :: ref<string>
void fix_wish(std::string&);
// prm_700 :: ref<string>
void fix_input_chat(std::string&);
// prm_701 :: ref<string>
void fix_input_chat2(std::string&);
// prm_702 :: ref<string>
void cnv_filestr(std::string&);
// prm_709 :: int
inline int himc_at_ime_control;
inline int hwnd;
void imeset(int = 0);
inline int imesw_at_ime_control;
int imeget();
// prm_711 :: int
// prm_713 :: string
// prm_714 :: string
inline int _stat_at_filedialog;
// _refstr_at_filedialog :: elona_vector1<int> | string | elona_vector1<int>
inline int p1_len_at_filedialog;
// prm_710 :: elona_vector1<T>
inline int p3_len_at_filedialog;
// prm_712 :: elona_vector1<T>
// szfilename_at_filedialog :: elona_vector1<int> | string | elona_vector1<int>
// szinitdir_at_filedialog :: elona_vector1<int> | string | elona_vector1<int>
inline std::string szappfilter_at_filedialog;
inline int start_at_filedialog;
inline int mutch_at_filedialog;
// ofn_at_filedialog :: elona_vector1<int> | string | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int> | elona_vector1<int>
// hinstance :: unknown
// prm_715 :: string
inline std::string m_at_m102;
inline std::string msg_at_m102;
inline int i_at_m102;
inline int xorg_at_m102;
inline int gmesx;
inline int size_at_m102;
inline elona_vector1<int> col_at_m102;
inline elona_vector1<int> gmescol;
inline int lim_at_m102;
inline int gmesw;
inline int p_at_m102;
inline int brwait_at_m102;
inline std::string s_at_m102;
inline int gmesy;
inline int gmestype;
void gmes(const std::string&);
// prm_716 :: int
// prm_717 :: int
// prm_718 :: int
// prm_719 :: int
void boxl(int = 0, int = 0, int = 0, int = 0);
// prm_724 :: string
// prm_725 :: int
inline std::string m_at_m104;
std::string fixtxt(const std::string&, int = 0);
// prm_726 :: int
// prm_727 :: int
// prm_728 :: int
// prm_729 :: int
// prm_730 :: int
// prm_731 :: int
inline int nowindowanime;
inline int cfg_windowanime;
inline int x2_at_m105;
inline int y2_at_m105;
inline int cenx_at_m105;
inline int ceny_at_m105;
void windowanime(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_732 :: int
// prm_733 :: int
// prm_734 :: int
// prm_735 :: int
// prm_736 :: int
// prm_737 :: int
void windowanimecorner(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_739 :: string
// prm_740 :: int
inline int x_at_m106;
inline int y_at_m106;
void showtitle(const std::string&, const std::string&, int = 0, int = 0);
// prm_742 :: int
inline int y_at_m107;
inline elona_vector1<int> x_at_m107;
inline int menucycle;
inline int curmenu;
void drawmenu(int = 0);
// prm_743 :: int
// prm_744 :: int
// prm_745 :: int
// prm_746 :: int
// prm_747 :: int
inline int inf_ver;
inline int cnt2_at_m108;
void fillbg(int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_748 :: int
// prm_749 :: int
// prm_750 :: int
// prm_751 :: int
int direction(int = 0, int = 0, int = 0, int = 0);
inline elona_vector1<int> matval;
inline elona_vector2<int> matref;
inline elona_vector2<int> matspot;
inline elona_vector1<std::string> matname;
inline elona_vector1<std::string> matdesc;
inline int f_at_m110;
inline elona_vector1<int> j_at_m110;
int prodcheck();
int label_1275();
inline int dbmax;
inline int dbsum;
inline int dbtmp;
inline int ichargelevel;
inline std::string infilterref;
int label_2163();
inline int efp;
int label_2169();
int label_2164();
int label_2171();
void label_22712();
int label_2170();
inline elona_vector1<int> isetfruit;
inline elona_vector1<int> ipicref;
// prm_752 :: int
inline int pierce;
inline elona_vector1<int> rangemap;
int calcweaponfix(int = 0);
inline int matid;
int label_1280();
// prm_753 :: int
inline int p_at_m112;
inline int i_at_m112;
void fixaiact(int = 0);
// prm_754 :: int
// prm_755 :: int
int eleinfo(int = 0, int = 0);
// prm_756 :: int
// prm_757 :: int
// prm_758 :: int
// prm_759 :: int
inline int characreatehack;
inline int cxinit;
inline int cyinit;
int label_1533();
inline int initlv;
inline int voidlv;
void label_1532();
int characreate(int = 0, int = 0, int = 0, int = 0);
// prm_760 :: int
int relationbetween(int = 0, int = 0);
// prm_762 :: int
// prm_763 :: int
void rowactend(int = 0);
// prm_764 :: int
// prm_765 :: int
inline int f_at_m116;
inline elona_vector1<std::string> buff_at_m116;
inline elona_vector1<std::string> usertxt;
inline std::string s_at_m116;
inline int p_at_m116;
void label_2299();
int customtalk(int = 0, int = 0);
// prm_766 :: int
inline int p_at_m117;
int findchara(int = 0);
// prm_767 :: int
int findally(int = 0);
// prm_768 :: int
int implevel(int = 0);
// prm_769 :: int
// prm_770 :: int
inline elona_vector1<int> p_at_m118;
inline int i_at_m118;
void modimp(int = 0, int = 0);
void put_questtarget();
inline int f_at_m119;
int exist_questtarget();
inline int p_at_m119;
void check_quest();
// prm_771 :: int
inline int gspdorg;
inline int r_at_m120;
inline int gspd;
void refreshspeed(int = 0);
// prm_772 :: int
void ride_begin(int = 0);
inline int p_at_m121;
void ride_end();
// prm_773 :: int
void chara_vanquish(int = 0);
// prm_774 :: int
// prm_775 :: int
// prm_776 :: int
void turn_aggro(int = 0, int = 0, int = 0);
// prm_777 :: int
// prm_778 :: int
// prm_779 :: int
// prm_780 :: int
// prm_781 :: int
// prm_782 :: int
void make_sound(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
inline int f_at_m125;
int get_freechara();
int get_freeally();
// prm_783 :: int
void del_chara(int = 0);
// prm_784 :: int
// prm_785 :: int
// prm_786 :: int
inline int tc_at_m125;
inline int x_at_m125;
inline int y_at_m125;
inline int p1_at_m125;
inline int p2_at_m125;
inline int p3_at_m125;
inline int hp_at_m125;
inline int p_at_m125;
inline int invrangecc_at_m125;
inline int cnt2_at_m125;
void label_2666();
int relocate_chara(int = 0, int = 0, int = 0);
// prm_787 :: int
// prm_788 :: int
void hostileaction(int = 0, int = 0);
// prm_789 :: int
void rowact_check(int = 0);
// prm_790 :: int
void rowact_item(int = 0);
void wake_up();
void incognitobegin();
void incognitoend();
// prm_791 :: int
// prm_792 :: int
// prm_793 :: int
void cell_setchara(int = 0, int = 0, int = 0);
// prm_794 :: int
// prm_795 :: int
void cell_removechara(int = 0, int = 0);
// prm_796 :: int
// prm_797 :: int
// prm_798 :: int
inline int f_at_m130;
inline int dy_at_m130;
inline int dx_at_m130;
int cell_findspace(int = 0, int = 0, int = 0);
// prm_799 :: int
// prm_800 :: int
inline int f_at_m131;
int findbuff(int = 0, int = 0);
// prm_801 :: int
// prm_802 :: int
// prm_803 :: int
// prm_804 :: int
inline int p_at_m132;
inline int fixeddur_at_m132;
inline int f_at_m132;
int addbuff(int = 0, int = 0, int = 0, int = 0);
// prm_805 :: int
// prm_806 :: int
void delbuff(int = 0, int = 0);
// prm_807 :: int
// prm_808 :: int
inline int cfg_animewait;
inline int dx_at_m133;
inline elona_vector1<int> dy_at_m133;
inline elona_vector1<int> i_at_m133;
void animeload(int = 0, int = 0);
// prm_809 :: int
// prm_810 :: int
// prm_811 :: int
inline int ele2_at_m133;
inline elona_vector1<int> x_at_m133;
inline elona_vector1<int> y_at_m133;
inline int cnt2_at_m133;
void animeblood(int = 0, int = 0, int = 0);
// prm_812 :: int
// prm_813 :: int
// prm_814 :: int
inline int lv_at_m134;
void resistmod(int = 0, int = 0, int = 0);
// prm_815 :: int
inline int org_at_m134;
inline int p_at_m134;
inline int mod_at_m134;
inline int cfg_extrahelp;
inline int ghelp;
void label_2701();
inline int cnt2_at_m134;
inline int i_at_m134;
inline int body;
void label_2196();
void modcorrupt(int = 0);
// prm_816 :: int
// prm_817 :: int
void wet(int = 0, int = 0);
// prm_818 :: int
// prm_819 :: int
// prm_820 :: int
inline int f_at_con;
inline int res_at_con;
void label_1346();
inline int p_at_con;
// cbind_at_con :: unknown
int dmgcon(int = 0, int = 0, int = 0);
inline int r_at_con;
// prm_821 :: int
// prm_822 :: int
void healhp(int = 0, int = 0);
// prm_823 :: int
// prm_824 :: int
void healmp(int = 0, int = 0);
// prm_825 :: int
// prm_826 :: int
void healsp(int = 0, int = 0);
// prm_827 :: int
// prm_828 :: int
// prm_829 :: int
void healcon(int = 0, int = 0, int = 0);
// prm_830 :: int
// prm_831 :: int
// prm_832 :: int
inline int dx_at_m136;
inline int dy_at_m136;
void spillblood(int = 0, int = 0, int = 0);
// prm_833 :: int
// prm_834 :: int
// prm_835 :: int
void spillfrag(int = 0, int = 0, int = 0);
// prm_836 :: int
// prm_837 :: int
inline int p_at_m137;
void check_kill(int = 0, int = 0);
// prm_838 :: int
// prm_839 :: int
inline int ci_at_m138;
inline int body_at_m138;
inline int p_at_m138;
void item_acid(int = 0, int = 0);
// prm_840 :: int
// prm_841 :: int
inline int max_at_m138;
inline int ti_at_m138;
inline elona_vector1<int> list_at_m138;
inline int f_at_m138;
inline int a_at_m138;
int item_fire(int = 0, int = 0);
// prm_842 :: int
// prm_843 :: int
void mapitem_fire(int = 0, int = 0);
// prm_844 :: int
// prm_845 :: int
inline std::string s_at_m138;
int item_cold(int = 0, int = 0);
// prm_846 :: int
// prm_847 :: int
void mapitem_cold(int = 0, int = 0);
// prm_848 :: int
inline int c_at_m139;
inline int f_at_m139;
inline int y_at_m139;
inline int x_at_m139;
int copy_chara(int = 0);
// prm_849 :: int
// prm_850 :: int
// prm_851 :: int
// prm_852 :: int
void txteledmg(int = 0, int = 0, int = 0, int = 0);
// prm_853 :: int
// prm_854 :: int
// prm_855 :: int
// prm_856 :: int
// prm_857 :: int
inline int ele_at_m141;
inline int txt3rd;
inline int c3_at_m141;
void label_1370();
inline int dmg_at_m141;
inline int r_at_m141;
inline int critical;
inline int rtdmg;
inline int lasttc;
inline int dmglevel_at_m141;
inline int animeid;
inline int animode;
void label_1426();
inline int f_at_m141;
inline int pcnoise_at_m141;
inline int cfg_heart;
inline int se_at_m141;
inline elona_vector1<int> p_at_m141;
inline std::string ndeathcause;
inline elona_vector1<int> y;
inline int exp_at_m141;
inline int catitem;
inline int rollanatomy;
void label_1573();
inline int cc_at_m141;
int dmghp(int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_858 :: int
// prm_859 :: int
void label_1463();
inline int d_at_m142;
int dmgmp(int = 0, int = 0);
// prm_860 :: int
// prm_861 :: int
int dmgsp(int = 0, int = 0);
// prm_862 :: int
// prm_863 :: int
void healsan(int = 0, int = 0);
// prm_864 :: int
// prm_865 :: int
inline int r_at_m143;
inline int dmg_at_m143;
int dmgsan(int = 0, int = 0);
// prm_866 :: int
// prm_867 :: int
int actionsp(int = 0, int = 0);
// prm_868 :: int
inline int i_at_m145;
int advfavoriteskill(int = 0);
// prm_869 :: int
int advfavoritestat(int = 0);
// prm_870 :: int
// prm_871 :: int
// prm_872 :: int
inline int mini_at_m146;
inline int max_at_m146;
void modweight(int = 0, int = 0, int = 0);
// prm_873 :: int
// prm_874 :: int
void modheight(int = 0, int = 0);
// prm_875 :: int
void cure_anorexia(int = 0);
// prm_876 :: int
inline int p_at_m146;
void chara_vomit(int = 0);
// prm_877 :: int
// prm_878 :: int
void eatstatus(int = 0, int = 0);
// prm_879 :: int
int chara_anorexia(int = 0);
// prm_880 :: int
// prm_881 :: int
// prm_882 :: int
void sickifcursed(int = 0, int = 0, int = 0);
// prm_883 :: string
// prm_884 :: int
inline int cfg_net;
inline std::string chattemp;
inline std::string url_at_m147;
inline std::string chatsendurl;
inline std::string msg_at_m147;
inline std::string conurl_at_m147;
inline elona_vector1<std::string> cgiurl3;
inline std::string votesendurl;
inline elona_vector1<std::string> cgiurl2;
int net_send(const std::string&, int = 0);
// prm_885 :: int
inline std::string chatnew;
inline std::string textreadurl;
inline std::string chatreadurl;
inline std::string votereadurl;
inline std::string a_at_m147;
inline int sz_at_m147;
inline int t_at_m147;
inline int c_at_m147;
inline int b_at_m147;
int label_1394();
int net_read(int = 0);
inline int header_at_m147;
inline int tail_at_m147;
inline int chat_count_at_m147;
inline int count_latest_at_m147;
inline int lastchat;
inline std::string chat_date_at_m147;
inline std::string chat_msg_at_m147;
inline std::string chat_ip_at_m147;
// prm_886 :: string
// prm_887 :: int
inline std::string file_at_m147;
inline int size_at_m147;
inline int p_at_m147;
inline int f_at_m147;
inline int nxt_at_m147;
inline std::string s_at_m147;
int net_dllist(const std::string&, int = 0);
// prm_888 :: string
// prm_889 :: string
int net_dl(const std::string&, const std::string&);
inline elona_vector1<std::string> serverlist;
inline int cfg_serverlist;
void label_1398();
inline int chatdeny;
inline int chatturn;
void label_21262();
void label_1399();
inline int comctrl;
void label_2057();
inline int cmbg;
inline int cfg_wait1;
inline int promptmax;
inline int promptx;
inline int prompty;
int label_2131();
int label_14002();
inline int inf_clockarrowx;
inline int inf_clockx;
inline int inf_clockarrowy;
inline int inf_clocky;
inline int inf_barh;
inline int inf_msgh;
inline int inf_raderx;
inline int inf_raderw;
inline int inf_vertype;
inline int inf_bary;
inline int inf_clockh;
inline int inf_radery;
inline int scposy;
inline int inf_hpx;
inline int inf_hpy;
inline int inf_mpx;
inline int inf_mpy;
inline int screenmsgy;
void label_1416();
void label_14170();
void label_14180();
void label_14190();
void label_1417();
void label_1418();
inline elona_vector1<int> ap;
inline elona_vector1<int> sx;
inline elona_vector1<int> sy;
void label_1440();
inline int screendrawhack;
void label_1428();
void label_1429();
void label_1433();
void label_1421();
void label_1423();
inline int racount;
void label_1420();
// _conangryheavy :: unknown
inline int inf_clockw;
inline int ap3;
inline int ap2;
inline std::string skilltmps;
inline elona_vector1<int> rowactre;
void label_1422();
void label_1446();
inline int w;
inline int h;
inline int msgx;
void label_1425();
inline int anicol;
inline int anisound;
inline int anidx;
inline int anidy;
inline elona_vector1<int> ax;
inline elona_vector1<int> ay;
inline elona_vector1<int> ax2;
inline elona_vector1<int> ay2;
inline int acnt2;
inline int tlocx;
inline int tlocy;
inline int aniw;
inline int anih;
inline elona_vector1<int> anix;
inline int aniy;
inline elona_vector1<int> anip;
inline elona_vector1<int> aniref;
inline int attackskill;
inline int anic;
inline int am;
inline int af;
inline int scposval;
inline int scroll;
inline int camera;
inline int cfg_alwayscenter;
inline int ly;
inline int lx;
inline elona_vector2<int> fovlist;
inline int raderx;
inline int radery;
inline int losmode;
inline int cfg_env;
void label_1434();
void label_1435();
void label_1436();
void label_1437();
inline int s_p;
inline int weatherbk;
inline int scxbk2;
inline int scybk2;
void label_1438();
inline int raderw;
inline int raderh;
void label_1439();
void label_1441();
void label_1442();
void label_1443();
inline int evx;
inline int evy;
inline int evscry;
inline int evtiles;
inline int evscrh;
inline int evscrw;
void label_1445();
void label_1444();
inline elona_vector1<int> fishdir;
inline int fishx;
inline int fishy;
inline int sx2;
inline int sy2;
// prm_890 :: int
int carmor(int = 0);
// prm_891 :: int
std::string cnveqweight(int = 0);
// prm_892 :: int
int calcexpalive(int = 0);
void label_1452();
void label_1453();
inline int r2;
void label_1525();
void label_1455();
void label_1456();
void label_1454();
void label_1457();
void label_1458();
void label_1459();
void label_1460();
void label_1461();
void label_1462();
void label_1464();
void label_1465();
void label_1466();
void label_1467();
void label_1468();
void label_1469();
void label_1470();
void label_1471();
void label_1472();
// prm_893 :: int
inline int tohitorg;
inline int tohitfix;
inline int cw;
inline int ammo;
inline int tohit;
inline int attackrange;
inline int rangedist;
inline int tohi;
inline int attacknum;
inline int twohit;
inline int evade;
inline int evaderef;
int calcattackhit(int = 0);
// prm_894 :: int
inline int dmgfix;
inline int dmgmulti;
inline int damage;
inline int prot;
inline int prot2;
inline int protdice1;
inline int protdice2;
inline int protfix;
inline int orgdmg;
inline int ammoproc;
inline int damagepierce;
inline int damagenormal;
int calcattackdmg(int = 0);
// prm_895 :: int
// prm_896 :: int
void cnvbonus(int = 0, int = 0);
inline int chararefreshhack;
void label_2295();
inline int rp;
inline elona_vector2<int> userdata;
inline elona_vector2<int> cbitorg;
inline elona_vector2<int> racebit;
inline int rp2;
inline int rp3;
inline int refreshmode;
void label_1884();
// prm_897 :: int
int calcmedalvalue(int = 0);
// prm_898 :: int
// prm_899 :: int
inline int reftype_at_m153;
inline int value_at_m153;
inline int limitvalue_at_m153;
int calcitemvalue(int = 0, int = 0);
int calcinvestvalue(int = 0);
int calcguiltvalue(int = 0);
// prm_902 :: int
int calchireadv(int = 0);
// prm_903 :: int
int calchirecost(int = 0);
// prm_904 :: int
inline int p_at_m153;
void generatemoney(int = 0);
inline int cost_at_m153;
void calccosthire();
int calccostbuilding();
int calccosttax();
int calcmealvalue();
// prm_905 :: int
// prm_906 :: int
inline int ci_at_m153;
inline int enc_at_m153;
inline elona_vector1<int> i_at_m153;
int calccostreload(int = 0, int = 0);
int calccargoupdate();
int calccargoupdatecost();
// prm_907 :: int
int calcidentifyvalue(int = 0);
// prm_908 :: int
// prm_909 :: int
// prm_910 :: int
int calctraincost(int = 0, int = 0, int = 0);
// prm_913 :: int
int calclearncost(int = 0, int = 0, int = 0);
// prm_914 :: int
int calcresurrectvalue(int = 0);
// prm_915 :: int
int calcslavevalue(int = 0);
int calcrestorecost();
// prm_917 :: int
inline int lootrich_at_m155;
int calcinitgold(int = 0);
// prm_918 :: int
// prm_919 :: int
int calcspellpower(int = 0, int = 0);
// prm_920 :: int
// prm_921 :: int
inline int i_at_m157;
inline int f_at_m157;
inline int p_at_m157;
int calcspellfail(int = 0, int = 0);
// prm_922 :: int
// prm_923 :: int
inline int cost_at_m158;
int calcspellcostmp(int = 0, int = 0);
// prm_924 :: int
// prm_925 :: int
inline int cost_at_m159;
int calcspellcoststock(int = 0, int = 0);
// prm_926 :: int
// prm_927 :: int
// prm_928 :: int
inline elona_vector1<int> p_at_m161;
void skillinit(int = 0, int = 0, int = 0);
void label_1512();
inline int f;
inline int r3;
inline int r4;
int label_2176();
int label_1513();
int label_1514();
inline int refdiff;
int label_1515();
void label_1516();
int label_1517();
inline int cv;
inline int pcnoise;
int label_1518();
void label_1519();
inline int regen;
void label_1520();
int calcscore();
void calcpartyscore();
void calcpartyscore2();
int eqweaponlight();
int eqweaponheavy();
// prm_929 :: int
inline int p_at_m162;
void eqrandweaponmage(int = 0);
inline int fixeq;
inline int probeq;
inline int cequipment;
inline int eqtwohand;
inline int eqtwowield;
inline int cspecialeq;
int label_2194();
inline int eqmultiweapon;
inline int nostack;
void label_1530();
void label_1531();
inline int placefail;
inline int cmshade;
inline int novoidlv;
void label_2104();
void label_1535();
void label_1534();
void label_2124();
void label_1536();
void label_1538();
void label_1537();
void label_15380();
void label_15390();
void label_1539();
inline int traveldone;
void label_1540();
inline int cfg_wizard;
inline std::string geneuse;
void label_2092();
void label_2115();
void label_1544();
void label_1541();
inline int cfg_extrarace;
inline std::string racename;
inline elona_vector1<std::string> cmrace;
void label_2703();
inline int cmsex;
inline std::string classname;
inline std::string cmclass;
inline elona_vector1<int> cmlock;
inline elona_vector1<int> cmstats;
void label_19672();
void label_1566();
inline std::string cmaka;
void label_1560();
int label_2039();
inline int cmportrait;
inline int csctrl;
int label_20332();
inline int input_mode;
inline std::string cmname;
inline std::string playerid;
inline int msgconfirm;
void label_2091();
void label_2732();
inline int ref1;
inline int ref2;
inline int r;
// prm_930 :: int
// prm_931 :: int
inline int f_at_m163;
inline int tc_at_m163;
inline std::string n_at_m163;
int label_1570();
int convertartifact(int = 0, int = 0);
inline elona_vector1<int> fsetincome;
inline elona_vector1<int> fsetchest;
inline elona_vector1<int> fsetrewardsupply;
inline elona_vector1<int> fsetperform;
inline elona_vector1<int> fsetdeliver;
inline elona_vector1<int> fsetsupply;
inline elona_vector1<int> fsetmagic;
inline elona_vector1<int> fsetarmor;
inline elona_vector1<int> fsetweapon;
inline elona_vector1<int> fsetplantartifact;
inline elona_vector1<int> fsetplantunknown;
inline elona_vector1<int> fsetremain;
inline elona_vector1<int> fsetbarrel;
inline elona_vector1<int> fsetcollect;
inline elona_vector1<int> isetdeed;
inline elona_vector1<int> isetthrowpotionminor;
inline elona_vector1<int> isetthrowpotionmajor;
inline elona_vector1<int> isetthrowpotiongreater;
inline elona_vector1<int> isethire;
inline elona_vector1<int> isetgiftminor;
inline elona_vector1<int> isetgiftmajor;
inline elona_vector1<int> isetgiftgrand;
inline elona_vector1<int> isethirerole;
inline elona_vector1<int> isetcrop;
inline elona_vector1<int> isetgod;
inline elona_vector1<int> asettown;
inline elona_vector1<int> moneybox;
inline elona_vector1<int> giftvalue;
inline elona_vector1<std::string> giftn;
inline elona_vector1<std::string> moneyboxn;
inline elona_vector1<std::string> biten;
inline elona_vector1<std::string> booktitle;
inline elona_vector1<int> isetbook;
inline elona_vector1<std::string> magebookn;
inline int lootrich;
inline elona_vector1<int> drop;
inline int idcupsule;
void label_2668();
void label_1576();
void label_1577();
void label_1578();
void label_1579();
inline int cfg_hideautoidentify;
void label_1580();
void label_1581();
inline elona_vector1<int> rpsourcelist;
inline int nooracle;
inline int ii_p;
// prm_932 :: int
inline int cibk;
void lovemiracle(int = 0);
inline int fdmax;
inline elona_vector2<int> fdlist;
inline int nutrition;
void label_1586();
inline int cooktool;
void label_1587();
inline int enc;
inline int enc2;
inline int cieat;
void label_1588();
void label_1589();
void label_1590();
void label_1591();
void label_1592();
void label_1593();
void label_1594();
void label_1595();
void label_1596();
void label_1597();
void label_1598();
void label_1599();
void label_1600();
void label_1601();
void label_1602();
void label_1603();
void label_1604();
void label_1605();
void label_1606();
void label_1607();
void label_1608();
void label_1609();
void label_1610();
void label_1611();
void label_1612();
void label_1613();
void label_1614();
void label_1615();
void label_1617();
void label_1616();
inline int tile_trap;
inline int tile_doorclosed;
inline int tile_doorclosed2;
inline int tile_doorclosed3;
inline int tile_doorclosed4;
inline int tile_dooropen;
inline int tile_downstairs;
inline int tile_upstairs;
inline int tile_hidden;
inline int tile_downlocked;
inline int tile_re;
inline int tile_plant;
inline int tile_board;
inline int tile_votebox;
inline int tile_townboard;
inline elona_vector2<int> cellobjdata;
inline elona_vector1<std::string> cellobjname;
inline int maxobjid;
inline elona_vector1<int> tile_default;
inline elona_vector1<int> tile_tunnel;
inline elona_vector1<int> tile_wall;
inline elona_vector1<int> tile_room;
void map_converttile();
// prm_933 :: int
inline int tile_trans;
inline int tile_dungeon;
inline int tile_battlesite;
inline int tile_pot;
inline int tile_roomlen;
void map_tileset(int = 0);
inline int p_at_m165;
inline int y_at_m165;
inline int x_at_m165;
inline int i_at_m165;
int dist_town();
// prm_934 :: string
inline std::string fmapfile;
inline int mapupdate;
void map_initcustom(const std::string&);
// prm_935 :: string
inline int y_at_m166;
inline int x_at_m166;
void map_reload(const std::string&);
inline int rdroomnum;
void map_initialize();
// prm_936 :: int
// prm_937 :: int
// prm_938 :: int
inline int x_at_m167;
inline int y_at_m167;
inline int mapstartx;
inline int mapstarty;
void map_placecharaonentrance(int = 0, int = 0, int = 0);
// prm_939 :: int
// prm_940 :: int
void map_placearena(int = 0, int = 0);
inline elona_vector1<int> followerin;
void map_placeplayer();
// prm_941 :: int
// prm_942 :: int
void map_randomtile(int = 0, int = 0);
// prm_953 :: int
// prm_954 :: int
int map_digcheck(int = 0, int = 0);
// prm_955 :: int
// prm_956 :: int
inline int tx_at_m168;
inline int ty_at_m168;
inline int dir_at_m168;
inline int dest_at_m168;
void map_nextdir1(int = 0, int = 0);
// prm_957 :: int
// prm_958 :: int
inline int dir2_at_m168;
inline int p_at_m168;
void map_nextdir2(int = 0, int = 0);
// prm_959 :: int
// prm_960 :: int
// prm_961 :: int
// prm_962 :: int
// prm_963 :: int
inline int f_at_m168;
inline int dx_at_m168;
inline int dy_at_m168;
inline int rdhiddenpath;
int map_digtoentrance1(int = 0, int = 0, int = 0, int = 0, int = 0);
void map_setfog(int = 0, int = 0);
inline int rdpos;
inline int cr;
inline elona_vector1<int> rddoorpos;
// rndshuffle :: unknown
inline int roomdoor;
void map_createroomdoor();
// prm_966 :: int
inline int roomsum;
inline int roompos;
inline int roomwall;
inline int rdroomsizemax;
inline int rdroomsizemin;
inline int x1;
inline int x2;
inline int y1;
inline int y2;
inline elona_vector1<int> tile;
int map_createroom(int = 0);
// prm_967 :: int
// prm_968 :: int
inline int x_at_m169;
inline int y_at_m169;
inline int rdroomupstair;
int map_placeupstairs(int = 0, int = 0);
// prm_969 :: int
// prm_970 :: int
inline int rdroomdownstair;
int map_placedownstairs(int = 0, int = 0);
// prm_971 :: int
// prm_972 :: int
inline int f_at_m169;
void map_randsite(int = 0, int = 0);
// prm_973 :: int
// prm_974 :: int
// prm_976 :: int
inline int dx_at_m170;
inline int dy_at_m170;
inline int p_at_m170;
int label_1653();
inline int trap_at_m170;
int map_trap(int = 0, int = 0, int = 0, int = 0);
// prm_977 :: int
// prm_978 :: int
// prm_979 :: int
int label_1656();
int map_web(int = 0, int = 0, int = 0);
// prm_980 :: int
// prm_981 :: int
int label_1659();
int map_barrel(int = 0, int = 0);
int label_1663();
inline int rdroomentrance;
int map_connectroom();
void label_1666();
void map_makedoor();
inline int rdtry;
inline int rdroomdoor;
inline elona_vector1<int> rdval;
inline int rdtunnel;
inline int rdextraroom;
inline int rdtype;
int label_1703();
int label_1697();
void label_1704();
int label_1701();
int label_1698();
int label_1699();
int label_1700();
int label_1702();
void label_1696();
void label_1705();
inline int _mclass;
inline int _bold;
void label_1710();
void label_1708();
inline int rdmonsterhouse;
inline int rdcreaturepack;
inline int rx;
inline int rw;
inline int ry;
inline int rh;
inline int rdsize;
int fltsetdungeon();
void label_1735();
inline int creaturepack;
inline int rdy3;
inline int rdx3;
inline int mobdensity;
inline int itemdensity;
void label_16952();
inline int size;
inline int crop;
inline int roomdiff;
inline int mx_at_m172;
// prm_983 :: elona_vector1<T>
inline int r_at_m172;
// tmp_at_m172 :: T
void label_1709();
inline int rdsecond;
inline elona_vector1<int> maze;
inline int mdig;
inline int _hole;
inline int sdigx;
inline int sdigy;
inline elona_vector1<int> way;
// dimmix :: unknown
inline int digno;
inline int pmdig;
inline int t;
void label_1711();
inline int area;
inline std::string midbk;
inline std::string mid;
void label_1749();
inline int levelexitby;
void label_1737();
void label_2742();
void label_1712();
inline int homemakewall;
inline int homemapmode;
inline int cxbk;
inline int cybk;
void label_1723();
inline int tlocinitx;
inline int tlocinity;
int label_1947();
void label_1730();
void label_2056();
inline int allyctrl;
int label_1980();
inline int tchome;
int label_1959();
inline int c;
inline int hire;
void label_1714();
void label_1725();
void label_1726();
void label_1724();
inline int worker;
inline int sold;
inline elona_vector1<int> income;
inline int shoplv;
inline int customer;
inline int dblistmax;
inline int a;
inline int in;
inline int cfg_hideshopresult;
void label_1727();
inline int rankorg;
inline int rankcur;
void label_1728();
void label_1729();
// prm_984 :: int
inline std::string s_at_m173;
inline int p_at_m173;
int cbreeder(int = 0);
inline int livestock;
inline int renewmulti;
inline int egg;
void label_1733();
inline int obvjlv;
void label_1736();
inline int usermapid;
inline int fixstart;
void label_2674();
void label_2735();
inline int autosave;
inline int fixtransfermap;
void label_1739();
void label_1738();
void label_17402();
inline int maxnpcbk;
inline elona_vector2<int> rolebk;
inline int maxmedal;
inline elona_vector2<int> medalbk;
inline std::string userfile;
inline elona_vector1<int> id;
void label_2095();
inline int importmode;
inline elona_vector1<int> arenaop;
inline int petarenawin;
inline int arenaimport;
inline int enemyteam;
int label_1747();
void label_2669();
inline int noaggrorefresh;
inline int encounter;
inline int encounterlv;
inline int encounterref;
inline int dbg_revealmap;
void label_1755();
inline int medit;
void label_1745();
void label_1746();
void label_2671();
inline int sceneid;
void label_2680();
void label_2088();
void label_1748();
inline int mapsubroutine;
void label_2733();
inline int pcattacker;
inline int exp;
void label_2233();
inline int mtilefilecur;
inline int shade;
int label_1753();
void label_1751();
void label_1750();
// tstown2 :: unknown
inline int dmg;
void label_2162();
void label_1754();
inline int cardreftype;
inline int cardrefrare;
inline int cardrefcost;
inline elona_vector1<std::string> cardrefn;
inline int cardrefpic;
inline std::string cardrefrace;
inline int cardrefdomain;
inline int cardrefattack;
inline int cardrefhp;
inline int cardrefskill;
inline int cardrefskillcost;
int label_1756();
// prm_985 :: int
// prm_986 :: int
inline elona_vector2<int> card_at_tcg;
int cdbit(int = 0, int = 0);
// prm_987 :: int
// prm_988 :: int
// prm_989 :: int
void cdbitmod(int = 0, int = 0, int = 0);
inline int cp_at_tcg;
inline int tp_at_tcg;
inline int cl_at_tcg;
inline int tl_at_tcg;
inline int ch_at_tcg;
inline int th_at_tcg;
void cpflip();
inline int ct_at_tcg;
void cpisme();
void cpisenemy();
// prm_990 :: int
inline elona_vector1<std::string> s_at_tcg;
std::string cnvrare(int = 0);
// prm_991 :: int
inline int cardrefbg;
int card_ref(int = 0);
inline elona_vector2<int> clist_at_tcg;
inline elona_vector1<int> clistmax_at_tcg;
inline int cnt2_at_tcg;
inline int lmax_at_tcg;
inline elona_vector1<int> p_at_tcg;
inline int maxcard_at_tcg;
inline int f_at_tcg;
inline int c1_at_tcg;
inline int c2_at_tcg;
inline int i_at_tcg;
void label_1844();
void makecardlist();
// prm_992 :: string
// prm_993 :: int
inline int helpdur_at_tcg;
inline int dur_at_tcg;
inline elona_vector1<std::string> helpmsg_at_tcg;
void cardhelp(const std::string&, int = 0);
// prm_994 :: int
// prm_995 :: int
inline int selected_at_tcg;
inline int cursor_at_tcg;
inline int cs_at_tcg;
inline int csline_at_tcg;
inline elona_vector2<int> dlist_at_tcg;
inline int dsc_at_tcg;
inline elona_vector1<std::string> carddetailn_at_tcg;
inline elona_vector1<int> x_at_tcg;
inline elona_vector1<int> y_at_tcg;
inline int basex_at_tcg;
inline int basey_at_tcg;
void tcgdrawcard(int = 0, int = 0);
inline int t_at_tcg;
void label_1825();
inline int anime_at_tcg;
inline elona_vector1<int> holderix_at_tcg;
inline int holderspace_at_tcg;
inline elona_vector1<int> holderiy_at_tcg;
inline elona_vector2<int> cpdata_at_tcg;
inline int c_at_tcg;
inline int cc_at_tcg;
inline int phase_at_tcg;
inline int selectmode_at_tcg;
inline int chaintime_at_tcg;
inline int cfg_chaintime;
inline elona_vector2<int> star_at_tcg;
inline int chainx_at_tcg;
inline int chainy_at_tcg;
inline int efllistmax_at_tcg;
inline elona_vector2<int> efllist_at_tcg;
inline int screenupdate_at_tcg;
void label_1773();
void tcgdraw();
// prm_996 :: int
// prm_997 :: int
// prm_998 :: int
// prm_999 :: int
// prm_1000 :: int
// prm_1001 :: int
void efllistadd(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
// prm_1002 :: int
// prm_1003 :: int
inline elona_vector2<std::string> cardn_at_tcg;
int create_card(int = 0, int = 0);
// prm_1004 :: int
// prm_1005 :: int
inline int l_at_tcg;
inline int spotlistmax_at_tcg;
inline elona_vector1<int> spotlist_at_tcg;
inline int x2_at_tcg;
inline int spotspace_at_tcg;
inline elona_vector1<int> spotiy_at_tcg;
void cardpos(int = 0, int = 0);
// prm_1006 :: int
inline int n_at_tcg;
inline elona_vector1<int> gravesum_at_tcg;
inline elona_vector2<int> gravelist_at_tcg;
void label_1823();
void gravecard(int = 0);
// prm_1007 :: int
// prm_1008 :: int
void dmgcard(int = 0, int = 0);
// prm_1009 :: int
// prm_1010 :: int
inline elona_vector1<int> cpx_at_tcg;
inline elona_vector1<int> cpy_at_tcg;
void dmgplayer(int = 0, int = 0);
// prm_1011 :: int
inline int delcard_at_tcg;
void delbottomcard(int = 0);
int gameover();
// prm_1012 :: int
int getholdersum(int = 0);
// prm_1013 :: int
int getspotsum(int = 0);
// prm_1014 :: int
int getdecksum(int = 0);
// prm_1015 :: int
int cardcandeclareattack(int = 0);
// prm_1016 :: int
int cardcanblock(int = 0);
// prm_1017 :: int
int cardcanuseskill(int = 0);
// prm_1018 :: int
void label_1790();
void getrandomcard(int = 0);
inline elona_vector1<int> deckix_at_tcg;
inline elona_vector1<int> deckiy_at_tcg;
// prm_1019 :: int
// prm_1020 :: int
inline int sac_at_tcg;
inline elona_vector1<int> landix_at_tcg;
inline elona_vector1<int> landsum_at_tcg;
inline int landspace_at_tcg;
inline elona_vector1<int> landiy_at_tcg;
inline elona_vector2<int> landlist_at_tcg;
void saccard(int = 0, int = 0);
// prm_1021 :: int
void opencard(int = 0);
inline elona_vector1<std::string> cdrefn_at_tcg;
inline int cdsummon_at_tcg;
void label_1793();
inline int spellused_at_tcg;
inline int stack_at_tcg;
inline elona_vector2<int> cardstack_at_tcg;
inline int attacktarget_at_tcg;
inline int chainmode_at_tcg;
inline int player_at_tcg;
void label_1836();
inline int aiblock_at_tcg;
void label_18462();
void label_1802();
inline int ac_at_tcg;
inline elona_vector1<int> act_at_tcg;
inline int ap_at_tcg;
inline int tc_at_tcg;
inline elona_vector1<int> deckmode_at_tcg;
inline std::string deckrefn_at_tcg;
void label_1828();
void actionproc();
// prm_1024 :: int
// prm_1025 :: int
int putcard(int = 0, int = 0);
inline int w_at_tcg;
inline int h_at_tcg;
void tcgdrawbg();
inline int turn_at_tcg;
inline int cardmode_at_tcg;
inline elona_vector2<int> elist_at_tcg;
inline elona_vector1<std::string> domname_at_tcg;
inline elona_vector1<std::string> phasen_at_tcg;
inline int basew_at_tcg;
inline int baseh_at_tcg;
inline elona_vector1<int> graveix_at_tcg;
inline elona_vector1<int> graveiy_at_tcg;
inline int gravespace_at_tcg;
inline elona_vector1<int> spotix_at_tcg;
void label_1826();
void tcginit();
// prm_1026 :: int
int calcstartcard(int = 0);
// prm_1027 :: int
void calcstartattb(int = 0);
inline elona_vector1<int> domain_at_tcg;
void calcdomain();
inline int curdeck;
inline int cardsize_at_tcg;
void calcdecksize();
inline std::string file_at_tcg;
inline int decksizebk_at_tcg;
inline int rtval_at_tcg;
void tcgdeck();
inline int rp_at_tcg;
void label_1816();
void label_1815();
void label_1817();
void label_1818();
void label_1819();
void tcgmain();
void csfix();
inline int cslinebk_at_tcg;
void cslineup();
void cslinedown();
inline elona_vector1<int> mana_at_tcg;
inline int m_at_tcg;
inline int cfmax_at_tcg;
inline int ccf_at_tcg;
inline elona_vector1<int> cflist_at_tcg;
inline elona_vector1<std::string> cfname_at_tcg;
inline int page_at_tcg;
inline int dlistmax_at_tcg;
void label_1824();
void label_1827();
void label_1840();
int label_1835();
inline int a_at_tcg;
void label_1839();
inline int chaincontinue_at_tcg;
void label_1842();
inline int emax_at_tcg;
int label_1845();
inline int ec_at_tcg;
void label_1848();
// prm_1028 :: int
// prm_1029 :: int
inline int f_at_m174;
inline int matnum;
inline int lv_at_m174;
inline int rare_at_m174;
inline int loc_at_m174;
inline int atxspot;
inline int p_at_m174;
inline int f2_at_m174;
inline int p2_at_m174;
int random_material(int = 0, int = 0);
// prm_1030 :: int
// prm_1031 :: int
// prm_1032 :: int
inline int n_at_m174;
inline std::string s_at_m174;
void matgetmain(int = 0, int = 0, int = 0);
// prm_1033 :: int
// prm_1034 :: int
void matdelmain(int = 0, int = 0);
void label_1854();
inline int prodtype;
inline elona_vector1<int> j;
inline int matuse;
void label_18552();
void label_2050();
void label_1859();
inline int atxthrough;
inline std::string atbuff;
inline int chatesc;
inline std::string atxbg;
inline std::string atxbgbk;
void atxinit();
void begintempinv();
void exittempinv();
inline elona_vector1<int> atxpic;
inline elona_vector1<std::string> atxinfon;
inline elona_vector1<int> atxid;
void label_1874();
void label_1878();
void label_1873();
void label_1866();
inline int txtadvmsgfix;
void label_1870();
void label_1871();
void label_18672();
void label_1872();
inline elona_vector1<int> mattile;
inline int p_double;
inline int invsubroutine;
int label_20592();
inline int atxap;
inline int atxlv;
void label_1877();
inline int txtadvscreenupdate;
void label_1876();
inline int atxrefval1;
void label_1879();
inline int stake;
inline int winrow;
inline int cardround;
inline int winner;
// prm_1035 :: int
int modpiety(int = 0);
void label_1882();
inline elona_vector1<std::string> godname;
void label_1885();
void label_1888();
void label_1886();
void label_1889();
int label_2659();
void label_1890();
void label_1892();
void label_1891();
inline int dbg_skipevent;
int label_1896();
int label_1893();
inline int cfg_skiprandevents;
inline elona_vector1<std::string> q;
int label_1898();
// prm_1036 :: int
inline int p_at_m176;
int calcincome(int = 0);
inline int invfile;
void label_1901();
// prm_1037 :: int
inline std::string s_at_m177;
inline elona_vector2<int> rpdata;
inline int rpid;
inline elona_vector2<std::string> rfnameorg;
inline int p_at_m177;
std::string rpmatname(int = 0);
// prm_1038 :: int
// prm_1039 :: int
inline int p_at_m178;
int blendcheckext(int = 0, int = 0);
// prm_1040 :: int
std::string rpsuccessrate(int = 0);
// prm_1042 :: int
// prm_1043 :: int
inline int p1_at_m180;
inline int f_at_m180;
inline int f2_at_m180;
inline elona_vector1<int> rpref;
inline int i_at_m180;
inline int d_at_m180;
inline int p_at_m180;
int rpdiff(int = 0, int = 0, int = 0);
// prm_1044 :: int
inline int f_at_m181;
inline int step_at_m181;
inline int id_at_m181;
inline int rp_at_m181;
inline int o_at_m181;
int blendcheckmat(int = 0);
// prm_1045 :: int
// prm_1046 :: int
inline int m_at_m182;
inline int o_at_m182;
int blendmatnum(int = 0, int = 0);
// prm_1048 :: int
inline int id_at_m183;
inline int m_at_m183;
inline int o_at_m183;
inline int step;
inline int reftype_at_m183;
inline int f_at_m183;
// prm_1047 :: elona_vector2<int>
inline int x_at_m183;
inline int w_at_m183;
inline int dx_at_m183;
inline int dy_at_m183;
inline std::string s_at_m183;
inline int p_at_m183;
inline int rpmode;
void window_recipe2();
// prm_1050 :: int
// prm_1051 :: int
// prm_1052 :: int
// prm_1053 :: int
// prm_1054 :: int
inline elona_vector1<std::string> s_at_m184;
// xfix_at_m184 :: unknown
inline elona_vector1<int> rppage;
inline int xfix2_at_m184;
inline int dx_at_m184;
inline int dy_at_m184;
inline int i_at_m184;
inline int p_at_m184;
// getinheritance :: unknown
// inhlist_at_m184 :: unknown
inline int cnt2_at_m184;
void clear_rprefmat();
void label_1920();
// rsjeweler :: unknown
// window_recipe :: unknown
// list2 :: unknown
void label_19342();
void label_1924();
// blendlist :: unknown
void label_1927();
void label_1922();
inline elona_vector1<int> blendchecklist;
int label_1931();
inline int rpresult;
int label_1932();
void label_1935();
void label_1933();
void label_2736();
// prm_1055 :: int
// prm_1056 :: int
inline elona_vector1<int> p_at_m185;
inline elona_vector1<int> i_at_m185;
std::string txtitemoncell(int = 0, int = 0);
// prm_1057 :: int
// prm_1058 :: int
// prm_1059 :: int
inline int dy_at_m186;
inline int cansee;
inline int i_at_m186;
inline int p_at_m186;
void txttargetnpc(int = 0, int = 0, int = 0);
inline int kdx;
inline int kdy;
int key_direction();
void label_2113();
inline elona_vector1<std::string> headtemp;
inline std::string username;
inline int userrelation;
void label_2114();
void label_1942();
int label_19432();
int label_2072();
void label_2076();
void label_1955();
inline int mousex;
inline int mousey;
inline int findlocmode;
inline int tgloc;
inline int tglocx;
inline int tglocy;
void label_1951();
void label_1958();
int label_2231();
int label_2230();
void label_1964();
void label_1968();
int label_196902();
void label_1969();
inline int featrq;
inline int dump_return;
inline int gold;
void label_2710();
void label_1972();
void label_2707();
inline int client;
inline int questteleport;
void label_2242();
inline int chatteleport;
void label_1976();
int label_1984();
void label_1988();
void label_1992();
int label_1993();
inline int wishfilter;
void label_1996();
void label_2000();
void label_2001();
inline int wishid;
void label_1997();
void label_2002();
inline std::string s2;
inline int invsc;
void label_2006();
void label_2026();
void label_2003();
int label_2127();
inline int refx;
inline int refy;
void label_2158();
void label_2224();
void label_2004();
void label_2201();
void label_2005();
int label_2174();
void label_2031();
void label_2027();
void label_2007();
void label_2055();
void label_2011();
void label_2218();
void label_2013();
inline int ccbk;
int label_2014();
void label_2012();
int label_2018();
void label_2022();
int label_2167();
void label_2032();
inline int csskill;
inline int cs_buff;
inline int returnfromportrait;
// calcage :: unknown
void label_2047();
inline int cs_buffmax;
inline int tcbk;
void label_2038();
int label_2044();
void label_2048();
int label_2075();
inline int attackvar;
inline int hit;
void label_2049();
inline int cs_prev;
inline int mainhand;
inline int showresist;
void label_2195();
void label_2068();
inline int returnfromidentify;
void label_2236();
void label_2235();
int label_2192();
void label_2054();
inline int invally;
inline elona_vector1<int> invcontainer;
void savecycle();
void label_2087();
inline int mainweapon;
inline int countequip;
inline int showmoney;
inline int shoptrade;
inline int cidip;
inline int citrade;
inline int dropcontinue;
inline int dropval;
int label_2193();
void label_2198();
void label_2197();
void label_2199();
void label_2200();
void label_2663();
void label_2228();
void label_2212();
void label_2227();
void label_2191();
int label_2665();
void label_2189();
void label_2237();
inline int efcancel;
void label_2264();
// prm_1060 :: string
// prm_1061 :: int
inline std::string q_at_m187;
inline int p_at_m187;
std::string trimdesc(const std::string&, int = 0);
// inhlist :: unknown
inline int inhmax;
inline std::string buf;
int label_2073();
int label_2217();
void label_2074();
void label_2152();
void label_2077();
void label_2078();
void label_2723();
void label_2079();
int label_2080();
void label_2081();
inline int tmat;
void label_2082();
void label_2148();
int label_2083();
void label_2719();
inline std::string fileext;
inline std::string filedsc;
// _fdialog :: unknown
void label_2108();
inline elona_vector1<int> followerexist;
inline int lv;
void label_2109();
inline std::string gnname1;
void label_2106();
// label_1404 :: unknown
void label_2084();
void label_2085();
void label_2086();
void label_2713();
inline int cfg_netwish;
inline int cfg_netchat;
inline int cfg_exanime;
void label_2090();
inline elona_vector1<std::string> file_cnv;
inline int p1;
inline int p2;
inline int p3;
void label_2089();
inline int lomiaseaster;
void label_2093();
// prm_1062 :: string
inline int len;
inline int lenhead;
inline int lensum;
inline elona_vector1<std::string> ziptmp1;
inline elona_vector1<std::string> ziptmp2;
inline elona_vector1<std::string> filebuff;
inline elona_vector1<std::string> filetemp;
void zipadd(const std::string&);
void label_2720();
inline int zipsize;
// prm_1063 :: string
// prm_1064 :: string
inline int lensum_at_m188;
inline std::string zipfolder_at_m188;
inline std::string zipfinalfile_at_m188;
inline elona_vector1<std::string> filebuff_at_m188;
void zipinit2(const std::string&, const std::string&);
// prm_1065 :: string
inline elona_vector1<int> p_at_m188;
inline int len_at_m188;
inline int lenhead_at_m188;
inline elona_vector1<std::string> ziptmp1_at_m188;
inline elona_vector1<std::string> ziptmp2_at_m188;
inline elona_vector1<std::string> filetemp_at_m188;
void zipadd2(const std::string&);
void zipend2();
// prm_1066 :: string
// prm_1067 :: string
inline int zipsize_at_m188;
void unzip2(const std::string&, const std::string&);
// prm_1068 :: string
// prm_1069 :: string
inline int p_at_m189;
inline elona_vector1<std::string> txtbuff;
std::string getnpctxt(const std::string&, const std::string&);
inline int initunid;
inline int cun;
inline elona_vector1<int> unaiactsubfreq;
inline elona_vector1<std::string> unres;
// csvstr2 :: unknown
inline elona_vector1<std::string> untaglist;
inline int hgz;
inline elona_vector1<int> bmpbuff;
inline std::string txtfile;
inline std::string bmpfile;
inline int fsize;
inline std::string usertitle;
void label_2112();
inline std::string save_buff;
inline int save_f;
inline std::string save_s;
inline int save_p;
inline int cfg_titleeffect;
inline int water_debug;
void label_2118();
void label_2121();
inline elona_vector2<int> fovmap;
inline int inputfail;
inline elona_vector1<std::string> inputlog2;
inline int cfg_msg_box;
inline int ime_esc;
// onkey_1 :: unknown
inline std::string dbm;
void label_2136();
void label_2138();
void label_2134();
inline int dbg_exitshowroom;
void label_2139();
inline int dbg_compare;
inline elona_vector2<std::string> cdatan2;
inline elona_vector2<int> cdata2;
inline elona_vector2<int> sdata2;
inline elona_vector2<int> inv2;
inline int dbg_freemove;
void label_2661();
inline elona_vector1<int> mapclient;
// prm_1072 :: int
// prm_1073 :: int
// prm_1074 :: int
// prm_1075 :: int
inline int efstatus;
int efstatusfix(int = 0, int = 0, int = 0, int = 0);
int label_2143();
inline int movx;
inline int movy;
void label_2144();
void label_2222();
inline int efsource;
void label_21452();
inline int performtips;
void label_2146();
inline int sexhost;
inline int sexvalue;
void label_2147();
inline int f2;
void label_2151();
void label_2149();
void label_2150();
inline int timeslept;
inline int grown;
void label_2161();
void label_2153();
inline int fish;
void label_2154();
void label_2155();
inline int fishstat;
void label_2156();
void label_2157();
inline int countdig;
void label_2223();
inline int digx;
inline int digy;
void label_2159();
void label_2160();
inline int cibkread;
// prm_1076 :: int
// prm_1077 :: int
int calcmagiccontrol(int = 0, int = 0);
inline int spellbk;
int label_2168();
int label_2175();
inline int npccostmp;
inline int mp;
inline int noeffect;
inline int rapidmagic;
inline int potionspill;
inline int potionthrow;
inline int obvious;
int label_2172();
inline int efcibk;
inline int efbad;
inline int chainbomb;
inline int range;
void label_2187();
inline elona_vector1<int> chainbomblist;
inline int tcprev;
inline int telex;
inline int teley;
inline int efidprev;
inline int ccprev;
void label_2188();
inline int equip;
inline int obvisou;
inline int fltbk;
inline int valuebk;
inline int subloop;
inline int ccthrowpotion;
void label_2190();
inline int inumbk;
inline int sellgold;
inline int cfg_ignoredislike;
void label_2206();
void label_2205();
void label_2203();
void label_2215();
inline int dirsub;
inline int foot;
inline int movelevelbystairs;
void label_2207();
int label_2209();
int label_2211();
void label_2263();
inline int refweight;
void label_2214();
void label_2213();
inline int ri;
void label_2216();
inline int ammox;
inline int ammoy;
inline int attackitem;
inline int extraattack;
void label_22192();
inline int distance;
inline int expmodifer;
inline int cfg_attackanime;
void label_2220();
inline int subdmg;
void label_2221();
// prm_1078 :: int
void dipcursed(int = 0, int = 0);
void label_2232();
inline int blendtool;
void label_2727();
// label_1410 :: unknown
void label_2234();
inline int j_at_m193;
inline int p_at_m193;
inline int i_at_m193;
inline int f_at_m193;
int clientguide(int = 0);
// prm_1081 :: int
int tradecheck(int = 0);
void label_2241();
inline int scenemode;
inline int chatflag;
void label_2262();
void label_2243();
void label_2249();
void label_2250();
void label_2257();
inline int scene_cut;
void label_2256();
void label_2244();
void label_2246();
void label_2252();
void label_2251();
inline int plat;
int label_2248();
inline elona_vector1<int> deliver;
void label_2679();
inline int supply;
inline int chatid;
void label_2255();
void label_2254();
inline int minlevel;
inline int enemylv;
inline int marry;
inline int tcchat;
inline int oc;
void label_2253();
void label_2260();
void label_2261();
void label_2259();
void label_22600();
void label_22610();
inline int chatpicloaded;
inline elona_vector2<std::string> actor;
void label_2267();
void label_2265();
void label_2266();
// prm_1082 :: int
// prm_1083 :: int
// prm_1084 :: int
// prm_1085 :: int
inline int p_at_m194;
void addbuilding(int = 0, int = 0, int = 0, int = 0);
inline int initeco;
inline elona_vector1<int> bkdata;
void label_2270();
inline int city;
void label_2276();
void label_2280();
// prm_1086 :: int
// prm_1087 :: int
// prm_1088 :: string
// prm_1089 :: int
// prm_1090 :: int
inline int p_at_m195;
void showeconomy(int, int, const std::string&, int = 0, int = 0);
inline int cpicref;
// label_2654 :: unknown
inline int dbtmp2;
inline int nerve;
inline int maxnpcid;
void label_2660();
int label_2664();
void label_2662();
void label_2667();
inline int eqdup;
inline elona_vector1<int> bodylist;
inline int haveweapon;
inline int mustequip;
inline int rewardfix;
void label_2670();
int label_2672();
void label_2676();
void label_2673();
void label_2675();
void label_2677();
void label_2678();
inline int cfg_story;
inline int scidx;
void label_2685();
inline int scidxtop;
void label_2684();
inline int blockedbychara;
int ai_check();
void label_2690();
inline int retreat;
void label_2693();
void label_2696();
inline int searchfov;
void label_2687();
inline elona_vector1<int> sell;
int label_2694();
int label_2695();
inline int act;
inline int quickpage;
void label_2700();
void label_2697();
void label_2702();
inline int page_bk;
inline int cs_bk2;
inline int header;
inline int tail;
inline std::string note_buff;
inline elona_vector1<std::string> key_buff;
inline int cfg_language;
inline std::string defload;
inline int cfg_scancel;
inline int cfg_showskillmod;
inline int cfg_zkey;
inline int cfg_xkey;
inline int cfg_scrsync;
inline std::string usermsg;
inline std::string userpassword;
// prm_1092 :: string
inline int p_at_m198;
int cnvjkey(const std::string&);
inline int cfg_sound2;
inline int cfg_music2;
inline int cfg_fullscreen2;
inline int windoww2;
inline int windowh2;
inline int sel;
inline int submenu;
inline int firstturn;
inline int dbgchara;
inline int sound;
inline int turncost;
void label_2754();
void label_2752();
inline int spd;
void label_27412();
inline int ef;
inline int hear;
inline int mousemove;
inline int automove;
void label_2748();
inline std::string wincomment;
void label_2751();
void label_27492();
void label_2753();
inline elona_vector1<int> voidboss;
// prm_258 :: int
// prm_259 :: int
// prm_0258 :: int
// prm_0259 :: int
}
