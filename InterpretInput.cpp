#include "InterpretInput.h"

void InterpretInput::readFile(int& width, int& height, int& frames,
	std::string& backgroundPath, std::string& outputFolder, std::string& outputName,
	int& steps, double& deltaT,
	double& camX, double& camY, double& camZ, double& camDX, double& camDY, double& camDZ,
	std::string& filePath)
{
	std::fstream f;

	f.open(filePath, std::ios::in);

	if (!f.is_open())
	{
		std::cout << "Instruction file at\n" << filePath << "\ncould not be opened, make sure the path is valid and the slashes are switched\n";
		/*
		* Instruction file at
		* **filepath**
		* could not be opened, make sure the path is valid and the slashes are switched
		* 
		*/
		return;
	}

	std::vector < std::string > instructionLines;
	instructionLines.reserve(14);

	//read file into memory
	int line = 0;
	int lines = 14;
	std::string readLine;

	while (line < lines && !f.eof()) //legitimately shitty code, !f.eof() should always be true with a valid instructions file
	{
		f >> readLine;

		instructionLines.push_back(readLine);

		++line;
	}
	f.close();

	//string to string
	backgroundPath = instructionLines[0];
	outputFolder =   instructionLines[1];
	outputName =     instructionLines[2];

	//string to int
	width  = std::stoi(instructionLines[3]);
	height = std::stoi(instructionLines[4]);
	frames = std::stoi(instructionLines[5]);

	steps  = std::stoi(instructionLines[6]);

	//string to double
	deltaT = std::stod(instructionLines[7]);

	camX  = std::stod(instructionLines[ 8]);
	camY  = std::stod(instructionLines[ 9]);
	camZ  = std::stod(instructionLines[10]);

	camDX = std::stod(instructionLines[11]);
	camDY = std::stod(instructionLines[12]);
	camDZ = std::stod(instructionLines[13]);
}
