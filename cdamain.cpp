/*
 * cdamain.cpp
 *
 *  Created on: 04-10-2014
 *      Author: mateusz
 */
#include "cdamain.h"


static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}


Cda_Main::Cda_Main()
{
    // Generate tmp files
    char cookie_f [L_tmpnam];
    char source_f [L_tmpnam];
    tmpnam(cookie_f);
    tmpnam(source_f);
    cookie_file = cookie_f;
    source_file = source_f;
}

Cda_Main::~Cda_Main() {
}

// Check mplayer installation path
// If mplayer is not installed return false
bool Cda_Main::getPlayerPath()
{
    string result = system("which mplayer");
    if(result.empty())
        return false;
    else
        player_path = result.substr(0, result.size()-1);
    return true;
}

// Func running media player
bool Cda_Main::openPlayer()
{
    string mplayer = player_path + " -cookies -cookies-file "+cookie_file+" '" + movie_url+"'";
    cout << mplayer << endl;
    string result = system(mplayer.c_str());
    cout << result << endl;


    if(result.empty()) {
        return false;
    }else if(result.substr(0,3) == "sh:") {
        error = result;
        return false;
    }

    return true;
}

// std::system function implementation
// return output from console
string Cda_Main::system(string cmd)
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

// Function get destination movie url from cda.pl url (tmp file)
bool Cda_Main::getSourceCode()
{
    CURL *curl;
    CURLcode res;
    FILE *file;
    curl = curl_easy_init();

    if(curl) {
        file = fopen(source_file.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, movie_site.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/37.0.2062.120 Chrome/37.0.2062.120 Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookie_file.c_str());
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_file.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        res = curl_easy_perform(curl);
        curl_global_cleanup();
        fclose(file);

        if(CURLE_OK != res) {
            /* we failed */
            fprintf(stderr, "curl told us %d\n", res);
        }

        if(getMovieUrlFromSourceCode(source_file.c_str())) {
            curl_easy_cleanup(curl);
            return true;
        }
    }
    return false;
}

// Get direct URL to movie from cda site source code
bool Cda_Main::getMovieUrlFromSourceCode(string source_file_path)
{
    ifstream file(source_file_path.c_str());
    string temp;

    static const boost::regex rx("\'([h]+[t]+[m]+[l]+[5])\'");
    static const boost::regex rx2("'([\\s\\S]+)'");
    string::const_iterator start, end;

    boost::match_results<string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;

    while(getline(file, temp)) {
        start = temp.begin();
        end = temp.end();

        if(boost::regex_search(start, end, what, rx, flags)) {
            getline(file, temp); // skip one line
            getline(file, temp);
            start = temp.begin();
            end = temp.end();
        }else
            continue;

        if(boost::regex_search(start, end, what, rx2, flags)) {
            movie_url = what[1].str();
            return true;
        }
    }
    return false;
}

// Preparing direct url to movie
// from cda site
bool Cda_Main::prepare()
{
    if(getSourceCode()) {
        return true;
    }
    return false;
}