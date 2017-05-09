#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>

HWND hwnd = GetDesktopWindow();
std::string password = "";
std::string character =   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							"abcdefghijklmnopqrstuvwxyz"
							"0123456789"
							"@#$%!";
int length = character.length() - 1;
std::string randomize(int k);
void toClipboard(HWND hwnd, const std::string &s);

int main()
{
	srand(time(NULL));

	while(true)
	{
		char next;
		int how_many = 0;

		std::cout << "\nHow many characters in the password? ";
		std::cin >> how_many;
		bool success = std::cin.good();
		if (success == false) break;
        std::cout << "\n[1] Roll again\n"
                    "[2] Change password length\n"
                    "[C] Copy to clipboard\n"
                    "[ESC] Exit program\n\n"
                    "Generated password: " << randomize(how_many);
		do
		{

			next = _getch();
			if (next == 99) next=toupper(next);
			switch (next)
			{
			case '1':
				std::cout << "\rGenerated password: " << randomize(how_many);
				break;
			case '2':
			    system("cls");
				break;
			case 'C':
				toClipboard(hwnd, password);
				break;
			case 27:
				exit(0);
			default:
				std::cout << " No matching key shortcut!";
				break;
			}
		} while (next != '2');
	}
}

std::string randomize(int k)
{
	password.clear();
	for (int i = 0; i < k; i++)
	{
		password += character[rand() % length];
	}
	return password;
}

void toClipboard(HWND hwnd, const std::string &s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}
