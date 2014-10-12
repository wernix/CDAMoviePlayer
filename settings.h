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
    string file_path;

    bool fullscreen_mode;
    bool mplayer_installed;
    bool checkMplayerInstalled();
    bool saveConfig(string config_file_path);
    bool fileExist(string config_file_path);
    bool createConfig(string config_file_path);
    bool loadConfig(string config_file_path);

private:
    string getMplayerPath();
    string system(string cmd);
};

#endif // SETTINGS_H
