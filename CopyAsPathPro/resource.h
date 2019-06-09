#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#define VER_N(major,minor,build,revision) major,minor,build,revision

#define VER_A_(v) #v
#define VER_A(major,minor,build,revision) VER_A_(major.minor.build.revision)

#define WSTR_(sa) L##sa
#define WSTR(sa) WSTR_(sa)

///////////////////////////////////////////////////////////////////////////////////////////////////

#define VERSION_MAJOR					1
#define VERSION_MINOR					1
#define VERSION_BUILD					0
#define VERSION_REVISION				0

///////////////////////////////////////////////////////////////////////////////////////////////////

#define IDI_ICON_MENU					100
#define ICON_MENU_NAME_A				"path.ico"

///////////////////////////////////////////////////////////////////////////////////////////////////

#define SUBMENU_UNQUOTED				0
#define SUBMENU_QUOTED					1
#define SUBMENU_SPACE_QUOTED			2
#define SUBMENU_SHORT_PATH				3
#define SUBMENU_SEPARATOR_1				4
#define SUBMENU_CSTYLE_UNQUOTED			5
#define SUBMENU_CSTYLE_QUOTED			6
#define MENU_ITEM						7

#define IDS_SUBMENU_UNQUOTED			200 + SUBMENU_UNQUOTED
#define IDS_SUBMENU_QUOTED				200 + SUBMENU_QUOTED
#define IDS_SUBMENU_SPACE_QUOTED		200 + SUBMENU_SPACE_QUOTED
#define IDS_SUBMENU_SHORT_PATH			200 + SUBMENU_SHORT_PATH
#define IDS_SUBMENU_CSTYLE_UNQUOTED		200 + SUBMENU_CSTYLE_UNQUOTED
#define IDS_SUBMENU_CSTYLE_QUOTED		200 + SUBMENU_CSTYLE_QUOTED
#define IDS_MENU_ITEM					200 + MENU_ITEM

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_NAME_A					"CopyAsPath Pro"
#define PRODUCT_NAME_W					WSTR(PRODUCT_NAME_A)

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_DESCRIPTION_A			"CopyAsPath Pro Shell Extension"

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_COPYRIGHT_A				"Copyright (c) 2019 Philippe Coulombe"

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_HKCR_W					L"AllFilesystemObjects"

///////////////////////////////////////////////////////////////////////////////////////////////////

#define PRODUCT_CLSID_W					L"{C3705C3C-9834-41D7-82AA-E3D9A7951EFE}"
