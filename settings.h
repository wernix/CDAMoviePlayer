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
    Settings(string config_file_path);

    string mplayer_path;
    string cda_address;
    string cfg_path;

    bool fullscreen_mode;
    bool mplayer_installed;
    bool checkMplayerInstalled();
    bool saveConfig(string cfg_path);
    bool fileExist(string cfg_path);
    bool createConfig(string cfg_path);
    bool loadConfig(string cfg_path);

private:
    string getMplayerPath();
    string system(string cmd);
    string option(string opt, string value);
};

#endif // SETTINGS_H
