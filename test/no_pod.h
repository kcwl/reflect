#pragma once
#include <boost/test/unit_test_suite.hpp>
#include <reflect.hpp>

BOOST_AUTO_TEST_SUITE(no_pod)

struct arm
{
	int left;
	int right;
};

struct leg :arm
{
	int left;
	int right;
	std::string flag;
};

struct person : leg
{
	int age;
	std::string name;
	std::vector<uint8_t> mac;
	std::vector<arm> arms;
};

struct s3dbi_role_base_info
{
	bool has_change_name;
	std::vector<uint8_t> login_pro_mac;
	int32_t sex;
	int32_t series;
	int32_t level;
	int32_t portrait;
	int32_t cur_exp;
	int32_t is_tong_member;
	int32_t last_login_map_id;
	int32_t new_birth_times;
	int64_t last_login_time;
	int64_t last_login_ip;
	std::string name;
	std::string login_pro_psw;
	uint32_t login_pro_ip;

	void swap(s3dbi_role_base_info& other)
	{
		std::swap(has_change_name, other.has_change_name);
		std::swap(login_pro_mac, other.login_pro_mac);
		std::swap(sex, other.sex);
		std::swap(series, other.series);
		std::swap(level, other.level);
		std::swap(portrait, other.portrait);
		std::swap(cur_exp, other.cur_exp);
		std::swap(is_tong_member, other.is_tong_member);
		std::swap(last_login_map_id, other.last_login_map_id);
		std::swap(new_birth_times, other.new_birth_times);
		std::swap(last_login_time, other.last_login_time);
		std::swap(last_login_ip, other.last_login_ip);
		std::swap(name, other.name);
		std::swap(login_pro_psw, other.login_pro_psw);
		std::swap(login_pro_ip, other.login_pro_ip);
	}
};

struct query_role_list_body_response
{
	std::vector<s3dbi_role_base_info> info;

	void swap(query_role_list_body_response& other)
	{
		std::swap(info, other.info);
	}
};


BOOST_AUTO_TEST_CASE(complex_type)
{
	constexpr std::size_t size = reflect::tuple_size_v<leg>;

	static_assert(size == 4);

	constexpr std::size_t a_size = reflect::tuple_size_v<query_role_list_body_response>;

	static_assert(a_size == 1);

	constexpr std::size_t str_size = reflect::tuple_size_v<std::string>;

	static_assert(str_size == 1);

	constexpr auto res = std::is_aggregate_v<s3dbi_role_base_info>;

	constexpr auto ress = std::is_aggregate_v<query_role_list_body_response>;
}

BOOST_AUTO_TEST_SUITE_END()