#include "pch.h"
#include "PathList.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

static const WCHAR QUOTE{ '\"' };
static const WCHAR SPACE{ ' ' };

///////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::wstring> PathList::GetUnquotedPaths()
{
	std::vector<std::wstring> paths{};

	if (pList_ != nullptr)
	{
		auto p{ pList_ };

		while (*p)
		{
			paths.push_back(std::wstring{ p });
			p += wcslen(p) + 1;
		}
	}

	return paths;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::wstring> PathList::GetQuotedPaths()
{
	std::vector<std::wstring> paths{};

	if (pList_ != nullptr)
	{
		auto p{ pList_ };

		while (*p)
		{
			paths.push_back(QUOTE + std::wstring(p) + QUOTE);
			p += wcslen(p) + 1;
		}
	}

	return paths;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::wstring> PathList::GetSpaceQuotedPaths()
{
	std::vector<std::wstring> paths{};

	if (pList_ != nullptr)
	{
		auto p{ pList_ };

		while (*p)
		{
			auto path{ std::wstring{ p } };
			if (path.find(SPACE) != path.npos)
			{
				paths.push_back(QUOTE + path + QUOTE);
			}
			else
			{
				paths.push_back(path);
			}
			p += wcslen(p) + 1;
		}
	}

	return paths;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::wstring> PathList::GetShortPaths()
{
	std::vector<std::wstring> paths{};

	if (pList_ != nullptr)
	{
		auto p{ pList_ };

		while (*p)
		{
			WCHAR path[MAX_PATH];
			auto length{ GetShortPathNameW(p, path, _countof(path)) };
			if (length > 0 && length < _countof(path))
			{
				paths.push_back(std::wstring{ path });
				p += wcslen(p) + 1;
			}
			else
			{
				paths.clear();
				break;
			}
		}
	}

	return paths;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::wstring> PathList::GetCstyleUnquotedPaths()
{
	std::vector<std::wstring> paths{};

	if (pList_ != nullptr)
	{
		auto p{ pList_ };

		while (*p)
		{
			paths.push_back(hlp::EscapeBackslash(std::wstring{ p }));
			p += wcslen(p) + 1;
		}
	}

	return paths;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::wstring> PathList::GetCstyleQuotedPaths()
{
	std::vector<std::wstring> paths{};

	if (pList_ != nullptr)
	{
		auto p{ pList_ };

		while (*p)
		{
			paths.push_back(QUOTE + hlp::EscapeBackslash(std::wstring{ p }) + QUOTE);
			p += wcslen(p) + 1;
		}
	}

	return paths;
}
