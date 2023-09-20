#include "GetFolderFiles.h"

GetFolderFiles::GetFolderFiles(std::string _folderPath)
{
	if (!getFileNames(_folderPath))
		exit(EXIT_FAILURE);
}

bool GetFolderFiles::getFileNames(std::string folderPath)
{
	using namespace std::filesystem;
	std::error_code err;
	directory_iterator iter(folderPath, err), end;

	for (const directory_entry& entry : recursive_directory_iterator(folderPath, err))
	{
		//const directory_entry entry = *iter;
		std::filesystem::path filePath = entry.path().string();
		if (filePath.extension() == ".csv" || filePath.extension() == ".CSV")
			fileList.push_back(entry.path().string());
#ifdef DEBUG
		std::cout << fileList.back() << std::endl;
#endif // DEBUG
	}

	/*for (; iter != end && !err; iter.increment(err)) {
		const directory_entry entry = *iter;
		std::filesystem::path filePath = entry.path().string();
		if (filePath.extension() == ".csv" || filePath.extension() == ".CSV")
			fileList.push_back(entry.path().string());
#ifdef DEBUG
		std::cout << fileList.back() << std::endl;
#endif // DEBUG
	}*/

	/* ƒGƒ‰[ˆ— */
	if (err) {
		std::cout << err.value() << std::endl;
		std::cout << err.message() << std::endl;
		return false;
	}
	return true;
}
