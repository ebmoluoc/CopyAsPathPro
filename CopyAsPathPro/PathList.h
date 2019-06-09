#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

class PathList : public hlp::DropFilesList
{
public:
	// Returns all the paths or an empty container if there is no data loaded.
	std::vector<std::wstring> GetUnquotedPaths();

	// Returns all the paths in quotation marks or an empty container if there is no data loaded.
	std::vector<std::wstring> GetQuotedPaths();

	// Returns all the paths in quotation marks if spaces found or an empty container if there is
	// no data loaded.
	std::vector<std::wstring> GetSpaceQuotedPaths();

	// Returns all the short paths or an empty container if there is no data loaded. Short paths
	// are not always available and for that reason you can't be sure that all returned paths will
	// be in a 8.3 format. Also, because this function calls Windows APIs, processing a large
	// selection may take longer than other functions in this class.
	std::vector<std::wstring> GetShortPaths();

	// Returns all the paths (C-style backslash escaped) or an empty container if there is no
	// data loaded.
	std::vector<std::wstring> GetCstyleUnquotedPaths();

	// Returns all the paths in quotation marks (C-style backslash escaped) or an empty container
	// if there is no data loaded.
	std::vector<std::wstring> GetCstyleQuotedPaths();
};
