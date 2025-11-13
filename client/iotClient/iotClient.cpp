//The client application is NOT a program to run on an IoT device; rather it emulates an IoT device

#include <iostream>
#include <nlohmann/json.hpp>
#include "httplib.h"
#include <random>
#include <string>

//Items necessary for random number generation
std::random_device rd;
std::mt19937 gen(rd()); // Seed the engine with a truly random value
std::uniform_int_distribution<> first_digit(1, 223);
std::uniform_int_distribution<> other_digits(1, 255);

//int giveRandom(std::uniform_int_distribution<> distrib);
//std::string giveIP();

class Sensor {
private:
	int giveRandom(std::uniform_int_distribution<> distrib) {
		return distrib(gen);

	}

	std::string giveIP() {
		return std::to_string(giveRandom(first_digit)) + "." + std::to_string(giveRandom(other_digits)) + "." + std::to_string(giveRandom(other_digits)) + "." + std::to_string(giveRandom(other_digits));
	}
public:
	float lat;
	float lon;
	std::string countryCode;
	std::string region;

	Sensor() {
		//Constructor Function to assign key member attributes of the class on creation
		httplib::Client cli("http://ip-api.com");

		while(true) {
			std::string currentIP = giveIP();
			auto res = cli.Get("/json/" + currentIP);
			if (res && res->status == 200) {

				auto res_body = nlohmann::json::parse(res->body);
				if (res_body["status"] == "success") {
					this->lat = res_body["lat"];
					this->lon = res_body["lon"];
					this->countryCode = res_body["countryCode"];
					this->region = res_body["region"];
					
					break;
				}
				//If the above branch does not execute, then the above request had a status of "failure".
			}
			else {
				std::cout << "Error: " << (res ? std::to_string(res->status) : "Request failed") << std::endl;
				break;
			}
		}


	}
};

int main() {

	Sensor testing;
	std::cout << std::to_string(testing.lat);
//	std::string currentIP = giveIP();
//
//	httplib::Client cli("http://ip-api.com");
//	auto res = cli.Get("/json/" + currentIP);
//	//std::cout << res;
//	if (res && res->status == 200) {
//		//std::cout << res->body << std::endl;
//		auto meat = nlohmann::json::parse(res->body);
//		std::cout << meat["countryCode"] << ",   " << meat["lat"] << std::endl;
//}
//	else {
//		std::cout << "Error: " << (res ? std::to_string(res->status) : "Request failed") << std::endl;
//	}

	//nlohmann::json test_color = {
	//	{"id", 6},
	//	{"color", "black"}
	//};

	//res = cli.Post("/colors", test_color.dump(), "application/json");

	//if (res && res->status == 201) {
	//	std::cout << "Color added successfully: " << res->body << std::endl;
	//}
	//else {
	//	std::cout << "Error adding color: " << (res ? std::to_string(res->status) : "Request failed") << std::endl;
	//}
}

//int giveRandom(std::uniform_int_distribution<> distrib) {
//	return distrib(gen);
//
//}
//
//std::string giveIP() {
//	return std::to_string(giveRandom(first_digit)) + "." + std::to_string(giveRandom(other_digits)) + "." + std::to_string(giveRandom(other_digits)) + "." + std::to_string(giveRandom(other_digits));
//}
