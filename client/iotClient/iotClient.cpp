// testhttp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include "httplib.h"

int main() {
	httplib::Client cli("localhost", 3000);
	auto res = cli.Get("/");
	if (res && res->status == 200) {
		std::cout << res->body << std::endl;
	}
	else {
		std::cout << "Error: " << (res ? std::to_string(res->status) : "Request failed") << std::endl;
	}

	/*
	httplib::Client cli("http://httpbin.org");
	if (auto res = cli.Get("/get")) {
		if (res->status == 200) {
			auto json = nlohmann::json::parse(res->body);
			std::cout << "Origin: " << json["origin"] << std::endl;
			std::cout << "URL: " << json["url"] << std::endl;
		}
		else {
			std::cout << "Status: " << res->status << std::endl;
		}
	}
	else {
		auto err = res.error();
		std::cout << "Error code: " << err << std::endl;
	}

	nlohmann::json j = {
		{"name", "John Doe"},
		{"age", 30},
		{"is_student", false},
		{"skills", {"C++", "Python", "JavaScript"}}
	};

	if (auto res = cli.Post("/post", j.dump(), "application/json")) {
		if (res->status == 200) {
			auto response_json = nlohmann::json::parse(res->body);
			std::cout << "Response JSON: " << response_json.dump(4) << std::endl;
		}
		else {
			std::cout << "Status: " << res->status << std::endl;
		}
	}
	else {
		auto err = res.error();
		std::cout << "Error code: " << err << std::endl;
	}
	*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
