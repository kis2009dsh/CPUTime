#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <array>
#include <utility>
#include <type_traits>
#include <cstdint>
#include <cmath>

#include <Windows.h>

int main()
{
	::SetProcessAffinityMask(
		::GetCurrentProcess(),
		0x00000001          //cpu mask
		);

	const std::uint32_t count = 100;  
	const std::double_t PI = 3.1415926536;
	const std::double_t time = 200;
	const std::double_t step = 2.0 * PI / count;

	std::array<std::double_t, count> sin_fun;

	for (int i = 0; i < count; ++i) {
		sin_fun[i] = std::sin(step * i) * time / 2 + time / 2;
	}

	std::uint32_t j(0);
	while (true) {

		/// Busy
		auto current = std::chrono::system_clock::now();
		while (true) {
			auto next = std::chrono::system_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(next - current);
			if (duration.count() > sin_fun[j])
				break;
		}

		/// Idle
		std::this_thread::sleep_for(std::chrono::milliseconds(std::uint32_t(time - sin_fun[j])));

		j = (j + 1) % count;
	}

	return 0;
}
