#include <benchmark/benchmark.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <immintrin.h>

using namespace std;

void lspace(const char *sp, size_t nb);

streampos memSize;
char *memblock;

static void setup(const benchmark::State &states)
{
    if (memSize > 0)
        return;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open("/mnt/c/Users/vbzha/Downloads/ubuntu-22.04.1-live-server-amd64.iso",
                  ios::in | ios::binary | ios::ate);

        if (file.is_open())
        {
            memSize = file.tellg();
            // cout << "the entire file content is in memory:" << memSize<< endl;
            memblock = (char *)_mm_malloc(memSize, 32);
            file.seekg(0, ios::beg);
            file.read(memblock, memSize);
            file.close();
        }
        cout << "space count:" << memSize << endl;
    }
    catch (ifstream::failure e)
    {
        cout << "failed to read file:" << e.what() << endl;
        // states.SkipWithError("failed to read file");
    }
}

// Define another benchmark
static void BM_StringCopy(benchmark::State &state)
{

    for (auto _ : state)
    {
        lspace(memblock, memSize);
    }
}
BENCHMARK(BM_StringCopy)->Setup(setup)->UseRealTime()->ThreadRange(1, 16);

BENCHMARK_MAIN();