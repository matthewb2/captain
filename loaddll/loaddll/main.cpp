#include <windows.h>
#include <iostream>

/* Define a function pointer for our imported
 * function.
 * This reads as "introduce the new type f_funci as the type: 
 *                pointer to a function returning an int and 
 *                taking no arguments.
 *
 * Make sure to use matching calling convention (__cdecl, __stdcall, ...)
 * with the exported function. __stdcall is the convention used by the WinAPI
 */
typedef int (__stdcall *f_funci)();

int main(int argc, char* argv[])
{
  HINSTANCE hGetProcIDDLL = LoadLibrary(argv[1]);

  if (!hGetProcIDDLL) {
    std::cout << "could not load the dynamic library" << std::endl;
    return EXIT_FAILURE;
  }

  f_funci funci = (f_funci)GetProcAddress(hGetProcIDDLL, "funci");
  if (!funci) {
    std::cout << "could not locate the function" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "funci() returned " << funci() << std::endl;

  return EXIT_SUCCESS;
}