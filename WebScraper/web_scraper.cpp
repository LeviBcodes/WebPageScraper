#include "web_scraper_header.h"
#include <iostream>
#include <curl/curl.h>

size_t writecallback(void* contents, size_t size, size_t nmemb, std::ofstream* file) {
    file->write(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

std::string gettext(std::string prompttext) {
    std::string text;
    std::cout << prompttext;
    std::getline(std::cin, text);
    return text;
}