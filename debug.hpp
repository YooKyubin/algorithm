#pragma once

#include <iostream>
#include <string_view>
#include <utility>

namespace debug
{
	inline std::string_view Trim(std::string_view name)
	{
		while (!name.empty() && name.front() == ' ')
		{
			name.remove_prefix(1);
		}

		while (!name.empty() && name.back() == ' ')
		{
			name.remove_suffix(1);
		}

		return name;
	}

	template <typename T, typename... Rest>
	void Print(std::string_view names, T&& value, Rest&&... rest)
	{
		const std::size_t comma = names.find(',');
		const std::string_view name = Trim(names.substr(0, comma));

		std::cout << name << ": " << std::forward<T>(value);
		// std::cerr << name << ": " << std::forward<T>(value);

		if constexpr (sizeof...(Rest) > 0)
		{
			std::cout << ", ";
			Print(names.substr(comma + 1), std::forward<Rest>(rest)...);
		}
		else
		{
			std::cout << '\n';
		}
	}
}

#define DBG(...) ::debug::Print(#__VA_ARGS__, __VA_ARGS__)

