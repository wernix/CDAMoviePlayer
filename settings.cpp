#include "settings.h"

Settings::Settings(string f) : file_path(f)
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
bool Settings::createConfig(string config_file_path)
{
    bool ok = false;

    ofstream file(config_file_path.c_str(), ofstream::binary);
    string option1 = "playing_mode = 'window'\n";
    if(file.is_open()) {
        file.write(option1.c_str(), option1.size());
        ok = true;
        file.close();
    }
    if(!loadConfig(config_file_path))
        ok = false;

    return ok;
}

// Load config from file
bool Settings::loadConfig(string config_file_path)
{
    ifstream file(config_file_path.c_str());
    string temp;

    string option1_name = "playing_mode";
    string option1_value;
    boost::regex option1_rx_name("(^[playing_mode]*)");
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
            if(option1_value == "window")
                fullscreen_mode = false;
            if(option1_value == "fullscreen")
                fullscreen_mode = true;

            return true;
        }
    }
    return false;
}

// Save config to file
bool Settings::saveConfig(string config_file_path)
{
    string option = "playing_mode = ";

    if(fullscreen_mode)
        option.append("'fullscreen'");
    else
        option.append("'window'");

    option.append("\n");

    fstream file(config_file_path.c_str());
    if(file.is_open()) {
        file.close();
        file.open(config_file_path.c_str(), std::ios::out | std::ios::trunc);
        file.write(option.c_str(), option.size());
        file.close();
    }else
        return false;
    return true;
}

// Check mplayer installation path
// If mplayer is not installed return false
bool Settings::checkMplayerInstalled()
{
    string result = system("which mplayer");
    if(result.empty())
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
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
                pclose(stream);
    }
    return data;
}
