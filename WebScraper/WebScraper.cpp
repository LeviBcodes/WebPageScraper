#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

// Callback function to write the received data into a file
size_t writecallback(void* contents, size_t size, size_t nmemb, std::ofstream* file) {
    file->write(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

std::string gettext(std::string prompttext);

int main() {
    // initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // create a curl object
    CURL* curl = curl_easy_init();
    if (curl) {
        std::string url;

        // get user input for the url
        std::cout << "Enter the URL of the webpage you want to scrape: ";
        std::getline(std::cin, url);

        // set the url to fetch
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // open a file to write the response
        std::ofstream outputfile("output.html", std::ios::out | std::ios::binary);
        if (outputfile.is_open()) {
            // set the callback function to write the received data into the file
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outputfile);

            // perform the request
            CURLcode result = curl_easy_perform(curl);
            if (result != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(result) << std::endl;
            }
            else {
                std::cout << "webpage content successfully saved to output.html" << std::endl;
            }

            // close the file
            outputfile.close();
        }
        else {
            std::cerr << "failed to open output file" << std::endl;
        }

        // clean up
        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "failed to initialize curl" << std::endl;
    }

    // clean up libcurl
    curl_global_cleanup();

    return 0;
}

std::string gettext(std::string prompttext)
{
    std::string text;
    std::cout << prompttext;
    std::getline(std::cin, text);
    return text;
}