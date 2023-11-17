// //Add this function to parse the alias command
// void parse_alias_command(const char *input, char **alias_name, char **alias_value)
// {
//     // Assuming the input format is "alias name=value"
//     // You can customize this parsing logic based on your requirements
//     char *alias_cmd = strdup(input + 6);  // Skip "alias " part
//     char *equal_sign = strchr(alias_cmd, '=');

//     if (equal_sign != NULL) {
//         *equal_sign = '\0';  // Null-terminate alias_name
//         *alias_name = strdup(alias_cmd);
//         *alias_value = strdup(equal_sign + 1);
//     } else {
//         // Handle invalid alias command
//         *alias_name = NULL;
//         *alias_value = NULL;
//     }

//     free(alias_cmd);
// }