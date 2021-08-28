#include <Windows.h>
#include <iostream>
#include <d3d11.h>
#include <tchar.h>


#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"

#pragma warning(disable : 4996)
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "libs\\BetterAuthUser.lib")
#include "betterauth.h"
#include "gui.h"

#define STB_IMAGE_IMPLEMENTATION
#define IMGUI_DEFINE_MATH_OPERATORS
