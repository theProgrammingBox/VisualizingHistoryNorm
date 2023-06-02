#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

float randomFloat(float min, float max)
{
	return (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
}

float InvSqrt(float number)
{
	long i = 0x5F1FFFF9 - (*(long*)&number >> 1);
	float tmp = *(float*)&i;
	return tmp;
	return tmp * 0.703952253f * (2.38924456f - number * tmp * tmp);
}

class Example : public olc::PixelGameEngine
{
public:
	int idx;

	const float beta1 = 0.9f;
	const float beta2 = 0.9f;
	const float epsilon = 1e-16f;

	float expDecayMean;
	float expDecayVariance;
	float mean;
	float variance;

	Example()
	{
		sAppName = "Example";
	}

	bool OnUserCreate() override
	{
		idx = 0;

		expDecayMean = 1.0f;
		expDecayVariance = 1.0f;
		mean = 0.0f;
		variance = 1.0f;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		/*expDecayMean *= beta1;
		expDecayVariance *= beta2;*/

		float input = randomFloat(0.0f, (ScreenHeight() * 0.5f - GetMouseY()) * 1);

		mean = beta1 * mean + (1.0f - beta1) * input;
		float delta = input - mean;
		variance = beta2 * variance + (1.0f - beta2) * delta * delta;

		/*float CorrectedMean = mean / (1.0f - expDecayMean);
		float CorrectedVariance = variance / (1.0f - expDecayVariance);*/

		/*float invStdDev = InvSqrt(CorrectedVariance + epsilon);
		float output = (input - CorrectedMean) * invStdDev;*/

		float invStdDev = InvSqrt(variance + epsilon);
		float output = (input - mean) * invStdDev;

		Draw(idx, (output * 0.25 + 1) * ScreenHeight() * 0.5);
		idx *= idx++ < ScreenWidth();
		DrawLine(idx, 0, idx, ScreenHeight(), olc::BLACK);
		return true;
	}
};

int main()
{
	srand(time(NULL));

	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}