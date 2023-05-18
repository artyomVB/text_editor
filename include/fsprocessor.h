#pragma once
#include <memory>
#include <vector>
#include <string>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

class FSProcessor {
private:
	std::string path;

public:
	FSProcessor(const std::string&);

	std::vector<std::string> get_files();

	void save_file(const std::string&, const char*, size_t);

	std::unique_ptr<char[]> read_file(const std::string& name);
};


