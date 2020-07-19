#pragma once

#include "filesystem.hpp"
#include "serialization/macros.hpp"



namespace elona
{

/**
 * Represents the header file which contains save data's summary. It is shown in
 * the save selection menu.
 */
struct SaveHeader
{
    /// Represents the format of the header file.
    enum class Format
    {
        /// Vanilla-compatible.
        vanilla,

        /// New format with extra properties.
        foobar,
    };



    /// The format of the header file. This field is not serialized.
    Format format;

    /// The save directory's name. This field is not serialized.
    std::string save_dir_name;

    /// The identifier of the save version.
    /// If the save is saved in foobar, it is just foobar's version like v1.2.3.
    /// If not, it pair of the variant and its version.
    /// @ref SaveHeader::Format::foobar only
    std::string version;

    /// Your name.
    std::string name;

    /// Your alias.
    /// @ref SaveHeader::Format::foobar only
    std::string alias;

    /// Your level.
    int64_t level;

    /// Your race name. Note that it is not a race ID.
    /// @ref SaveHeader::Format::foobar only
    std::string race;

    /// Your class name. Note that it is not a class ID.
    /// @ref SaveHeader::Format::foobar only
    std::string class_;

    /// The location where you are. Note that it is not a map ID.
    std::string location;

    /// The flag whether Wizard mode is on.
    /// @ref SaveHeader::Format::foobar only
    bool is_wizard;

    /// In-game current time.
    /// @ref SaveHeader::Format::foobar only
    std::string ingame_time;

    /// The time when you played the save most recently in Unix time.
    /// cf. https://en.wikipedia.org/wiki/Unix_time
    /// @ref SaveHeader::Format::foobar only
    int64_t last_played_at;

    /// The played duration in seconds.
    /// @ref SaveHeader::Format::foobar only
    int64_t play_seconds;



    /**
     * Get the title shown in the save selection menu.
     *
     * @return The title of the save.
     */
    std::string title() const;



    /**
     * Convert the save header to the displayed text.
     *
     * @return The lines of text.
     */
    std::vector<std::string> to_string() const;



    /*
     * Load a save header file in @a save_dir. If both formats exist, @ref
     * SaveHeader::Format::foobar is loaded.
     *
     * @param save_dir The save directory.
     * @return The loaded save header.
     */
    static SaveHeader load(const fs::path& save_dir);



    /*
     * Save a save header file in @a save_dir.
     *
     * @param save_dir The save directory.
     */
    static void save(const fs::path& save_dir);



    /*
     * Check if a save header file exists in @a save_dir.
     *
     * @param save_dir The save directory.
     * @return True if exists; false if not.
     */
    static bool exists(const fs::path& save_dir);



private:
    SaveHeader() = default;



    /**
     * Construct a save header instance by the current game state.
     *
     * @return The constructed save header.
     */
    static SaveHeader current_state();



    /*
     * Load a save header file in @a save_dir, whose format is @ref
     * SaveHeader::Format::vanilla.
     *
     * @param save_dir The save directory.
     * @return The loaded save header.
     */
    static SaveHeader load_vanilla(const fs::path& save_dir);



    /*
     * Load a save header file in @a save_dir, whose format is @ref
     * SaveHeader::Format::foobar.
     *
     * @param save_dir The save directory.
     * @return The loaded save header.
     */
    static SaveHeader load_foobar(const fs::path& save_dir);
};

} // namespace elona
