#include "settings.h"

Settings::Settings(string f) : file_name(f)
{

}

// Return true if cnfig file is exist
bool Settings::configFileExist()
{
    FILE *file;
    file = fopen(file_name.c_str(), "r");
    if(!file)
        return false;
    else
        fclose(file);

    return true;
}

// Create config file with default settings
bool Settings::createConfig()
{
    bool ok = false;

    ofstream file(file_name.c_str(), ofstream::binary);
    string option = "default_player_path = '/usr/bin/mplayer'";
    if(file.is_open()) {
        file.write(option.c_str(), option.size());
        ok = true;
        file.close();
    }
    if(!loadConfig())
        ok = false;

    return ok;
}

// Load config from file
bool Settings::loadConfig()
{
//    if(!fileExist(file_name))
//        if(!createConfig())
//            return false;

    ifstream file(file_name.c_str());
    string temp;
    string option1_name = "default_player_path";
    string option1_value;

    boost::regex option1_rx_name("(^[default_player_path]*)");
    boost::regex option1_rx_value("'([/a-zA-Z0-9]+)'");

    boost::match_results<string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    string::const_iterator start, end;

    while(getline(file, temp)) {
        start = temp.begin();
        end - temp.end();

        if(boost::regex_search(start, end, what, option1_rx_name, flags)) {
            if(option1_name == what[1].str())
                start = what[0].second;
        }
        if(boost::regex_search(start, end, what, option1_rx_value, flags)) {
            option1_value = what[1].str();
        }

        if(!option1_value.empty()) {
            default_player_path = option1_value;
            return true;
        }
    }
    return false;
}

// Save config to file
bool Settings::saveConfig()
{
    string option = "default_player_path = '"+default_player_path+"'";
    fstream file(file_name.c_str());
    if(file.is_open()) {
        file.close();
        file.open(file_name.c_str(), std::ios::out | std::ios::trunc);
        file.write(option.c_str(), option.size());
        file.close();
    }else
        return false;
    return true;
}
