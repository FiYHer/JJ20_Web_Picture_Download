#pragma once
#include <winsock2.h>
#include <windows.h>

#include <process.h>
#include <WinInet.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>

#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "ws2_32.lib")

typedef struct _ITEM
{
	std::string url;
	std::string name;
}item;

HWND g_hwnd;
std::string g_url;
std::string g_path;

std::mutex g_mutex;
std::vector<item> g_items;

std::string g_initialize_item;
std::string g_down_item;

std::string get_web_resource_code(std::string url, std::string name = "A")
{
	std::string res;

	auto open = InternetOpenA(name.c_str(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!open) return res;

	auto tag = InternetOpenUrlA(open, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (!tag)
	{
		InternetCloseHandle(open);
		return res;
	}

	unsigned long bres = 0;
	const int max_size = 10240;
	char buffer[max_size]{ 0 };
	while (true)
	{
		auto b = InternetReadFile(tag, buffer, max_size, &bres);
		if (!b || !bres) break;
		else res += buffer;

		Sleep(2);
	}

	InternetCloseHandle(open);
	InternetCloseHandle(tag);

	return res;
}

void dowmload_jpg(const std::string& path, const std::vector<std::string>& urls, std::string name = "G")
{
	for (int i = 0; i < urls.size(); i++)
	{
		auto open = InternetOpenA(name.c_str(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (open)
		{
			auto tag = InternetOpenUrlA(open, urls[i].c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
			if (tag)
			{
				std::string fi = path + std::string{ "\\" } + std::to_string(i) + std::string{ ".jpg" };
				HANDLE h = CreateFileA(fi.c_str(), GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
				if (h != INVALID_HANDLE_VALUE)
				{
					unsigned long bres = 0;
					const int max_size = 1024 * 1024;
					char* buffer = new char[max_size];
					if (buffer)
					{
						while (true)
						{
							auto b = InternetReadFile(tag, buffer, max_size, &bres);
							if (!b || !bres) break;
							else WriteFile(h, buffer, bres, &bres, NULL);

							Sleep(2);
						}

						delete[] buffer;
					}

					CloseHandle(h);
				}

				InternetCloseHandle(tag);
			}

			InternetCloseHandle(open);
		}
	}
}

void get_all_picture_url(std::string url, std::vector<std::string>& urls)
{
	std::vector<std::string> res;

	auto code = get_web_resource_code(url);
	if (code.empty()) return;

	auto npos = std::string::npos;
	std::string str_n = "点击浏览下一张壁纸";
	auto beg = code.find(str_n);
	if (beg != npos)
	{
		beg = url.find("_");
		if (beg != npos)
		{
			std::string temp = url.substr(0, beg + 1);
			int index = std::stoi(url.substr(beg + 1).c_str());
			temp += std::to_string(index + 1) + std::string{ ".html" };
			get_all_picture_url(temp, urls);
		}
		else
		{
			std::string temp = url.substr(0, url.size() - 5);
			temp += std::string{ "_2.html" };
			get_all_picture_url(temp, urls);
		}
	}

	std::string str_t = "<script>var id=";
	std::string str_b = "http:";
	std::string str_e = ".jpg";

	auto pos = code.find(str_t);
	beg = code.find(str_b, pos);
	auto end = code.find(str_e, beg);
	if (pos == npos || beg == npos || end == npos) return;
	std::string temp =/* std::string{ "http://pic.jj20.com" } +*/ code.substr(beg, end + str_e.size() - beg);
	urls.push_back(temp);
}

void _cdecl download_thread(void*)
{
	while (true)
	{
		item it;
		g_mutex.lock();
		if (g_items.size())
		{
			it = g_items.back();
			g_items.pop_back();
		}
		g_mutex.unlock();
		if (it.url.empty() || it.name.empty()) break;

		std::vector<std::string> urls;
		get_all_picture_url(std::string{ "http://www.jj20.com" } + it.url, urls);
		if (urls.empty()) continue;

		std::string path = g_path + std::string{ "\\" } + it.name;
		CreateDirectoryA(path.c_str(), 0);

		dowmload_jpg(path, urls, std::to_string(GetCurrentThreadId()));

		std::string show = std::to_string(g_items.size()) + std::string{ " - " } + it.name + std::string{ " \r\n " };
		show += std::move(g_down_item);
		g_down_item = std::move(show);
		SetWindowTextA(g_hwnd, g_down_item.c_str());
	}
}

void _cdecl initialize_thread(void*)
{
	auto pos = g_url.rfind("_");
	if (pos == std::string::npos) return;

	std::string url = g_url.substr(0, pos + 1);
	int index = std::stoi(g_url.substr(pos + 1).c_str());

	while (true)
	{
		std::string new_url = url + std::to_string(index++) + ".html";
		std::string code = get_web_resource_code(new_url);
		if (code.empty()) break;

		auto npos = std::string::npos;
		auto tag = code.find("g-tit-tp");
		auto stop = code.find("tsp_nav", tag);
		if (tag == npos || stop == npos) break;

		while (true)
		{
			item it;

			std::string str_b = "<a href=";
			std::string str_t = "target";
			std::string str_e = "<a href=";

			auto beg = code.find(str_b, tag);
			if (beg == npos || beg > stop) break;

			auto target = code.find(str_t, beg);
			auto end = code.find(str_e, beg + 1);
			if (target == npos || end == npos) break;

			tag = end;
			if (target > end) continue;

			std::string temp = code.substr(beg, end - beg);

			str_b = "href=\"";
			str_e = "target";

			beg = temp.find(str_b);
			end = temp.find(str_e, beg);
			if (beg == npos || end == npos) break;
			it.url = temp.substr(beg + str_b.size(), end - 2 - (beg + str_b.size()));

			str_b = "alt=";
			str_e = ">";

			beg = temp.find(str_b, end);
			end = temp.find(str_e, beg);
			if (beg == npos || end == npos) break;
			it.name = temp.substr(beg + str_b.size() + 1, end - 1 - (beg + str_b.size() + 1));

			if (it.name.size() && it.url.size() && it.url.find(".html") != npos)
			{
				g_items.push_back(it);

				static int index = 0;
				std::string show = std::to_string(index++) + std::string{ " - " } + it.name + std::string{ " - " } + it.url + std::string{ " \r\n " };
				show += std::move(g_initialize_item);
				g_initialize_item = std::move(show);
				SetWindowTextA(g_hwnd, g_initialize_item.c_str());
			}
		}

		tag = code.find("下一页");
		if (tag == std::string::npos) break;
	}

	for (int i = 0; i < 4; i++) _beginthread(download_thread, 0, 0);
}

void start_work(HWND h, std::string url, std::string path)
{
	if (h == 0 || url.empty() || path.empty()) return;

	g_hwnd = h;
	g_url = url;
	g_path = path;

	_beginthread(initialize_thread, 0, 0);
}