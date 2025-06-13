#include "../include/objParser.hpp"
#include <fstream>
#include <string>
#include <iostream>

namespace rast {
    std::vector<std::string> splitByLine(std::fstream& file) {
        std::vector<std::string> result;
        std::string buff;

        for (char c; c = file.get(); ) {
            if (c == '\n') {
                result.push_back(buff);
                buff.clear();
            } else {
                buff.append(1, c);
            }
            if (c == EOF) {
                break;
            }
        }

        return result;
    }

    auto split(const std::string &str, const std::string &delimiter) {
        std::vector<std::string> result;
        std::string buff;

        for (int i = 0; i < str.size(); i++) {
            if (str[i] == delimiter[0] || i == str.size() - 1) {
                if (buff.empty()) {
                    continue;
                }

                result.push_back(buff);
                buff.clear();
            } else {
                buff.append(1, str[i]);
            }
        }

        return result;
    }

    auto to_float(const std::vector<std::string> &input) {
        std::vector<float> result;

        for (const auto & i : input) {
            result.push_back(atof(i.c_str()));
        }

        return result;
    }

    auto to_int(const std::vector<std::string> &input) {
        std::vector<int> result;

        for (const auto & i : input) {
            result.push_back(atoi(i.c_str()));
        }

        return result;
    }

    std::vector<float3> loadObjectFile(const std::string &filename) {
        std::vector<float3> allPoints;
        std::vector<float3> trianglePoints;

        std::fstream f;
        f.open(filename, std::ios::in);

        for (auto lines = splitByLine(f); auto & line : lines) {
            if (line.starts_with("v ")) {
                line.replace(line.find("v "), 2, "");
                std::vector<float> axes = to_float(split(line, " "));
                allPoints.push_back(float3(axes[0], axes[1], axes[2]));
            } else if (line.starts_with("f ")) {
                line.replace(line.find("f "), 2, "");
                std::vector<std::string> faceIndexGroups = split(line, " ");

                for (int j = 0; j < faceIndexGroups.size(); j++) {
                    std::vector<int> indexGroup = to_int(split(faceIndexGroups[j], "/"));
                    const int pointIndex = indexGroup[0] - 1;
                    if (j >= 3) trianglePoints.push_back(trianglePoints[trianglePoints.size() - (3 * j - 6)]);
                    if (j >= 3) trianglePoints.push_back(trianglePoints[trianglePoints.size() - 2]);
                    trianglePoints.push_back(allPoints[pointIndex]);
                }
            }
        }
        return trianglePoints;
    }
}
