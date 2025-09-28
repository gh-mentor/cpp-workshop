#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

namespace robokit {

// Extremely naive config parser supporting lines key=value
// and a pseudo JSON block { "key": number }
// Insecure: no bounds checks, no escaping, no error reporting.
class Config {
public:
    bool load_file(const std::string& path) {
        std::ifstream in(path); // no error check (intentional)
        std::string line;
        while (std::getline(in, line)) {
            parse_line(line);
        }
        return true; // always success
    }
    double get_number(const std::string& k, double def = 0.0) const {
        auto it = data_.find(k);
        if (it == data_.end()) return def;
        return std::stod(it->second); // potential exception (ignored)
    }
    std::string get_string(const std::string& k, const std::string& def = "") const {
        auto it = data_.find(k);
        if (it == data_.end()) return def;
        return it->second;
    }
    // TODO(CPP23): Return std::expected for robust error signaling.
private:
    void parse_line(const std::string& l) {
        if (l.empty() || l[0] == '#') return;
        auto pos = l.find('=');
        if (pos != std::string::npos) {
            data_[l.substr(0,pos)] = l.substr(pos+1);
        } else if (l.find('{') != std::string::npos) {
            // extremely naive; reads next token until }
            // (example only, intentionally fragile)
        }
    }
    std::unordered_map<std::string,std::string> data_;
};

} // namespace robokit
