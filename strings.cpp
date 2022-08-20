#include <cstring>
#include <fstream>
#include <iostream>
#include <immintrin.h>

using namespace std;


void lspace(const char *sp, size_t nb)
{
    int32_t ms;
    int32_t total = 0;
    
    const char *ss = sp;

    while (nb >= 32)
    {

        __m256i x = _mm256_load_si256((const __m256i *)sp);

        __m256i a = _mm256_cmpeq_epi8(x, _mm256_set1_epi8(' '));
        __m256i c = _mm256_cmpeq_epi8(x, _mm256_set1_epi8('\t'));
        __m256i d = _mm256_cmpeq_epi8(x, _mm256_set1_epi8('\n'));
        __m256i b = _mm256_cmpeq_epi8(x, _mm256_set1_epi8('a'));

        __m256i u = _mm256_or_si256(a, b);
        __m256i v = _mm256_or_si256(c, d);
        __m256i w = _mm256_or_si256(u, v);

        ms = _mm256_movemask_epi8(w);
        _mm256_zeroupper();
        total += __builtin_ctzll(~(uint64_t)ms);

        sp += 32;
        nb -= 32;
    }
    // cout << "space count:" << total << endl;
    return;
}
