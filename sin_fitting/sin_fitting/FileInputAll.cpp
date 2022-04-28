#include "FileInputAll.h"

FileInputAll::FileInputAll(std::string _folderPath)
{

}

std::vector<std::string> FileInputAll::getFileNames(std::string folderPath)
{
	using namespace std::filesystem;
	directory_iterator iter(folderPath), end;
	std::error_code err;
	std::vector<std::string> fileNames;

	for (; iter != end && !err; iter.increment(err)) {
		const directory_entry entry = *iter;

		fileNames.push_back(entry.path().string());
		printf("%s\n", fileNames.back().c_str());
	}

	/* ƒGƒ‰[ˆ— */
	if (err) {
		std::cout << err.value() << std::endl;
		std::cout << err.message() << std::endl;
		exit(EXIT_FAILURE);
	}
	return fileNames;
}
