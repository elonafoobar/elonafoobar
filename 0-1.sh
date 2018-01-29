cp 0.hsp 1.hsp

sed -i "" -e "117307,117308d" -e "1s/.*/#deffunc main/" 1.hsp

sed -E -i "" -e "/#uselib|#func|#cfunc/d" 1.hsp
sed -i "" -e "s/if ( prm_489 == 1 )/else/" -e "s/if ( dir@m168 == 3 | dir@m168 == 0 )/else/" -e "s/if ( dir@m168 == 3 | dir@m168 == 0 )/else/" 1.hsp
sed -i "" -e "s/ie->\"Navigate\"/ie_Navigate/" 1.hsp
vim -es +"%s/exgoto \(.*\), 1, \(.*\), \*label_\(.*\)/if(\1 >= \2){:goto *label_\3:}/" +"wq" 1.hsp

sed -i "" -e "/onexit /d" 1.hsp
sed -i "" -e "s/onkey \([01]\)$/onkey_\1/" 1.hsp
sed -i "" -e "s/_switch_sw@tcg/_switch_sw/g" -e "s/_switch_val@tcg/_switch_val/g" 1.hsp
vim -es +"%s/^\(\t*end\)$/\1:return" +"wq" 1.hsp
sed -i "" -e "s/comevent .*, \(\*label_.*\)/comevent gosub\1/" 1.hsp


sed -i "" -e "s/prm_517/prm_518/g" 1.hsp



sed -i "" \
-e "s/^\*label_2659/return:*label_2659/" \
-e "s/^\*label_1417/*label_1417:gosub*label_14170:gosub*label_14180:gosub*label_14190:return:*label_1418:gosub*label_14180:gosub*label_14190:return:*label_1419:gosub*label_14190:return:*label_14170/" \
-e "s/^\*label_1418/return:*label_14180/" \
-e "s/^\*label_1419/return:*label_14190/" \
-e "s/^\*label_1538/*label_1538:gosub*label_15380:gosub*label_15390:return:*label_1539:gosub*label_15390:return:*label_15380/" \
-e "s/^\*label_1539/return:*label_15390/" \
-e "s/^\*label_2260/*label_2260:gosub*label_22600:gosub*label_22610:return:*label_2261:gosub*label_22610:return:*label_22600/" \
-e "s/^\*label_2261/return:*label_22610/" \
-e "s/^\*label_1967/*label_1967:gosub*label_19670:gosub*label_19690:return:*label_1969:gosub*label_19690:return:*label_19670/" \
-e "s/goto \*label_1969/goto *label_19690/" \
-e "s/^\*label_1969/return:*label_19690/" \
1.hsp






# Function refchara returns int or string.
# Since different return types are not allowed in C++,
# replace this function.

# #defcfunc refchara int prm_258, int prm_259, int prm_260
#     dbmode = 16
#     dbid = prm_258
#     dbspec = prm_259
#     gosub *label_2299
#     if ( prm_260 == 0 ) {
#         return stat
#     }
#     else {
#         return refstr
#     }


# Delete the original definition of refchara().
sed -i "" -e "/#defcfunc refchara/d" 1.hsp

# Replace its invocations.
sed -i "" \
-e "s/refchara(\(.*\), 8, 1)/refchara_str(\1, 8)/g" \
-e "s/refchara(\([^f]*\), 2, 1)/refchara_str(\1, 2)/g" \
1.hsp

# Append new definitions.
cat <<EOS > tmp_refchara
#defcfunc refchara int prm_258, int prm_259
    dbmode = 16
    dbid = prm_258
    dbspec = prm_259
    gosub *label_2299
    return stat
#defcfunc refchara_str int prm_0258, int prm_0259
    dbmode = 16
    dbid = prm_0258
    dbspec = prm_0259
    gosub *label_2299
    return refstr
EOS
cat tmp_refchara >> 1.hsp
rm -f tmp_refchara
