#pragma once

#include "json.hpp"
#include <fstream>

class Asar {
  public:
    Asar(const std::string _filename) {
      filename = _filename;

      std::ifstream stream(filename);

      char *size = new char[8];
      stream.read(size, 8);

      uint32_t uSize = *(uint32_t*)(size + 4) - 8;

      char *buffer = new char[uSize + 1];
      buffer[uSize] = '\0';

      stream.seekg(16);
      stream.read(buffer, uSize);

      header = json::JSON::Load(buffer);
      offset = uSize + 16;

      delete[] size;
      delete[] buffer;

      stream.close();
    }

    std::string content(const std::string path) {
      auto * c = resolve_asar_path(path);
      
      if (!exist(c)) return "";

      uint64_t _size = std::stoull(c->at("size").stringify());
      uint64_t _offset = std::stoull(c->at("offset").ToString());

      char * buffer = new char[_size];
      std::ifstream stream(filename, std::ios::binary);
      std::stringstream content;

      stream.seekg(offset + _offset);
      stream.read(buffer, _size);
      stream.close();
      
      content.write(buffer, _size);

      delete[] buffer;

      return content.str();
    }

    bool exist(const std::string path) {
      auto * c = resolve_asar_path(path);
      return !(c->IsNull());
    }

    bool exist(const json::JSON * file) {
      return !(file->IsNull());
    }

  protected:
    std::string filename;
    json::JSON header;
    int offset;
  
    json::JSON * resolve_asar_path(std::string path) {
      auto * address = &header.at("files"); 
      int e = path.find('/');
      
      while (e != std::string::npos) {
        std::string i = path.substr(0, e);
        path.erase(path.begin(), path.begin() + e + 1);
        e = path.find('/');

        if (i.empty()) continue;
        if (i.find_last_of(".") != std::string::npos) address = &address->at(i); // is_file
        else { address = &address->at(i); address = &address->at("files"); } // is_directory
      }

      address = &address->at(path.substr(0));
      return address;
    }
  };
