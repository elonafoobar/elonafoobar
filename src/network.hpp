#pragma once

#include <string>



namespace elona
{



void netload(const std::string& prm_194);
int net_send(const std::string& prm_883, int prm_884 = 0);
int net_read(int prm_885 = 0);
int net_dllist(const std::string& prm_886, int prm_887);
int net_dl(const std::string& prm_888, const std::string& prm_889);
void initialize_server_info();
void show_chat_dialog();
int voting_box();



} // namespace elona
