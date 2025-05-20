#pragma once

#include <string>
#include <fstream>

#include "arkanoid/i_high_score_storage.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid
{

class BinaryFileHighScoreStorage : public IHighScoreStorage {
public:
    explicit BinaryFileHighScoreStorage(const std::string& filename = consts::Top10FileName);
    ~BinaryFileHighScoreStorage(); // RAII-safe cleanup
    std::vector<HighScoreEntry> load() const override;
    void save(const std::vector<HighScoreEntry>& entries) const override;
    void append_entry(const HighScoreEntry& entry) override;

private:
    std::string filename_;
    mutable std::fstream file_;
};

} // namespace arkanoid