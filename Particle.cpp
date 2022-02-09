#include "Particle.h"

/*
* ############################################################################# 
* ParticleData struct
* #############################################################################
*/

ParticleData::ParticleData()
{
}

ParticleData::ParticleData(Vector3 c) :
	color(c)
{
}

ParticleData::ParticleData(double brightness) :
	color(brightness)
{
}

ParticleData::ParticleData(double r, double g, double b) :
	color(r, g, b)
{
}

Vector3 ParticleData::ReturnClippedColor(double lowerBound, double upperBound)
{
	return Vector3(Clamp(color.x, lowerBound, upperBound),
		Clamp(color.y, lowerBound, upperBound),
		Clamp(color.z, lowerBound, upperBound));
}

Vector3 ParticleData::ReturnScaledColor(double scalar)
{
	return scalar * Vector3::Normalize(color);
}

double ParticleData::Clamp(double d, double lower, double upper)
{
	if (d < lower)
		return lower;

	if (d > upper)
		return upper;

	return d;
}

/*
* #############################################################################
* Particle struct
* #############################################################################
*/

Particle::Particle(Vector3 initialPosition, Vector3 initialVelocity) :
	position(initialPosition), velocity(initialVelocity)
{
	double rs = (2.0 * VectorField::GetG() * VectorField::GetM()) / (maxParticleVelocity * maxParticleVelocity);   //Schwarzchild radius
	double attractorFieldStrength = 0;
}

void Particle::DoSteps(int steps, double timeStep)//, int width, int height, Background& bg)
{
	Vector3 fieldStrength = Vector3();

	for(int step = 0; step < steps; ++step)
	{
		//sample vector field
		fieldStrength = VectorField::SamplePoint(&position, &attractorFieldStrength);

		//test if the particle is trapped (acc > maxVel), meaning it will never see background, and never existed in the first place if time moved in the correct direction
		/*if (-attractorFieldStrength > maxParticleVelocity)
		{
			bh = 0;
			return;
		}*/

		//update particle velocity and position
		velocity = velocity + (timeStep * (fieldStrength));

		//velocity = maxParticleVelocity * Vector3::Normalize(velocity);

		position = position + (timeStep * velocity);

		//data.pathLength = data.pathLength + (timeStep * maxParticleVelocity);

		//test if the particle is out of bounds
		if (position.x + position.y + position.z > bounds)
		{
			return;
		}

		data.particlePositions.push_back(position);
		data.particleVelocities.push_back(velocity);
		data.particleAccelerations.push_back(fieldStrength);
	}
}

void Particle::Terminate(int steps, double dt, int width, int height, Background& bg)
{
	Vector3 pixel = Vector3::DirectionToSphericalPixel(velocity, width, height);

	data.color = bg.GetPixel(pixel.x, pixel.y, width, height);
	
	data.lostVelocity /= data.pathLength;
}

void Particle::SetPosVel(Vector3 initialPosition, Vector3 initialVelocity)
{
	position = initialPosition;
	velocity = initialVelocity;
}