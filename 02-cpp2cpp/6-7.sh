cp 6.cpp 7.cpp

# patch < 7.patch

cp 7.cpp 7.cpp.before


vim -es +"%s/label_0192();\n    return\zs;/ 0;" +"wq" 7.cpp


# Optional arguments.
sed -i "" \
    -e "s/, , , / -1, -1, /" \
    -e "s/, , \([01]\))/, 0, \1)/" \
7.cpp


# Preserve parameters.
sed -i "" \
    -e "s/\(buffer(10 + prm_409, 384, 198);\)/elona::prm_409=prm_409;\1/" \
    -e "s/\(itemnamehack = inv(3, prm_518) + 1;\)/elona::prm_518=prm_518;\1/" \
    -e "s/\(if (prm_820 < 1) {\)/elona::prm_818=prm_818;elona::prm_820=prm_820;\1/" \
    -e "s/\(ele_at_m141 = prm_856;\)/elona::prm_853=prm_853;\1/" \
7.cpp


# Add cast.
sed -i "" \
    -e "s/return \(gdata(10) - cdata(21, prm_762)\);/return elona_str(\1);/" \
7.cpp



# Add empty statements.
sed -i "" \
    -e "s/\(label_0387_internal:\)/\10;/" \
    -e "s/\(label_0391_internal:\)/\10;/" \
    -e "s/\(label_0395_internal:\)/\10;/" \
    -e "s/\(label_0400_internal:\)/\10;/" \
    -e "s/\(label_0404_internal:\)/\10;/" \
    -e "s/\(label_0408_internal:\)/\10;/" \
7.cpp


sed -i "" \
    -e "s/dup(sdatadup_at_m161, sdata(\(prm_926 + 600, prm_927\)));/elona_dup2<int> sdatadup_at_m161{sdata, \1};/" \
7.cpp



# Replace type `array` with appriciate types.
sed -i "" \
    -e "/void csvsort/s/array/elona_vector1<std::string>\&/" \
    -e "/void getinheritance/s/array/elona_vector1<int>\&/" \
    -e "/void csvstr2/s/array/elona_vector1<std::string>\&/" \
    -e "/void rndshuffle/s/array/elona_vector1<int>\&/" \
    -e "/void _fdialog/s/array/std::string\&/g" \
    -e "/void dimmix/s/array/elona_vector1<int>\&/" \
    -e "/void window_recipe/s/window_recipe(array, /window_recipe_(/" \
    -e "s/void blendlist(array prm_1047/int blendlist(elona_vector2<int>\& prm_1047/" \
7.cpp



# Correct the return type.
sed -i "" \
    -e "s/void calcage(int prm_762)/std::string calcage(int prm_762)/" \
    -e "s/void randomname(int)/std::string randomname(int)/" \
    -e "s/void label_2654/int label_2654/" \
7.cpp


sed -i "" \
    -e "s/label_2654();/stat=label_2654();return;/" \
7.cpp



sed -i "" \
    -e "/void csvsort/s/std::string&/std::string/" \
7.cpp



# Fix typo.
sed -i "" \
    -e "s/cbind_at_con(prm_818)/cdata(253, prm_818)/" \
    -e "s/_conangryheavy(2)/_conangry(1)/" \
    -e "s/tstown2/2/" \
    -e "s/xfix_at_m184/0/g" \
    -e "s/rsjeweler/0/g" \
7.cpp


sed -i "" -e "/cdref_at_tcg/d" 7.cpp
sed -i "" -e "s/cdsummon_at_tcg/0/" 7.cpp


sed -i "" -e "s/rqop(1)/0/" -e "s/rqop,/0,/" 7.cpp



# Always false: if ((feat(1) == 0) >= 24 && (feat(1) == 0) <= 28)
# => if (feat(1) >= 24 && feat(1) <= 28)
sed -i "" \
    -e "s/if ((feat(1) == 0) >= 24 && (feat(1) == 0) <= 28) {/if (feat(1) >= 24 \&\& feat(1) <= 28) {/" \
7.cpp




sed -i "" -e "s/label_0397();/goto label_0397_internal;/" 7.cpp
vim -es +"%s/}\nint label_0397()\n{/label_0397_internal:/" +"wq" 7.cpp
sed -i "" -e "s/label_0410();/goto label_0410_internal;/" 7.cpp
vim -es +"%s/}\nint label_0410()\n{/label_0410_internal:/" +"wq" 7.cpp
sed -i "" -e "s/label_1394();/goto label_1394_internal;/" 7.cpp
vim -es +"%s/}\nint label_1394()\n{/label_1394_internal:/" +"wq" 7.cpp
vim -es +"%s/^    label_0225();\n    return;\n}\nstd::string label_0225()\n{//" +"wq" 7.cpp
sed -i "" -e "s/label_1570();/goto label_1570_internal;/" 7.cpp
vim -es +"%s/}\nint label_1570()\n{/label_1570_internal:/" +"wq" 7.cpp
sed -i "" -e "s/label_1790();/goto label_1790_internal;/" 7.cpp
vim -es +"%s/}\nvoid label_1790()\n{/label_1790_internal:/" +"wq" 7.cpp
sed -i "" -e "s/label_1876();/goto label_1876_internal;/" 7.cpp
vim -es +"%s/}\nvoid label_1876()\n{/label_1876_internal:/" +"wq" 7.cpp
sed -i "" -e "s/label_1924();/goto label_1924_internal;/" 7.cpp
vim -es +"%s/}\nvoid label_1924()\n{/label_1924_internal:/" +"wq" 7.cpp
sed -i "" -e "s/label_1927();/goto label_1927_internal;/" 7.cpp
vim -es +"%s/}\nvoid label_1927()\n{/label_1927_internal:/" +"wq" 7.cpp
sed -i "" -e "s/label_2684();/goto label_2684_internal;/" 7.cpp
vim -es +"%s/}\nvoid label_2684()\n{/label_2684_internal:/" +"wq" 7.cpp
sed -i "" -e "s/label_2211();/goto label_2211_internal;/" 7.cpp
vim -es +"%s/}\nint label_2211()\n{/label_2211_internal:/" +"wq" 7.cpp
sed -i "" -e "s/label_2700();/goto label_2700_internal;/" 7.cpp
vim -es +"%s/}\nvoid label_2700()\n{/label_2700_internal:/" +"wq" 7.cpp



# Delete unimplemented functions.
sed -i "" -e "/label_1404();/d" 7.cpp
sed -i "" -e "/label_1410();/d" 7.cpp

sed -i "" -e "s/goto label_1669;/std::exit(1);return;/" 7.cpp



# strlen -> strlen_u
sed -i "" \
    -e "/ pos(/s/strlen/strlen_u/" \
    -e "/ line(/s/strlen/strlen_u/" \
    -e "/ window2(/s/strlen/strlen_u/" \
    -e "/if (strlen(/s/strlen/strlen_u/" \
    -e "/dx += strlen(elona_str(val(5))) * 8;/s/strlen/strlen_u/" \
    -e "/dx = 80 + strlen(s) * 8;/s/strlen/strlen_u/" \
    -e "/p = 1000 - (strlen(s) - strlen(s2)) * 10;/s/strlen/strlen_u/" \
    -e "/p_at_m89 = prm_645 - strlen(prm_644);/s/strlen/strlen_u/" \
    -e "/sx = strlen(s) * 8 + 45;/s/strlen/strlen_u/" \
    -e "/tx_at_m72 = limit(strlen(prm_543) * 7 + 32 + prm_547, 10, 480);/s/strlen/strlen_u/" \
    -e "/x += (strlen(bodyn(p \/ 10000)) + 1) * 6;/s/strlen/strlen_u/" \
    -e "/x = windoww \/ 2 - strlen(s) * 4;/s/strlen/strlen_u/" \
7.cpp



sed -i "" \
    -e "/mes(strmid(skillname(r), 0, 4 - (jp == 0)) + u8\": \"s + s(p));/s/4 - (jp == 0)/jp ? 6 : 3/" \
7.cpp




cat header 7.cpp footer > tmp_7_cpp
mv -f tmp_7_cpp 7.cpp





vim -es \
    +"%s/void label_1547()\n{/void label_1547(bool label_1548_flg){if(label_1548_flg){" \
    +"%s/void label_1550()\n{/void label_1550(bool label_1551_flg){if(label_1551_flg){" \
    +"%s/void label_1553()\n{/void label_1553(bool label_1554_flg){if(label_1554_flg){" \
    +"%s/void label_1557()\n{/void label_1557(bool label_1558_flg){if(label_1558_flg){" \
    +"%s/void label_2737()\n{/void label_2737(bool label_2738_flg){if(label_2738_flg){" \
    +"%s/void label_2743()\n{/void label_2743(bool label_2747_flg){if(label_2747_flg){" \
+"wq" 7.cpp

sed -i "" \
    -e "s/label_1548:/}&/" \
    -e "s/label_1551:/}&/" \
    -e "s/label_1554:/}&/" \
    -e "s/label_1558:/}&/" \
    -e "s/label_2738:/}&/" \
    -e "s/label_2747:/}&/" \
    -e "s/goto label_1548;/label_1547(false);/" \
    -e "s/goto label_1551;/label_1550(false);/" \
    -e "s/goto label_1554;/label_1553(false);/" \
    -e "s/goto label_1558;/label_1557(false);/" \
    -e "s/goto label_2738;/label_2737(false);/" \
    -e "s/goto label_2747;/label_2743(false);/" \
7.cpp

sed -i "" \
    -e "122673,122642s/label_1547(false);/goto label_1548;/" \
    -e "122744,122841s/label_1550(false);/goto label_1551;/" \
    -e "122843,122977s/label_1553(false);/goto label_1554;/" \
    -e "122979,123099s/label_1557(false);/goto label_1558;/" \
    -e "237873,238272s/label_2737(false);/goto label_2738;/" \
    -e "238355,239297s/label_2743(false);/goto label_2747;/" \
7.cpp



vim -es \
    +"%s/\(proclist(procid) = u8\"main_init:End ct:\"s + ct;\)\n    label_2737();/\1    try { label_2737(); } catch (elona_turn_sequence\&) { goto redo; }/" \
    +"wq" \
7.cpp

vim -es \
    +"%s/void label_2733()\n{/void label_2733(){redo:" \
    +"wq" \
7.cpp

vim -es \
    +"%s/\(if (ct >= 245) {\)\n        label_2733();/\1        throw elona_turn_sequence{};/" \
    +"wq" \
7.cpp

# Fix typo.
sed -i "" \
    -e "/ s(1) = /s/頭/HD/g" \
    -e "/ s(1) = /s/首/N_/g" \
    -e "/ s(1) = /s/背/BK/g" \
    -e "/ s(1) = /s/体/BD/g" \
    -e "/ s(1) = /s/手/HA/g" \
    -e "/ s(1) = /s/指/R_/g" \
    -e "/ s(1) = /s/腕/A_/g" \
    -e "/ s(1) = /s/腰/W_/g" \
    -e "/ s(1) = /s/足/L_/g" \
    -e "s/if (s == u8\"頭\"s) {/if (s == u8\"HD\"s) {/" \
    -e "s/if (s == u8\"首\"s) {/if (s == u8\"N_\"s) {/" \
    -e "s/if (s == u8\"背\"s) {/if (s == u8\"BK\"s) {/" \
    -e "s/if (s == u8\"体\"s) {/if (s == u8\"BD\"s) {/" \
    -e "s/if (s == u8\"手\"s) {/if (s == u8\"HA\"s) {/" \
    -e "s/if (s == u8\"指\"s) {/if (s == u8\"R_\"s) {/" \
    -e "s/if (s == u8\"腕\"s) {/if (s == u8\"A_\"s) {/" \
    -e "s/if (s == u8\"腰\"s) {/if (s == u8\"W_\"s) {/" \
    -e "s/if (s == u8\"足\"s) {/if (s == u8\"L_\"s) {/" \
7.cpp



# Delete `cnt`s without repeat statements.
sed -i "" \
    -e "/void cs_list(/s/.*/void cs_list(int CNT, const std::string\& prm_543, int prm_544 = 0, int prm_545 = 0, int prm_546 = 0, int prm_547 = 0, int prm_548 = 0, int prm_549 = 0)/" \
    -e "s/  cs_list(/  cs_list(cnt, /" \
    -e "s/void label_1567(/void label_1567(int CNT/" \
    -e "s/  label_1567(/  label_1567(cnt/" \
    -e "s/rnd((CNT/rnd((prm_936/" \
    -e "s/cnt2_at_tcg = CNT;/cnt2_at_tcg = 0;/" \
7.cpp



# diff -u 7.cpp.before 7.cpp > 7.patch
