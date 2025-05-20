#include "arkanoid/binary_file_high_score_storage.hpp"
#include <cstring>
#include <iostream>

namespace arkanoid {

BinaryFileHighScoreStorage::BinaryFileHighScoreStorage(const std::string& filename)
: filename_(filename)
{
    // Try to open the file in read/write binary mode
    file_.open(filename_, std::ios::in | std::ios::out | std::ios::binary);

    if (!file_) {
        // File doesn't exist — create it empty
        std::ofstream create_file(filename_, std::ios::binary);
        create_file.close();

        // Now reopen for read/write
        file_.open(filename_, std::ios::in | std::ios::out | std::ios::binary);
    }
}

BinaryFileHighScoreStorage::~BinaryFileHighScoreStorage()
{
    if (file_.is_open()) {
        file_.close();
    }
}

std::vector<HighScoreEntry> BinaryFileHighScoreStorage::load() const
{
    std::vector<HighScoreEntry> entries;
    //file_.clear();
    file_.seekg(0, std::ios::beg);

    while (file_) {
        char name_buf[consts::NameWidth] = {};
        ScoreType score = 0;
        TimeType time_ms = 0;

        // check each read for success
        file_.read(reinterpret_cast<char*>(&name_buf), consts::NameWidth);
        if (file_.gcount() != consts::NameWidth) {
            break;
        }
        file_.read(reinterpret_cast<char*>(&score), consts::ScoreWidth);
        if (file_.gcount() != consts::ScoreWidth) {
            break;
        }
        file_.read(reinterpret_cast<char*>(&time_ms), consts::TimeWidth);
        if (file_.gcount() != consts::TimeWidth) {
            break;
        }
        float time_s = static_cast<float>(time_ms) / 1000.0f;

        entries.push_back({
            
            std::string(name_buf, strnlen(name_buf, consts::NameWidth)),
            score,
            time_s
        });
    }

    return entries;
}

void BinaryFileHighScoreStorage::save(const std::vector<HighScoreEntry>& entries) const
{
    file_.close();
    file_.open(filename_, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!file_) return;

    for (const auto& entry : entries) {
        char name_buf[consts::NameWidth] = {};
        uint64_t time_ms = static_cast<uint64_t>(entry.time_s * 1000.0f);
        std::strncpy(name_buf, entry.name.c_str(), consts::NameWidth);
        file_.write(reinterpret_cast<const char*>(&name_buf), consts::NameWidth);
        file_.write(reinterpret_cast<const char*>(&entry.score), consts::ScoreWidth);
        file_.write(reinterpret_cast<const char*>(&time_ms), consts::TimeWidth);
    }

    file_.flush();

    // Reopen for further use
    file_.close();
    file_.open(filename_, std::ios::in | std::ios::out | std::ios::binary);
}

void BinaryFileHighScoreStorage::append_entry(const HighScoreEntry& entry)
{
    file_.clear();
    file_.seekp(0, std::ios::end);

    char name_buf[consts::NameWidth] = {};
    std::strncpy(name_buf, entry.name.c_str(), consts::NameWidth);

    file_.write(reinterpret_cast<const char*>(&name_buf), consts::NameWidth);
    file_.write(reinterpret_cast<const char*>(&entry.score), consts::ScoreWidth);
    uint64_t time_ms = static_cast<uint64_t>(entry.time_s * 1000.0f);
    file_.write(reinterpret_cast<const char*>(&time_ms), consts::TimeWidth);

    file_.flush();
}

} // namespace arkanoid
