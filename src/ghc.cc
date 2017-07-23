#include <string>

std::string ghc_output(const std::string& path)
{
    std::string res;
    std::string cmd = "ghc -ddump-rn " + path;
    FILE* f = popen(cmd.c_str(), "r");

    char buf[256];
    int chars;
    while (chars = std::fread(buf, 1, 256, f), chars != 0) {
        if (chars != 256) {
            buf[chars] = '\0';
        }
        res += buf;
    }

    fclose(f);
    return res;
}
