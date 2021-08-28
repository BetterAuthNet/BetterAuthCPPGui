#include "includes.h"
#include "imgui/stb_image.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_xorstr.h"
int main() {
	if (!betterauth::init_application(L"betterauthexample"))
		return 0;
	gui::create_menu();
	system("pause");
}

const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

struct MenuInfo {
	enum TABS : uint8_t {
		t_login,
		t_register,
		t_activate_key,
		t_products
	};
	uint8_t tab = t_login;
	char username[15]{ 0 };
	char password[15]{ 0 };
	char key[20]{ 0 };
	bool is_logged_in = false;
	bool activated_key = false;
	int last_item = INT_MAX;
	bool has_sub = false;
	const WCHAR* time_left;
};
MenuInfo menuinfo;

void draw_login();
void draw_register();
void draw_activate_key();
void draw_products();
void gui::draw_menu() {
	ImGui::SetNextWindowSize(ImVec2(587, 220));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	if (ImGui::Begin("##mainpanel", 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{

		ImGui::GetOverlayDrawList()->AddRectFilled(ImGui::GetWindowPos() + ImVec2(1, 1), ImGui::GetWindowPos() + ImVec2(5, ImGui::GetWindowHeight() - 1), ImColor(13, 15, 25, 255), 2.5, ImDrawCornerFlags_All);
		ImGui::GetOverlayDrawList()->AddRectFilled(ImGui::GetWindowPos() + ImVec2(1, 1), ImGui::GetWindowPos() + ImVec2(118, 2), ImColor(13, 15, 25, 255), 2.5, ImDrawCornerFlags_All);
		ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + ImVec2(118, ImGui::GetWindowHeight()), ImColor(13, 15, 25, 255), ImGui::GetStyle().FrameRounding, ImDrawCornerFlags_All);


		ImGui::Columns(2, nullptr, false);
		{
			ImGui::SetCursorPosX(117 - (ImGui::CalcTextSize(xorstr("BetterAuth.net"), NULL, TRUE).x + 117) / 2);
			ImGui::TextColored(ImVec4(1, 1, 1, 1), xorstr("BetterAuth.net"));
			if (!menuinfo.is_logged_in) {
				if (ImGui::Button("Login")) {
					menuinfo.tab = menuinfo.t_login;
				}
				if (ImGui::Button("Register")) {
					menuinfo.tab = menuinfo.t_register;
				}
			}
			else
			{
				if (ImGui::Button("Activate key")) {
					menuinfo.tab = menuinfo.t_activate_key;
				}
				if (ImGui::Button("Products")) {
					menuinfo.tab = menuinfo.t_products;
				}
			}
			

		}
		ImGui::NextColumn();
		ImGui::SetColumnOffset(1, 117);
		{
			switch (menuinfo.tab) {
			case menuinfo.t_login: {
				draw_login();
				break;
			}
			case menuinfo.t_register: {
				draw_register();
				break;
			}
			case menuinfo.t_activate_key: {
				draw_activate_key();
				break;
			}
			case menuinfo.t_products: {
				draw_products();
				break;
			}
			}
		}
		ImGui::End();
	}
}

void draw_login() {
	ImGui::BeginChild(xorstr("##misc_main_child"), ImVec2(435, 165), true);
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (ImGui::CalcTextSize(xorstr("Login"), NULL, TRUE).x + ImGui::GetWindowWidth()) / 2);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
	
	ImGui::Text("Login");
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (290 + ImGui::GetWindowWidth()) / 2); ImGui::SetCursorPosY(40);
	ImGui::InputText("##lusername", (char*)menuinfo.username, 15);
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (290 + ImGui::GetWindowWidth()) / 2); ImGui::SetCursorPosY(80);
	ImGui::InputText("##lpassword", (char*)menuinfo.password, 15, ImGuiInputTextFlags_Password);
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (290 + ImGui::GetWindowWidth()) / 2); ImGui::SetCursorPosY(120);
	if (ImGui::Button("Login", ImVec2(ImGui::CalcTextSize("Login").x + 5, 30))) {
		if (betterauth::c_login(GetWC(menuinfo.username), GetWC(menuinfo.password))) {
			menuinfo.is_logged_in = true;
			menuinfo.tab = menuinfo.t_activate_key;
		}
	}
	ImGui::EndChild();
}

void draw_register() {
	ImGui::BeginChild(xorstr("##misc_main_child"), ImVec2(435, 165), true);
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (ImGui::CalcTextSize(xorstr("Register"), NULL, TRUE).x + ImGui::GetWindowWidth()) / 2);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
	ImGui::Text("Register");

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (290 + ImGui::GetWindowWidth()) / 2); ImGui::SetCursorPosY(40);
	ImGui::InputText("##lusername", (char*)menuinfo.username, 15);
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (290 + ImGui::GetWindowWidth()) / 2); ImGui::SetCursorPosY(80);
	ImGui::InputText("##lpassword", (char*)menuinfo.password, 15, ImGuiInputTextFlags_Password);
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (290 + ImGui::GetWindowWidth()) / 2); ImGui::SetCursorPosY(120);
	if (ImGui::Button("Register", ImVec2(ImGui::CalcTextSize("Register").x + 5, 30))) {
		if (betterauth::c_register(GetWC(menuinfo.username), GetWC(menuinfo.password))) {
			menuinfo.tab = menuinfo.t_login;
		}
	}
	ImGui::EndChild();
}

void draw_activate_key() {
	ImGui::BeginChild(xorstr("##misc_main_child"), ImVec2(435, 165), true);

	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (ImGui::CalcTextSize(xorstr("Key Activation"), NULL, TRUE).x + ImGui::GetWindowWidth()) / 2);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
	ImGui::Text("Key Activation");
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (290 + ImGui::GetWindowWidth()) / 2); ImGui::SetCursorPosY(40);
	ImGui::InputText("##key", (char*)menuinfo.key, 20);

	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 100) / 2); ImGui::SetCursorPosY(80);
	if (ImGui::Button("Activate", ImVec2(100, 30))) {
		if (betterauth::c_activatekey(GetWC(menuinfo.key))) {
			menuinfo.activated_key = true;
			menuinfo.tab = menuinfo.t_products;
		}
	}
	ImGui::EndChild();
}

void draw_products() {
	ImGui::BeginChild(xorstr("##misc_main_child"), ImVec2(435, 165), true);

	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - (ImGui::CalcTextSize(xorstr("Products"), NULL, TRUE).x + ImGui::GetWindowWidth()) / 2);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
	ImGui::Text("Products");
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));
	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcItemWidth()) / 2);
	const char* items[] = { "Product1", "Product2" }; //Product1 = Index 0 -> Webpanel productid 0
	static int item_current = 0;
	ImGui::Combo("##productcombo", &item_current, items, IM_ARRAYSIZE(items), 3);

	if (menuinfo.last_item != item_current || menuinfo.activated_key) {
		menuinfo.time_left = betterauth::has_sub(item_current, &menuinfo.has_sub);
		menuinfo.last_item = item_current;
		menuinfo.activated_key = false;
	}
	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 120) / 2);
	if (menuinfo.has_sub) {
		if (ImGui::Button("Download product", ImVec2(120, 30))) {
			uintptr_t data; DWORD size;
			if (betterauth::get_file(item_current, &data, &size)) {
				//
			}
		}
	}
	ImGui::EndChild();
}