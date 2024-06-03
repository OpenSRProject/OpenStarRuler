#pragma once
#include "glad/gl.h"
#ifdef _WIN32
// defines APIENTRY, GL/gl.h includes it but Glad doesn't
#  include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
#  include <OpenGL/glu.h>
#else
#  include <GL/glu.h>
#endif
#include "GLFW/glfw3.h"
