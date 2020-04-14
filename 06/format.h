template <class T>
static void process(int depth, std::vector <std::pair <int, std::string>>&args, T&& t) {
	std::stringstream stream;
	stream << t;

	std::string arg = stream.str();
	for (auto &i : args) {
		if (i.first > depth)
			throw std::runtime_error("invalid argument index");
		else if (i.first == depth)
			i.second = arg;
	}
}

template <class T, class... ArgvT>
static void process(int depth, std::vector <std::pair <int, std::string>>& args, T&& t, ArgvT&&... argv) {
	std::stringstream stream;
	stream << t;

	std::string arg = stream.str();
	for (auto &i : args)
		if (i.first == depth)
			i.second = arg;

	process(++depth, args, std::forward<ArgvT>(argv)...);
}

static bool is_size_t(const std::string& str) {
	for (auto i : str)
		if (i < '0' || i > '9')
			return false;
	return true;
}

template <class... ArgvT>
std::string format(const std::string& f, ArgvT&&... argv) {
	std::vector <std::pair <int, std::string>> args;

	for (int i = 0; i < f.size(); ++i) {
		if (f[i] == '{') {
			int j = i + 1;
			for (; j < f.size(); ++j)
				if (f[j] == '}')
					break;

			if (j == f.size())
				throw std::runtime_error("invalid brackets use");

			std::string number = f.substr(i + 1, j - i - 1);
			if (is_size_t(number))
				args.push_back(std::make_pair(std::stoi(number), ""));
		}
	}

	process(0, args, std::forward<ArgvT>(argv)...);

	std::string res = "";
	int ind = 0;
	for (int i = 0; i < f.size(); ++i) {
		if (f[i] == '{') {
			while (f[i] != '}')
				++i;

			res += args[ind++].second;
		}
		else
			res += f[i];
	}

	return res;
}