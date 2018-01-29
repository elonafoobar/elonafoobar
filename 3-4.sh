cp 3.cpp 4.cpp
vim -es +"%s/nevercalledfunction .*\n{\n\zefunction//" +"wq" 4.cpp
vim -es +"%s/^}\n\zsnevercalledfunction/function/" +"wq" 4.cpp
vim -es +"%s/nevercalledfunction .*\n{\n//" +"wq" 4.cpp
vim -es +"%s/^:label.*:\n\zefunction//" +"wq" 4.cpp
true
