#pragma once

#include <vector>
#include "core.h"
#include "Vector3.h"
#include "VectorField.h"
#include "Background.h"

static double maxParticleVelocity = 100.0;
static double bounds = 1000000000.0;
static double mass = 0.0; //0 means magnitude of velocity is always max velocity

struct ParticleData //holds return data of the particle
{
    std::vector<Vector3> particlePositions;
    std::vector<Vector3> particleVelocities;
    std::vector<Vector3> particleAccelerations;

    Vector3 color = Vector3(0);
    double pathLength = 0;
    double lostVelocity = 0;

    ParticleData(); //init with default values

    ParticleData(Vector3 c); //init with color only

    ParticleData(double brightness); //init with color only

    ParticleData(double r, double g, double b); //init with color only

    Vector3 ReturnClippedColor(double lowerBound, double upperBound);

    Vector3 ReturnScaledColor(double scalar);

    double Clamp(double d, double lower, double upper);
};

struct Particle
{
	Vector3 position = Vector3(0);
	Vector3 velocity = Vector3(0);
#define pos position //me when lazy
#define vel velocity

    double attractorFieldStrength = 0;
    int bh = 1;

    ParticleData data = ParticleData();

    Particle(Vector3 initialPosition, Vector3 initialVelocity);

    void SetPosVel(Vector3 initialPosition, Vector3 initialVelocity);

    void DoSteps(int steps, double dt);//, int width, int height, Background& bg);

    void Terminate(int steps, double dt, int width, int height, Background& bg);
};