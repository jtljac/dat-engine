#include <filesystem>

#include <shader-processor.h>

int main(int argc, char *argv[]) {
    std::filesystem::path in = "/home/jacob/Projects/C++/dat-engine/engine-assets/gradient.comp";
    std::filesystem::path out = "/home/jacob/Projects/C++/dat-engine/cmake-build-debug/examples/test-project/assets";

    AssetProcessor::Processors::ShaderProcessor processor({});

    processor.processFile(in, out);
}