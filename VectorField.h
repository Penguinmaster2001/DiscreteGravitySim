#pragma once

#include "core.h"
#include "Vector3.h"
#include <cmath>

static constexpr long double G = 6.6743e-11; //grav const (m^3 Kg^-1 s^-2)
static constexpr long double M = 5.9724e24; //mass of Earth (Kg)

static constexpr double T = 1E6; //spin const
static constexpr double S = 1;   //spin speed, ang vel or somthn? idk what this even is

static constexpr long double GM = G * M; //this would need to be calculated every time step

static struct VectorField
{
	//static double attractorFieldStrength; //this is for areas within the field that particles may not be able to escape, such as a gravitational field

	static double GetG();
	static double GetM();

	static Vector3 SamplePoint(Vector3* v, double* attractorFieldStrength);
};