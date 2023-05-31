#include <Windows.h>
#include <thread>

#include "logger.h"

FILE* out;
FILE* err;

void Logger::Init()
{
	AllocConsole();
	freopen_s(&out, "CONOUT$", "w", stdout);
	freopen_s(&err, "CONOUT$", "w", stderr);

	Logger::Initialized = true;
}

void Logger::Kill()
{
	if (Logger::Initialized)
	{
		fclose(out);
		fclose(err);
		FreeConsole();
	}
}

void Logger::Log(std::string message)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ LOG ] :: " + message << std::endl;
}

void Logger::LogPosition(Vector3 position)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ LOG POS ] :: X -> " << position.x << " Y -> " << position.y << " Z ->" << position.z << std::endl;
}

void Logger::Err(std::string message)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ ERR ] :: " + message << std::endl;
}

void Logger::LogWait(std::string message, int seconds)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ LOG ] :: " + message << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void Logger::ErrWait(std::string message, int seconds)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ ERR ] :: " + message << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
