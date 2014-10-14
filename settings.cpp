#include "settings.h"

Settings::Settings(string f) : cda_address("http://www.cda.pl"),
    cfg_path(f)
{
    if(checkMplayerInstalled()) {
        mplayer_installed = true;
        mplayer_path = getMplayerPath();
    }else
        mplayer_installed = false;
}

// Return true if cnfig file is exist
bool Settings::fileExist(string file_path)
{
    FILE *file;
    file = fopen(file_path.c_str(), "r");

    if(!file)
        return false;
    else
        fclose(file);

    return true;
}

// Create config file with default settings
bool Settings::createConfig(string cfg_path)
{
    fstream cfg_file(cfg_path.c_str(), ios::out | ios::trunc);
    string option1 = option("playing_mode", "window");

    if(cfg_file) {
        cfg_file.write(option1.c_str(), option1.size());
        cfg_file.close();
    }
    if(!loadConfig(cfg_path))
        return false;

    return true;
}

// Load config from file
bool Settings::loadConfig(string cfg_path)
{
    ifstream cfg_file(cfg_path.c_str());
    string temp;

    string option1_name = "playing_mode";
    string option1_value;
    boost::regex option1_rx_name("(^[playing_mode]*)");
    boost::regex option1_rx_value("'([/a-zA-Z0-9]+)'");

    boost::match_results<string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    string::const_iterator start, end;

    while(getline(cfg_file, temp)) {
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
            if(option1_value == "window")
                fullscreen_mode = false;
            if(option1_value == "fullscreen")
                fullscreen_mode = true;
            return true;
        }
    }
    cfg_file.close();

    return false;
}

// Save config to file
bool Settings::saveConfig(string cfg_path)
{
    string option1_name = "playing_mode";

    fstream cfg_file(cfg_path.c_str(), ios::out | ios::trunc);

    if(cfg_file) {
        string save_opt;

        if(fullscreen_mode)
            save_opt = option(option1_name, "fullscreen");
        else
            save_opt = option(option1_name, "window");

        cfg_file.write(save_opt.c_str(), save_opt.size());
        cfg_file.close();
    }else
        return false;

    return true;
}

string Settings::option(string opt, string value)
{
    return (opt + " = '" + value + "'\n");
}

// Check mplayer installation path
// If mplayer is not installed return false
bool Settings::checkMplayerInstalled()
{
    string output = system("which mplayer");

    if(output.empty())
        return false;

    return true;
}

// Check mplayer installation path
// If mplayer is not installed return false
string Settings::getMplayerPath()
{
    string result = system("which mplayer");

    if(result.empty())
        return "MPlayer is not installed";

    return result.substr(0, result.size()-1);
}

// std::system function implementation
// return output from console
string Settings::system(string cmd)
{
    string output;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) output.append(buffer);
                pclose(stream);
    }
    return output;
}
