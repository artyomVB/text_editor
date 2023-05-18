#include "fsprocessor.h"

FSProcessor::FSProcessor(const std::string& s) : path(s) {}

std::vector<std::string> FSProcessor::get_files() {
	std::vector<std::string> ans;
	DIR * dir;
	struct dirent * sd;
	dir = opendir(path.c_str());
	while ((sd = readdir(dir)) != NULL) {
		if (sd->d_type == DT_DIR) {
			continue;
		} 
		ans.push_back(std::string(sd->d_name));
	}
	return ans;
}

void FSProcessor::save_file(const std::string& name, const char* text, size_t n) {	
	std::string full_path = path + "/" + name;
	int fd = open(full_path.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	write(fd, text, n);
	close(fd);	
}

std::unique_ptr<char[]> FSProcessor::read_file(const std::string& name) {
	std::string full_path = path + "/" + name;
	int fd = open(full_path.c_str(), O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	struct stat st;
	fstat(fd, &st);	
	size_t n = static_cast<size_t>(st.st_size);
	std::unique_ptr<char[]> buf(new char[n + 1]);
	read(fd, buf.get(), n);
	buf[n] = 0;
	close(fd);
	return buf;	
}



