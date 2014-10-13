#include "cdasearch.h"

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

Cda_Search::Cda_Search(string search_text, Progress_Bar *progress_bar, int page) : p_bar(progress_bar),
    source_file(tmpFile()),
    search_url("http://www.cda.pl/video/show/"+search_text+"/p"+istr(page)+"?s=popular")
{
    if(getSourceCode(search_url)) {
        p_bar->upgrade(10);
        searchResult();
    }

//        if(searchResult() == 24) {
//            next_page = true;
//        }else
//            next_page = false;
}

// Conversion int -> string
string Cda_Search::istr(int i)
{
    ostringstream ss;
    ss << i;
    return ss.str();
}

// Generate tmp file path
string Cda_Search::tmpFile()
{
    char tmp_path [L_tmpnam];
    tmpnam(tmp_path);
    return tmp_path;
}

// Function save source code website to tmp file
bool Cda_Search::getSourceCode(string site)
{
    CURL *curl;
    CURLcode res;
    FILE *file;

    curl = curl_easy_init();

    if(curl) {
        file = fopen(source_file.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, site.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/37.0.2062.120 Chrome/37.0.2062.120 Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        res = curl_easy_perform(curl);
        curl_global_cleanup();
        fclose(file);

        if(CURLE_OK != res)
            fprintf(stderr, "curl told us %d\n", res);
        else
            return true;
    }
    return false;
}

// Return search result number items
// If result is empty return 0
int Cda_Search::searchResult()
{
    boost::regex div_class_videoContainer("class=.([videoContainer]+).");
    boost::regex div_class_rowElem("class=.([rowElem]+).");
    boost::regex search_result_box("class=.thumbElem.(video_[0-9]+).");
    boost::regex end_result_box("class=.(clear+).>$");

    boost::regex result("class=.titleElem.+href=.(/video/[\\s\\S]+)\">([\\s\\S]+)</a>");
    boost::regex end_result("(</label>)");

    string::const_iterator start, end;

    boost::match_results<string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;

    fstream file(source_file.c_str());
    string cur_line;

    int items = 0;

    while(getline(file, cur_line)) {
        start = cur_line.begin();
        end = cur_line.end();

        if(boost::regex_search(start, end, what, div_class_videoContainer, flags)) {

            while(getline(file, cur_line)) {
                start = cur_line.begin();
                end = cur_line.end();

                if(boost::regex_search(start, end, what, end_result_box, flags)) { break; }

                if(boost::regex_search(start, end, what, div_class_rowElem, flags)) {

                    while(getline(file, cur_line)) {
                        start = cur_line.begin();
                        end = cur_line.end();

                        if(boost::regex_search(start, end, what, end_result_box, flags)) { break; }

                        if(boost::regex_search(start, end, what, search_result_box, flags)) {
                            result_id.push_back(what[1].str());

                            while(getline(file, cur_line)) {
                                start = cur_line.begin();
                                end = cur_line.end();

                                if(boost::regex_search(start, end, what, end_result, flags))
                                    break;

                                if(boost::regex_search(start, end, what, result, flags)) {
                                    result_title.push_back(what[2].str());
                                    result_url.push_back("http://www.cda.pl" + what[1].str());
                                    items++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return items;
}
