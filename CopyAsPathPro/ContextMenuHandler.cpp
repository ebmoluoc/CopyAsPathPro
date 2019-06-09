#include "pch.h"
#include "ContextMenuHandler.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

ContextMenuHandler::ContextMenuHandler(Dll& dll) : dll_{ dll }, refCount_{ 1 }, hBitmapMenu_{ nullptr }
{
	dll_.AddRef();

	hBitmapMenu_ = hlp::BitmapFromIconResource(dll_.Handle(), IDI_ICON_MENU, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

ContextMenuHandler::~ContextMenuHandler()
{
	if (hBitmapMenu_ != nullptr)
	{
		DeleteObject(hBitmapMenu_);
	}

	dll_.Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
	if (ppvObject == nullptr)
	{
		return E_POINTER;
	}
	else if (IsEqualIID(riid, IID_IContextMenu))
	{
		*ppvObject = static_cast<LPCONTEXTMENU>(this);
	}
	else if (IsEqualIID(riid, IID_IShellExtInit))
	{
		*ppvObject = static_cast<LPSHELLEXTINIT>(this);
	}
	else
	{
		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}

	this->AddRef();

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP_(ULONG) ContextMenuHandler::AddRef()
{
	return ++refCount_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP_(ULONG) ContextMenuHandler::Release()
{
	auto rc{ --refCount_ };
	if (rc == 0)
	{
		delete this;
	}
	return rc;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::Initialize(PCIDLIST_ABSOLUTE pidlFolder, LPDATAOBJECT pdtobj, HKEY hkeyProgID)
{
	UNREFERENCED_PARAMETER(pidlFolder);
	UNREFERENCED_PARAMETER(hkeyProgID);

	if (pdtobj == nullptr)
	{
		return E_INVALIDARG;
	}

	return pathList_.Load(pdtobj) ? S_OK : E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	UNREFERENCED_PARAMETER(idCmdLast);

	if ((uFlags & CMF_DEFAULTONLY) != 0)
	{
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
	}

	auto hSubmenu{ CreatePopupMenu() };
	if (hSubmenu == nullptr)
	{
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
	}

	auto idCmd{ idCmdFirst };
	auto hModule{ dll_.Handle() };
	auto submenuUnquoted{ hlp::LoadStringResource(hModule, IDS_SUBMENU_UNQUOTED) };
	auto submenuQuoted{ hlp::LoadStringResource(hModule, IDS_SUBMENU_QUOTED) };
	auto submenuSpaceQuoted{ hlp::LoadStringResource(hModule, IDS_SUBMENU_SPACE_QUOTED) };
	auto submenuShortPath{ hlp::LoadStringResource(hModule, IDS_SUBMENU_SHORT_PATH) };
	auto submenuCstyleUnquoted{ hlp::LoadStringResource(hModule, IDS_SUBMENU_CSTYLE_UNQUOTED) };
	auto submenuCstyleQuoted{ hlp::LoadStringResource(hModule, IDS_SUBMENU_CSTYLE_QUOTED) };
	auto menuItem{ hlp::LoadStringResource(hModule, IDS_MENU_ITEM) };

	if (!hlp::AddMenuItem(hSubmenu, SUBMENU_UNQUOTED, submenuUnquoted.c_str(), idCmd++, nullptr, hBitmapMenu_) ||
		!hlp::AddMenuItem(hSubmenu, SUBMENU_QUOTED, submenuQuoted.c_str(), idCmd++, nullptr, hBitmapMenu_) ||
		!hlp::AddMenuItem(hSubmenu, SUBMENU_SPACE_QUOTED, submenuSpaceQuoted.c_str(), idCmd++, nullptr, hBitmapMenu_) ||
		!hlp::AddMenuItem(hSubmenu, SUBMENU_SHORT_PATH, submenuShortPath.c_str(), idCmd++, nullptr, hBitmapMenu_) ||
		!hlp::AddMenuItem(hSubmenu, SUBMENU_SEPARATOR_1, nullptr, idCmd++, nullptr, nullptr) ||
		!hlp::AddMenuItem(hSubmenu, SUBMENU_CSTYLE_UNQUOTED, submenuCstyleUnquoted.c_str(), idCmd++, nullptr, hBitmapMenu_) ||
		!hlp::AddMenuItem(hSubmenu, SUBMENU_CSTYLE_QUOTED, submenuCstyleQuoted.c_str(), idCmd++, nullptr, hBitmapMenu_) ||
		!hlp::AddMenuItem(hmenu, indexMenu, menuItem.c_str(), idCmd++, hSubmenu, hBitmapMenu_))
	{
		DestroyMenu(hSubmenu);
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
	}

	return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, idCmd - idCmdFirst);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::InvokeCommand(LPCMINVOKECOMMANDINFO pici)
{
	if (HIWORD(pici->lpVerb) != 0)
	{
		return E_FAIL;
	}

	std::vector<std::wstring> paths;

	switch (LOWORD(pici->lpVerb))
	{
	case SUBMENU_UNQUOTED:
		paths = pathList_.GetUnquotedPaths();
		break;
	case SUBMENU_QUOTED:
		paths = pathList_.GetQuotedPaths();
		break;
	case SUBMENU_SPACE_QUOTED:
		paths = pathList_.GetSpaceQuotedPaths();
		break;
	case SUBMENU_SHORT_PATH:
		paths = pathList_.GetShortPaths();
		break;
	case SUBMENU_CSTYLE_UNQUOTED:
		paths = pathList_.GetCstyleUnquotedPaths();
		break;
	case SUBMENU_CSTYLE_QUOTED:
		paths = pathList_.GetCstyleQuotedPaths();
		break;
	default:
		return E_FAIL;
	}

	auto buffer{ hlp::JoinStrings(paths, L"\n", MAX_PATH) };

	return hlp::CopyToClipboard(pici->hwnd, buffer) ? S_OK : E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP ContextMenuHandler::GetCommandString(UINT_PTR idCmd, UINT uType, UINT* pReserved, LPSTR pszName, UINT cchMax)
{
	UNREFERENCED_PARAMETER(idCmd);
	UNREFERENCED_PARAMETER(uType);
	UNREFERENCED_PARAMETER(pReserved);
	UNREFERENCED_PARAMETER(pszName);
	UNREFERENCED_PARAMETER(cchMax);

	return E_NOTIMPL;
}
