#ifndef INZ_COMPILER_CONTROLLER_HPP
#define INZ_COMPILER_CONTROLLER_HPP

#define TOML_EXCEPTIONS 0

#include "tomlplusplus/toml.hpp"
#include <cstdint>
#include <filesystem>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

//
// Driver/controller flags (uint16_t bitmask)
//
enum class DriverFlag : std::uint16_t
{
    None = 0,
    DumpAst = (1u << 0),
    DumpIr = (1u << 1),
};

constexpr std::uint16_t to_u16(DriverFlag f) noexcept
{
    return static_cast<std::uint16_t>(f);
}

constexpr DriverFlag operator|(DriverFlag a, DriverFlag b) noexcept
{
    return static_cast<DriverFlag>(to_u16(a) | to_u16(b));
}

constexpr DriverFlag operator&(DriverFlag a, DriverFlag b) noexcept
{
    return static_cast<DriverFlag>(to_u16(a) & to_u16(b));
}

constexpr DriverFlag& operator|=(DriverFlag& a, DriverFlag b) noexcept
{
    a = (a | b);
    return a;
}

constexpr bool has_flag(DriverFlag mask, DriverFlag bit) noexcept
{
    return (to_u16(mask) & to_u16(bit)) != 0;
}

struct CompilerConfig
{
    std::string projectName;

    struct Files
    {
        std::filesystem::path filesDir;
    } files;

    struct Link
    {
        std::vector<std::string> libs;
    } link;

    struct Flags
    {
        std::unordered_map<std::string, DriverFlag> presets;
        std::unordered_map<std::string, std::vector<std::string>> extra_tokens;
    } flags;
};

namespace cfg
{
    // ---------- small TOML helpers ----------

    inline std::optional<std::string> get_string(const toml::table& t,
                                                 std::string_view key)
    {
        if (auto v = t[key].value<std::string>())
            return *v;
        return std::nullopt;
    }

    inline std::optional<bool> get_bool(const toml::table& t,
                                        std::string_view key)
    {
        if (auto v = t[key].value<bool>())
            return *v;
        return std::nullopt;
    }

    inline std::vector<std::string> get_string_array(const toml::table& t,
                                                     std::string_view key)
    {
        std::vector<std::string> out;
        if (auto arr = t[key].as_array())
        {
            out.reserve(arr->size());
            for (auto&& node : *arr)
            {
                if (auto s = node.value<std::string>())
                    out.push_back(*s);
            }
        }
        return out;
    }

    inline bool require_table(const toml::table& root, std::string_view key,
                              const toml::table*& outTable, std::string& err)
    {
        if (auto t = root[key].as_table())
        {
            outTable = t;
            return true;
        }
        err = "Missing or invalid table: [" + std::string(key) + "]";
        outTable = nullptr;
        return false;
    }

    inline bool require_string(const toml::table& t, std::string_view key,
                               std::string& outValue, std::string& err)
    {
        if (auto s = t[key].value<std::string>())
        {
            outValue = *s;
            return true;
        }
        err = "Missing or invalid string key: " + std::string(key);
        return false;
    }

    // ---------- flags parsing (relaxed) ----------

    inline std::optional<DriverFlag> flag_from_token(std::string_view tok)
    {
        if (tok == "--dump-ast") return DriverFlag::DumpAst;
        if (tok == "--dump-ir") return DriverFlag::DumpIr;

        // Add more mappings here.
        return std::nullopt;
    }

    inline std::vector<std::string> split_ws(const std::string& s)
    {
        std::vector<std::string> out;
        std::istringstream iss(s);
        std::string tok;
        while (iss >> tok) out.push_back(tok);
        return out;
    }

    // Relaxed policy:
    // - Known tokens set bits.
    // - Unknown tokens are kept in outExtra.
    // - No error on unknown tokens.
    inline void parse_flag_list_relaxed(const std::vector<std::string>& tokens,
                                        DriverFlag& outMask,
                                        std::vector<std::string>& outExtra)
    {
        outMask = DriverFlag::None;
        outExtra.clear();

        for (const auto& t : tokens)
        {
            if (auto bit = flag_from_token(t)) outMask |= *bit;
            else outExtra.push_back(t);
        }
    }

    inline bool parse_flags_table(const toml::table& root,
                                  CompilerConfig& outCfg,
                                  std::string& err)
    {
        auto flagsTbl = root["flags"].as_table();
        if (!flagsTbl) return true; // optional

        for (auto&& [k, v] : *flagsTbl)
        {
            const std::string presetName = std::string(k.str());
            std::vector<std::string> tokens;

            if (auto s = v.value<std::string>())
            {
                tokens = split_ws(*s);
            }
            else if (auto arr = v.as_array())
            {
                tokens.reserve(arr->size());
                for (auto&& node : *arr)
                {
                    if (auto sv = node.value<std::string>()) tokens.push_back(*sv);
                    else
                    {
                        err = "Invalid non-string value in [flags]. Key: " + presetName;
                        return false;
                    }
                }
            }
            else
            {
                err = "Invalid value type in [flags]. Key: " + presetName +
                    " (expected string or array of strings)";
                return false;
            }

            DriverFlag mask = DriverFlag::None;
            std::vector<std::string> extra;
            parse_flag_list_relaxed(tokens, mask, extra);

            outCfg.flags.presets[presetName] = mask;
            if (!extra.empty()) outCfg.flags.extra_tokens[presetName] = std::move(extra);
            else outCfg.flags.extra_tokens.erase(presetName);
        }

        return true;
    }

    // ---------- main parse ----------

    inline bool parseCompilerConfig(const std::filesystem::path& path,
                                    CompilerConfig& outCfg,
                                    std::string& err)
    {
        err.clear();

        auto result = toml::parse_file(path.string());
        if (!result)
        {
            err = std::string("TOML parse error: ") +
                std::string(result.error().description());
            return false;
        }

        const toml::table& root = result;

        if (auto name = get_string(root, "project_name"))
            outCfg.projectName = *name;

        // [files] (required)
        const toml::table* filesTbl = nullptr;
        if (!require_table(root, "files", filesTbl, err))
            return false;

        {
            std::string dir;
            if (!require_string(*filesTbl, "files_dir", dir, err))
                return false;

            outCfg.files.filesDir = dir;
        }

        // [link] (optional)
        if (auto linkTbl = root["link"].as_table())
        {
            outCfg.link.libs = get_string_array(*linkTbl, "libs");
        }

        // [flags] (optional, relaxed)
        if (!parse_flags_table(root, outCfg, err))
            return false;

        return true;
    }
} // namespace cfg

struct CompilationController
{
    static constexpr std::string_view defaultConfigPath = "./validate.toml";

    CompilerConfig config;
    std::filesystem::path filesDirectory;

    bool loadConfiguration(const std::filesystem::path& path, std::string& err)
    {
        CompilerConfig tmp{};
        if (!cfg::parseCompilerConfig(path, tmp, err))
            return false;

        config = std::move(tmp);
        filesDirectory = config.files.filesDir;
        return true;
    }
};

#endif // INZ_COMPILER_CONTROLLER_HPP
