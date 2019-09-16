// PC INFO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

//program warning errors
#pragma warning(disable : 4996)

#pragma region funkcje
void Start();
std::string numerKomputera();
std::string exec(const char* cmd);
void saveToFile(std::string sepparator, std::string text);
void zaslaw();
void backup(std::string outFileName);
#pragma endregion

int main()
{
	Start();
}

void Start()
{
#pragma region space
	std::string line = "-------------------------------------------------------------------------------";
	std::string stars = "*******************************************************************************";
#pragma endregion

#pragma region pobranie numeru komputera i backup
	auto _numerKomputera = numerKomputera();
	backup(_numerKomputera);
	saveToFile(stars, _numerKomputera);
#pragma endregion
	system("cls");
	zaslaw();
	std::cout << std::endl << std::endl << std::setfill(' ') << std::setw(32) << _numerKomputera << std::endl;
#pragma region pobranie nazwy komputera grupy roboczej opisu komputerera oraz u¿ytkownikow
	auto _daneKomputera = exec("wmic computersystem get name,domain,model,manufacturer");
	auto _serialNumber = exec("wmic bios get serialnumber");
	auto _user = exec("wmic computersystem get username");
	auto _komp = _daneKomputera + _serialNumber + _user;

	saveToFile(line, _komp);
#pragma endregion
	std::cout << "Dane komputera: SUCCESS" << std::endl;
#pragma region pogranie IP komputera
	auto _ip = exec("wmic nicconfig where 'IPEnabled = True' get ipaddress, IPSubnet, defaultipgateway");
	if (_ip == "\r\n\r\n")
		std::cout << "IP komputera: FAILED!" << std::endl;
	else {
		saveToFile(line, _ip);
		std::cout << "IP komputera: SUCCESS" << std::endl;
	}
#pragma endregion
#pragma region pobieranie pamieci ram
	auto _ram = "RAM \n" + exec("wmic memorychip get capacity");
	saveToFile(line, _ram);
#pragma endregion
	std::cout << "Ram: SUCCESS" << std::endl;
#pragma region pobranie dyskow
	auto _disk = "DISK \n" + exec("wmic diskdrive GET index,caption,name,size");
	saveToFile(line, _disk);
#pragma endregion
	std::cout << "Dyski w komputerze: SUCCESS" << std::endl;
#pragma region pobranie programow
	auto _programy = "PROGRAMS \n" + exec("wmic product get name,version");
	saveToFile(line, _programy);
#pragma endregion
	std::cout << "Programy w komputerze: SUCCESS" << std::endl;
	saveToFile(stars, "");

	system("pomoc.txt");
	system("Magical\keyfinder.exe");
	remove("pomoc.txt");
	exit(0);
}

std::string numerKomputera()
{
	std::string numer;
	int nr;
	std::cout << "Podaj numer komputera: ";
	std::cin >> nr;

	if (nr < 10)
	{
		numer += "K00";
		numer += std::to_string(nr);
	}
	else if (nr < 100 && nr >= 10)
	{
		numer += "K0";
		numer += std::to_string(nr);
	}
	else
	{
		numer += "K";
		numer += std::to_string(nr);
		numer += "\n";
	}
	return numer;
}

std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}

void saveToFile(std::string sepparator, std::string text)
{
	std::fstream file("RejestrKomputerow.txt", std::ios::app);
	std::fstream file2("pomoc.txt", std::ios::app);

	text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());
	file << sepparator << std::endl;
	file << text << std::endl;

	file2 << sepparator << std::endl;
	file2 << text << std::endl;

	file.close();
	file2.close();
}

void zaslaw()
{
	std::cout << "    _/_/_/_/_/    _/_/      _/_/_/  _/          _/_/    _/          _/\n";
	std::cout << "         _/    _/    _/  _/        _/ _/     _/    _/  _/          _/ \n";
	std::cout << "      _/      _/_/_/_/    _/_/    _/_/      _/_/_/_/  _/    _/    _/  \n";
	std::cout << "   _/        _/    _/        _/  _/        _/    _/    _/  _/  _/     \n";
	std::cout << "_/_/_/_/_/  _/    _/  _/_/_/    _/_/_/_/  _/    _/      _/  _/        \n";

}

void backup(std::string outFileName)
{
	std::ifstream inFile("RejestrKomputerow.txt");

	std::ofstream outFile(("backup/" + outFileName + ".txt").c_str());
	outFile << inFile.rdbuf();
}