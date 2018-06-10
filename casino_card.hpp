#pragma once

namespace elona
{

void initcard(int = 0, int = 0, int = 0);
void showcard();
void showcard2(int = 0, int = 0);
void showcardholder();
void showcardpile();
int opencard2(int = 0, int = 0);
int servecard(int = 0);
void cardplayeradd(int = 0, int = 0, int = 0);
void cardplayerinit(int = 0, int = 0);
int trashcard(int = 0);
int lastcard(int = 0);
int cpblackcard(int = 0);
int cpcardnum(int = 0);
int cpscore(int = 0);

} // namespace elona
