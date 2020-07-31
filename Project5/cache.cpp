#include "dlist.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class LRUCache
{
private:
  int mem_size; // size of memory
  int *memory;
  struct block
  {
    int address; // its address in memory
    int data;
  };
  Dlist<block> cache;
  int cur_cache_size; // current length of `cache`
  int max_cache_size; // maximum length of `cache`
  static bool compare(const block *a, const block *b);
  // EFFECTS: returns true if two blocks have the same address
public:
  LRUCache(int cache_size, int memory_size); // constructor
  // Initialize `cur_cache_size`, `max_cache_size`, `memory`
  // Initialize all elements in `memory` to 0
  ~LRUCache(); // destructor

  int read(int address);
  // EFFECTS: returns data corresponding to address.

  void write(int address, int data);
  // EFFECTS: writes data to address, 0 <= address < mem_size.

  void printCache();
  // EFFECTS: prints the cache in given format
  void printMem();
  // EFFECTS: prints the memory in given format
};

bool LRUCache::compare(const block *a, const block *b)
{
  return (a->address == b->address); // Only compares address.
}

LRUCache::LRUCache(int cache_size, int memory_size)
{
  this->mem_size = memory_size;
  this->max_cache_size = cache_size;
  this->cur_cache_size = 0;
  // Init mem
  int *mem = new int[mem_size];
  this->memory = mem;
  for (int i = 0; i < mem_size; i++)
  {
    this->memory[i] = 0;
  }
}

LRUCache::~LRUCache()
{
  delete[] this->memory;
  // cache will be left to the destructor of Dlist<block>.
}

int LRUCache::read(int address)
{
  int data = 0;
  if (address < 0 || address >= this->mem_size)
  {
    cout << "ERROR: Address out of bound" << endl;
    throw - 1;
  }
  else
  {
    block *addrIn = new block;
    addrIn->address = address;
    block *blockFound;
    blockFound = this->cache.remove(compare, addrIn);
    if (blockFound) // hit
    {
      data = blockFound->data;
      this->cache.insertFront(blockFound);
    }
    else // miss
    {
      data = memory[address];
      block *newBlock = new block;
      newBlock->address = address;
      newBlock->data = data;
      if (cur_cache_size == max_cache_size)
      {
        block *blockRemoved = this->cache.removeBack();
        this->memory[blockRemoved->address] = blockRemoved->data;
        delete blockRemoved;
        cur_cache_size--;
      }
      this->cache.insertFront(newBlock);
      cur_cache_size++;
      delete addrIn;
    }
  }
  return data;
}

void LRUCache::write(int address, int data)
{
  if (address < 0 || address >= this->mem_size)
  {
    cout << "ERROR: Address out of bound" << endl;
    throw - 1;
  }
  else
  {
    block *addrIn = new block;
    addrIn->address = address;
    block *blockFound;
    blockFound = this->cache.remove(compare, addrIn);
    if (blockFound) // hit
    {
      blockFound->data = data;
      this->cache.insertFront(blockFound);
    }
    else
    { // miss
      block *newBlock = new block;
      newBlock->address = address;
      newBlock->data = data;
      if (cur_cache_size == max_cache_size)
      { // Remove the last, write its data to mem
        block *blockRemoved = this->cache.removeBack();
        this->memory[blockRemoved->address] = blockRemoved->data;
        delete blockRemoved;
        cur_cache_size--;
      }
      this->cache.insertFront(newBlock);
      cur_cache_size++;
    }
    delete addrIn;
  }
}
void LRUCache::printCache()
{
  for (int i = 0; i < this->cur_cache_size; i++)
  {
    block *currBlock = this->cache.removeFront();
    cout << currBlock->address << " " << currBlock->data << endl;
    this->cache.insertBack(currBlock);
  }
}

void LRUCache::printMem()
{
  for (int i = 0; i < this->mem_size; i++)
  {
    cout << this->memory[i];
    cout << " ";
  }
  cout << endl;
}

int main()
{
  int CACHESIZE;
  int MEMSIZE;
  bool EXIT = false;
  string INSTRUCTION;
  string temp;
  int address;
  int data;
  istringstream is;
  getline(cin, temp);
  is.str(temp);
  is >> CACHESIZE >> MEMSIZE;
  LRUCache L(CACHESIZE, MEMSIZE);
  while (!EXIT)
  {
    getline(cin, temp);
    is.clear();
    is.str(temp);
    is >> INSTRUCTION;
    try
    {
      if (INSTRUCTION == "READ")
      {
        if (is >> address)
        {
          if (is.peek() != EOF)
          {
            cout << "ERROR: Too many operands" << endl;
          }
          else
          {
            data = L.read(address);
            cout << data << endl;
          }
        }
        else
        {
          cout << "ERROR: Not enough operands" << endl;
        }
      }
      else if (INSTRUCTION == "WRITE")
      {
        if (is >> address && is >> data)
        {
          if (is.peek() != EOF)
          {
            cout << "ERROR: Too many operands" << endl;
          }
          else
          {
            L.write(address, data);
          }
        }
        else
        {
          cout << "ERROR: Not enough operands" << endl;
        }
      }
      else if (INSTRUCTION == "PRINTCACHE")
      {
        if (is.peek() != EOF)
        {
          cout << "ERROR: Too many operands" << endl;
        }
        else
        {
          L.printCache();
        }
      }
      else if (INSTRUCTION == "PRINTMEM")
      {
        if (is.peek() != EOF)
        {
          cout << "ERROR: Too many operands" << endl;
        }
        else
        {
          L.printMem();
        }
      }
      else if (INSTRUCTION == "EXIT")
      {
        if (is.peek() != EOF)
        {
          cout << "ERROR: Too many operands" << endl;
        }
        else
        {
          EXIT = true;
        }
      }
      else
      {
        cout << "ERROR: Unknown instruction" << endl;
      }
    }
    catch (int a)
    {
      continue;
    }
  }
  return 0;
}