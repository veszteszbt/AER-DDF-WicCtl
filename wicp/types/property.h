#ifndef WICP_TYPES_PROPERTY_H
# define WICP_TYPES_PROPERTY_H
# include <chrono>
namespace wicp {
namespace types
{
	template <
		uintmax_t tMemberId,
		bool tAccess,
		typename Tvalue,
		uintmax_t tCooldownTime,
		size_t tHistorySize = 1
	>
	struct Property
	{
		static_assert(tHistorySize > 0, "History size must be greater than zero");

		typedef Tvalue value_type;

		constexpr static const bool access = tAccess;

		constexpr static const uintmax_t member_id = tMemberId;

		constexpr static const uintmax_t cooldown_time = tCooldownTime;

		constexpr static const size_t history_size = tHistorySize;
	};
}}
#endif