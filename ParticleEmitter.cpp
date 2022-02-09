#include "ParticleEmitter.h"

#include <string>

ParticleEmitter::ParticleEmitter(Vector3& cameraPos, int& width, int& height, int& startX, int& endX, int& startY, int& endY,
	int& simSteps, double& simTimeStep, Background& bg, std::vector< std::vector<Vector3> >& finalPixel) :
	cameraPos(cameraPos), getWidth(width), getHeight(height), startX(startX), endX(endX), startY(startY), endY(endY),
	getSimSteps(simSteps), simTimeStep(simTimeStep), bg(bg), finalPixel(finalPixel)
{
}

void ParticleEmitter::EmitSpherical()
{
	for (int x = startX; x < endX; ++x)
	{
		for (int y = startY; y < endY; ++y)
		{
			Vector3 startingVel = Vector3::PixelToSphericalDirection(x, y, getWidth, getHeight);

			Particle newParticle = Particle(cameraPos, startingVel);

			newParticle.DoSteps(getSimSteps, simTimeStep);

			Vector3 pixel = Vector3::DirectionToSphericalPixel(newParticle.velocity, getWidth, getHeight);

			//std::string track = std::to_string(startingVel.x) + " " + std::to_string(startingVel.y) + " " + std::to_string(startingVel.x) + " " + " " + std::to_string(x) + " " + std::to_string(width) + "\n";

			//std::cout << track; // newParticle.velocity << "\n";// << " " << pixel << "\n";

			if (pixel.x <= 0 || pixel.y <= 0 || getWidth <= 0 || getHeight <= 0)
			{
				std::cout << "";
			}

			finalPixel[x][y] = (newParticle.bh * bg.GetPixel(pixel.x, pixel.y, getWidth, getHeight));
		}
	}
}
