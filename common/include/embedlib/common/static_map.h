#include <cassert>
#include <iostream>
#include <array>
#include <limits>

template <typename KeyT, typename ValueT, size_t size>
class StaticMap {
public:
    struct Pair {
        KeyT key;
        ValueT value;
    };

    StaticMap(std::initializer_list<Pair> list) {
        assert(list.size() <= size);

        for (const Pair& pair : list) {
            list_[i] = pair;
        }
    }

    const char* operator[](EnumT index) {
        const char* str = nullptr;
        for (uint32_t i = 0; i < 128; i++) {
            if (index == list_[i].first) {
                str = list_[i].second;
                break;
            }
        }
        return str;
    }

private:
    std::array<Pair, 128> list_;
};

enum class MyEnum {
    kValue0,
    kValue1,
    kValue2,
    kValue3
};

int main(int argc, char** argv) {
    EnumString<MyEnum> my_enum = {{MyEnum::kValue0, "A string"},
                                  {MyEnum::kValue1, "Another string"},
                                  {MyEnum::kValue2, "More strings"},
                                  {MyEnum::kValue3, "Final string"}};

    std::cout << my_enum[MyEnum::kValue0] << std::endl;
    std::cout << my_enum[MyEnum::kValue1] << std::endl;
    std::cout << my_enum[MyEnum::kValue2] << std::endl;
    std::cout << my_enum[MyEnum::kValue3] << std::endl;
    std::cout << my_enum[4] << std::endl; // Causes compile-time error

    return 0;
}