#ifndef CDASEARCH_H
#define CDASEARCH_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>

#include <curl/curl.h>
#include <boost/regex.hpp>

#include <progressbar.h>

using namespace std;

class Cda_Search
{
public:
    Cda_Search(string search_text, Progress_Bar *p_bar, int page);

    vector<string> result_title;
    vector<string> result_url;
    vector<string> result_id;

    bool next_page;

private:
    Progress_Bar *p_bar;
    string source_file;
    string search_url;

    bool getSourceCode(string site);

    int searchResult();

    string istr(int i);
    string tmpFile();
};

#endif // CDASEARCH_H
