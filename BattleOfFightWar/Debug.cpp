#include "debug.h"

std::ofstream OutputStream("debug.txt");

Debug::Debug()
{
}

void Debug::releaseDebug()
{
	if (OutputStream.good()) {
		OutputStream.close();
	}
}

void Debug::end(int nr)
{
	for (int i = 0; i< nr; i++) {
		OutputStream << std::endl;
	}
}

void Debug::print(char c[])
{
	OutputStream << c << std::endl;
}

std::ofstream& Debug::operator<<(char c[])
{
	OutputStream << c;
	return OutputStream;
}

std::ofstream& Debug::operator<<(int i)
{
	OutputStream << i;
	return OutputStream;
}

std::ofstream& Debug::operator<<(float f)
{
	OutputStream << f;
	return OutputStream;
}

std::ofstream& Debug::operator<<(bool b)
{
	if (b) {
		OutputStream << "True";
	} else {
		OutputStream << "False";
	}
	return OutputStream;
}

std::ofstream& Debug::operator<<(D3DXVECTOR3 V)
{
	OutputStream << "x: " << V.x << ", y: " << V.y << ", z: " << V.z;
	return OutputStream;
}