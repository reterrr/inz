#ifndef INZ_COMPILER_CONTROLLER_HPP
#define INZ_COMPILER_CONTROLLER_HPP

#define TOML_EXCEPTIONS 0

#include "tomlplusplus/toml.hpp"
#include <filesystem>
#include <string>
#include <vector>
#include <optional>


struct CompilerConfig
{
    std::string projectName;

    struct Files
    {
        std::filesystem::path filesDir;
        std::vector<std::string> sources;
        std::vector<std::filesystem::path> includeDirs;
        std::vector<std::string> exclude;
        bool recursive = false;
    } files;

    struct Libs
    {
        std::vector<std::string> link;
        std::vector<std::filesystem::path> libDirs;
        std::vector<std::filesystem::path> includeDirs;
    } libs;

    struct Toolchain
    {
        std::string cxx; // e.g. "clang++"
        std::string cppStd; // e.g. "c++20" (avoid member name "std")
        std::vector<std::string> flags;
        std::vector<std::string> defines;
    } compiler;
};

namespace cfg
{
    inline std::optional<std::string> get_string(const toml::table& t, std::string_view key)
    {
        if (auto v = t[key].value<std::string>())
            return *v;
        return std::nullopt;
    }

    inline std::optional<bool> get_bool(const toml::table& t, std::string_view key)
    {
        if (auto v = t[key].value<bool>())
            return *v;
        return std::nullopt;
    }

    inline std::vector<std::string> get_string_array(const toml::table& t, std::string_view key)
    {
        std::vector<std::string> out;
        if (auto arr = t[key].as_array())
        {
            for (auto&& node : *arr)
                if (auto s = node.value<std::string>())
                    out.push_back(*s);
        }
        return out;
    }

    inline std::vector<std::filesystem::path> get_path_array(const toml::table& t, std::string_view key)
    {
        std::vector<std::filesystem::path> out;
        if (auto arr = t[key].as_array())
        {
            for (auto&& node : *arr)
                if (auto s = node.value<std::string>())
                    out.emplace_back(*s);
        }
        return out;
    }

    inline bool require_table(const toml::table& root,
                              std::string_view key,
                              const toml::table*& outTable,
                              std::string& err)
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

    inline bool require_string(const toml::table& t,
                               std::string_view key,
                               std::string& outValue,
                               std::string& err)
    {
        if (auto s = t[key].value<std::string>())
        {
            outValue = *s;
            return true;
        }
        err = "Missing or invalid string key: " + std::string(key);
        return false;
    }

    // Returns true on success, false on failure (with err filled).
    inline bool parseCompilerConfig(const std::filesystem::path& path,
                                    CompilerConfig& outCfg,
                                    std::string& err)
    {
        err.clear();

        // With TOML_EXCEPTIONS=0 this returns toml::noex::parse_result
        auto result = toml::parse_file(path.string());

        if (!result) // parse failed
        {
            // toml++ exposes an error object in noex mode
            // description() is commonly available; keep formatting simple.
            err = std::string("TOML parse error: ") + std::string(result.error().description());
            return false;
        }

        // Avoid ambiguous conversion by binding to const-ref:
        const toml::table& root = result;

        // top-level (optional)
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
            outCfg.files.sources = get_string_array(*filesTbl, "sources");
            outCfg.files.includeDirs = get_path_array(*filesTbl, "include_dirs");
            outCfg.files.exclude = get_string_array(*filesTbl, "exclude");

            if (auto r = get_bool(*filesTbl, "recursive"))
                outCfg.files.recursive = *r;
        }

        // [libs] (optional)
        if (auto libs = root["libs"].as_table())
        {
            outCfg.libs.link = get_string_array(*libs, "link");
            outCfg.libs.libDirs = get_path_array(*libs, "lib_dirs");
            outCfg.libs.includeDirs = get_path_array(*libs, "include_dirs");
        }

        // [compiler] (optional)
        if (auto comp = root["compiler"].as_table())
        {
            if (auto cxx = get_string(*comp, "cxx")) outCfg.compiler.cxx = *cxx;
            if (auto st = get_string(*comp, "std")) outCfg.compiler.cppStd = *st;

            outCfg.compiler.flags = get_string_array(*comp, "flags");
            outCfg.compiler.defines = get_string_array(*comp, "defines");
        }

        return true;
    }
} // namespace cfg

struct CompilationController
{
    static constexpr std::string_view defaultConfigPath = "./validate.toml";

    CompilerConfig config;
    std::filesystem::path filesDirectory;

    // Return status instead of throwing
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
#endif
