#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

struct InterpretInput
{
	void readFile(int& width, int& height, int& frames,
		std::string& backgroundPath, std::string& outputFolder, std::string& outputName,
		int& steps, double& deltaT,
		double& camX, double& camY, double& camZ, double& camDX, double& camDY, double& camDZ,
		std::string& filePath);
};