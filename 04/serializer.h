#pragma once

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = '\n';
public:
    explicit Serializer(std::ostream& out)
        : out_(out) {}

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args) {
        return process(args...);
    }
    
private:
	std::ostream& out_;

	template <class T>
	Error process(T t) {
		return load(t);
	}

	template <class T, class... Args>
	Error process(T t, Args... args) {
		process(args...);
		return load(t);
	}

	Error load(uint64_t n) {
		out_ << n << Separator;

		return Error::NoError;
	}

	Error load(bool n) {
		out_ << (n ? "true" : "false") << Separator;

		return Error::NoError;
	}
};

class Deserializer
{
public:
    explicit Deserializer(std::istream& in)
        : in_(in) {}

    template <class T>
    Error load(T& object) {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args) {
        return process(args...);
    }
    
private:
	std::istream& in_;

	template <class T>
	Error process(T& t) {
		return save(t);
	}

	template <class T, class... Args>
	Error process(T& t, Args&... args) {
		process(args...);
		return save(t);
	}

	Error save(uint64_t& n) {
		in_ >> n;

		return Error::NoError;
	}

	Error save(bool& n) {
		std::string text;
		in_ >> text;

		if (text == "true")
        	n = true;
	    else if (text == "false")
	        n = false;

	    return Error::NoError;
	}
};