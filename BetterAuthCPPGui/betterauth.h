namespace betterauth {

	extern "C" __declspec(dllimport) bool init_application(const WCHAR * application_name);
	extern "C" __declspec(dllimport) bool get_file(DWORD id, uintptr_t * data, DWORD * size);
	extern "C" __declspec(dllimport) bool c_register(const WCHAR * username, const WCHAR * password);
	extern "C" __declspec(dllimport) bool c_login(const WCHAR * username, const WCHAR * password);
	extern "C" __declspec(dllimport) bool c_activatekey(const WCHAR * key);
	extern "C" __declspec(dllimport) const WCHAR * has_sub(DWORD productid, bool* hassub);
}