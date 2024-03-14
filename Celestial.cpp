#include "Celestial.h"

void CelestialBody::makeVertices()
{
	float x, y, z, xy;                // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                       // vertex texCoord

	float sectorStep = float(2 * M_PI / sectorCount);
	float stackStep = float(M_PI / stackCount);
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = float(M_PI / 2 - i * stackStep);// starting from pi/2 to -pi/2
		xy = 1.02f * radius * cosf(stackAngle); // r * cos(u)
		z = radius * sinf(stackAngle);          // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep; // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);  // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);  // r * cos(u) * sin(v)
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			vertices.push_back(nx);
			vertices.push_back(ny);
			vertices.push_back(nz);

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			vertices.push_back(s);
			vertices.push_back(t);
		}
	}


	// generate CCW index list of sphere triangles
	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
}


void Planet::createModel(float time)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, currentOrigin);
}

void Star::createModel(float time)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, origin);

}
