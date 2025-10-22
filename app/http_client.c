#include "http_client.h"

static CURL *curl = NULL;

bool http_led_control(const char *state)
{

    char json[20];
    snprintf(json, sizeof(json), "{\"state\":\"%s\"}", state);

    return http_post_local("/led", json);
}

bool http_client_init(void)
{
    if (curl_global_init(CURL_GLOBAL_DEFAULT) != 0)
        return false;

    curl = curl_easy_init();
    return (curl != NULL);
}

void http_client_cleanup(void)
{
    if (curl)
        curl_easy_cleanup(curl);
    curl_global_cleanup();
}

bool http_post_local(const char *path, const char *json_body)
{
    if (!curl)
        return false;

    char url[128];
    snprintf(url, sizeof(url), "http://localhost:30080%s", path);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "[HTTP] POST %s failed: %s\n", url, curl_easy_strerror(res));
        fflush(stderr);
        
        return false;
    }

    return true;
}