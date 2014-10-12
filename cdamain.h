/*
 * cdamain.h
 *
 *  Created on: 04-10-2014
 *      Author: mateusz
 */

#ifndef CDAMAIN_H_
#define CDAMAIN_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include <curl/curl.h>
#include <boost/regex.hpp>

using namespace std;

class Cda_Main {

private:
    string movie_url;
    string system(string cmd);

    bool getSourceCode();
    bool getMovieUrlFromSourceCode(string source_file_path);

public:
    Cda_Main();
    virtual ~Cda_Main();

    string movie_site;
    string cookie_file;
    string source_file;
    string error;

    bool prepare();
    bool openPlayer(string mplayer_path, bool fullscreen);
};

#endif /* CDAMAIN_H_ */
