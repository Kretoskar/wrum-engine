#include "PCH.h"
#include "WrumCore/ResourceHandling/File.h"

namespace Wrum
{
    File::File(const char* path, bool lookInResFolder, ArenaAllocator* allocator)
    {
        std::string pathStr = lookInResFolder ? GetPathInRes(path) : path;

        _path = pathStr;

        std::ifstream file(pathStr);

        if (file.good())
        {
            if (allocator)
            {
                bSelfAllocated = false;
                _fileContents = ArenaAllocator::New<std::string>(*allocator,
                    (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            }
            else
            {
                bSelfAllocated = true;
                _fileContents = new std::string((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
            }
            
            _isValid = true;
        }
        else
        {
            _fileContents = new std::string("");
            _isValid = false;
        }
    }

    File::~File()
    {
        if (bSelfAllocated)
        {
            delete _fileContents;
        }
    }

    const std::vector<std::string>& File::GetLines()
    {
        if (!_fileContents)
        {
            return _lines;
        }

        if (_lines.empty())
        {
            std::string line;

            for (size_t i = 0; i < _fileContents->length(); ++i) 
            {
                if (_fileContents->at(i) == '\n') 
                {
                    _lines.push_back(line);
                    line.clear();
                }
                else 
                {
                    line += _fileContents->at(i);
                }
            }

            // Add the last line if there's no newline at the end of the string
            if (!line.empty()) 
            {
                _lines.push_back(line);
            }
        }

        return _lines;
    }

    void File::OverrideContent(const std::string& newContent) const
    {
        std::ofstream file;

        file.open(_path, std::ofstream::out | std::ofstream::trunc);
        if (file.good())
        {
            file << newContent;
        }
    }

    std::string File::GetFileName(const std::string& path)
    {
        std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
        std::string::size_type const p(base_filename.find_last_of('.'));
        return base_filename.substr(0, p);
    }

    std::string File::GetFileExtension(const std::string& path)
    {
        return path.substr(path.find_last_of(".") + 1);
    }

    std::string File::GetFileNameAndExtension(const std::string& path)
    {
        return path.substr(path.find_last_of("/\\") + 1);
    }
}
