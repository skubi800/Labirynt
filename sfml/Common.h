#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <chrono>
#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include <random>

class IMainMenu {

public:
	virtual void showMenu() = 0;
};