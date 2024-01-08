# 📤 asar.hpp
asar.hpp | C++ asar unpacker library.

```cpp
#include "asar.hpp"

int main() {
  Asar resources("path/to/file.asar");

  std::string data = resources.content("/path/to/file");
  bool exist = resources.exist("/path/to/file");

  return 1;
}
```

## 📜 License

- [asar.hpp](./) - The Unlicensed
- [json.hpp](https://github.com/FelipeIzolan/json.hpp/) - The Unlicensed
