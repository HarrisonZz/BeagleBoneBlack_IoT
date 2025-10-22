#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  
#include <stddef.h>
#include <stdint.h> 
#include <curl/curl.h>

bool http_client_init(void);

void http_client_cleanup(void);

bool http_post_local(const char *path, const char *json_body);

bool http_led_control(const char *state);


#endif /* HTTP_CLIENT_H */