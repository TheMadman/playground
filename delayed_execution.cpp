#include <functional>
#include <cstdio>
#include <array>

auto delay(const auto &callback, const auto & ... params)
{
	return std::function{[callback, params...]() {
		return callback(params...);
	}};
}

int main()
{
	std::array jobs{
		delay(std::printf, "%d:%s\n", 4, "four"),
		delay(std::puts, "wibbly"),
	};

	for (auto job : jobs) {
		job();
	}

	return 0;
}
