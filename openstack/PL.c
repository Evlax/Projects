#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include ".credential.h" файл с ключами для авторизации.
#include <jansson.h>

int main() {
  char TOKEN_REQUEST[500];
  sprintf(TOKEN_REQUEST, "{\
    \"domain\": { \"name\": \"Default\"},\
    \"auth\": {\
      \"identity\": {\
        \"methods\": [\"application_credential\"],\
        \"application_credential\": {\
          \"id\": \"%s\",\
          \"secret\": \"%s\"\
        }\
      }\
    }\
  }", APPLICATION_ID, APPLICATION_SECRET);

  char command[1000];
  sprintf(command, "curl -i -H \"Content-Type: application/json\" -d '%s' https://gpmcloud.ru:5443/v3/auth/tokens --dump-header - -o /dev/null", TOKEN_REQUEST);

  FILE *output = popen(command, "r");
  char line[1024];
  char OS_TOKEN[1024];

  while (fgets(line, sizeof(line), output) != NULL) {
    if (strstr(line, "x-subject-token:") != NULL) {
      char *token_start = strstr(line, ": ") + 2;
      char *token_end = strchr(token_start, '\r');
      *token_end = '\0';
      strcpy(OS_TOKEN, token_start);
    }
  }

  pclose(output);

  printf("\nList of projects\n");
  sprintf(command, "curl -s -H \"X-Auth-Token: %s\" \"https://gpmcloud.ru:5443/v3/projects\" | json_pp -json_opt pretty,canonical", OS_TOKEN);
  output = popen(command, "r");

  while (fgets(line, sizeof(line), output) != NULL) {
    printf("%s", line);
  }

  pclose(output);
  
  return 0;
}