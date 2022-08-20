#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>
#include <pthread.h>
#include <immintrin.h>

using namespace std;

void lspace(const char *sp, size_t nb);

int main(int, char **)
{
  streampos size;
  char *memblock;

  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try
  {
    file.open("/mnt/c/Users/vbzha/Downloads/"
              "512.95-desktop-win10-win11-64bit-international-dch-whql.exe",
              ios::in | ios::binary | ios::ate);

    if (file.is_open())
    {
      size = file.tellg();
      cout << "the entire file content is in memory:" << size << endl;
      memblock = (char *)_mm_malloc(size, 32);
      file.seekg(0, ios::beg);
      file.read(memblock, size);
      file.close();
      std::thread f1(lspace, memblock, size);
      std::thread f2(lspace, memblock, size);
      std::thread f3(lspace, memblock, size);
      std::thread f4(lspace, memblock, size);
      std::thread f5(lspace, memblock, size);

      f1.join();
      f2.join();
      f3.join();
      f4.join();
      f5.join();
      delete[] memblock;
    }
  }
  catch (ifstream::failure e)
  {
    cout << "failed to read file:" << e.what() << endl;
  }
}
