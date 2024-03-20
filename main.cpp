#include <iostream>
#include <memory>
#include <string>

using namespace std::literals::string_literals;

class NTDtor {
    public:
    NTDtor() { std::cout << "constructed"s << std::endl; }
    ~NTDtor() { std::cout << "destructed"s << std::endl; }
};

template <typename T>
struct Result {
	bool success;
	union {
		T value;
		std::string error;
	};

	~Result() noexcept { value.~T(); };
};

void a() {
    std::cout << "a"s << std::endl;
    Result<NTDtor>{.success{true}, .value{}};
}
void b() {
    std::cout << "b"s << std::endl;
    Result<int>{.success{true}, .value{5}};
}
void c() {
    std::cout << "c"s << std::endl;
    Result<int>{.success{false}, .error{"fdsa"s}};
}
void d() {
    std::cout << "d"s << std::endl;
    NTDtor{};
}
void e() {
    std::cout << "e"s << std::endl;
    Result<std::unique_ptr<NTDtor>>{
    	.success{true},
    	.value{std::make_unique<NTDtor>()},
    };
}

int main() {
    a();
    b();
    c();
    d();
    e();
}
