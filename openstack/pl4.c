#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define APPLICATION_ID "1bfc9191060e454d8206981d91c27d02"
#define APPLICATION_SECRET "eNfmtQjGy5zeMNbSew6JhVMbd0VZnlE7MAFtdzGVY_pjzbbAvPYBYt6H12-iaSvu4xjrGf4Rf0PmFz-qV-t5NA"

int main() {
    CURL *curl;
    CURLcode res;

    char *payload_format = "{\"domain\": { \"name\": \"Default\"}, \"auth\": { \"identity\": {\"methods\": [\"application_credential\"], \"application_credential\": {\"id\": \"%s\", \"secret\": \"%s\"}}}}";
    char token_request[1024];
    snprintf(token_request, sizeof(token_request), payload_format, APPLICATION_ID, APPLICATION_SECRET);
    
    curl = curl_easy_init();
    if(curl) {
        printf("\nList of projects:\n");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, "https://gpmcloud.ru:5443/v3/auth/tokens");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, token_request);
        //printf("\nList of projects:\n");
        
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            char *line = NULL;
            char *response = NULL;
            size_t response_len = 0;
            while (curl_easy_getinfo(curl, CURLINFO_HEADER_OUT, &line) == CURLE_OK) {
                if (strncmp(line, "x-subject-token:", 16) == 0) {
                    char *token = strchr(line, ':');
                    if (token != NULL) {
                        token += 2;
                        token[strcspn(token, "\r\n")] = 0;
                        response_len = strlen(token);
                        response = (char *)malloc(response_len + 1);
                        strncpy(response, token, response_len);
                        response[response_len] = '\0';
                    }
                    break;
                }
            }
            
            if (response != NULL) {
                char url[1024];
                snprintf(url, sizeof(url), "https://gpmcloud.ru:5443/v3/projects");
                headers = curl_slist_append(headers, response);
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
                curl_easy_perform(curl);
                free(response);
            }
        }
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    
    return 0;
}