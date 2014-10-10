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
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <vector>

#include <boost/thread.hpp>
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
    bool getPlayerPath();
    bool prepare();
    bool openPlayer();
    string movie_site;
    string player_path;
    string cookie_file;
    string source_file;
    string error;
};

#endif /* CDAMAIN_H_ */
