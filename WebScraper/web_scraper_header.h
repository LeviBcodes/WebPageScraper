#ifndef WEB_SCRAPER_H
#define WEB_SCRAPER_H

#include <fstream>
#include <string>

// Callback function to write the received data into a file
size_t writecallback(void* contents, size_t size, size_t nmemb, std::ofstream* file);

std::string gettext(std::string prompttext);

#endif // WEB_SCRAPER_H