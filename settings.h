#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <boost/regex.hpp>

using namespace std;

class Settings
{
public:
    Settings(string f);
    string default_player_path;
    string file_name;
    bool saveConfig();
    bool configFileExist();
    bool createConfig();
    bool loadConfig();
};

#endif // SETTINGS_H
