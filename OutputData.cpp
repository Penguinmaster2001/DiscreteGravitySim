#include "OutputData.h"

void OutputData::ExportDataTxt(std::string& exportTxtPath, double& timeStep, std::vector<Vector3>& dataListPos, std::vector<Vector3>& dataListVel, std::vector<Vector3>& dataListAcc)
{
	std::fstream f;

	f.open(exportTxtPath, std::ios::out);

	if (!f.is_open())
	{
		std::cout << "File could not be created at\n" << exportTxtPath << "\nMake sure the path is valid and the slashes are switched in the instruction file";
		/*
		* File could not be created at
		* **exportTxtPath**
		* Make sure the path is valid and the slashes are switched in the instruction file
		* 
		*/
	}

	int size = dataListPos.size();
	int interval = floor(double(size) / 10000.0);
	interval += (interval < 1) * 1;

	f << "index,time,posx,posy,posz,r,errr,th,errth,velx,vely,velz,v,accx,accy,accz,a";

	for (int i = 0; i < size; i += interval)
	{
		double r = Vector3::CalcLength(dataListPos[i]);
		double v = Vector3::CalcLength(dataListVel[i]);
		double a = Vector3::CalcLength(dataListAcc[i]);
		double th = acos(dataListPos[i].x / r); //dot product of the vector [1,0,0], and pos of particle
		th *= 1.0 + (-2.0 * (dataListPos[i].y + dataListPos[i].z < 0)); //allows the angle to be negative

		f << ("\n" + std::to_string(i) + "," + std::to_string(timeStep * i) + ","
			+ Vector3::Vector3ToString(dataListPos[i]) + "," + std::to_string(r) + "," + std::to_string(0.0) + ","
			+ std::to_string(th) + "," + std::to_string(0.00174532925199) + "," //0.1 deg error
			+ Vector3::Vector3ToString(dataListVel[i]) + "," + std::to_string(v) + ","
			+ Vector3::Vector3ToString(dataListAcc[i]) + "," + std::to_string(a)).c_str();
	}

	//f << "time,measuredTimeInterval,angle";

	//double c = 299792458;

	//for (int i = 0; i < size; i += interval)
	//{
	//	double r = Vector3::CalcLength(dataListPos[i]);
	//	double tm = (2.0 * r) / c;
	//	double th = acos(dataListPos[i].x / r); //dot product of the vector [1,0,0], and pos of particle
	//	th *= 1.0 + (-2.0 * (dataListPos[i].y + dataListPos[i].z < 0)); //allows the angle to be negative

	//	f << ("\n" + std::to_string(timeStep * i) + "," + std::to_string(tm) + "," + std::to_string(th)).c_str();
	//}

	std::cout << ".csv file is " << std::to_string(size / interval) << " lines long\n";

	f.close();
}