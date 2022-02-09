#pragma once
#include <vector>
#include <string>
#include "Vector3.h"

#include <iostream>
#include <fstream>

class OutputData
{
public:
	void ExportDataTxt(std::string& exportTxtPath, double& timestep, std::vector<Vector3>& dataListPos, std::vector<Vector3>& dataListVel, std::vector<Vector3>& dataListAcc);
};