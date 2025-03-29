#include <application/asset-processor-application.h>

#include <vector>
#include <filesystem>

#include <spdlog/spdlog.h>
#include <CLI/CLI.hpp>

#include "base-asset-processor.h"
#include "shader-processor.h"

/* -------------------------------------------- */
/* Command Line Options                         */
/* -------------------------------------------- */

static bool clear = false;
static bool forceProcess = false;
static bool recursive = false;
static bool flatten = false;
static bool softLinkFiles = false;
static int threadCount = 0;

static std::vector<std::filesystem::path> sysIncludePaths;

static std::vector<std::filesystem::path> inputs;
static std::filesystem::path output;

/* -------------------------------------------- */
/* Asset Processor                              */
/* -------------------------------------------- */


static std::vector<AssetProcessor::Processors::IBaseAssetProcessor*> processors;

void setupAssetProcessors() {
    processors.push_back(new AssetProcessor::Processors::ShaderProcessor(sysIncludePaths));
}

void teardownAssetProcessors() {
    for (auto* processor: processors) {
        delete processor;
    }

    processors.clear();
}

void processFile(const std::filesystem::path& assetPath, const std::filesystem::path& outputDir) {
    std::string extension = assetPath.extension().string();

    try {
    if (!exists(outputDir)) {
        create_directories(outputDir);
    }

    for (auto* processor: processors) {
        if (processor->supportsFormat(extension)) {
            const std::filesystem::path outputFile = outputDir / processor->suggestFileName(assetPath.filename());

            bool reprocess = false;

             if (exists(outputFile)) {
                if (last_write_time(outputFile) < last_write_time(assetPath) || forceProcess) {
                    std::filesystem::remove(outputFile);
                    reprocess = true;
                } else {
                    spdlog::info("Skipping {}, already processed", assetPath.string());
                    return;
                }
            }

            std::ifstream input(assetPath);
            std::ofstream output(outputFile);

            processor->processFile(assetPath, input, output);

            if (reprocess) {
                spdlog::info(
                        "[{}] Out of date, reprocessing {}:\nOutput: {}",
                        processor->getProcessorName(),
                        assetPath.string(),
                        outputFile.string()
                );
            } else {
                spdlog::info(
                        "[{}] processed {}:\nOutput: {}",
                        processor->getProcessorName(),
                        assetPath.string(),
                        outputFile.string()
                );
            }

            return;
        }
    }


    const std::filesystem::path outputFile = outputDir / assetPath.filename();

        if (exists(outputFile)) {
            if (last_write_time(outputFile) < last_write_time(assetPath) || forceProcess) {
                std::filesystem::remove(outputFile);
            } else {
                spdlog::info("Skipping {}, already processed", assetPath.string());
                return;
            }
        }

        if (softLinkFiles) {
            create_symlink(assetPath, outputFile);
        } else {
            copy(assetPath, outputFile);
        }
    } catch (std::exception& e) {
        spdlog::error("Exception thrown whilst processing {}:\n{}", assetPath.string(), e.what());
    }
}

void processDirectory(const std::filesystem::path& assetDirPath, const std::filesystem::path& outputDir) {
    spdlog::info("Processing directory {}", assetDirPath.string());

  for (const auto& dirEntry : std::filesystem::directory_iterator(assetDirPath)) {
      if (dirEntry.is_directory() && recursive) {
          processDirectory(dirEntry.path(), outputDir / dirEntry.path().filename());
      } else {
          processFile(dirEntry.path(), outputDir);
      }
  }
}

int main(int argc, char *argv[]) {
    CLI::App app("Dat Shader Processor");
    app.description("A program for processing assets for the Dat Engine.\n"
                    "Compiles standard formats into Dat Engine specific formats, directly copies all other files.\n"
                    "If an output already exists, unless specified, it will only be replaced if the asset is newer than the output file");
    argv = app.ensure_utf8(argv);

    app.add_flag("--clear,-c", clear, "Clear the asset destination before processing")
        ->default_val(false);
    app.add_flag("--force,-F", forceProcess, "Force reprocessing assets that wouldn't normally be processed ")
        ->default_val(false);
    app.add_flag("--recursive,-r", recursive, "Recurse into subdirectories")
        ->default_val(false);
    app.add_flag("--flatten,-f", flatten, "Write all the output files to the same directory")
        ->default_val(false);
    app.add_flag("--link,-l", softLinkFiles, "Instead of copying files that don't have a processor, create symbolic links")
        ->default_val(false);
    app.add_option("--threads,-t", threadCount, "Number of threads to use")
        ->check(CLI::NonNegativeNumber)
        ->default_val(0);
    app.add_option("--shader-include,-s", sysIncludePaths, "Shader include files")
        ->check(CLI::ExistingDirectory);

    app.add_option("--input,-i", inputs, "A path to process.")
        ->required()
        ->check(CLI::ExistingPath);
    app.add_option("output", output, "Path to the output directory. All supplied paths will output to this directory")
        ->required();

    CLI11_PARSE(app, argc, argv);

    setupAssetProcessors();

    if (clear) {
        remove_all(output);
    }

    for (const auto& path : inputs) {
        try {
            if (is_directory(path)) {
                processDirectory(path, output);
            } else {
                processFile(path, output);
            }
        } catch (const std::exception& e) {
            spdlog::error("Error whilst processing input path: \"{}\":\n{}", path.string(), e.what());
        }
    }

    teardownAssetProcessors();
}