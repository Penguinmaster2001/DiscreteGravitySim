#pragma once

#include "core.h"
#include "Vector3.h"
#include "Particle.h"

struct ParticleEmitter
{
	Vector3& cameraPos;
	int& getWidth;
	int& getHeight;
	int& startX;
	int& endX;
	int& startY;
	int& endY;
	int& getSimSteps;
	double& simTimeStep;
	Background& bg;
	std::vector< std::vector<Vector3> >& finalPixel;
	
	ParticleEmitter(Vector3& cameraPos, int& width, int& height, int& startX, int& endX, int& startY, int& endY,
		int& simSteps, double& simTimeStep, Background& bg, std::vector< std::vector<Vector3> >& finalPixel);

	void EmitSpherical();
};