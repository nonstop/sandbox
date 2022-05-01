#define JSMN_STRICT
#define JSMN_PARENT_LINKS
#include "jsmn.h"
#include <vector>
#include <string.h>
#include <stdio.h>

const char* jsonTextPlain
    //= R"({"f1": "v1", "f2": 123, "f3": true})";
    = R"({"f1": {"f11":"v11", "f12": 321, "f13": false}})";
    //= R"({"f1": "v1"})";


int main()
{
    jsmn_parser p;
    jsmn_init(&p);
    int res = jsmn_parse(&p, jsonTextPlain, strlen(jsonTextPlain), nullptr, 0);
    if (res < 0) {
        fprintf(stderr, "error=%d\n", res);
        return 1;
    }
    fprintf(stderr, "number of tokens %d\n", res);
    std::vector<jsmntok_t> tokens;
    tokens.resize(res, jsmntok_t{});
    jsmn_init(&p);
    res = jsmn_parse(&p, jsonTextPlain, strlen(jsonTextPlain), tokens.data(), res);
    fprintf(stderr, "res=%d\n", res);
    for (const auto& t : tokens) {
        fprintf(stderr, "%d start=%d end=%d size=%d\n",
                t.type, t.start, t.end, t.size);
    }
    return 0;
}
