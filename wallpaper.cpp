#include <windows.h>
#include <cstdio>

// cl wallpaper.cpp user32.lib

void printusage(char *program)
{
	fprintf(stderr, "Usage:  %s background-file.bmp\n", program);
	fprintf(stderr, "   Changes desktop background to background-file\n");
	return;
}

int main(int argc, char *argp[])
{
	DWORD dResult;
	BOOL result;
	char oldWallPaper[255];

	if (argc != 2) {
		printusage(argp[0]);
		return 1;
	}

	result = SystemParametersInfo(
		SPI_GETDESKWALLPAPER,
		sizeof(oldWallPaper)-1,
		oldWallPaper,
		0);

	fprintf(stderr, "Current desktop background is %s\n", oldWallPaper);

	result = SystemParametersInfo(
		SPI_SETDESKWALLPAPER,
		0,
		argp[1],
		0);

	if (!result) {
		dResult = GetLastError();
		fprintf(stderr, "Attempt to set new desktop background failed; code%d\n", dResult);
		fprintf(stderr, "Will restore prior setting (%s)\n", oldWallPaper);

		result = SystemParametersInfo(
			SPI_SETDESKWALLPAPER,
			0,
			oldWallPaper,
			0);

		return 2;
	}

	fprintf(stderr, "Desktop background changed to %s\n", argp[1]);
	return 0;

}
